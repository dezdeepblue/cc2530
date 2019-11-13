#include <ioCC2530.h>

#define uint unsigned int
#define uchar unsigned char

//定义控制灯的端口
#define LED1 P1_0	//定义LED1为P10口控制
#define LED2 P1_5	//定义LED2为P15口控制
#define LED3 P1_3	//定义LED3为P13口控制
#define LED4 P1_4	//定义LED3为P14口控制

void Initial(void);

/****************************
//延时
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

void LedFlash(uint Num8)
{
   uchar L1,L2,L3,L4;
   
   L1 = LED1;
   L2 = LED2;
   L3 = LED3;
   L4 = LED4;
   if(Num8%10 == 0)
      LED4 = 1;
   if(Num8%100 == 0)
      LED1 = 1;
   if(Num8%1000 == 0)
      LED2 = 1; 
    Delay(10000);
   if(Num8%10 == 0)
      LED4 = 0;
   if(Num8%100 == 0)
      LED1 = 0;
   if(Num8%1000 == 0)
      LED2 = 0; 
    Delay(10000);
    LED1 = L1;
    LED2 = L2;
    LED3 = L3;
    LED4 = L4;       
}

/****************************
//初始化程序
***************************/
void Initial(void)
{ 
  P1SEL &= ~0x3B; //定义GPIO设备
  P1DIR |= 0x3B;  //LED定义为输出
  LED1 = 0;
  LED2 = 0;
  LED3 = 0;
  LED4 = 0;   
}

/***************************
//主函数
***************************/
void main()
{
  uint Num8;
  
  Initial();
  while(1)
  {
      LED3 = 1;   
      Delay(10000);
      LED3 = 0;
      Delay(10000);
      if(Num8<65535)
      {
        Num8++;
        LedFlash(Num8);
      }
      else
      {
        Num8=0;
        LED1 = 0;
        LED2 = 0;
        LED3 = 0;
        LED4 = 0;
      }
     if(Num8%16 == 0)
        LED4 = 1;
     if(Num8%256 == 0)
        LED1 = 1;
     if(Num8%4096 == 0)
        LED2 = 1;     
  }
}

