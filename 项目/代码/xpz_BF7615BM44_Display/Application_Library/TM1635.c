#include ".\CTK_Library\Config.h"
#include "TM1635.h"
#include ".\Project\Project.h"
#if CHIP_BF6916AX

	#include ".\CTK_Library\BF6916AX\BF6916AX.H"
	#include ".\CTK_Library\BF6916AX\BF6916AX_API.h"
	#include ".\CTK_Library\BF6916AX\BF6916AX_CTK.H"
	#include ".\CTK_Library\BF6916AX\BF6916AX_SetTouchFlag.h"

	#if (TRACEMODE == TRUE)
		#include ".\CTK_Library\BF6916AX\BF6916AX_TraceMode.h"
	#endif

#endif

#define TM1635_IO_INIT() SET_PC0_IO_OUT;SET_PC1_IO_OUT;SET_PC0_H;SET_PC1_H
#define SET_DIO_OUT()	SET_PC1_IO_OUT 
#define SET_DIO_IN()	SET_PC1_IO_IN 
#define SET_DIO()   	SET_PC1_H  
#define CLR_DIO()   	SET_PC1_L
#define SET_SCLK()  	SET_PC0_H
#define CLR_SCLK()  	SET_PC0_L
#define GET_ACK()  		GET_PC1

unsigned char code SEG_TAB_UC[12] = {0x77, 0x24, 0x3B, 0x3E, 0x6C, 0x5E, 0x5F, 0x34, 0x7F, 0x7E,0x5B,0x08};//0~9,E,-
unsigned char xdata DIS_TAB[4] = {0x00,0x00,0x00,0x00};	//(COM2)-(COM1)-(S4-S5-S6-S7-S8--bin(0.0.0.S8.S7.S6.S4.S5))-(S1-S2-S3-S9-S10--bin(000S1--S2.S3.S9.S10))
//-----------------------------------------------------------------//
//函数名称： void TM1635_Delay_us(uint us)
//函数功能： 延时为7us + (us-1)*3us
//输入参数： us
//输出参数： 无
//返 回 值： 无
//-----------------------------------------------------------------//
void TM1635_Delay_us(uint us) 
{ 
	for (; us > 0; us--)
	{	
		WDT_CTRL = 0x07;
	}
} 


//-----------------------------------------------------------------//
//函数名称： TM1635_I2CStart(void)
//函数功能： TM1635 Start开始信号 
//输入参数： 无
//输出参数： 无
//返 回 值： 无
//-----------------------------------------------------------------//
void TM1635_I2CStart(void) 
{ 
	SET_DIO(); 
	SET_SCLK(); 
	TM1635_Delay_us(2); 
	CLR_DIO(); 
	TM1635_Delay_us(2); 
	CLR_SCLK(); 
} 


//-----------------------------------------------------------------//
//函数名称： TM1635_I2Cask(void)
//函数功能： TM1635 获取ACK应答信号 
//输入参数： 无
//输出参数： 无
//返 回 值： 无
//-----------------------------------------------------------------// 
void TM1635_I2Cask(void)
{ 
	CLR_SCLK();  
	TM1635_Delay_us(5); 
	SET_DIO(); 
	TM1635_Delay_us(2); 
	SET_SCLK();
	SET_DIO_IN(); 
	while(GET_ACK());
	SET_DIO_OUT(); 
	CLR_SCLK(); 
} 

//-----------------------------------------------------------------//
//函数名称： void TM1635_I2CStop(void) 
//函数功能： TM1635 停止信号 
//输入参数： 无
//输出参数： 无
//返 回 值： 无
//-----------------------------------------------------------------// 
void TM1635_I2CStop(void) 
{ 
	CLR_SCLK(); 
	TM1635_Delay_us(2); 
	CLR_DIO(); 
	TM1635_Delay_us(2); 
	SET_SCLK(); 
	TM1635_Delay_us(2); 
	SET_DIO(); 
}

//-----------------------------------------------------------------//
//函数名称： void TM1635_I2CWrByte(unsigned char oneByte) 
//函数功能： TM1635 写一个字节
//输入参数： 无
//输出参数： 无
//返 回 值： 无
//-----------------------------------------------------------------//  
void TM1635_I2CWrByte(unsigned char oneByte) 
{ 
	unsigned char i; 
	for(i=0;i<8;i++) 
	{ 
		CLR_SCLK(); 
		if(oneByte&0x01) //低位在前 
		{ 
			SET_DIO();
		} 
		else 
		{ 
			CLR_DIO();
		} 
		TM1635_Delay_us(3); 
		oneByte=oneByte>>1; 
		SET_SCLK();
		TM1635_Delay_us(3); 
	} 
}

//-----------------------------------------------------------------//
//函数名称： void TM1635_ScanKey(unsigned char oneByte) 
//函数功能： TM1635 读按键
//输入参数： 无
//输出参数： 无
//返 回 值： 无
//-----------------------------------------------------------------// 
//unsigned char TM1635_ScanKey(void) 
//{ 
//	unsigned char rekey, i     ; 
//	TM1635_I2CStart(); 
//	TM1635_I2CWrByte(0x42); //读按键命令 
//	TM1635_I2Cask();
//	SET_DIO_IN();  
//	SET_DIO(); 
//	// 在读按键前拉高数据线 
//	for(i=0;i<8;i++) //从低位开始读 
//	{ 
//		SET_SCLK(); 
//		rekey=rekey>>1; 
//		TM1635_Delay_us(30); 
//		SET_SCLK(); 
//		if(GET_ACK()) 
//		{ 
//			rekey=rekey|0x80; 
//		}
//		else 
//		{ 
//			rekey=rekey|0x00; 
//		} 
//		TM1635_Delay_us(30); 
//	}
//	SET_DIO_OUT(); 
//	TM1635_I2Cask(); 
//	TM1635_I2CStop(); 
//	return (rekey); 
//}

//-----------------------------------------------------------------//
//函数名称： void TM1635_SmgDisplay(bit on_off,uchar *dis_tab,uchar light)  
//函数功能： TM1635 写显示寄存器
//输入参数： bit on_off:开关1为开0为关；uchar *dis_tab:显示数据;uchar light：亮度(0~7)；
//输出参数： 无
//返 回 值： 无
//-----------------------------------------------------------------// 
void TM1635_SmgDisplay(bit on_off,uchar *dis_tab,uchar light) 
{ 
	unsigned char i; 
	TM1635_I2CStart(); 
	TM1635_I2CWrByte(0x40); // 40H地址自加 44H固定地址模式 
	TM1635_I2Cask(); 
	TM1635_I2CStop(); 
	TM1635_I2CStart(); 
	TM1635_I2CWrByte(0xc0); //设置首地址， 
	TM1635_I2Cask(); 
	for(i=0;i<4;i++) //地址自加，不必每次都写地址 
	{ 
		TM1635_I2CWrByte(*(dis_tab+i)); //送数据 
		TM1635_I2Cask(); 
	} 
	TM1635_I2CStop(); 
	TM1635_I2CStart();
	if(on_off)
	{ 
		TM1635_I2CWrByte(0x88|light); //开显示 ，最大亮度
	} 
	else
	{
		TM1635_I2CWrByte(0x80|light); //关显示
	}
	TM1635_I2Cask(); 
	TM1635_I2CStop(); 
} 

//-----------------------------------------------------------------//
//函数名称： void TM1635_Init()
//函数功能： TM1635 初始化子程序
//输入参数： 无
//输出参数： 无
//返 回 值： 无
//-----------------------------------------------------------------// 
void TM1635_Init() 
{ 
	TM1635_IO_INIT();
	TM1635_SmgDisplay(LED_OnOff,DIS_TAB,LED_Light); 
}