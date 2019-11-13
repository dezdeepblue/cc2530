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
static uint8 pTxData[MAX_SEND_BUF_LEN]; //�������߷��ͻ������Ĵ�С
static uint8 pRxData[MAX_RECV_BUF_LEN]; //�������߽��ջ������Ĵ�С


#define MAX_UART_SEND_BUF_LEN  128
#define MAX_UART_RECV_BUF_LEN  128
uint8 uTxData[MAX_UART_SEND_BUF_LEN]; //���崮�ڷ��ͻ������Ĵ�С
uint8 uRxData[MAX_UART_RECV_BUF_LEN]; //���崮�ڽ��ջ������Ĵ�С
uint16 uTxlen = 0;
uint16 uRxlen = 0;

/*****��Ե�ͨѶ��ַ����******/
#define RF_CHANNEL                20         // Ƶ�� 11~26
#define PAN_ID                    0x1A5B     //����id 
#define MY_ADDR                   0xAC3A     // ����ģ���ַ
#define SEND_ADDR                 0x1015     //���͵�ַ

//#define MY_ADDR                   0x1015     // ����ģ���ַ
//#define SEND_ADDR                 0xAC3A     //���͵�ַ
/**************************************************/
static basicRfCfg_t basicRfConfig;
// ����RF��ʼ��
void ConfigRf_Init(void)
{
    basicRfConfig.panId       =   PAN_ID;        //zigbee��ID������
    basicRfConfig.channel     =   RF_CHANNEL;    //zigbee��Ƶ������
    basicRfConfig.myAddr      =  MY_ADDR;        //���ñ�����ַ
    basicRfConfig.ackRequest  =   TRUE;          //Ӧ���ź�
    while(basicRfInit(&basicRfConfig) == FAILED); //���zigbee�Ĳ����Ƿ����óɹ�
    basicRfReceiveOn();                // ��RF
}

/********************MAIN************************/
void main(void)
{
    uint16 len = 0;
    halBoardInit();  //ģ�������Դ�ĳ�ʼ��
    ConfigRf_Init(); //�����շ����������ó�ʼ�� 
    while(1)
    {
       if(scan_key())   //�а�������������
       {           
            halLedToggle(3);       // �̵�ȡ��������ָʾ
            basicRfSendPacket(SEND_ADDR,"ZIGBEE TEST\r\n",13);            
                          
        } 
    
        if(basicRfPacketIsReady())   // �ж������յ�zigbee�ź�
        {
            halLedToggle(1);
            len = basicRfReceive(pRxData, MAX_RECV_BUF_LEN, NULL);   // ��������
        } 
    }
}
/************/

#define key_io P1_2

uint8   scan_key()
{
    static  uint8   keysta=1;
    if (key_io)
    {       //�����¿�
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