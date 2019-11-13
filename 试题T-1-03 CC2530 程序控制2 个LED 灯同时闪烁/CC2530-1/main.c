
#include <ioCC2530.h>
#define uint unsigned int
#define uchar unsigned char
//定义控制灯的端口
#define LED1 P1_0	//定义LED1为P10口控制
#define LED2 P1_5	//定义LED2为P15口控制

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
  P1 &= ~0x03B;
  LED1 = 0;
  LED2 = 0;
}
/***************************
//主函数
***************************/
void main(void)
{
	Initial();  //调用初始化函数
	while(1)
	{
     LED1 = !LED1;
     LED2 = !LED2;
     Delay(10000);
	}
}
