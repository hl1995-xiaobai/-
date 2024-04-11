#include "Include.h"
#include "Config.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Define.h"
#include "SM16306SJ.h"

//#include "View.h"


#define NOP_TIM 1

unsigned char idata SM16xx_Dat[6];
unsigned char idata SM16xx_DatRs[6];

unsigned char idata SM16xx_KeyTab[6];
unsigned char idata SM16xx_KeyTabRS[6];

uint8 KeyScan_Step;

xdata uint16 r_SM16106 = 0x0000;



void Delay_NOP(uint8_t Nop_Cnt) {
	while (Nop_Cnt > 0)
		{
			Nop_Cnt--;
		}
}

void SM16xx_WriteOneByte(uint16_t Dat_OneByte) {
	uint8_t i;
	SM16xx_CLK = 0;
	Delay_NOP(NOP_TIM);
	for (i = 0; i < 16; i++)
		{
			SM16xx_CLK = 0;
			if (Dat_OneByte & 0x8000) {
				SM16xx_SDI = 1;
			} else {
				SM16xx_SDI = 0;
			}
			Dat_OneByte = Dat_OneByte << 1;
			SM16xx_CLK = 1;
			Delay_NOP(NOP_TIM);
		}
	SM16xx_CLK = 0;
}

unsigned char SM16xx_WriteAll_Cnt = 0;
unsigned char SM16xx_ScanCNT = 0;
unsigned char SM16xx_Step = 0;
unsigned char KeyScan_Step = 0;


unsigned char HuXiDengRunStep = 0;
unsigned char HuXiDengRunTimeBasicCnt = 0;
unsigned char HuXiDengRunDutyCnt = 0;
unsigned char HuXiDengRunDuty = 0;


void SM16xx_Init(void) {
	
	memset(pSM16106, 0, sizeof(SM16106_T));
	
	SET_PB3_IO_OUT;
	SET_PB6_IO_OUT;
	SET_PB4_IO_OUT;
	SET_PB5_IO_OUT;
	
	SM16xx_LE = 0;
	SM16xx_OE = 0;
	SM16xx_CLK = 0;
	SM16xx_SDI = 0;
	
	SET_PE6_IO_OUT;
	SET_PE7_IO_OUT;
	SET_PG0_IO_OUT;
	SET_PG1_IO_OUT;

#if(0)			
	Port_COM1 = 1;
	Port_COM2 = 1;
	Port_COM3 = 1;
	Port_COM4 = 1;
#endif

#if(1)
	Port_COM1 = 0;
	Port_COM2 = 0;
	Port_COM3 = 0;
	Port_COM4 = 0;
#endif	
	
}



void SM16xx_WriteAll(void){
		
		SM16xx_OE = 1;
		SM16xx_LE = 1;

//		SM16xx_WriteOneByte(r_SM16106);

		SM16xx_WriteOneByte(0xFFFF);
		
		SM16xx_LE = 0;
			
		SM16xx_OE = 0;
} 






 
