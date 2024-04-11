//**********************************************************************************   
//********************   copyright(c) 2020, company   **************************   
//************************    All rights reserved    *******************************   
//*****************************  ---    ---  ************************************   
//**********************************************************************************                                              
//========================================================================= 
//  Project Name : MCU02                                                                                                                     
//  File    Name : BF7615BMXX_XXXX.h 
//  Date         : 2020.07.20                                                              
//  By           : xs                                                                 
//  Version      : V1.0                                 
//=========================================================================  

 
#ifndef __BF7615BMXX_XXXX_H__
#define __BF7615BMXX_XXXX_H__
/*  ----------------BYTE Register------------------  */
sfr	DATAB					= 0x80;
sfr	SP						= 0x81;
sfr	DPL						= 0x82;
sfr	DPH						= 0x83;
sfr	TIMER3_CFG				= 0x84;
sfr	TIMER3_SET_H			= 0x85;
sfr	TIMER3_SET_L			= 0x86;
sfr	PCON					= 0x87;
sfr	TCON					= 0x88;
sfr	TMOD					= 0x89;
sfr	TL0						= 0x8A;
sfr	TL1						= 0x8B;
sfr	TH0						= 0x8C;
sfr	TH1						= 0x8D;
sfr	SOFT_RST				= 0x8E;
sfr	DATAC					= 0x90;
sfr	WDT_CTRL				= 0x91;
sfr	WDT_EN					= 0x92;	
sfr	TIMER2_CFG				= 0x93;				   
sfr	TIMER2_SET_H			= 0x94;
sfr	TIMER2_SET_L			= 0x95;
sfr	REG_ADDR			= 0x96;
sfr	REG_DATA			= 0x97;
sfr	SCI_S1				= 0x98;//20-07-27
sfr	PWM0_L_L			= 0x99;
sfr	PWM0_L_H			= 0x9A;
sfr	PWM0_H_L			= 0x9B;
sfr	PWM0_H_H			= 0x9C;
sfr	PWM1_L_L			= 0x9D;
sfr	PWM1_L_H			= 0x9E;
sfr	PWM1_H_L			= 0x9F;
sfr	P2_XH					= 0xA0;//若使用到MOVX @Ri,A指令时，操作pdata区时，P2_XH需要清0
sfr	PWM1_H_H			= 0xA1;
sfr	PWM2_L_L			= 0xA2;
sfr	PWM2_L_H			= 0xA3;
sfr	PWM2_H_L			= 0xA4;
sfr	PWM2_H_H			= 0xA5;
sfr	PWM3_L_L			= 0xA6;
sfr	PWM3_L_H			= 0xA7;
sfr	IEN0					= 0xA8;
sfr	PWM3_H_L			= 0xA9;
sfr	PWM3_H_H			= 0xAA;
sfr	CSD_RAWDATAL	= 0xAB;
sfr	CSD_RAWDATAH	= 0xAC;
sfr	SYS_CLK_CFG		= 0xAD;
sfr	INT_PE_STAT		= 0xAE;
sfr	SCAN_START		= 0xAF;
sfr	DATAE					= 0xB0;
sfr	DP_CON				= 0xB1;
sfr	DP_MODE				= 0xB2;
sfr	SCAN_WIDTH		= 0xB3;
sfr	LED2_WIDTH		= 0xB4;
sfr	SPI_CFG1			= 0xB5;//20-07-27
sfr	SPI_CFG2			= 0xB6;//20-07-27
sfr	IPL0					= 0xB8;
sfr	DP_CON1				= 0xB9;
sfr	SCI_C2				= 0xBA;//20-07-27
sfr	SCI_C3				= 0xBB;//20-07-27
sfr	SCI_S2				= 0xBC;//20-07-27
sfr	SCI_D					= 0xBD;//20-07-27
sfr	SPI_STATE		= 0xBE;//20-07-27
sfr	SPI_SPID			= 0xBF;//20-07-27
sfr	DATAF					= 0xC0;
sfr	ADC_SPT				= 0xC1;
sfr	SCI_INT_CLR		= 0xC2;//20-07-27
sfr	ADC_SCAN_CFG	= 0xC3;
sfr	ADCCKC				= 0xC4;
sfr	ADC_RDATAH		= 0xC5;
sfr	ADC_RDATAL		= 0xC6;
sfr	EXINT_STAT		= 0xC7;
sfr	DATAG					= 0xC8;
sfr	CSD_START			= 0xC9;
sfr	PULL_I_SEL		= 0xCA;
sfr	SNS_SCAN_CFG1	= 0xCB;
sfr	SNS_SCAN_CFG2	= 0xCC;
sfr	SNS_SCAN_CFG3	= 0xCD;
sfr	SPROG_ADDR_H	= 0xCE;
sfr	SPROG_ADDR_L	= 0xCF;
sfr	PSW						= 0xD0;
sfr	SPROG_DATA		= 0xD1;
sfr	SPROG_CMD			= 0xD2;
sfr	SPROG_TIM			= 0xD3;
sfr	SPROG_RDATA		= 0xD4;
sfr	INT_POBO_STAT	= 0xD5;
sfr	UART1_BDL			= 0xD6;
sfr	UART1_CON1		= 0xD7;
sfr	DATAH					= 0xD8;
sfr	UART1_CON2		= 0xD9;
sfr	UART1_STATE		= 0xDA;
sfr	UART1_BUF			= 0xDB;
sfr	UART0_BDL			= 0xDC;
sfr	UART0_CON1		= 0xDD;
sfr	UART0_CON2		= 0xDE;
sfr	UART0_STATE		= 0xDF;
sfr	ACC						= 0xE0;
sfr	IRCON2				= 0xE1;
sfr	UART0_BUF			= 0xE2;
sfr	IICADD				= 0xE3;
sfr	IICBUF				= 0xE4;
sfr	IICCON				= 0xE5;
sfr	IEN1					= 0xE6;
sfr	IEN2					= 0xE7;
sfr	IICSTAT				= 0xE8;
sfr	IICBUFFER			= 0xE9;
sfr	TRISA					= 0xEA;
sfr	TRISB					= 0xEB;
sfr	TRISC					= 0xEC;
sfr	SCI_C1				= 0xED;//20-07-27
sfr	TRISE					= 0xEE;
sfr	TRISF					= 0xEF;
sfr	B							= 0xF0;
sfr	IRCON1				= 0xF1;
sfr	TRISG					= 0xF2;
sfr	IPL2					= 0xF4;
sfr	IPL1					= 0xF6;
sfr	TRISH					= 0xF7;
sfr	DATAA					= 0xF8;
sfr	PCD_BUF1			= 0xF9;
sfr	PCD_BUF2			= 0xFA;
sfr	PCD_CFG				= 0xFB;
sfr	PCD_CMD				= 0xFC;
sfr	PCD_CFG2			= 0xFD;
sfr	PCD_BIT_ER		= 0xFE;
sfr	PCD_CFG3			= 0xFF;
/*  ----------------BYTE Register------------------  */

/*  ----------------Bit Register------------------  */

/*  DATAA  */
sbit PA0  = DATAA^0;
sbit PA1  = DATAA^1;
sbit PA2  = DATAA^2;
sbit PA3  = DATAA^3;


/*  DATAB  */
sbit PB0  = DATAB^0;
sbit PB1  = DATAB^1;
sbit PB2  = DATAB^2;
sbit PB3  = DATAB^3;
sbit PB4  = DATAB^4;
sbit PB5  = DATAB^5;
sbit PB6  = DATAB^6;
sbit PB7  = DATAB^7;

/*  TCON  */
sbit IE0  = TCON^1;
sbit IE1  = TCON^3;
sbit TR0  = TCON^4;
sbit TF0  = TCON^5;
sbit TR1  = TCON^6;
sbit TF1  = TCON^7;


/*  DATAC  */
sbit PC0  = DATAC^0;
sbit PC1  = DATAC^1;
sbit PC2  = DATAC^2;
sbit PC3  = DATAC^3;
sbit PC4  = DATAC^4;
sbit PC5  = DATAC^5;
sbit PC6  = DATAC^6;
sbit PC7  = DATAC^7;

/*  IEN0  */
sbit EX0  = IEN0^0;
sbit ET0  = IEN0^1;
sbit EX1  = IEN0^2;
sbit ET1  = IEN0^3;
sbit EA  	= IEN0^7;


/*  DATAE  */
sbit PE0  = DATAE^0;
sbit PE1  = DATAE^1;
sbit PE2  = DATAE^2;
sbit PE3  = DATAE^3;
sbit PE4  = DATAE^4;
sbit PE5  = DATAE^5;
sbit PE6  = DATAE^6;
sbit PE7  = DATAE^7;


/*  IPL0  */
sbit PX0  = IPL0^0;
sbit PT0  = IPL0^1;
sbit PX2  = IPL0^2;
sbit PT1  = IPL0^3;

/*  DATAF  */
sbit PF0  = DATAF^0;
sbit PF1  = DATAF^1;
sbit PF2  = DATAF^2;
sbit PF3  = DATAF^3;
sbit PF4  = DATAF^4;
sbit PF5  = DATAF^5;
sbit PF6  = DATAF^6;
sbit PF7  = DATAF^7;

/*  DATAG  */
sbit PG0  = DATAG^0;
sbit PG1  = DATAG^1;
sbit PG2  = DATAG^2;
sbit PG3  = DATAG^3;



/*  PSW  */
sbit P   = PSW^0;
sbit F1  = PSW^1;
sbit OV  = PSW^2;
sbit RS0 = PSW^3;
sbit RS1 = PSW^4;
sbit F0  = PSW^5;
sbit AC  = PSW^6;
sbit CY  = PSW^7;


/*  DATAH  */
sbit PH0  = DATAH^0;
sbit PH1  = DATAH^1;
sbit PH2  = DATAH^2;
sbit PH3  = DATAH^3;
sbit PH4  = DATAH^4;
sbit PH5  = DATAH^5;
sbit PH6  = DATAH^6;
sbit PH7  = DATAH^7;

/*  IICSTAT  */
sbit IIC_RECOV  = IICSTAT^0;
sbit IIC_WCOL  	= IICSTAT^1;
sbit IIC_ACK 	 	= IICSTAT^2;
sbit IIC_BF  		= IICSTAT^3;
sbit IIC_AD  		= IICSTAT^4;
sbit IIC_RW  		= IICSTAT^5;
sbit IIC_STOP  	= IICSTAT^6;
sbit IIC_START  = IICSTAT^7;


/*  SCI_S1  */
sbit SCI_P  	= SCI_S1^0;
sbit SCI_F  	= SCI_S1^1;
sbit SCI_N  	= SCI_S1^2;
sbit SCI_RO 	= SCI_S1^3;
sbit SCI_I  	= SCI_S1^4;
sbit SCI_RI  	= SCI_S1^5;
sbit SCI_TF  	= SCI_S1^6;
sbit SCI_TE  	= SCI_S1^7;



/*  ----------------Bit Register------------------  */

#endif