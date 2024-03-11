#include "DS18b20.h"
#include "nrf_gpio.h"

//DS18b20��ʼ��
void init_1820(void)  
{
		gpio_init_out(5,9);  //����5-9��Ϊ�����
    nrf_gpio_pin_set(9);    //��9�ŵ�ƽ��Ϊ�ߵ�ƽ    
    nrf_gpio_pin_clear(9);  //��9�ŵ�ƽ��Ϊ�͵�ƽ
    nrf_delay_us(750);       //��ʱ1ms
    nrf_gpio_pin_set(9);   //��9�ŵ�ƽ����       
    gpio_init_in(5,9,3);    //��5-9����Ϊ��������      
     nrf_delay_us(20);       //��ʱ30us
    while((NRF_GPIO->IN >>9));  //9������Ϊ0ʱ����ѭ��
    gpio_init_out(5,9);  //��������5-9��Ϊ���
    nrf_gpio_pin_set(9);  //��������9�ŵ�ƽ
    nrf_delay_us(140);      //��ʱ140us
}

//��18b20д1B������
void write_1820(unsigned char data)  
{
		gpio_init_out(5,9);  //��5-9����Ϊ���
    unsigned char i;  
    for(i=0;i<8;i++)    //�ӵ͵�������д����
    {  
       nrf_gpio_pin_clear(9);  //��9�ŵ�ƽ��Ϊ�͵�ƽ
				nrf_delay_us(15);      //��ʱ15us
       if(data&(1<<i))    
       	 nrf_gpio_pin_set(9);    //��9�ŵ�ƽ��Ϊ�ߵ�ƽ  
       else  
         nrf_gpio_pin_clear(9);  //��9�ŵ�ƽ��Ϊ�͵�ƽ
       nrf_delay_us(40);      //��ʱ40us  
      nrf_gpio_pin_set(9);    //��9�ŵ�ƽ��Ϊ�ߵ�ƽ 
    }  
    nrf_gpio_pin_set(9);    //��9�ŵ�ƽ��Ϊ�ߵ�ƽ 
}

//��18b20����1B������
unsigned char read_1820(void)  
{      
    unsigned char temp,k,n;  
    temp=0;  
    for(n=0;n<8;n++)  
    {
      nrf_gpio_pin_clear(9);  //��9�ŵ�ƽ��Ϊ�͵�ƽ
      nrf_gpio_pin_set(9);    //��9�ŵ�ƽ��Ϊ�ߵ�ƽ 
      gpio_init_in(5,9,3);       //��Ϊ����
      k=(NRF_GPIO->IN >>9);       
      if(k)                     //�����ݣ��ӵ�λ��ʼ
        temp|=(1<<n);  
      else  
        temp&=~(1<<n);  
      nrf_delay_us(60);        //��ʱ60-120us 
     gpio_init_out(5,9);  //��5-9����Ϊ���
    }  
   return (temp);  
}

//��ȡ�¶�
unsigned char gettemp(void)         
{  
     unsigned char temh,teml,wm0,wm1,wm2,wm3,wmh,wml,temp; 
     init_1820();         //��ʼ��18b20
     write_1820(0xCC);   //����ROM
     write_1820(0x44);  //�¶ȱ任

     init_1820();
     write_1820(0xCC);    //����ROM
     write_1820(0xbe);    //д�ݴ�洢��
     teml=read_1820();     //������
     temh=read_1820();  
     wm0=teml>>4;       //ֻҪ��8λ�ĵ���λ�͵�8λ�ĸ���λ���¶ȷ�ΧΪ0~99
     wm1=temh<<4;
	
     wm2=wm1+wm0;       //16����ת10����
     wm3=wm2/100; 
     wmh=(wm2%100)/10;   //wmh����ʾ�ĸ�λ��wml����ʾ�ĵ�λ
     wml=(wm2%100)%10;
	 temp=wmh*10+wml;
	 
	 return temp;
}