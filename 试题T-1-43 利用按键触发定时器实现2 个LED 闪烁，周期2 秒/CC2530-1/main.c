#include <ioCC2530.h>

#define uint unsigned int
#define uchar unsigned char

//定义控制灯的端口
#define D3 P1_0	//定义LED1为P10口控制
#define D4 P1_5	//定义LED2为P15口控制
#define D5 P1_3	//定义LED3为P13口控制
#define D6 P1_4	//定义LED4为P14口控制

uint counter=0;				//统计溢出次数
uint TimerFlag;				//用来标志是否开启定时器

void Initial(void);

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
  D3 = 0;
  D4 = 0;
  D5 = 0;
  D6 = 0;
}

/***************************
//主函数
***************************/
void main()
{
  unsigned int TimeCouter = 0;
  
  Initial(); 	 //调用初始化函数
  while(1)   	 //查询溢出
  {
      if(KeyScan() == 1)
      {
        T1CTL = 0x05;         //  T1 通道 0，8 分频; 自动重载模式(0x0000->0xffff); 
        CLKCONCMD &= 0x80;    //时钟速度设置为32MHz
        TimerFlag  = 1;
        D5 = 1;
        D6 = 1;        
      }
      if(IRCON > 0)
      {
        IRCON = 0;         //清溢出标志
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

