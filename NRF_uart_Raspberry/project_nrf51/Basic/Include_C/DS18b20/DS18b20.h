/*#ifndef __18b20_H__
#define __18b20_H__  1

#define TEM_PORT PORTF
#define TEM_DDR DDRF
#define TEM_PIN PINF

#define TEM_SDT 2
//nrf_gpio_pin_set();��λĳһλ���ţ�
//nrf_gpio_pin_clear();��λĳһλ���ţ�
#define SET_TEM_SDT (TEM_PORT|=(1<<TEM_SDT))  //����ߵ�ƽ
#define CLR_TEM_SDT (TEM_PORT&=~(1<<TEM_SDT))  //����͵�ƽ

#define SET_TEM_DDR (TEM_DDR|=(1<<TEM_SDT))  //��Ϊ���
#define CLR_TEM_DDR (TEM_DDR&=~(1<<TEM_SDT))  //��Ϊ����

#define CHECK_TEM_SDT (TEM_PIN&(1<<TEM_SDT))  //����ĵ�ƽֵΪ��*/

extern void init_1820(void);
extern void write_1820(unsigned char data);
extern unsigned char read_1820(void);
extern unsigned char gettemp(void);

//#endif