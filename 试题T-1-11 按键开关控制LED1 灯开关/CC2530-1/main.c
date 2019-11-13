#include <ioCC2530.h>

#define uint unsigned int
#define uchar unsigned char

//定义控制灯的端口
#define GLED P1_0	//定义LED1为P10口控制
#define RLED P1_1	
void Initial(void);
uchar Keyscan(void);

/*****************************************
//读键值
*****************************************/
uchar KeyScan(void)
{
  if(P0_0 == 0)     //低电平有效
  {
    if(P0_0 == 0)
    {
        while(!P0_0); //直到松开按键
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
  P1 &= ~0x03B;
  GLED= 0;  
  RLED= 0; 
}

/***************************
//主函数
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

