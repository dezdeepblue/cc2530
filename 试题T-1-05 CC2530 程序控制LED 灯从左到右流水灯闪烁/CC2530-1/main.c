
#include <ioCC2530.h>
#define uint unsigned int
#define uchar unsigned char
//定义控制灯的端口
#define LED1 P1_0	//定义LED1为P10口控制
#define LED2 P1_5	//定义LED2为P15口控制
#define LED3 P1_3	//定义LED3为P13口控制
#define LED4 P1_4	//定义LED4为P14口控制


//函数声明
void Delay(uint);		//延时函数
void Initial(void);		//初始化P0口

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
/****************************
//初始化程序
*****************************/
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
void main(void)
{
  uchar i;
	Initial();  //调用初始化函数
	while(1)
	{
     for(i=1;i<=4;i++)
     {
       switch(i)
       {
         case 1:
            LED2 = 1;
            LED1 = 0;
            LED4 = 0;
            LED3 = 0;
            break;
         case 2:
            LED2 = 0;
            LED1 = 1;
            LED4 = 0;
            LED3 = 0;
            break;
         case 3:
            LED2 = 0;
            LED1 = 0;
            LED4 = 1;
            LED3 = 0;
            break;
         case 4:
            LED2 = 0;
            LED1 = 0;
            LED4 = 0;
            LED3 = 1;
            break;            
        default:
            break;        
       }
       Delay(10000);
       Delay(10000);
       LED1 = 0;
       LED2 = 0;
       LED3 = 0;
       LED4 = 0;
       Delay(10000);
       Delay(10000);       
     }
	}
}
