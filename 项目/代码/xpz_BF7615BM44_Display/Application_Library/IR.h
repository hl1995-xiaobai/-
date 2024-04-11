#ifndef __IR_H__
#define __IR_H__
/*******************************************************
IR发送用到了定时器0，使用时需要将定时时间设置为5ms
IR接收用到了定时器0，使用时需要将定时时间设置为100us
/******************************************************/
#include ".\CTK_Library\Config.h"
#include "INTRINS.H"

#define IR_SEND_OR_REC 0 		//1为发送，0为接收
#define CARRIER_SWITCH 1		//载波开关--1:开;0:关
#define CARRIER_DELAY_9MS 343	//载波延时9ms
#define CARRIER_DELAY_560US 21	//载波延时0.56ms
#define CARRIER_DELAY_420US 16	//载波延时0.42ms

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

extern uint EndCnt;   					//用于延时
extern uchar Key_Value;					//按键值
extern uchar Last_key;					//最后一次按键值
extern uchar Timer0_cnt;   				//完整码发送后开始计数
extern bit 	First_Reaptcode; 			//标示第一个连续码
extern bit Start_Flag;					//引导码标志
extern bit Repeat_Flag;					//连续码标志

extern uint Timer1_IR_ReceiveCount;   	//IR接收计算
extern bit ReceiveCount_Flag;   		//开始计数标志
extern uchar IR_Receive_Data[];			//IR接收缓存
extern uchar IR_Receive_Data_Cout;		//IR接收计数


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

/****************************非NEC_IR**********************************/
extern void IRSend_7bit(uchar dat);
extern void IRSend_2bit(uchar dat);
extern void IRSend_3bit_Start(uchar dat);
extern void IRSend_code_1(uchar custom,uchar dat);
extern void IRSend_KeyValue_1(uchar custom,uchar key_value);
/****************************非NEC_IR**********************************/


/****************************NEC_IR_接收**********************************/
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
/****************************NEC_IR_接收**********************************/
#endif