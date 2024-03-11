//-----------------------------------------
//------------------------------------------------
#ifndef ADCMEASURE_H
#define ADCMEASURE_H


extern void Adc_Init(uint8_t AdcRes,uint8_t AdcPin);
extern uint16_t Adc_Read_Value(void);
extern uint16_t Get_Adc_Average(uint8_t times);



#endif