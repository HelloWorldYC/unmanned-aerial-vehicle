#include "project_nrf51822.c"//����51822������Ҫ�õ���ͷ�ļ���������ʱ��io��ʲô��
#include "pca1000x.h"
#include "key_scan_1.h"
#include <stdbool.h>//����bool
#include "stdio.h"//��׼�������
#include <stdint.h>//������֪��С����������ʾ����������



static uint8_t btn0_nstate;     // Button0 �� new state ��־λ
static uint8_t btn1_nstate;     // Button1 �� new state ��־λ

static uint8_t btn0_ostate;			// Button0 �� old state ��־λ
static uint8_t btn1_ostate;			// Button1 �� old state ��־λ

//----------------------------------
//key��ʼ����
//----------------------------------
void KEY_Init(void)
{
			gpio_init_in(16,17,3);//����16~17������Ϊ����3�����������裨������Ϊ��ťkey0��key1��
			btn0_ostate = nrf_gpio_pin_read(BUTTON_0); // ��ʼ Button0 old state
			btn1_ostate = nrf_gpio_pin_read(BUTTON_1); // ��ʼ Button1 old state

}

//----------------------------------
//keyɨ�躯��
//----------------------------------
uint8_t Key_Scan(void)
{
    btn0_nstate = nrf_gpio_pin_read(BUTTON_0);  // ��ʼ Button0 new state
    btn1_nstate = nrf_gpio_pin_read(BUTTON_1);	// ��ʼ Button1 new state
		
    if ((btn0_ostate == 1) && (btn0_nstate == 0))
    {
      return 1;
    }
     
    if ((btn1_ostate == 1) && (btn1_nstate == 0))
    {
      return 2;
    }
		else
		return 3 ;
    
    btn0_ostate = btn0_nstate;
    btn1_ostate = btn1_nstate;
}

