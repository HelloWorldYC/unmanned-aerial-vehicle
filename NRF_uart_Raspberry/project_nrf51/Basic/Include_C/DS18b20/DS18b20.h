/*#ifndef __18b20_H__
#define __18b20_H__  1

#define TEM_PORT PORTF
#define TEM_DDR DDRF
#define TEM_PIN PINF

#define TEM_SDT 2
//nrf_gpio_pin_set();置位某一位引脚；
//nrf_gpio_pin_clear();复位某一位引脚；
#define SET_TEM_SDT (TEM_PORT|=(1<<TEM_SDT))  //输出高电平
#define CLR_TEM_SDT (TEM_PORT&=~(1<<TEM_SDT))  //输出低电平

#define SET_TEM_DDR (TEM_DDR|=(1<<TEM_SDT))  //置为输出
#define CLR_TEM_DDR (TEM_DDR&=~(1<<TEM_SDT))  //置为输入

#define CHECK_TEM_SDT (TEM_PIN&(1<<TEM_SDT))  //输入的电平值为真*/

extern void init_1820(void);
extern void write_1820(unsigned char data);
extern unsigned char read_1820(void);
extern unsigned char gettemp(void);

//#endif