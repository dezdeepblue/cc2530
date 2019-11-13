#include <ioCC2530.h>

#define uint unsigned int
#define uchar unsigned char

//������ƵƵĶ˿�
#define D3 P1_0	//����LED1ΪP10�ڿ���
#define D4 P1_5	//����LED2ΪP15�ڿ���
#define D5 P1_3	//����LED3ΪP13�ڿ���
#define D6 P1_4	//����LED4ΪP14�ڿ���

uint counter=0;				//ͳ���������
uint TimerFlag;				//������־�Ƿ�����ʱ��

void Initial(void);

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
  D3 = 0;
  D4 = 0;
  D5 = 0;
  D6 = 0;
}

/***************************
//������
***************************/
void main()
{
  unsigned int TimeCouter = 0;
  
  Initial(); 	 //���ó�ʼ������
  while(1)   	 //��ѯ���
  {
      if(KeyScan() == 1)
      {
        T1CTL = 0x05;         //  T1 ͨ�� 0��8 ��Ƶ; �Զ�����ģʽ(0x0000->0xffff); 
        CLKCONCMD &= 0x80;    //ʱ���ٶ�����Ϊ32MHz
        TimerFlag  = 1;
        D5 = 1;
        D6 = 1;        
      }
      if(IRCON > 0)
      {
        IRCON = 0;         //�������־
        TimeCouter++;
      }
      if(TimerFlag)
      {
        if(D5)
        {
          if(TimeCouter >=30)  //0.5s  (32/8)*10^6/65535/30=2Hz
          {
            TimeCouter = 0;
            D5 = 0;
            D6 = 0;
          }
        }
        else
        {
          if(TimeCouter >=90)
          {
            TimeCouter = 0;
            D5 = 1;
            D6 = 1;
          }
        }
      }
  }
}

