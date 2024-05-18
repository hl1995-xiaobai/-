/*************************************************************
//文 件 名：TM1640.h
//文件描述：LED驱动芯片TM1640接口定义
//编 写 者：wxh
//创建日期：2010-04-09 14:50
//版 本 号：1.0
//修改纪录：
**************************************************************/
#ifndef _TM1640_H_
#define _TM1640_H_


#define CFG_DATA_CMD_SETTING    0x44
#define CFG_BRIGHTNESS          7

extern void TM1640_Init        (void);
extern void TM1640_SendAddrDat (unsigned char addr,unsigned char dat);
extern void TM1640_Switch      (unsigned char flag);


#endif