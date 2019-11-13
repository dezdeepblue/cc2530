#include <ioCC2530.h>

#define uint unsigned int
#define uchar unsigned char

//������ƵƵĶ˿�
#define LED1 P1_0	//����LED1ΪP10�ڿ���
#define LED2 P1_5	//����LED2ΪP15�ڿ���
#define LED3 P1_3	//����LED3ΪP13�ڿ���
#define LED4 P1_4	//����LED3ΪP14�ڿ���

void Initial(void);

/****************************
//��ʱ
*****************************/
void Delay(uint n)
{
	uint tt;
	for(tt = 0;tt<n;tt++);
	for(tt = 0;tt<n;tt++);
	for(tt = 0;tt<n;tt++);
	for(tt = 0;tt<n;tt++);
	for(tt = 0;tt<n;tt++);
}

/*****************************************
//����ֵ
*****************************************/
uchar KeyScan(void)
{
  if(P1_2 == 0)     //�͵�ƽ��Ч
  {
    if(P1_2 == 0)
    {
        while(!P1_2); //ֱ���ɿ�����
        return(1);
    }
  }
  return(0);
}
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
}

/***************************
//������
***************************/
void main()
{
  uchar LEDFlag,i;
  
  Initial();
  LEDFlag = 0;
  i=0;
  while(1)
  {
      if(KeyScan() == 1)//���SW1����
      {
        if(LEDFlag == 0)//�������º�ı�LED��ʾ״̬
          LEDFlag = 1;
        else
        {
          LEDFlag = 0;
          LED1 = 0;
          LED2 = 0;
          LED3 = 0;
          LED4 = 0; 
        }
      }
      if(LEDFlag)//��ǰLED��ʾ������Ч
      {
       switch(i)
       {
         case 0:
            LED2 = 1;
            LED1 = 0;
            LED4 = 0;
            LED3 = 1;
            break;
         case 1:
            LED2 = 0;
            LED1 = 0;
            LED4 = 0;
            LED3 = 0;
            break;
         case 2:
            LED2 = 0;
            LED1 = 1;
            LED4 = 1;
            LED3 = 0;
            break;
         case 3:
            LED2 = 0;
            LED1 = 0;
            LED4 = 0;
            LED3 = 0;
            break;            
        default:
            break;        
       }
      Delay(10000);
      Delay(10000);       
      if(i<3)
       i++;
      else
       i=0;
    }
  }
}

