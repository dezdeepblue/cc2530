#include <ioCC2530.h>

#define uint unsigned int
#define uchar unsigned char

//������ƵƵĶ˿�
#define LED1 P1_0	//����LED1ΪP10�ڿ���
#define LED2 P1_5	//����LED2ΪP15�ڿ���
#define LED3 P1_3	//����LED3ΪP13�ڿ���
#define LED4 P1_4	//����LED4ΪP14�ڿ���

uint counter=0;				//ͳ���������
uint TimerFlag;				//������־�Ƿ�����ʱ��
uchar LEDFlash = 0;
void Initial(void);

/****************************
//��ʼ������
***************************/
void Initial(void)
{
  P1SEL &= ~0x3B; //����GPIO�豸
  P1DIR |= 0x3B;  //LED����Ϊ���
  LED1 = 0;
  LED2 = 0;
  LED3 = 0;
  LED4 = 0;
  T1CTL = 0x05;         //  T1 ͨ�� 0��8 ��Ƶ; �Զ�����ģʽ(0x0000->0xffff); 
  CLKCONCMD &= 0x80;    //ʱ���ٶ�����Ϊ32MHz
}

/***************************
//������
***************************/
void main()
{
  unsigned int TimeCouter = 0;
  
  Initial(); 	 //���ó�ʼ������
  LED1 = 0;
  while(1)   	 //��ѯ���
  {
    if(  (IRCON & 0x02)==0x02) //��ѯ����жϱ�־���Ƿ����жϲ���Ϊ��ʱ��1�������ж�
      {  IRCON &= ~0x02;      //�������־
         TimeCouter++;
        if(TimeCouter ==120)  //2s  (32/8)*10^6/65535/30=2Hz
        {
          TimeCouter = 0;
          LED1 = 1;
          LEDFlash = 1;
        }
        if(LEDFlash)
        {
         if(TimeCouter==30)
         {
           LEDFlash = 0;
           LED1 = 0;
         }
        }
      }
  }
}

