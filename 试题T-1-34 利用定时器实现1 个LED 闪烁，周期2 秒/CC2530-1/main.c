#include <ioCC2530.h>

#define uint unsigned int
#define uchar unsigned char

//定义控制灯的端口
#define LED1 P1_0	//定义LED1为P10口控制
#define LED2 P1_5	//定义LED2为P15口控制
#define LED3 P1_3	//定义LED3为P13口控制
#define LED4 P1_4	//定义LED4为P14口控制

uint counter=0;				//统计溢出次数
uint TimerFlag;				//用来标志是否开启定时器
uchar LEDFlash = 0;
void Initial(void);

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
  T1CTL = 0x05;         //  T1 通道 0，8 分频; 自动重载模式(0x0000->0xffff); 
  CLKCONCMD &= 0x80;    //时钟速度设置为32MHz
}

/***************************
//主函数
***************************/
void main()
{
  unsigned int TimeCouter = 0;
  
  Initial(); 	 //调用初始化函数
  LED1 = 0;
  while(1)   	 //查询溢出
  {
    if(  (IRCON & 0x02)==0x02) //查询溢出中断标志，是否有中断并且为定时器1发出的中断
      {  IRCON &= ~0x02;      //清溢出标志
         TimeCouter++;
        if(TimeCouter ==120)  //2s  (32/8)*10^6/65535/30=2Hz
        {
          TimeCouter = 0;
          LED1 = 1;
          LEDFlash = 1;
        }
        if(LEDFlash)
        {
         if(TimeCouter==30)
         {
           LEDFlash = 0;
           LED1 = 0;
         }
        }
      }
  }
}

