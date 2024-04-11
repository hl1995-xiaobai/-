#ifndef __IR_H__
#define __IR_H__
/*******************************************************
IR�����õ��˶�ʱ��0��ʹ��ʱ��Ҫ����ʱʱ������Ϊ5ms
IR�����õ��˶�ʱ��0��ʹ��ʱ��Ҫ����ʱʱ������Ϊ100us
/******************************************************/
#include ".\CTK_Library\Config.h"
#include "INTRINS.H"

#define IR_SEND_OR_REC 0 		//1Ϊ���ͣ�0Ϊ����
#define CARRIER_SWITCH 1		//�ز�����--1:��;0:��
#define CARRIER_DELAY_9MS 343	//�ز���ʱ9ms
#define CARRIER_DELAY_560US 21	//�ز���ʱ0.56ms
#define CARRIER_DELAY_420US 16	//�ز���ʱ0.42ms

//#define IR			PC4
//#define SET_IR		PC4 =0
//#define CLR_IR		PC4 =1
//#define SET_IR_TX	TC4 =0
//#define SET_IR_RX	TC4 =1

//#define IR			PC4
//#define SET_IR		PC4 =0
//#define CLR_IR		PC4 =1
//#define SET_IR_TX	TC4 =0
//#define SET_IR_RX	TC4 =1

#define IR			GET_PD0
#define SET_IR		SET_PD0_H
#define CLR_IR		SET_PD0_L
#define SET_IR_TX	SET_PD0_IO_OUT
#define SET_IR_RX	SET_PD0_IO_IN


#define SET_ONE_LINE_RX_IN   
#define GET_IR_DATA GET_PD0


#define START_3BIT	0x03
#define CUSTOM_2BIT	0x03

extern uint EndCnt;   					//������ʱ
extern uchar Key_Value;					//����ֵ
extern uchar Last_key;					//���һ�ΰ���ֵ
extern uchar Timer0_cnt;   				//�����뷢�ͺ�ʼ����
extern bit 	First_Reaptcode; 			//��ʾ��һ��������
extern bit Start_Flag;					//�������־
extern bit Repeat_Flag;					//�������־

extern uint Timer1_IR_ReceiveCount;   	//IR���ռ���
extern bit ReceiveCount_Flag;   		//��ʼ������־
extern uchar IR_Receive_Data[];			//IR���ջ���
extern uchar IR_Receive_Data_Cout;		//IR���ռ���


extern void IR_Start();
extern void IRSend_Byte(uchar dat);
extern void IRSend_Opposite_Byte(uchar dat);
extern void IRSend_16Byte(uint dat);
extern void IR_EndPulse();
extern void IR_SendRepeat_Code();
extern void IRSend_code(uint custom,uchar dat);
extern void IRSend_KeyValue(uint custom,uchar key_value);
extern void Signal_Carrier(uint count);
extern void IR_Receive_Init(void);

/****************************��NEC_IR**********************************/
extern void IRSend_7bit(uchar dat);
extern void IRSend_2bit(uchar dat);
extern void IRSend_3bit_Start(uchar dat);
extern void IRSend_code_1(uchar custom,uchar dat);
extern void IRSend_KeyValue_1(uchar custom,uchar key_value);
/****************************��NEC_IR**********************************/


/****************************NEC_IR_����**********************************/
extern uint Send_Count1;
extern uint Send_Count2;
extern uint Send_Count3;
extern uchar Send_Byte1;
extern uchar Send_Byte2;

extern uint Receive_Count1;
extern uint Receive_Count3;
extern uint Receive_Count4;
extern uchar Receive_Count5;

extern bit Rec_Start_Flag;
extern bit Repeat_Flag;
extern bit Over_Flag;
extern bit Low_Flag;
extern bit Add_Flag;
extern uchar Bit_Flag;

extern  uchar Receive_Data_Buffer[];
extern void IR_Receive(void);
/****************************NEC_IR_����**********************************/
#endif