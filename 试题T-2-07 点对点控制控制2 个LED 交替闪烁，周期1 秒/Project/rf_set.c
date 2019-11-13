#include "hal_defs.h"
#include "hal_cc8051.h"
#include "hal_int.h"
#include "hal_mcu.h"
#include "hal_board.h"
#include "hal_led.h"
#include "hal_rf.h"
#include "basic_rf.h"
#include "hal_uart.h" 
#include <stdio.h>
#include <string.h>
#include	<stdarg.h>
uint8   scan_key();

#define MAX_SEND_BUF_LEN  128
#define MAX_RECV_BUF_LEN  128
static uint8 pTxData[MAX_SEND_BUF_LEN]; //定义无线发送缓冲区的大小
static uint8 pRxData[MAX_RECV_BUF_LEN]; //定义无线接收缓冲区的大小


#define MAX_UART_SEND_BUF_LEN  128
#define MAX_UART_RECV_BUF_LEN  128
uint8 uTxData[MAX_UART_SEND_BUF_LEN]; //定义串口发送缓冲区的大小
uint8 uRxData[MAX_UART_RECV_BUF_LEN]; //定义串口接收缓冲区的大小
uint16 uTxlen = 0;
uint16 uRxlen = 0;
unsigned int counter=0; //统计溢出次数
uint8 LEDFlag = 0;
uint8 LEDFlash = 0;

/*****点对点通讯地址设置******/
#define RF_CHANNEL                20         // 频道 11~26
#define PAN_ID                    0x1A5B     //网络id 
#define MY_ADDR                   0xAC3A     // 本机模块地址
#define SEND_ADDR                 0x1015     //发送地址

//#define MY_ADDR                   0x1015     // 本机模块地址
//#define SEND_ADDR                 0xAC3A     //发送地址
/**************************************************/
static basicRfCfg_t basicRfConfig;
// 无线RF初始化
void ConfigRf_Init(void)
{
    basicRfConfig.panId       =   PAN_ID;        //zigbee的ID号设置
    basicRfConfig.channel     =   RF_CHANNEL;    //zigbee的频道设置
    basicRfConfig.myAddr      =   MY_ADDR;       //设置本机地址
    basicRfConfig.ackRequest  =   TRUE;          //应答信号
    while(basicRfInit(&basicRfConfig) == FAILED); //检测zigbee的参数是否配置成功
    basicRfReceiveOn();                // 打开RF
}

/********************MAIN************************/
void main(void)
{
    uint16 len = 0;
    halBoardInit();  //模块相关资源的初始化
    ConfigRf_Init(); //无线收发参数的配置初始化 
    T1CTL = 0x05;   //  T1 通道 0，8 分频; 自动重载模式(0x0000->0xffff); 
    while(1)
    {
       if(scan_key())   //有按键，则发送数据
       {
            basicRfSendPacket(SEND_ADDR,"ZIGBEE TEST\r\n",13);                 
        } 
    
        if(basicRfPacketIsReady())   // 判断有无收到zigbee信号
        {
            if(LEDFlag == 0)
            {
              LEDFlag = 1;
              halLedSet(1);
              halLedClear(2);
            }
            else
            {
              LEDFlag = 0;
              halLedClear(1);
              halLedClear(2);
              halLedClear(3);               
            }
            counter = 0;
            len = basicRfReceive(pRxData, MAX_RECV_BUF_LEN, NULL);   // 接收数据
        }
       if(LEDFlag)
       {
       if(  (IRCON & 0x02)==0x02) //查询溢出中断标志，是否有中断并且为定时器1发出的中断
          {  IRCON &= ~0x02;      //清溢出标志 
             counter++;
             if(counter==60) //中断计数，约1s  (32/8)*10^6/65535/30=2Hz
              {
                   counter =0;
                   halLedToggle(1);
                   halLedToggle(2);
              }
         }         
       }
    }
}
/************/

#define key_io P1_2

uint8   scan_key()
{
    static  uint8   keysta=1;
    if (key_io)
    {       //按键新开
        keysta=1;
        return 0;        
    }
    else
    {
       if(keysta==0)
           return 0;
       keysta=0;
       return 1; 
    }
}