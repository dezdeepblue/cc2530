#include <ioCC2530.h>

#define uint unsigned int
#define uchar unsigned char

//������ƵƵĶ˿�
#define LED1 P1_0	//����LED1ΪP10�ڿ���
#define LED2 P1_5	//����LED2ΪP15�ڿ���

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
  P1 &= ~0x03B;
  LED1 = 0;
  LED2 = 0;
}

/***************************
//������
***************************/
void main()
{
  Initial();
  while(1)
  {
      if(KeyScan() == 1)
      {
        LED1 = !LED1;
        LED2 = !LED2;
      }
  }
}

