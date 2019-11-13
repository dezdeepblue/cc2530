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
  uchar i;
  
  ,m Initial();
  i=0;
  while(1)
  {
      LED3 = i&0x01;      //��4λLED��ʾ
      LED4 = (i&0x02)>>1;
      LED1 = (i&0x04)>>2;
      LED2 = (i&0x08)>>3;     
      Delay(10000);
      Delay(10000);
      Delay(10000);      
      LED1 = 0;
      LED2 = 0;
      LED3 = 0;
      LED4 = 0;
      Delay(10000);
      Delay(10000);
      Delay(10000); 
      if(i<16)
        i++;
      else
        i=0;
  }
}

