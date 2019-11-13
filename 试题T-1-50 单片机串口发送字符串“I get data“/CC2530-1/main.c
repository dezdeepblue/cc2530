//cd wxl 2009 串口0发数据
#include <ioCC2530.h>
#include <string.h>

#define uint unsigned int
#define uchar unsigned char

//定义控制灯的端口
#define led1 P1_0
#define led2 P1_1

//函数声明
void Delay(uint);
void initUARTtest(void);
void UartTX_Send_String(char *Data,int len);


char Txdata[30];

/****************************************************************
*函数功能 ：延时						
*入口参数 ：定性延时									
*返 回 值 ：无												
*说    明 ：													
****************************************************************/
void Delay(uint n)
{
	uint i;
	for(i=0;i<n;i++);
	for(i=0;i<n;i++);
	for(i=0;i<n;i++);
	for(i=0;i<n;i++);
	for(i=0;i<n;i++);
}

/****************************************************************
*函数功能 ：初始化串口1										
*入口参数 ：无												
*返 回 值 ：无							
*说    明 ：57600-8-n-1						
****************************************************************/
void initUARTtest(void)
{
    CLKCONCMD&=0X80;//时钟设备为32MHz
    
    PERCFG = 0x00;		  //位置1 P0口
    P0SEL = 0x3c;				//P0用作串口
    
    U0CSR |= 0x80;				//UART方式
    U0GCR |= 10;				//baud_e
    U0BAUD |= 216;				//波特率设为57600
    UTX0IF = 0;
}

/****************************************************************
*函数功能 ：串口发送字符串函数					
*入口参数 : data:数据									
*			len :数据长度							
*返 回 值 ：无											
*说    明 ：				
****************************************************************/
void UartTX_Send_String(char *Data,int len)
{
  int j;
  for(j=0;j<len;j++)
  {
    U0DBUF = *Data++;
    while(UTX0IF == 0);
    UTX0IF = 0;
  }
}


/****************************************************************
*函数功能 ：主函数								
*入口参数 ：无							
*返 回 值 ：无						
*说    明 ：无							
****************************************************************/
void main(void)
{	
	initUARTtest();   
  strcpy(Txdata,"I get data");       //将UART0 TX test赋给Txdata;

	while(1)
	{
        UartTX_Send_String(Txdata,sizeof("I get data")); //串口发送数据
        Delay(50000);       //延时
        Delay(50000);
        Delay(50000);
	}
}
