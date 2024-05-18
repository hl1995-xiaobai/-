#ifndef _CMD_H_
#define _CMD_H_


#define MAGIC_NUMBER 							0xA5
#define CRC16_INIT 								0xFFFF


// ������궨��
#define CMD_QUERY_DEVICE_STATUS 				0x01		/*��ѯ�豸״̬			��λ��������λ��							*/
#define CMD_RESPONSE_DEVICE_STATUS 				0x31		/*��ѯ�豸�Ĺ̼��汾���豸����״̬���¶�,�豸ID��λ��   				      	*/

#define CMD_STANDARD_WASH 						0x02		/*��׼ϴ��				��λ��������λ��							*/
#define CMD_RESPONSE_STANDARD_WASH 				0x32		/*��λ���·���ϴ���ݡ�����ִ��ϴ��										*/

#define CMD_MAINTENANCE_FUNCTION_TEST 			0x03		/*ά�����ܲ���			��λ��������λ��							*/
#define CMD_RESPONSE_MAINTENANCE_TEST 			0x33		/*��λ���·����Թ��ܣ���λ��ִ�й���										*/

#define CMD_ERROR_REPORT 						0x04		/*ά�����ܲ���			��λ��������λ��							*/
#define CMD_RESPONSE_ERROR_REPORT 				0x34		/*��λ���ϴ�������Ϣ����λ��������Ϣ���޸�									*/

#define CMD_FUNCTION_SETTING 					0x05		/*�����趨				��λ��������λ��							*/
#define CMD_RESPONSE_FUNCTION_SETTING 			0x35		/*��λ���������趨���ݣ��򿪻�ر�ϴƿ���Ĺ���								*/

#define CMD_PARAMETER_CALIBRATION 				0x06		/*����У׼				��λ��������λ��							*/
#define CMD_RESPONSE_PARAMETER_CALIBRATION 		0x36		/*��λ����У׼��������λ��ִ��У׼����									*/

#define CMD_DRYING 								0x07		/*���				��λ��������λ��							*/
#define CMD_RESPONSE_DRYING 					0x37		/*��λ������ɲ�������λ��ִ�к�ɲ���									*/


/*��ͷ*/
typedef struct{
	uint8  magic;				/*ħ��*/
	uint8  packet_id;			/*��ID*/
	uint8  length;				/*������*/
	uint8  CommandCode;			/*������*/
}CMD_HEAD_T,*PCMD_HEAD_T;


typedef struct{
	uint8 VersionNumber;					// ��λ���̼��汾��
	uint16 crc;								// ���ֽڵ�CRCУ��ֵ
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
































