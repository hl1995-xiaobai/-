#ifndef _SM16306SJ_H_
#define _SM16306SJ_H_	

#include "Define.h"

#define NOP_TIM				1

#define SM16xx_SDI 			PB5
#define SM16xx_CLK			PB4
#define SM16xx_LE			PB3
#define SM16xx_OE			PB6

// LED_COM
#define Port_COM1			PE6
#define	Port_COM2			PE7
#define Port_COM3			PG0
#define Port_COM4			PG1

#define DISPLAY_BUFFER_SIZE 1



extern unsigned char idata  SM16xx_Dat[6] ; 
extern unsigned char idata	SM16xx_DatRs[6];

extern unsigned char idata	SM16xx_KeyTab[6];
extern unsigned char idata  SM16xx_KeyTabRS[6];

extern xdata uint16 r_SM16106;


extern void SM16xx_WriteAll(void);




extern void HuxiDeng(unsigned char in);

#define SM_SP(x,y)    SM16xx_DatRs[x+(y>>3)] |= (0x01<<(y&0x07))
#define SM_CP(x,y)	  SM16xx_DatRs[x+(y>>3)] &= ~(0x01<<(y&0x07))

#define LD_NL		0
#define LD_BL		2
#define LD_QL		10

#define COM_1		0
#define COM_2		2
#define COM_3		10


#define LD_K1		0
#define LD_K2       1
#define LD_K3		2
#define LD_K4       3
#define LD_K5       4
#define LD_k6		5


void SM16xx_Init(void);

void SM16xx_WriteAll(void);



		 				    
#endif
 


































