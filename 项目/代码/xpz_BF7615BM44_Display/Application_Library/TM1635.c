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
//�������ƣ� void TM1635_Delay_us(uint us)
//�������ܣ� ��ʱΪ7us + (us-1)*3us
//��������� us
//��������� ��
//�� �� ֵ�� ��
//-----------------------------------------------------------------//
void TM1635_Delay_us(uint us) 
{ 
	for (; us > 0; us--)
	{	
		WDT_CTRL = 0x07;
	}
} 


//-----------------------------------------------------------------//
//�������ƣ� TM1635_I2CStart(void)
//�������ܣ� TM1635 Start��ʼ�ź� 
//��������� ��
//��������� ��
//�� �� ֵ�� ��
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
//�������ƣ� TM1635_I2Cask(void)
//�������ܣ� TM1635 ��ȡACKӦ���ź� 
//��������� ��
//��������� ��
//�� �� ֵ�� ��
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
//�������ƣ� void TM1635_I2CStop(void) 
//�������ܣ� TM1635 ֹͣ�ź� 
//��������� ��
//��������� ��
//�� �� ֵ�� ��
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
//�������ƣ� void TM1635_I2CWrByte(unsigned char oneByte) 
//�������ܣ� TM1635 дһ���ֽ�
//��������� ��
//��������� ��
//�� �� ֵ�� ��
//-----------------------------------------------------------------//  
void TM1635_I2CWrByte(unsigned char oneByte) 
{ 
	unsigned char i; 
	for(i=0;i<8;i++) 
	{ 
		CLR_SCLK(); 
		if(oneByte&0x01) //��λ��ǰ 
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
//�������ƣ� void TM1635_ScanKey(unsigned char oneByte) 
//�������ܣ� TM1635 ������
//��������� ��
//��������� ��
//�� �� ֵ�� ��
//-----------------------------------------------------------------// 
//unsigned char TM1635_ScanKey(void) 
//{ 
//	unsigned char rekey, i     ; 
//	TM1635_I2CStart(); 
//	TM1635_I2CWrByte(0x42); //���������� 
//	TM1635_I2Cask();
//	SET_DIO_IN();  
//	SET_DIO(); 
//	// �ڶ�����ǰ���������� 
//	for(i=0;i<8;i++) //�ӵ�λ��ʼ�� 
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
//�������ƣ� void TM1635_SmgDisplay(bit on_off,uchar *dis_tab,uchar light)  
//�������ܣ� TM1635 д��ʾ�Ĵ���
//��������� bit on_off:����1Ϊ��0Ϊ�أ�uchar *dis_tab:��ʾ����;uchar light������(0~7)��
//��������� ��
//�� �� ֵ�� ��
//-----------------------------------------------------------------// 
void TM1635_SmgDisplay(bit on_off,uchar *dis_tab,uchar light) 
{ 
	unsigned char i; 
	TM1635_I2CStart(); 
	TM1635_I2CWrByte(0x40); // 40H��ַ�Լ� 44H�̶���ַģʽ 
	TM1635_I2Cask(); 
	TM1635_I2CStop(); 
	TM1635_I2CStart(); 
	TM1635_I2CWrByte(0xc0); //�����׵�ַ�� 
	TM1635_I2Cask(); 
	for(i=0;i<4;i++) //��ַ�Լӣ�����ÿ�ζ�д��ַ 
	{ 
		TM1635_I2CWrByte(*(dis_tab+i)); //������ 
		TM1635_I2Cask(); 
	} 
	TM1635_I2CStop(); 
	TM1635_I2CStart();
	if(on_off)
	{ 
		TM1635_I2CWrByte(0x88|light); //����ʾ ���������
	} 
	else
	{
		TM1635_I2CWrByte(0x80|light); //����ʾ
	}
	TM1635_I2Cask(); 
	TM1635_I2CStop(); 
} 

//-----------------------------------------------------------------//
//�������ƣ� void TM1635_Init()
//�������ܣ� TM1635 ��ʼ���ӳ���
//��������� ��
//��������� ��
//�� �� ֵ�� ��
//-----------------------------------------------------------------// 
void TM1635_Init() 
{ 
	TM1635_IO_INIT();
	TM1635_SmgDisplay(LED_OnOff,DIS_TAB,LED_Light); 
}