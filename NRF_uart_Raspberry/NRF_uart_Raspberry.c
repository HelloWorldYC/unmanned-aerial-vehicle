//arm_startup_nrf51.s是启动文件，包含中断定义
//#include "nrf51.h"//包含51822各个寄存器结构地址。以上2文件就可以控制51822了。
//nrf51_bitfields.h包含各个寄存器设置值的作用
#include "project_nrf51822.c"//包含51822工程需要用到的头文件（晶振，延时，io脚什么的

#include <stdbool.h>//调用bool
#include "stdio.h"//标准输入输出
#include <stdint.h>//声明已知大小的整数或显示特征的整数


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
    gpio_init_out(19,22);//led:red,green,blue
	
  	gpio_init_out(0,7);//设置0~15脚配置为输出
//	  gpio_init_in(16,17,3);//设置16~17脚配置为输入（开发板为按钮key0，key1）
//  	gpio_init_out(18,25);//设置18~25脚配置为输出/那个26~27接的是低速晶振
//    gpio_init_out(28,31);//设置28~31脚配置为输出
}


static uint8_t Receive_packet[5];  				//接收地面发送的数据
uint8_t voltage_collect_information[3]; 	//要通过串口发送给树莓派的电压信息收集的数据
uint8_t i=0;


void Receive_NRFdata()
{
				NRF_RADIO->EVENTS_READY = 0U; //收发模式转换完成  标志位       
        NRF_RADIO->TASKS_RXEN   = 1U; //接收模式
        while(NRF_RADIO->EVENTS_READY == 0U) //等待收发模式转换完成(接收模式)标志位
          {
            // Do nothing.等待
          }
        NRF_RADIO->EVENTS_END  = 0U;//传输完成  标志位     
        NRF_RADIO->TASKS_START = 1U; // 开始传输

        while(NRF_RADIO->EVENTS_END == 0U)//等待传输完成  标志位
           {
           //  nrf_gpio_pin_set(22);// blue灭  //传输不成功
						 // Do nothing.等待
           }
        if (NRF_RADIO->CRCSTATUS == 1U)//如果CRC校验正确
        {
					
            //nrf_gpio_port_write(NRF_GPIO_PORT_SELECT_PORT1, packet[0]);
					if(Receive_packet[0]== ('Q'))//确定开始
					   {
              if(Receive_packet[4]== ('R'))//结束正确
                {  
									nrf_gpio_pin_set(21);// blue亮，数据成功了，灯越暗说明数据传输越快。
									                       //不亮说明,数据传输失败。
                }
								else
								{
									
									NRF_RADIO->EVENTS_DISABLED = 0U;//无线关闭   标志位
									return;
								}
             }
						 else
						 {
							 NRF_RADIO->EVENTS_DISABLED = 0U;//无线关闭   标志位
							 return;
						 }
        }
        NRF_RADIO->EVENTS_DISABLED = 0U;//无线关闭   标志位
				NRF_RADIO->TASKS_DISABLE   = 1U;// 关闭无线设备 
        while(NRF_RADIO->EVENTS_DISABLED == 0U)//等待设备关闭
        {
            // Do nothing.
        }
}

//将发送到树莓派的变量缓冲区清零
void voltage_collect_information_clear()
{
			for(i=0; i<3; i++)
			{
				voltage_collect_information[i] = 0;
			}
}

//将接收到的数据传给要发送到树莓派的变量缓冲区
void Get_voltage_collect_information()
{
			for(i=0; i<3; i++)
			{
				voltage_collect_information[i] = Receive_packet[i+1];
			}
}

	int main(void)//main主程序开始
{

		init();						//时钟初始化
    ioinit();					//引脚初始化
		radio_configure();//无线电配置（也可用于和nrf2401通讯）
    NRF_RADIO->PACKETPTR  = (uint32_t)Receive_packet;					//指针指向数据缓冲packet
	  simple_uart_config(RTS_PIN_NUMBER,TX_PIN_NUMBER,CTS_PIN_NUMBER,RX_PIN_NUMBER,HWFC); /*UART初始化，宏定义中分别设置RTS为8，     
                                                                 TX为9，CTS为10，RX为11，HWFC为false  */
		voltage_collect_information_clear();										 //清零发送给树莓派的变量缓冲区
	  while(1)
    {

						nrf_gpio_pin_set(19); 
						nrf_delay_ms(300);
						Receive_NRFdata();															 //接收地面NRF板传来的信息
						nrf_gpio_pin_set(20); 
						Get_voltage_collect_information();							 //对地面NRF板传来的信息进行处理得到电压收集数据
						simple_uart_put(voltage_collect_information[0]); //将电压收集数据通过串口传给树莓派
						simple_uart_put(voltage_collect_information[1]);
						simple_uart_put(voltage_collect_information[2]);
						nrf_gpio_pin_clear(19);
						nrf_delay_ms(300);
						voltage_collect_information_clear();						 //清零发送给树莓派的变量缓冲区
						nrf_gpio_pin_clear(21);

			}  
}

