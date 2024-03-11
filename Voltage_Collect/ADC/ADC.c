#include "project_nrf51822.c"//包含51822工程需要用到的头文件（晶振，延时，io脚什么的
#include "ADC.h"
#include <stdbool.h>//调用bool
#include "stdio.h"//标准输入输出
#include <stdint.h>//声明已知大小的整数或显示特征的整数


//数据读取
/******************************************************************
*参考电压:1/2供电电压(3.3V/2)---V1
*采样精度:10位
*输入电压:1/3分压-----V2
*计算公式:V1/2^10*AdcDat*V2 = (3.3/2/1024)*AdcDat*3 = 实测电压
******************************************************************/


//初始化设置
void Adc_Init(uint8_t AdcRes,uint8_t AdcPin)
{

   if(AdcPin <= 7)
     {                     //多小位                         //BBB=2
       NRF_ADC->CONFIG = AdcRes << ADC_CONFIG_RES_Pos |     //分辨率设置
                  ADC_CONFIG_INPSEL_AnalogInputOneThirdPrescaling << ADC_CONFIG_INPSEL_Pos |    //设置采样电压的分压
                  ADC_CONFIG_REFSEL_VBG << ADC_CONFIG_REFSEL_Pos | //设置参考电压
                  (1 << AdcPin) << ADC_CONFIG_PSEL_Pos; //配置输入管脚    
                          //cc=3
             NRF_ADC->ENABLE = 1;  //ADC使能

    }
 }


//读取数据
uint16_t Adc_Read_Value(void) 
{
  uint16_t AdcDat;

  NRF_ADC->TASKS_START = 1;     		//启动ADC转换
  while(NRF_ADC->EVENTS_END == 0);  //等待转换结束
  NRF_ADC->EVENTS_END = 0;
  AdcDat = NRF_ADC->RESULT; 				//读出转换结果

  return AdcDat;    
}

//多次测量取平均值
//ADC采集取平均值
uint16_t Get_Adc_Average(uint8_t times)  //参数是要多次测量的次数
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