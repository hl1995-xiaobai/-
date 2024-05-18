#ifndef _SM16306SJ_H_
#define _SM16306SJ_H_	

#include "Define.h"

#define NOP_TIM				1

#define SM16xx_SDI 			PG1			//LED_DI
#define SM16xx_CLK			PG0			//LED_DCK
#define SM16xx_LE			PF5			//LED_LAT
#define SM16xx_OE			PE2			//GCLK

// LED_COM
#define Port_COM1			PH2
#define	Port_COM2			PH1

#define Port_SW1			PB5
#define	Port_SW2			PB4
#define Port_SW3			PB3
#define	Port_SW4			PB2
#define Port_SW5			PB1
#define	Port_SW6			PB0
#define Port_SW7			PA1
#define	Port_SW8			PA0
#define	Port_SW9			PH0
#define Port_SW10			PG3
#define	Port_SW11			PG2
#define Port_SW12			PE7
#define	Port_SW13			PE6
#define	Port_HandMove		PE1



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
 


































