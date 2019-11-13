#include <ioCC2530.h>

#define uint unsigned int
#define uchar unsigned char

//������ƵƵĶ˿�
#define GLED P1_0	//����LED1ΪP10�ڿ���
#define RLED P1_1	
void Initial(void);
uchar Keyscan(void);

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
  GLED= 0;  
  RLED= 0; 
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
        GLED = !GLED;
        RLED = !RLED;
      }
  }
}

