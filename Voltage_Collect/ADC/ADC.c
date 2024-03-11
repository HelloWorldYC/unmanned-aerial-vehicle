#include "project_nrf51822.c"//����51822������Ҫ�õ���ͷ�ļ���������ʱ��io��ʲô��
#include "ADC.h"
#include <stdbool.h>//����bool
#include "stdio.h"//��׼�������
#include <stdint.h>//������֪��С����������ʾ����������


//���ݶ�ȡ
/******************************************************************
*�ο���ѹ:1/2�����ѹ(3.3V/2)---V1
*��������:10λ
*�����ѹ:1/3��ѹ-----V2
*���㹫ʽ:V1/2^10*AdcDat*V2 = (3.3/2/1024)*AdcDat*3 = ʵ���ѹ
******************************************************************/


//��ʼ������
void Adc_Init(uint8_t AdcRes,uint8_t AdcPin)
{

   if(AdcPin <= 7)
     {                     //��Сλ                         //BBB=2
       NRF_ADC->CONFIG = AdcRes << ADC_CONFIG_RES_Pos |     //�ֱ�������
                  ADC_CONFIG_INPSEL_AnalogInputOneThirdPrescaling << ADC_CONFIG_INPSEL_Pos |    //���ò�����ѹ�ķ�ѹ
                  ADC_CONFIG_REFSEL_VBG << ADC_CONFIG_REFSEL_Pos | //���òο���ѹ
                  (1 << AdcPin) << ADC_CONFIG_PSEL_Pos; //��������ܽ�    
                          //cc=3
             NRF_ADC->ENABLE = 1;  //ADCʹ��

    }
 }


//��ȡ����
uint16_t Adc_Read_Value(void) 
{
  uint16_t AdcDat;

  NRF_ADC->TASKS_START = 1;     		//����ADCת��
  while(NRF_ADC->EVENTS_END == 0);  //�ȴ�ת������
  NRF_ADC->EVENTS_END = 0;
  AdcDat = NRF_ADC->RESULT; 				//����ת�����

  return AdcDat;    
}

//��β���ȡƽ��ֵ
//ADC�ɼ�ȡƽ��ֵ
uint16_t Get_Adc_Average(uint8_t times)  //������Ҫ��β����Ĵ���
{
    uint8_t cnt;
    uint16_t AdcVal=0;

    for(cnt=0;cnt<times;cnt++)
    {
        AdcVal += Adc_Read_Value();
        nrf_delay_ms(200);
    }
    return AdcVal/times;
}