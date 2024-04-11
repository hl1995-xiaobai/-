#ifndef __BF7615AMXX_API_IIC_MASTER_H__
#define __BF7615AMXX_API_IIC_MASTER_H__

#include ".\CTK_Library\BF7615AMXX\BF7615AMXX_CTK.H"

#define IICM_PA_EN 			1 //IIC模拟主机，1:使能编译，0:不使能编译

#if IICM_PA_EN 

	#pragma message "编译，void IICM_Init(void)"
	
	#define SET_SDA()   DATAA |= 0x02
	#define CLR_SDA()   DATAE &= ~0x20
	#define OUT_SDA()   SET_PE5_PU_ON;SET_PE5_IO_OUT
	#define IN_SDA()    SET_PE5_PU_ON;SET_PE5_IO_IN
	#define SDA()       DATAE & 0x20

	#define SET_SCL()   DATAE |= 0x10
	#define CLR_SCL()   DATAE &= ~0x10
	#define OUT_SCL()   SET_PE4_PU_ON;SET_PE4_IO_OUT
	#define IN_SCL()    SET_PE4_PU_ON;SET_PE4_IO_IN
	
	#define NACK    1
	#define ACK     0



	#define NACK    1
	#define ACK     0

	extern void  Delay(uchar time); // unit: 10us
	extern void IICM_Init(void);
	extern void  Start();
	extern void  Stop();
	extern void  Respond(uchar ACKSignal);
	extern uchar ReceiveByte();
	extern bit   SendByteAndGetNACK(uchar dataToSend);
	extern void IICM_WriteDeviceFromData(uchar deviceAddr, uchar *dataSource, uchar lengthOfData);
	extern void IICM_ReadDeviceDataTo(uchar deviceAddr, uchar *target, uchar lengthOfData);
#endif

#endif