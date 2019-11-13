#include "OSAL.h"
#include "AF.h"
#include "ZDApp.h"
#include "ZDObject.h"
#include "ZDProfile.h"
#include <string.h>

//#include "Coordinator.h"
#include "GenericApp.h"

#include "DebugTrace.h"
#if !defined(WIN32)
#include "OnBoard.h"
#endif

#include "hal_led.h"
#include "hal_lcd.h"
#include "hal_key.h"
#include "hal_uart.h"
#include "OSAL_Nv.h"
#include "aps_groups.h"

const cId_t GenericApp_ClusterList[GENERICAPP_MAX_CLUSTERS]={
GENERICAPP_CLUSTERID  \
 };
const SimpleDescriptionFormat_t GenericApp_SimpleDesc=
{
  GENERICAPP_ENDPOINT,
  GENERICAPP_PROFID,
  GENERICAPP_DEVICEID,
  GENERICAPP_DEVICE_VERSION,
  GENERICAPP_FLAGS,
  GENERICAPP_MAX_CLUSTERS,
  (cId_t *)GenericApp_ClusterList,
  0,
  (cId_t *)NULL
};
aps_Group_t GenericApp_Group;

endPointDesc_t GenericApp_epDesc;
devStates_t GenericApp_NwkState;

byte GenericApp_TaskID;
byte GenericApp_TransID;
unsigned char uartbuf[128];

void GenericApp_MessageMSGCB(afIncomingMSGPacket_t *pckt);
void GenericApp_SendTheMessage(void);

void GenericApp_Init(byte task_id)
{
	halUARTCfg_t uartConfig;
	
	GenericApp_TaskID		=task_id;
	GenericApp_TransID		=0;
	GenericApp_epDesc.endPoint=GENERICAPP_ENDPOINT;
	GenericApp_epDesc.task_id=&GenericApp_TaskID;
	GenericApp_epDesc.simpleDesc=(SimpleDescriptionFormat_t *)&GenericApp_SimpleDesc;
	GenericApp_epDesc.latencyReq=noLatencyReqs;
	afRegister(&GenericApp_epDesc);

	uartConfig.configured		=TRUE;
	uartConfig.baudRate		=HAL_UART_BR_115200;
	uartConfig.flowControl		=FALSE;
	uartConfig.callBackFunc		=NULL;
	HalUARTOpen(0,&uartConfig);
	GenericApp_Group.ID=0x0001;
	GenericApp_Group.name[0]=6;
	osal_memcpy(&(GenericApp_Group.name[1]),"Group1",6);
}
UINT16 GenericApp_ProcessEvent(byte tadk_id,UINT16 events)
{
	afIncomingMSGPacket_t *MSGpkt;
	if(events&SYS_EVENT_MSG)
		{
			MSGpkt=(afIncomingMSGPacket_t *)osal_msg_receive(GenericApp_TaskID);
			while(MSGpkt)
				{
					switch(MSGpkt->hdr.event)
						{
							case AF_INCOMING_MSG_CMD:
								GenericApp_MessageMSGCB(MSGpkt);
								break;
							case ZDO_STATE_CHANGE:
									GenericApp_NwkState=(devStates_t)(MSGpkt->hdr.status);
									if(GenericApp_NwkState==DEV_ZB_COORD)
										{
											aps_AddGroup(GENERICAPP_ENDPOINT,&GenericApp_Group);
										}
									break;
						        default:
									break;
						}
					osal_msg_deallocate((uint8 *) MSGpkt);
					MSGpkt=(afIncomingMSGPacket_t *)osal_msg_receive(GenericApp_TaskID);
				}
			return (events ^SYS_EVENT_MSG);
		
		}
	return 0;
}
void GenericApp_MessageMSGCB(afIncomingMSGPacket_t * pkt)
{
	unsigned char buffer[10];
	switch(pkt->clusterId)
		{
			case GENERICAPP_CLUSTERID:
				osal_memcpy(buffer, pkt->cmd.Data,9);
        HalUARTWrite(0,buffer,9);
				break;
		}  
}