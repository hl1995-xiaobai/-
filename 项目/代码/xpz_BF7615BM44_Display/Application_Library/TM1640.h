/*************************************************************
//�� �� ����TM1640.h
//�ļ�������LED����оƬTM1640�ӿڶ���
//�� д �ߣ�wxh
//�������ڣ�2010-04-09 14:50
//�� �� �ţ�1.0
//�޸ļ�¼��
**************************************************************/
#ifndef _TM1640_H_
#define _TM1640_H_


#define CFG_DATA_CMD_SETTING    0x44
#define CFG_BRIGHTNESS          7

extern void TM1640_Init        (void);
extern void TM1640_SendAddrDat (unsigned char addr,unsigned char dat);
extern void TM1640_Switch      (unsigned char flag);


#endif