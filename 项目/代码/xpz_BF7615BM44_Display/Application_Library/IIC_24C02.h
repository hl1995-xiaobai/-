#ifndef __BF7613AMXX_API_IIC_24C02_H__
#define __BF7613AMXX_API_IIC_24C02_H__

#define IIC_24C02 		0//24C02读写，1:使能编译，0:不使能编译，此功能在有EEPROM功能芯片上有效

#if IIC_24C02 

	#define SET_SDA()   DATAC |= 0x20
	#define CLR_SDA()   DATAC &= ~0x20
	#define OUT_SDA()   SET_PC5_OD_ON;SET_PC5_PU_ON;TRISC &= ~0x20
	#define IN_SDA()    SET_PC5_OD_ON;SET_PC5_PU_ON;TRISC |= 0x20
	#define SDA()       DATAC & 0x20

	#define SET_SCL()   DATAC |= 0x10
	#define CLR_SCL()   DATAC &= ~0x10
	#define OUT_SCL()   SET_PC4_OD_ON;SET_PC4_PU_ON;TRISC &= ~0x10
	#define IN_SCL()    SET_PC4_OD_ON;SET_PC4_PU_ON;TRISC |= 0x10



	#define NACK    1
	#define ACK     0

	extern void  IICM_Init();
	extern void  DelayMilliSeconds(uint _milliSec);
	extern void  Delay(uchar time);
	extern void  Start();
	extern void  Stop();
	extern void  Respond(uchar ACKSignal);
	extern uchar ReceiveByte();
	extern bit   SendByteAndGetNACK(uchar dataToSend);

	extern void IICM_WriteDeviceFromData_24C02(uchar deviceAddr, uchar *dataSource, uchar lengthOfData,uchar FormNByte);
	extern void IICM_ReadDeviceDataTo_24C02(uchar deviceAddr, uchar *target, uchar lengthOfData,uchar FormNByte);

	extern void IICM_CurrentAddressRead_24C02(uchar deviceAddr,uchar *target, uchar lengthOfData);
	extern void IICM_RandomRead_24C02(uchar deviceAddr, uchar wordAddr,uchar *target, uchar lengthOfData);
	extern void IICM_SequentialRead_24C02(uchar deviceAddr, uchar wordAddr,uchar *target, uchar lengthOfData);

	extern void IICM_ByteWrite_24C02(uchar deviceAddr,uchar wordAddr, uchar *dataSource, uchar lengthOfData);
	extern void IICM_PageWrite_24C02(uchar deviceAddr,uchar wordAddr, uchar *dataSource, uchar lengthOfData);
#endif

#endif