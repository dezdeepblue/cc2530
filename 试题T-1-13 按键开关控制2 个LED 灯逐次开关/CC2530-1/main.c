#include <ioCC2530.h>

#define uint unsigned int
#define uchar unsigned char

//������ƵƵĶ˿�
#define LED1 P1_0	//����LED1ΪP10�ڿ���
#define LED2 P1_1	//����LED2ΪP15�ڿ���

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
  if(P0_0 == 0)     //�͵�ƽ��Ч
  {
    if(P0_0 == 0)
    {
        while(!P0_0); //ֱ���ɿ�����
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
  uchar i;
  
  Initial();
  i=0;
  while(1)
  {
      if(KeyScan() == 1)//����ÿ����һ����ε���LED1��LED2
      {
       switch(i)
         {
           case 0:
              LED1 = 1;
              LED2 = 0;
              break;
           case 1:
              LED1 = 0;
              LED2 = 1;
              break;
           case 2:
              LED1 = 0;
              LED2 = 0;
              break;        
          default:
              break;        
         }
       if(i<2)
         i++;
       else
         i=0;
      }
  }
}

