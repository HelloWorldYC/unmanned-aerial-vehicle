//arm_startup_nrf51.s�������ļ��������ж϶���
//#include "nrf51.h"//����51822�����Ĵ����ṹ��ַ������2�ļ��Ϳ��Կ���51822�ˡ�
//nrf51_bitfields.h���������Ĵ�������ֵ������
#include "project_nrf51822.c"//����51822������Ҫ�õ���ͷ�ļ���������ʱ��io��ʲô��

#include <stdbool.h>//����bool
#include "stdio.h"//��׼�������
#include <stdint.h>//������֪��С����������ʾ����������


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
    gpio_init_out(19,22);//led:red,green,blue
	
  	gpio_init_out(0,7);//����0~15������Ϊ���
//	  gpio_init_in(16,17,3);//����16~17������Ϊ���루������Ϊ��ťkey0��key1��
//  	gpio_init_out(18,25);//����18~25������Ϊ���/�Ǹ�26~27�ӵ��ǵ��پ���
//    gpio_init_out(28,31);//����28~31������Ϊ���
}


static uint8_t Receive_packet[5];  				//���յ��淢�͵�����
uint8_t voltage_collect_information[3]; 	//Ҫͨ�����ڷ��͸���ݮ�ɵĵ�ѹ��Ϣ�ռ�������
uint8_t i=0;


void Receive_NRFdata()
{
				NRF_RADIO->EVENTS_READY = 0U; //�շ�ģʽת�����  ��־λ       
        NRF_RADIO->TASKS_RXEN   = 1U; //����ģʽ
        while(NRF_RADIO->EVENTS_READY == 0U) //�ȴ��շ�ģʽת�����(����ģʽ)��־λ
          {
            // Do nothing.�ȴ�
          }
        NRF_RADIO->EVENTS_END  = 0U;//�������  ��־λ     
        NRF_RADIO->TASKS_START = 1U; // ��ʼ����

        while(NRF_RADIO->EVENTS_END == 0U)//�ȴ��������  ��־λ
           {
           //  nrf_gpio_pin_set(22);// blue��  //���䲻�ɹ�
						 // Do nothing.�ȴ�
           }
        if (NRF_RADIO->CRCSTATUS == 1U)//���CRCУ����ȷ
        {
					
            //nrf_gpio_port_write(NRF_GPIO_PORT_SELECT_PORT1, packet[0]);
					if(Receive_packet[0]== ('Q'))//ȷ����ʼ
					   {
              if(Receive_packet[4]== ('R'))//������ȷ
                {  
									nrf_gpio_pin_set(21);// blue�������ݳɹ��ˣ���Խ��˵�����ݴ���Խ�졣
									                       //����˵��,���ݴ���ʧ�ܡ�
                }
								else
								{
									
									NRF_RADIO->EVENTS_DISABLED = 0U;//���߹ر�   ��־λ
									return;
								}
             }
						 else
						 {
							 NRF_RADIO->EVENTS_DISABLED = 0U;//���߹ر�   ��־λ
							 return;
						 }
        }
        NRF_RADIO->EVENTS_DISABLED = 0U;//���߹ر�   ��־λ
				NRF_RADIO->TASKS_DISABLE   = 1U;// �ر������豸 
        while(NRF_RADIO->EVENTS_DISABLED == 0U)//�ȴ��豸�ر�
        {
            // Do nothing.
        }
}

//�����͵���ݮ�ɵı�������������
void voltage_collect_information_clear()
{
			for(i=0; i<3; i++)
			{
				voltage_collect_information[i] = 0;
			}
}

//�����յ������ݴ���Ҫ���͵���ݮ�ɵı���������
void Get_voltage_collect_information()
{
			for(i=0; i<3; i++)
			{
				voltage_collect_information[i] = Receive_packet[i+1];
			}
}

	int main(void)//main������ʼ
{

		init();						//ʱ�ӳ�ʼ��
    ioinit();					//���ų�ʼ��
		radio_configure();//���ߵ����ã�Ҳ�����ں�nrf2401ͨѶ��
    NRF_RADIO->PACKETPTR  = (uint32_t)Receive_packet;					//ָ��ָ�����ݻ���packet
	  simple_uart_config(RTS_PIN_NUMBER,TX_PIN_NUMBER,CTS_PIN_NUMBER,RX_PIN_NUMBER,HWFC); /*UART��ʼ�����궨���зֱ�����RTSΪ8��     
                                                                 TXΪ9��CTSΪ10��RXΪ11��HWFCΪfalse  */
		voltage_collect_information_clear();										 //���㷢�͸���ݮ�ɵı���������
	  while(1)
    {

						nrf_gpio_pin_set(19); 
						nrf_delay_ms(300);
						Receive_NRFdata();															 //���յ���NRF�崫������Ϣ
						nrf_gpio_pin_set(20); 
						Get_voltage_collect_information();							 //�Ե���NRF�崫������Ϣ���д���õ���ѹ�ռ�����
						simple_uart_put(voltage_collect_information[0]); //����ѹ�ռ�����ͨ�����ڴ�����ݮ��
						simple_uart_put(voltage_collect_information[1]);
						simple_uart_put(voltage_collect_information[2]);
						nrf_gpio_pin_clear(19);
						nrf_delay_ms(300);
						voltage_collect_information_clear();						 //���㷢�͸���ݮ�ɵı���������
						nrf_gpio_pin_clear(21);

			}  
}

