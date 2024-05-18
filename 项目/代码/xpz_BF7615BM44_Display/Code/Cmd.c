#include "include.h"

#include "Cmd.h"


#define CMD_READ_DATA_SIZE 32
#define CMD_SEND_DATA_SIZE 20


static xdata uint8 m_CmdReadBuf[CMD_READ_DATA_SIZE] 	= {0};
static xdata uint8 m_CmdReadCount 						= 0;

static xdata uint8 m_CmdSendBuf[CMD_SEND_DATA_SIZE] 	= {0};
static xdata uint8 m_CmdSendCount 						= 0;
static xdata uint8 m_CmdSendLen 						= 0;

static xdata PCMD_HEAD_T m_CmdSendHead = 0;



static xdata uint16 		   m_crc16;



void CmdInit(void){
	memset(m_CmdReadBuf, 0, CMD_READ_DATA_SIZE);
	m_CmdReadCount = 0;
	memset(m_CmdSendBuf, 0, CMD_SEND_DATA_SIZE);
	m_CmdSendCount = 0;
	m_CmdSendLen = 0;
}


uint8 CmdGetSendChr(uint8* out){
	if(m_CmdSendLen == 0) return FALSE;

	if(m_CmdSendCount >= m_CmdSendLen ){
		m_CmdSendLen = 0;
		m_CmdSendCount = 0;
		return FALSE;
	}

	*out = m_CmdSendBuf[m_CmdSendCount++];

	return TRUE;

}

void CmdRecv(uint8 in){

	if(m_CmdReadCount >= CMD_READ_DATA_SIZE) return;

	if((m_CmdReadCount == 0) && (in != 0x5a)){
		m_CmdReadCount = 0;
		return;
	}
	else if((m_CmdReadCount == 1) && (in != 0xa5)){
		m_CmdReadCount = 0;
		return;
	}

	m_CmdReadBuf[m_CmdReadCount++] = in;

	
}

void CmdCloseRecvData(uint8 in){
	//memset(m_CmdReadBuf, 0, CMD_READ_DATA_SIZE);
	m_CmdReadCount = 0;
	UART1_BUF = in;
}


void CmdRecvPool(){

#if(0)


	if((m_CmdReadCount == 1) && (m_CmdReadBuf[0] != 0x5a)){
		m_CmdReadCount = 0;
		return;
	}
	else if((m_CmdReadCount == 2) && (m_CmdReadBuf[1]  != 0xa5)){
		m_CmdReadCount = 0;
		return;
	}
	
	if(m_CmdReadCount < 29 )		return;

	//g_SysHardware.SysCnt = 0;
	
	m_CmdRecv = (PCMD_READ_T)(m_CmdReadBuf + 2);

	CmdSend();
	
//	m_crc16 = CRC16_Modbus(m_CmdReadBuf,27);

	if(m_crc16 == m_CmdRecv->crc16){
		g_View.VersionYearP 		= m_CmdRecv->VersionYear;
		g_View.VersionMonthP 		= m_CmdRecv->VersionMonth;
		g_View.VersionDayP 			= m_CmdRecv->VersionDay;

		if(g_View.buzzer == m_CmdRecv->buzzer ){
			g_View.buzzer = 0;
		}
		
//		SteamOvenCmdRecv(&m_CmdRecv->SteamOven);
//		RangeHoodCmdRecv(&m_CmdRecv->RangeHood);
	}
	else{
		//printf("Err:%04X,%04X\n", m_crc16, m_CmdRecv->crc16);
		m_crc16 = 0;
	}


	memset(m_CmdReadBuf, 0, CMD_READ_DATA_SIZE);
	m_CmdReadCount = 0;

#endif
	
}


/*²éÑ¯Éè±¸×´Ì¬*/
void CmdSendDeviceStatusQuery(){
	PCMD_QUERY_DEVICE_STATUS_T cmd_query_device_status = 0;

	memset(m_CmdSendBuf, 0, CMD_SEND_DATA_SIZE);
	
	(PCMD_HEAD_T)m_CmdSendHead = (PCMD_HEAD_T)(m_CmdSendBuf);

	m_CmdSendHead->magic = MAGIC_NUMBER;

	m_CmdSendHead->packet_id = g_View.packet_id_query_device_status;

	g_View.packet_id_query_device_status ++;

	if(g_View.packet_id_query_device_status > 0x10){
		g_View.packet_id_query_device_status = 0;
	}

	m_CmdSendHead->length = sizeof(CMD_HEAD_T) + sizeof(CMD_QUERY_DEVICE_STATUS_T);

	m_CmdSendHead->CommandCode = CMD_QUERY_DEVICE_STATUS;

	cmd_query_device_status = (PCMD_QUERY_DEVICE_STATUS_T)(m_CmdSendBuf + sizeof(CMD_HEAD_T));


//	m_CmdSend->crc16 = CRC16_Modbus(m_CmdSendBuf,12);

	m_CmdSendLen = m_CmdSendHead->length;

	m_CmdSendCount = 0;
		
	UART0_BUF = m_CmdSendBuf[m_CmdSendCount++] ;
}


void CmdSend(){

#if(0)

	//if(Uart0_Send_Flag){  Uart0_Send_Flag = 0;

	//memset(m_CmdSendBuf, 0, CMD_SEND_DATA_SIZE);

	m_CmdSendBuf[0] = 0x5a;
	m_CmdSendBuf[1] = 0xa5;
	
	m_CmdSend = (PCMD_SEND_T)(m_CmdSendBuf + 2);

	m_CmdSend->PowerOn 		= g_View.PowerOn;
	m_CmdSend->buzzer 		= g_View.buzzer;

//	SteamOvenCmdSend(&m_CmdSend->SteamOven);
//	RangeHoodCmdSend(&m_CmdSend->RangeHood);
	
//	m_CmdSend->crc16 = CRC16_Modbus(m_CmdSendBuf,12);

	m_CmdSendLen = 12 + 2;
	m_CmdSendCount = 0;
		
	UART0_BUF=m_CmdSendBuf[m_CmdSendCount++] ;

#endif	
	
}


void CmdSend1sLoop(){

	
}























