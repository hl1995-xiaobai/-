#ifndef	__LED_H
#define __LED_H


typedef struct{

	uint8 LedCom;

}LED_DATA_T;



void Led_init();

void Led_All_Open();

void Led_All_Close();




void Led_100usPool(uint8 area,uint8 brightness);



extern volatile LED_DATA_T m_LedData;


#endif



















