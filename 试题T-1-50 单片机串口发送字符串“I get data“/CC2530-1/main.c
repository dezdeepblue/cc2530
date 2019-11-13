//cd wxl 2009 ����0������
#include <ioCC2530.h>
#include <string.h>

#define uint unsigned int
#define uchar unsigned char

//������ƵƵĶ˿�
#define led1 P1_0
#define led2 P1_1

//��������
void Delay(uint);
void initUARTtest(void);
void UartTX_Send_String(char *Data,int len);


char Txdata[30];

/****************************************************************
*�������� ����ʱ						
*��ڲ��� ��������ʱ									
*�� �� ֵ ����												
*˵    �� ��													
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
*�������� ����ʼ������1										
*��ڲ��� ����												
*�� �� ֵ ����							
*˵    �� ��57600-8-n-1						
****************************************************************/
void initUARTtest(void)
{
    CLKCONCMD&=0X80;//ʱ���豸Ϊ32MHz
    
    PERCFG = 0x00;		  //λ��1 P0��
    P0SEL = 0x3c;				//P0��������
    
    U0CSR |= 0x80;				//UART��ʽ
    U0GCR |= 10;				//baud_e
    U0BAUD |= 216;				//��������Ϊ57600
    UTX0IF = 0;
}

/****************************************************************
*�������� �����ڷ����ַ�������					
*��ڲ��� : data:����									
*			len :���ݳ���							
*�� �� ֵ ����											
*˵    �� ��				
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
*�������� ��������								
*��ڲ��� ����							
*�� �� ֵ ����						
*˵    �� ����							
****************************************************************/
void main(void)
{	
	initUARTtest();   
  strcpy(Txdata,"I get data");       //��UART0 TX test����Txdata;

	while(1)
	{
        UartTX_Send_String(Txdata,sizeof("I get data")); //���ڷ�������
        Delay(50000);       //��ʱ
        Delay(50000);
        Delay(50000);
	}
}
