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

/*****************************************
//读键值
*****************************************/
uchar KeyScan(void)
{
  if(P1_2 == 0)     //低电平有效
  {
    if(P1_2 == 0)
    {
        while(!P1_2); //直到松开按键
        return(1);
    }
  }
  return(0);
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
  uchar LEDFlag,i;
  
  Initial();
  LEDFlag = 0;
  i=0;
  while(1)
  {
      if(KeyScan() == 1)//检测SW1按键
      {
        if(LEDFlag == 0)//按键按下后改变LED显示状态
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
      if(LEDFlag)//当前LED显示控制有效
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

