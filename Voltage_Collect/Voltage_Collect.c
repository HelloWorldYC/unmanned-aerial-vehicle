#include "project_nrf51822.c"//包含51822工程需要用到的头文件（晶振，延时，io脚什么的
#include "pca1000x.h"
#include "ADC.h"

#include <stdbool.h>//调用bool
#include "stdio.h"//标准输入输出
#include <stdint.h>//声明已知大小的整数或显示特征的整数


static uint8_t volatile Send_packet[5] = {'Q','S','D','F','R'};  //要发送出去的数据缓冲区
uint16_t Voltage_data;		//ADC采集的电压数据
uint8_t i=0;

void init(void)//51822时钟初始化
{ 
	 //判断电源时钟状态
	 if ((((*(uint32_t *)0xF0000FE0) & 0xFF) == 1) && (((*(uint32_t *)0xF0000FE4) & 0xF) == 0))
    {
        if ((((*(uint32_t *)0xF0000FE8) & 0xF0) == 0x0) && (((*(uint32_t *)0xF0000FEC) & 0xF0) == 0x0))
        {
					//解决radio无法写入  
          *(uint32_t *)0x40000504 = 0xC007FFDF;//电源时钟设置
          *(uint32_t *)0x40006C18 = 0x00008000;//GPIOTE设置    
        }
				else if ((((*(uint32_t *)0xF0000FE8) & 0xF0) == 0x10) && (((*(uint32_t *)0xF0000FEC) & 0xF0) == 0x0))
        {
          //解决radio无法写入  
          *(uint32_t *)0x40000504 = 0xC007FFDF;//电源时钟设置
          *(uint32_t *)0x40006C18 = 0x00008000;//GPIOTE设置  
        }
        else if ((((*(uint32_t *)0xF0000FE8) & 0xF0) == 0x30) && (((*(uint32_t *)0xF0000FEC) & 0xF0) == 0x0))
        {
          //解决radio无法写入  
          *(uint32_t *)0x40000504 = 0xC007FFDF;//电源时钟设置
          *(uint32_t *)0x40006C18 = 0x00008000;//GPIOTE设置    
        }
    }
	NRF_CLOCK->EVENTS_HFCLKSTARTED = 0;//HFCLK晶振运行状态0关闭，1运行
  NRF_CLOCK->TASKS_HFCLKSTART = 1;//高外晶振HFCLK 0关闭，1启动
  while(!NRF_CLOCK->EVENTS_HFCLKSTARTED);//等待HFCLK晶振运行状态为1
}

void ioinit()//51822引脚初始化
{
    //接收用usb-jtag的nrf51822
//	  gpio_init_in(9,9,3);//p0.09输入
//	  gpio_init_in(11,11,3);//p0.11输入
//    gpio_init_out(21,23);//led:red,green,blue
	
			gpio_init_in(0,7,0);//设置0~7脚配置为输入
    	gpio_init_out(8,15);//设置8~15脚配置为输出
  	  gpio_init_in(16,17,3);//设置16~17脚配置为输入3代表上拉电阻（开发板为按钮key0，key1）
    	gpio_init_out(18,25);//设置18~25脚配置为输出/那个26~27接的是低速晶振
      gpio_init_out(28,31);//设置28~31脚配置为输出
}



void Send_NRFdata()
{
	  nrf_gpio_pin_clear(18);
		NRF_RADIO->PACKETPTR    = (uint32_t)Send_packet;//指针指向数据缓冲packet
		NRF_RADIO->EVENTS_READY = 0U;//收发模式转换完成标志位。复位
    NRF_RADIO->TASKS_TXEN = 1U;//启动无线电为发射模式
    while (NRF_RADIO->EVENTS_READY == 0U);//等待收发模式转换完成
    NRF_RADIO->EVENTS_END  = 0U;//传输完成标志位，复位     
		NRF_RADIO->TASKS_START = 1U;//开始传输
        while(NRF_RADIO->EVENTS_END == 0U) //等待传输完成
        {
					  nrf_gpio_pin_set(18);//传输失败led0灭
            // Do nothing.
        }

        // 组1引脚（8~15）
        //nrf_gpio_port_write(P0, ~Send_packet[0]);//数值显示在单片机P0口上 1000 1111
        nrf_gpio_pin_clear(18);//传输成功led0灭，越暗说明有干扰，需要改频率  输出高电平到pa.1

				NRF_RADIO->EVENTS_DISABLED = 0U;//无线关闭标志位  复位
				NRF_RADIO->TASKS_DISABLE   = 1U;// 关闭无线设备
        while(NRF_RADIO->EVENTS_DISABLED == 0U)//等待设备关闭
        {
            // Do nothing.
        }
}

int main(void)
{
	
	init();//时钟初始化
  ioinit();//引脚初始化
	simple_uart_config(RTS_PIN_NUMBER, TX_PIN_NUMBER, CTS_PIN_NUMBER, RX_PIN_NUMBER, HWFC);
	radio_configure();//无线电配置（也可用于和nrf2401通讯）
	Adc_Init(ADC_CONFIG_RES_10bit,ADC_CONFIG_PSEL_AnalogInput1);
	
  while(1)
  {	
				nrf_delay_ms(300);
				nrf_gpio_pin_toggle(LED_2);														//将LED2电平状态进行翻转
				nrf_delay_ms(300);
				Voltage_data = Get_Adc_Average(10); 									//读取ADC采集到的电压数据
				Send_packet[1] = (uint8_t)((Voltage_data&0xff00)>>8); //电压数据的高八位
			  Send_packet[2] = (uint8_t)(Voltage_data&0x00ff) ;			//电压数据的低八位
				Send_packet[3] = '1';																	//自定义的接收数据成功标志位，无人机收到该数据会飞往下一个目标点
				Send_NRFdata();																				//将数据发送出去

  }
	
}