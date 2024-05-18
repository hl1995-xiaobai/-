#ifndef _CMD_H_
#define _CMD_H_


#define MAGIC_NUMBER 							0xA5
#define CRC16_INIT 								0xFFFF


// 命令码宏定义
#define CMD_QUERY_DEVICE_STATUS 				0x01		/*查询设备状态			上位机发给下位机							*/
#define CMD_RESPONSE_DEVICE_STATUS 				0x31		/*查询设备的固件版本、设备工作状态，温度,设备ID，位置   				      	*/

#define CMD_STANDARD_WASH 						0x02		/*标准洗涤				上位机发给下位机							*/
#define CMD_RESPONSE_STANDARD_WASH 				0x32		/*上位机下发清洗数据。主板执行洗涤										*/

#define CMD_MAINTENANCE_FUNCTION_TEST 			0x03		/*维保功能测试			上位机发给下位机							*/
#define CMD_RESPONSE_MAINTENANCE_TEST 			0x33		/*上位机下发测试功能，下位机执行功能										*/

#define CMD_ERROR_REPORT 						0x04		/*维保功能测试			上位机发给下位机							*/
#define CMD_RESPONSE_ERROR_REPORT 				0x34		/*下位机上传错误信息，上位机保存信息并修复									*/

#define CMD_FUNCTION_SETTING 					0x05		/*功能设定				上位机发给下位机							*/
#define CMD_RESPONSE_FUNCTION_SETTING 			0x35		/*上位机发功能设定数据，打开或关闭洗瓶机的功能								*/

#define CMD_PARAMETER_CALIBRATION 				0x06		/*参数校准				上位机发给下位机							*/
#define CMD_RESPONSE_PARAMETER_CALIBRATION 		0x36		/*上位机发校准参数，下位机执行校准操作									*/

#define CMD_DRYING 								0x07		/*烘干				上位机发给下位机							*/
#define CMD_RESPONSE_DRYING 					0x37		/*上位机发烘干参数，下位机执行烘干操作									*/


/*包头*/
typedef struct{
	uint8  magic;				/*魔数*/
	uint8  packet_id;			/*包ID*/
	uint8  length;				/*包长度*/
	uint8  CommandCode;			/*命令码*/
}CMD_HEAD_T,*PCMD_HEAD_T;


typedef struct{
	uint8 VersionNumber;					// 上位机固件版本号
	uint16 crc;								// 两字节的CRC校验值
}CMD_QUERY_DEVICE_STATUS_T,*PCMD_QUERY_DEVICE_STATUS_T;



void CmdInit(void);
uint8 CmdGetSendChr(uint8* out);
void CmdRecv(uint8 in);
void CmdCloseRecvData(uint8 in);
void CmdRecvPool();
void CmdSendDeviceStatusQuery();
void CmdSend();
void CmdSend1sLoop();




#endif
































