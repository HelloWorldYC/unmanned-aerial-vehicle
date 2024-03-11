#include "DS18b20.h"
#include "nrf_gpio.h"

//DS18b20初始化
void init_1820(void)  
{
		gpio_init_out(5,9);  //设置5-9脚为输出；
    nrf_gpio_pin_set(9);    //将9脚电平设为高电平    
    nrf_gpio_pin_clear(9);  //将9脚电平设为低电平
    nrf_delay_us(750);       //延时1ms
    nrf_gpio_pin_set(9);   //将9脚电平拉高       
    gpio_init_in(5,9,3);    //将5-9脚设为输入上拉      
     nrf_delay_us(20);       //延时30us
    while((NRF_GPIO->IN >>9));  //9脚输入为0时跳出循环
    gpio_init_out(5,9);  //重新设置5-9脚为输出
    nrf_gpio_pin_set(9);  //重新拉高9脚电平
    nrf_delay_us(140);      //延时140us
}

//向18b20写1B的数据
void write_1820(unsigned char data)  
{
		gpio_init_out(5,9);  //将5-9脚设为输出
    unsigned char i;  
    for(i=0;i<8;i++)    //从低到高依次写数据
    {  
       nrf_gpio_pin_clear(9);  //将9脚电平设为低电平
				nrf_delay_us(15);      //延时15us
       if(data&(1<<i))    
       	 nrf_gpio_pin_set(9);    //将9脚电平设为高电平  
       else  
         nrf_gpio_pin_clear(9);  //将9脚电平设为低电平
       nrf_delay_us(40);      //延时40us  
      nrf_gpio_pin_set(9);    //将9脚电平设为高电平 
    }  
    nrf_gpio_pin_set(9);    //将9脚电平设为高电平 
}

//从18b20读出1B的数据
unsigned char read_1820(void)  
{      
    unsigned char temp,k,n;  
    temp=0;  
    for(n=0;n<8;n++)  
    {
      nrf_gpio_pin_clear(9);  //将9脚电平设为低电平
      nrf_gpio_pin_set(9);    //将9脚电平设为高电平 
      gpio_init_in(5,9,3);       //设为输入
      k=(NRF_GPIO->IN >>9);       
      if(k)                     //读数据，从低位开始
        temp|=(1<<n);  
      else  
        temp&=~(1<<n);  
      nrf_delay_us(60);        //延时60-120us 
     gpio_init_out(5,9);  //将5-9脚设为输出
    }  
   return (temp);  
}

//读取温度
unsigned char gettemp(void)         
{  
     unsigned char temh,teml,wm0,wm1,wm2,wm3,wmh,wml,temp; 
     init_1820();         //初始化18b20
     write_1820(0xCC);   //跳过ROM
     write_1820(0x44);  //温度变换

     init_1820();
     write_1820(0xCC);    //跳过ROM
     write_1820(0xbe);    //写暂存存储器
     teml=read_1820();     //读数据
     temh=read_1820();  
     wm0=teml>>4;       //只要高8位的低四位和低8位的高四位，温度范围为0~99
     wm1=temh<<4;
	
     wm2=wm1+wm0;       //16进制转10进制
     wm3=wm2/100; 
     wmh=(wm2%100)/10;   //wmh是显示的高位，wml是显示的低位
     wml=(wm2%100)%10;
	 temp=wmh*10+wml;
	 
	 return temp;
}