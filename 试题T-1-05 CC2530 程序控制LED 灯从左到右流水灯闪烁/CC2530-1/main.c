
#include <ioCC2530.h>
#define uint unsigned int
#define uchar unsigned char
//������ƵƵĶ˿�
#define LED1 P1_0	//����LED1ΪP10�ڿ���
#define LED2 P1_5	//����LED2ΪP15�ڿ���
#define LED3 P1_3	//����LED3ΪP13�ڿ���
#define LED4 P1_4	//����LED4ΪP14�ڿ���


//��������
void Delay(uint);		//��ʱ����
void Initial(void);		//��ʼ��P0��

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
/****************************
//��ʼ������
*****************************/
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
void main(void)
{
  uchar i;
	Initial();  //���ó�ʼ������
	while(1)
	{
     for(i=1;i<=4;i++)
     {
       switch(i)
       {
         case 1:
            LED2 = 1;
            LED1 = 0;
            LED4 = 0;
            LED3 = 0;
            break;
         case 2:
            LED2 = 0;
            LED1 = 1;
            LED4 = 0;
            LED3 = 0;
            break;
         case 3:
            LED2 = 0;
            LED1 = 0;
            LED4 = 1;
            LED3 = 0;
            break;
         case 4:
            LED2 = 0;
            LED1 = 0;
            LED4 = 0;
            LED3 = 1;
            break;            
        default:
            break;        
       }
       Delay(10000);
       Delay(10000);
       LED1 = 0;
       LED2 = 0;
       LED3 = 0;
       LED4 = 0;
       Delay(10000);
       Delay(10000);       
     }
	}
}
