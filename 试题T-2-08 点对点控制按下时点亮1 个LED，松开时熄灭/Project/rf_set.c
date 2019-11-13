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
    uint8 SendON  = 0;
    halBoardInit();  //模块相关资源的初始化
    ConfigRf_Init(); //无线收发参数的配置初始化 
    while(1)
    {
       if(P1_2 == 0)   //按键按下
       {
         if(SendON == 0)
         {
            basicRfSendPacket(SEND_ADDR,"ZIGBEE ON\r\n",11);
            SendON = 1;
         }
       }
       else
       {
         if(SendON == 1)
         {
           SendON = 0;
           basicRfSendPacket(SEND_ADDR,"ZIGBEE OFF\r\n",12);
         }
       }
    
        if(basicRfPacketIsReady())   // 判断有无收到zigbee信号
        {
            len = basicRfReceive(pRxData, MAX_RECV_BUF_LEN, NULL);   // 接收数据
            if(memcmp(pRxData,"ZIGBEE ON\r\n",11) == 0)
            {
              halLedSet(1);
            }
            else if(memcmp(pRxData,"ZIGBEE OFF\r\n",12) == 0)
            {
              halLedClear(1);
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