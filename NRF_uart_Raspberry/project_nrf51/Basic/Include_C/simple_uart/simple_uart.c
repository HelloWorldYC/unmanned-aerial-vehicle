/* Copyright (c) 2009 Nordic Semiconductor. All Rights Reserved.
 *
 * The information contained herein is property of Nordic Semiconductor ASA.
 * Terms and conditions of usage are described in detail in NORDIC
 * SEMICONDUCTOR STANDARD SOFTWARE LICENSE AGREEMENT.
 *
 * Licensees are granted free, non-transferable use of the information. NO
 * WARRANTY of ANY KIND is provided. This heading must NOT be removed from
 * the file.
 *
 */

#include <stdint.h>

#include "nrf.h"
#include "simple_uart.h"
#include "nrf_delay.h"
#include "nrf_gpio.h"


//UART接收一个字节数据
uint8_t simple_uart_get(void)
{
  while (NRF_UART0->EVENTS_RXDRDY != 1)	//等待接收数据结束
  {
    // Wait for RXD data to be received
  }
  
  NRF_UART0->EVENTS_RXDRDY = 0;		 //读取成功会有一个RXDRDY事件，读取结束后将其清零，以能够继续检测下一次数据的读取
  return (uint8_t)NRF_UART0->RXD;  //返回RXD寄存器的数据，读取接收到的数据
}

bool simple_uart_get_with_timeout(int32_t timeout_ms, uint8_t *rx_data)
{
  bool ret = true;
  
  while (NRF_UART0->EVENTS_RXDRDY != 1)
  {
    if (timeout_ms-- >= 0)
    {
      // wait in 1ms chunk before checking for status
      nrf_delay_us(1000);
    }
    else
    {
      ret = false;
      break;
    }
  }  // Wait for RXD data to be received

  if (timeout_ms >= 0)
  {
    // clear the event and set rx_data with received byte
      NRF_UART0->EVENTS_RXDRDY = 0;
      *rx_data = (uint8_t)NRF_UART0->RXD;
  }

  return ret;
}

//UART发送一个字节的数据
void simple_uart_put(uint8_t cr)
{
  NRF_UART0->TXD = (uint8_t)cr; //将发送的指针指向要发送的数据缓冲区，开始发送

  while (NRF_UART0->EVENTS_TXDRDY!=1) //等待数据发送结束
  {
    // Wait for TXD data to be sent
  }

  NRF_UART0->EVENTS_TXDRDY=0;	//数据发送结束会产生一个TXDRDY事件，将其清零以检测下一次的数据发送
}

void simple_uart_putstring(const uint8_t *str)
{
  uint_fast8_t i = 0;
  uint8_t ch = str[i++];
  while (ch != '\0')
  {
    simple_uart_put(ch);
    ch = str[i++];
  }
}

void simple_uart_config(  uint8_t rts_pin_number,    /*RTS:请求发送（输出），nrf51822通过RTS向外部设备发出请求发送信号，
	                                                          在收到外部设备的回应后开始发送数据，低电平有效 */
                          uint8_t txd_pin_number,    //TXD：数据发送信号线
                          uint8_t cts_pin_number,    /*CTS：发送允许（输入），外部设备向nrf51822发送允许信号，
                                                             nrf51822接受到此信号后开始发送数据，低电平有效*/
                          uint8_t rxd_pin_number,    //RXD：数据接收信号线
                          bool hwfc)       //硬件流控制，当为真时表示使能硬件流控制，即增加了CTS和RTS功能
{
  nrf_gpio_cfg_output(txd_pin_number);
  nrf_gpio_cfg_input(rxd_pin_number, NRF_GPIO_PIN_NOPULL);  

  NRF_UART0->PSELTXD = txd_pin_number;   //选择GPIO引脚作为发送引脚TXD
  NRF_UART0->PSELRXD = rxd_pin_number;   //选择GPIO引脚作为接受引脚RXD

  if (hwfc)			//开启流控，增加CTS和RTS引脚
  {
    nrf_gpio_cfg_output(rts_pin_number);
    nrf_gpio_cfg_input(cts_pin_number, NRF_GPIO_PIN_NOPULL);
    NRF_UART0->PSELCTS = cts_pin_number;   //选择GPIO引脚作为CTS
    NRF_UART0->PSELRTS = rts_pin_number;    //选择GPIO引脚作为RTS
    NRF_UART0->CONFIG  = (UART_CONFIG_HWFC_Enabled << UART_CONFIG_HWFC_Pos);
  }

  NRF_UART0->BAUDRATE         = (UART_BAUDRATE_BAUDRATE_Baud115200 << UART_BAUDRATE_BAUDRATE_Pos);  //对UART波特率进行设置
  NRF_UART0->ENABLE           = (UART_ENABLE_ENABLE_Enabled << UART_ENABLE_ENABLE_Pos);  	//使能UART
  NRF_UART0->TASKS_STARTTX    = 1;   //UART发送传输时序启动
  NRF_UART0->TASKS_STARTRX    = 1;	 //UART接收传输时序启动
  NRF_UART0->EVENTS_RXDRDY    = 0;	 //UART接收新字节成功标志位置零，接收成功将置位
}
