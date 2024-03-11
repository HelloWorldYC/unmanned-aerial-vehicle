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


//UART����һ���ֽ�����
uint8_t simple_uart_get(void)
{
  while (NRF_UART0->EVENTS_RXDRDY != 1)	//�ȴ��������ݽ���
  {
    // Wait for RXD data to be received
  }
  
  NRF_UART0->EVENTS_RXDRDY = 0;		 //��ȡ�ɹ�����һ��RXDRDY�¼�����ȡ�����������㣬���ܹ����������һ�����ݵĶ�ȡ
  return (uint8_t)NRF_UART0->RXD;  //����RXD�Ĵ��������ݣ���ȡ���յ�������
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

//UART����һ���ֽڵ�����
void simple_uart_put(uint8_t cr)
{
  NRF_UART0->TXD = (uint8_t)cr; //�����͵�ָ��ָ��Ҫ���͵����ݻ���������ʼ����

  while (NRF_UART0->EVENTS_TXDRDY!=1) //�ȴ����ݷ��ͽ���
  {
    // Wait for TXD data to be sent
  }

  NRF_UART0->EVENTS_TXDRDY=0;	//���ݷ��ͽ��������һ��TXDRDY�¼������������Լ����һ�ε����ݷ���
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

void simple_uart_config(  uint8_t rts_pin_number,    /*RTS:�����ͣ��������nrf51822ͨ��RTS���ⲿ�豸�����������źţ�
	                                                          ���յ��ⲿ�豸�Ļ�Ӧ��ʼ�������ݣ��͵�ƽ��Ч */
                          uint8_t txd_pin_number,    //TXD�����ݷ����ź���
                          uint8_t cts_pin_number,    /*CTS�������������룩���ⲿ�豸��nrf51822���������źţ�
                                                             nrf51822���ܵ����źź�ʼ�������ݣ��͵�ƽ��Ч*/
                          uint8_t rxd_pin_number,    //RXD�����ݽ����ź���
                          bool hwfc)       //Ӳ�������ƣ���Ϊ��ʱ��ʾʹ��Ӳ�������ƣ���������CTS��RTS����
{
  nrf_gpio_cfg_output(txd_pin_number);
  nrf_gpio_cfg_input(rxd_pin_number, NRF_GPIO_PIN_NOPULL);  

  NRF_UART0->PSELTXD = txd_pin_number;   //ѡ��GPIO������Ϊ��������TXD
  NRF_UART0->PSELRXD = rxd_pin_number;   //ѡ��GPIO������Ϊ��������RXD

  if (hwfc)			//�������أ�����CTS��RTS����
  {
    nrf_gpio_cfg_output(rts_pin_number);
    nrf_gpio_cfg_input(cts_pin_number, NRF_GPIO_PIN_NOPULL);
    NRF_UART0->PSELCTS = cts_pin_number;   //ѡ��GPIO������ΪCTS
    NRF_UART0->PSELRTS = rts_pin_number;    //ѡ��GPIO������ΪRTS
    NRF_UART0->CONFIG  = (UART_CONFIG_HWFC_Enabled << UART_CONFIG_HWFC_Pos);
  }

  NRF_UART0->BAUDRATE         = (UART_BAUDRATE_BAUDRATE_Baud115200 << UART_BAUDRATE_BAUDRATE_Pos);  //��UART�����ʽ�������
  NRF_UART0->ENABLE           = (UART_ENABLE_ENABLE_Enabled << UART_ENABLE_ENABLE_Pos);  	//ʹ��UART
  NRF_UART0->TASKS_STARTTX    = 1;   //UART���ʹ���ʱ������
  NRF_UART0->TASKS_STARTRX    = 1;	 //UART���մ���ʱ������
  NRF_UART0->EVENTS_RXDRDY    = 0;	 //UART�������ֽڳɹ���־λ���㣬���ճɹ�����λ
}
