#include "project_nrf51822.c"//����51822������Ҫ�õ���ͷ�ļ���������ʱ��io��ʲô��
#include "pca1000x.h"
#include "ADC.h"

#include <stdbool.h>//����bool
#include "stdio.h"//��׼�������
#include <stdint.h>//������֪��С����������ʾ����������


static uint8_t volatile Send_packet[5] = {'Q','S','D','F','R'};  //Ҫ���ͳ�ȥ�����ݻ�����
uint16_t Voltage_data;		//ADC�ɼ��ĵ�ѹ����
uint8_t i=0;

void init(void)//51822ʱ�ӳ�ʼ��
{ 
	 //�жϵ�Դʱ��״̬
	 if ((((*(uint32_t *)0xF0000FE0) & 0xFF) == 1) && (((*(uint32_t *)0xF0000FE4) & 0xF) == 0))
    {
        if ((((*(uint32_t *)0xF0000FE8) & 0xF0) == 0x0) && (((*(uint32_t *)0xF0000FEC) & 0xF0) == 0x0))
        {
					//���radio�޷�д��  
          *(uint32_t *)0x40000504 = 0xC007FFDF;//��Դʱ������
          *(uint32_t *)0x40006C18 = 0x00008000;//GPIOTE����    
        }
				else if ((((*(uint32_t *)0xF0000FE8) & 0xF0) == 0x10) && (((*(uint32_t *)0xF0000FEC) & 0xF0) == 0x0))
        {
          //���radio�޷�д��  
          *(uint32_t *)0x40000504 = 0xC007FFDF;//��Դʱ������
          *(uint32_t *)0x40006C18 = 0x00008000;//GPIOTE����  
        }
        else if ((((*(uint32_t *)0xF0000FE8) & 0xF0) == 0x30) && (((*(uint32_t *)0xF0000FEC) & 0xF0) == 0x0))
        {
          //���radio�޷�д��  
          *(uint32_t *)0x40000504 = 0xC007FFDF;//��Դʱ������
          *(uint32_t *)0x40006C18 = 0x00008000;//GPIOTE����    
        }
    }
	NRF_CLOCK->EVENTS_HFCLKSTARTED = 0;//HFCLK��������״̬0�رգ�1����
  NRF_CLOCK->TASKS_HFCLKSTART = 1;//���⾧��HFCLK 0�رգ�1����
  while(!NRF_CLOCK->EVENTS_HFCLKSTARTED);//�ȴ�HFCLK��������״̬Ϊ1
}

void ioinit()//51822���ų�ʼ��
{
    //������usb-jtag��nrf51822
//	  gpio_init_in(9,9,3);//p0.09����
//	  gpio_init_in(11,11,3);//p0.11����
//    gpio_init_out(21,23);//led:red,green,blue
	
			gpio_init_in(0,7,0);//����0~7������Ϊ����
    	gpio_init_out(8,15);//����8~15������Ϊ���
  	  gpio_init_in(16,17,3);//����16~17������Ϊ����3�����������裨������Ϊ��ťkey0��key1��
    	gpio_init_out(18,25);//����18~25������Ϊ���/�Ǹ�26~27�ӵ��ǵ��پ���
      gpio_init_out(28,31);//����28~31������Ϊ���
}



void Send_NRFdata()
{
	  nrf_gpio_pin_clear(18);
		NRF_RADIO->PACKETPTR    = (uint32_t)Send_packet;//ָ��ָ�����ݻ���packet
		NRF_RADIO->EVENTS_READY = 0U;//�շ�ģʽת����ɱ�־λ����λ
    NRF_RADIO->TASKS_TXEN = 1U;//�������ߵ�Ϊ����ģʽ
    while (NRF_RADIO->EVENTS_READY == 0U);//�ȴ��շ�ģʽת�����
    NRF_RADIO->EVENTS_END  = 0U;//������ɱ�־λ����λ     
		NRF_RADIO->TASKS_START = 1U;//��ʼ����
        while(NRF_RADIO->EVENTS_END == 0U) //�ȴ��������
        {
					  nrf_gpio_pin_set(18);//����ʧ��led0��
            // Do nothing.
        }

        // ��1���ţ�8~15��
        //nrf_gpio_port_write(P0, ~Send_packet[0]);//��ֵ��ʾ�ڵ�Ƭ��P0���� 1000 1111
        nrf_gpio_pin_clear(18);//����ɹ�led0��Խ��˵���и��ţ���Ҫ��Ƶ��  ����ߵ�ƽ��pa.1

				NRF_RADIO->EVENTS_DISABLED = 0U;//���߹رձ�־λ  ��λ
				NRF_RADIO->TASKS_DISABLE   = 1U;// �ر������豸
        while(NRF_RADIO->EVENTS_DISABLED == 0U)//�ȴ��豸�ر�
        {
            // Do nothing.
        }
}

int main(void)
{
	
	init();//ʱ�ӳ�ʼ��
  ioinit();//���ų�ʼ��
	simple_uart_config(RTS_PIN_NUMBER, TX_PIN_NUMBER, CTS_PIN_NUMBER, RX_PIN_NUMBER, HWFC);
	radio_configure();//���ߵ����ã�Ҳ�����ں�nrf2401ͨѶ��
	Adc_Init(ADC_CONFIG_RES_10bit,ADC_CONFIG_PSEL_AnalogInput1);
	
  while(1)
  {	
				nrf_delay_ms(300);
				nrf_gpio_pin_toggle(LED_2);														//��LED2��ƽ״̬���з�ת
				nrf_delay_ms(300);
				Voltage_data = Get_Adc_Average(10); 									//��ȡADC�ɼ����ĵ�ѹ����
				Send_packet[1] = (uint8_t)((Voltage_data&0xff00)>>8); //��ѹ���ݵĸ߰�λ
			  Send_packet[2] = (uint8_t)(Voltage_data&0x00ff) ;			//��ѹ���ݵĵͰ�λ
				Send_packet[3] = '1';																	//�Զ���Ľ������ݳɹ���־λ�����˻��յ������ݻ������һ��Ŀ���
				Send_NRFdata();																				//�����ݷ��ͳ�ȥ

  }
	
}