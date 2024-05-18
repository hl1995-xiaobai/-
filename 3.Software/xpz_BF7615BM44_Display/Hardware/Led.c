#include "include.h"

#include "Led.h"





#if(0)

typedef struct{

	uint8 LedCom;

}LED_DATA_T;

#endif

//static LED_DATA_T m_LedData;
volatile LED_DATA_T m_LedData;


void Led_init(){

	memset(&m_LedData, 0, sizeof(LED_DATA_T));

	memset(&g_DisplayLed, 0, sizeof(DISPLAY_LED_T));

//	memset(&g_KeyCode,0,sizeof(KEY_CODE_T));
	

}



void Led_All_Open(){
	Port_COM1 = 0;
	Port_COM2 = 0;

	Port_SW1 = 0;			
	Port_SW2 = 0;		
	Port_SW3 = 0;		
	Port_SW4 = 0;			
	Port_SW5 = 0;			
	Port_SW6 = 0;			
	Port_SW7 = 0;		
	Port_SW8 = 0;		
	Port_SW9 = 0;		
	Port_SW10 = 0;			
	Port_SW11 = 0;
	Port_SW12 = 0;			
	Port_SW13 = 0;
	Port_HandMove = 0;

	r_SM16106 = 0XFFFF;

	SM16xx_WriteAll();
	
	

}

void Led_All_Close(){
	Port_COM1 = 1;
	Port_COM2 = 1;

	Port_SW1 = 1;			
	Port_SW2 = 1;		
	Port_SW3 = 1;		
	Port_SW4 = 1;			
	Port_SW5 = 1;			
	Port_SW6 = 1;			
	Port_SW7 = 1;		
	Port_SW8 = 1;		
	Port_SW9 = 1;		
	Port_SW10 = 1;			
	Port_SW11 = 1;
	Port_SW12 = 1;			
	Port_SW13 = 1;
	Port_HandMove = 1;

	memset(pSM16106, 0, sizeof(SM16106_T));

	SM16xx_WriteAll();
	
	

}



#if(0)

void Led_100usPool(uint8 area,uint8 brightness){


	if(g_View.BrightnessTime[area] > 10){
		g_View.BrightnessTime[area] = 0;
	}else{
		g_View.BrightnessTime[area] ++;
	}

	if(g_View.BrightnessTime[area] == brightness){
		Led_All_Close();
	}else if(g_View.BrightnessTime[area] == 0){
		Led_All_Close();

		if(m_LedData.LedCom == AREA_POWER){
		Port_COM1 = 1;
		Port_COM2 = 1;

		Port_SW1 = 0;			
		Port_SW2 = 1;		
		Port_SW3 = 1;		
		Port_SW4 = 1;			
		Port_SW5 = 1;			
		Port_SW6 = 1;			
		Port_SW7 = 1;		
		Port_SW8 = 1;		
		Port_SW9 = 1;		
		Port_SW10 = 1;			
		Port_SW11 = 1;
		Port_SW12 = 1;			
		Port_SW13 = 1;
		Port_HandMove = 1;

		memset(pSM16106, 0, sizeof(SM16106_T));

		if(area == AREA_POWER){
			pSM16106->LED_OUT0 = g_DisplayLed.v_f.key_power_led;
			pSM16106->LED_OUT1 = g_DisplayLed.v_f.key_power_led;
			pSM16106->LED_OUT2 = g_DisplayLed.v_f.key_power_led;
			pSM16106->LED_OUT3 = g_DisplayLed.v_f.key_power_led;
			pSM16106->LED_OUT4 = g_DisplayLed.v_f.key_power_led;
			pSM16106->LED_OUT5 = g_DisplayLed.v_f.key_power_led;
			pSM16106->LED_OUT6 = g_DisplayLed.v_f.key_power_led;
			pSM16106->LED_OUT7 = g_DisplayLed.v_f.key_power_led;
			pSM16106->LED_OUT8 = g_DisplayLed.v_f.key_power_led;
			pSM16106->LED_OUT9 = g_DisplayLed.v_f.key_power_led;
			pSM16106->LED_OUT10 = g_DisplayLed.v_f.key_power_led;
		}

		SM16xx_WriteAll();
		
	}

	else if(m_LedData.LedCom == AREA_DOOR){
		Port_COM1 = 1;
		Port_COM2 = 1;

		Port_SW1 = 1;			
		Port_SW2 = 0;		
		Port_SW3 = 1;		
		Port_SW4 = 1;			
		Port_SW5 = 1;			
		Port_SW6 = 1;			
		Port_SW7 = 1;		
		Port_SW8 = 1;		
		Port_SW9 = 1;		
		Port_SW10 = 1;			
		Port_SW11 = 1;
		Port_SW12 = 1;			
		Port_SW13 = 1;
		Port_HandMove = 1;

		memset(pSM16106, 0, sizeof(SM16106_T));

		if(area == AREA_DOOR){
			pSM16106->LED_OUT0 = g_DisplayLed.v_f.key_door_led;
			pSM16106->LED_OUT1 = g_DisplayLed.v_f.key_door_led;
			pSM16106->LED_OUT2 = g_DisplayLed.v_f.key_door_led;
			pSM16106->LED_OUT3 = g_DisplayLed.v_f.key_door_led;
			pSM16106->LED_OUT4 = g_DisplayLed.v_f.key_door_led;
			pSM16106->LED_OUT5 = g_DisplayLed.v_f.key_door_led;
			pSM16106->LED_OUT6 = g_DisplayLed.v_f.key_door_led;
			pSM16106->LED_OUT7 = g_DisplayLed.v_f.key_door_led;
			pSM16106->LED_OUT8 = g_DisplayLed.v_f.key_door_led;
			pSM16106->LED_OUT9 = g_DisplayLed.v_f.key_door_led;
			pSM16106->LED_OUT10 = g_DisplayLed.v_f.key_door_led;
		}

		

		SM16xx_WriteAll();
	}

	else if(m_LedData.LedCom == AREA_A){
		Port_COM1 = 1;
		Port_COM2 = 1;

		Port_SW1 = 1;			
		Port_SW2 = 1;		
		Port_SW3 = 0;		
		Port_SW4 = 1;			
		Port_SW5 = 1;			
		Port_SW6 = 1;			
		Port_SW7 = 1;		
		Port_SW8 = 1;		
		Port_SW9 = 1;		
		Port_SW10 = 1;			
		Port_SW11 = 1;
		Port_SW12 = 1;			
		Port_SW13 = 1;
		Port_HandMove = 1;

		memset(pSM16106, 0, sizeof(SM16106_T));

		pSM16106->LED_OUT0 = g_DisplayLed.v_f.key_A_led;
		pSM16106->LED_OUT1 = g_DisplayLed.v_f.key_A_led;
		pSM16106->LED_OUT2 = g_DisplayLed.v_f.key_A_led;
		pSM16106->LED_OUT3 = g_DisplayLed.v_f.key_A_led;
		pSM16106->LED_OUT4 = g_DisplayLed.v_f.key_A_led;
		pSM16106->LED_OUT5 = g_DisplayLed.v_f.key_A_led;
		pSM16106->LED_OUT6 = g_DisplayLed.v_f.key_A_led;
		pSM16106->LED_OUT7 = g_DisplayLed.v_f.key_A_led;
		pSM16106->LED_OUT8 = g_DisplayLed.v_f.key_A_led;
		pSM16106->LED_OUT9 = g_DisplayLed.v_f.key_A_led;
		pSM16106->LED_OUT10 = g_DisplayLed.v_f.key_A_led;
		pSM16106->LED_OUT11 = g_DisplayLed.v_f.key_A_led;

		SM16xx_WriteAll();
	}

	else if(m_LedData.LedCom == AREA_B){
		Port_COM1 = 1;
		Port_COM2 = 1;

		Port_SW1 = 1;			
		Port_SW2 = 1;		
		Port_SW3 = 1;		
		Port_SW4 = 0;			
		Port_SW5 = 1;			
		Port_SW6 = 1;			
		Port_SW7 = 1;		
		Port_SW8 = 1;		
		Port_SW9 = 1;		
		Port_SW10 = 1;			
		Port_SW11 = 1;
		Port_SW12 = 1;			
		Port_SW13 = 1;
		Port_HandMove = 1;

		memset(pSM16106, 0, sizeof(SM16106_T));

		pSM16106->LED_OUT0 = g_DisplayLed.v_f.key_B_led;
		pSM16106->LED_OUT1 = g_DisplayLed.v_f.key_B_led;
		pSM16106->LED_OUT2 = g_DisplayLed.v_f.key_B_led;
		pSM16106->LED_OUT3 = g_DisplayLed.v_f.key_B_led;
		pSM16106->LED_OUT4 = g_DisplayLed.v_f.key_B_led;
		pSM16106->LED_OUT5 = g_DisplayLed.v_f.key_B_led;
		pSM16106->LED_OUT6 = g_DisplayLed.v_f.key_B_led;
		pSM16106->LED_OUT7 = g_DisplayLed.v_f.key_B_led;
		pSM16106->LED_OUT8 = g_DisplayLed.v_f.key_B_led;
		pSM16106->LED_OUT9 = g_DisplayLed.v_f.key_B_led;
		pSM16106->LED_OUT10 = g_DisplayLed.v_f.key_B_led;
		pSM16106->LED_OUT11 = g_DisplayLed.v_f.key_B_led;

		SM16xx_WriteAll();
	}

	else if(m_LedData.LedCom == AREA_C){
		Port_COM1 = 1;
		Port_COM2 = 1;

		Port_SW1 = 1;			
		Port_SW2 = 1;		
		Port_SW3 = 1;		
		Port_SW4 = 1;			
		Port_SW5 = 0;			
		Port_SW6 = 1;			
		Port_SW7 = 1;		
		Port_SW8 = 1;		
		Port_SW9 = 1;		
		Port_SW10 = 1;			
		Port_SW11 = 1;
		Port_SW12 = 1;			
		Port_SW13 = 1;
		Port_HandMove = 1;

		memset(pSM16106, 0, sizeof(SM16106_T));

		pSM16106->LED_OUT0 = g_DisplayLed.v_f.key_C_led;
		pSM16106->LED_OUT1 = g_DisplayLed.v_f.key_C_led;
		pSM16106->LED_OUT2 = g_DisplayLed.v_f.key_C_led;
		pSM16106->LED_OUT3 = g_DisplayLed.v_f.key_C_led;
		pSM16106->LED_OUT4 = g_DisplayLed.v_f.key_C_led;
		pSM16106->LED_OUT5 = g_DisplayLed.v_f.key_C_led;
		pSM16106->LED_OUT6 = g_DisplayLed.v_f.key_C_led;
		pSM16106->LED_OUT7 = g_DisplayLed.v_f.key_C_led;
		pSM16106->LED_OUT8 = g_DisplayLed.v_f.key_C_led;
		pSM16106->LED_OUT9 = g_DisplayLed.v_f.key_C_led;
		pSM16106->LED_OUT10 = g_DisplayLed.v_f.key_C_led;
		pSM16106->LED_OUT11 = g_DisplayLed.v_f.key_C_led;

		SM16xx_WriteAll();
	}

	else if(m_LedData.LedCom == AREA_D){
		Port_COM1 = 1;
		Port_COM2 = 1;

		Port_SW1 = 1;			
		Port_SW2 = 1;		
		Port_SW3 = 1;		
		Port_SW4 = 1;			
		Port_SW5 = 1;			
		Port_SW6 = 0;			
		Port_SW7 = 1;		
		Port_SW8 = 1;		
		Port_SW9 = 1;		
		Port_SW10 = 1;			
		Port_SW11 = 1;
		Port_SW12 = 1;			
		Port_SW13 = 1;
		Port_HandMove = 1;

		memset(pSM16106, 0, sizeof(SM16106_T));

		pSM16106->LED_OUT0 = g_DisplayLed.v_f.key_D_led;
		pSM16106->LED_OUT1 = g_DisplayLed.v_f.key_D_led;
		pSM16106->LED_OUT2 = g_DisplayLed.v_f.key_D_led;
		pSM16106->LED_OUT3 = g_DisplayLed.v_f.key_D_led;
		pSM16106->LED_OUT4 = g_DisplayLed.v_f.key_D_led;
		pSM16106->LED_OUT5 = g_DisplayLed.v_f.key_D_led;
		pSM16106->LED_OUT6 = g_DisplayLed.v_f.key_D_led;
		pSM16106->LED_OUT7 = g_DisplayLed.v_f.key_D_led;
		pSM16106->LED_OUT8 = g_DisplayLed.v_f.key_D_led;
		pSM16106->LED_OUT9 = g_DisplayLed.v_f.key_D_led;
		pSM16106->LED_OUT10 = g_DisplayLed.v_f.key_D_led;
		pSM16106->LED_OUT11 = g_DisplayLed.v_f.key_D_led;

		SM16xx_WriteAll();
	}

	else if(m_LedData.LedCom == AREA_E){
		Port_COM1 = 1;
		Port_COM2 = 1;

		Port_SW1 = 1;			
		Port_SW2 = 1;		
		Port_SW3 = 1;		
		Port_SW4 = 1;			
		Port_SW5 = 1;			
		Port_SW6 = 1;			
		Port_SW7 = 0;		
		Port_SW8 = 1;		
		Port_SW9 = 1;		
		Port_SW10 = 1;			
		Port_SW11 = 1;
		Port_SW12 = 1;			
		Port_SW13 = 1;
		Port_HandMove = 1;

		memset(pSM16106, 0, sizeof(SM16106_T));

		pSM16106->LED_OUT0 = g_DisplayLed.v_f.key_E_led;
		pSM16106->LED_OUT1 = g_DisplayLed.v_f.key_E_led;
		pSM16106->LED_OUT2 = g_DisplayLed.v_f.key_E_led;
		pSM16106->LED_OUT3 = g_DisplayLed.v_f.key_E_led;
		pSM16106->LED_OUT4 = g_DisplayLed.v_f.key_E_led;
		pSM16106->LED_OUT5 = g_DisplayLed.v_f.key_E_led;
		pSM16106->LED_OUT6 = g_DisplayLed.v_f.key_E_led;
		pSM16106->LED_OUT7 = g_DisplayLed.v_f.key_E_led;
		pSM16106->LED_OUT8 = g_DisplayLed.v_f.key_E_led;
		pSM16106->LED_OUT9 = g_DisplayLed.v_f.key_E_led;
		pSM16106->LED_OUT10 = g_DisplayLed.v_f.key_E_led;
		pSM16106->LED_OUT11 = g_DisplayLed.v_f.key_E_led;

		SM16xx_WriteAll();
	}


	else if(m_LedData.LedCom == AREA_DRAIN){
		Port_COM1 = 1;
		Port_COM2 = 1;

		Port_SW1 = 1;			
		Port_SW2 = 1;		
		Port_SW3 = 1;		
		Port_SW4 = 1;			
		Port_SW5 = 1;			
		Port_SW6 = 1;			
		Port_SW7 = 1;		
		Port_SW8 = 0;		
		Port_SW9 = 1;		
		Port_SW10 = 1;			
		Port_SW11 = 1;
		Port_SW12 = 1;			
		Port_SW13 = 1;
		Port_HandMove = 1;

		memset(pSM16106, 0, sizeof(SM16106_T));

		pSM16106->LED_OUT0 = g_DisplayLed.v_f.key_drain_led;
		pSM16106->LED_OUT1 = g_DisplayLed.v_f.key_drain_led;
		pSM16106->LED_OUT2 = g_DisplayLed.v_f.key_drain_led;
		pSM16106->LED_OUT3 = g_DisplayLed.v_f.key_drain_led;
		pSM16106->LED_OUT4 = g_DisplayLed.v_f.key_drain_led;
		pSM16106->LED_OUT5 = g_DisplayLed.v_f.key_drain_led;
		pSM16106->LED_OUT6 = g_DisplayLed.v_f.key_drain_led;
		pSM16106->LED_OUT7 = g_DisplayLed.v_f.key_drain_led;
		pSM16106->LED_OUT8 = g_DisplayLed.v_f.key_drain_led;
		pSM16106->LED_OUT9 = g_DisplayLed.v_f.key_drain_led;
		pSM16106->LED_OUT10 = g_DisplayLed.v_f.key_drain_led;
		pSM16106->LED_OUT11 = g_DisplayLed.v_f.key_drain_led;

		SM16xx_WriteAll();
	}

	else if(m_LedData.LedCom == AREA_MENU){
		Port_COM1 = 1;
		Port_COM2 = 1;

		Port_SW1 = 1;			
		Port_SW2 = 1;		
		Port_SW3 = 1;		
		Port_SW4 = 1;			
		Port_SW5 = 1;			
		Port_SW6 = 1;			
		Port_SW7 = 1;		
		Port_SW8 = 1;		
		Port_SW9 = 0;		
		Port_SW10 = 1;			
		Port_SW11 = 1;
		Port_SW12 = 1;			
		Port_SW13 = 1;
		Port_HandMove = 1;

		memset(pSM16106, 0, sizeof(SM16106_T));

		pSM16106->LED_OUT0 = g_DisplayLed.v_f.key_menu_led;
		pSM16106->LED_OUT1 = g_DisplayLed.v_f.key_menu_led;
		pSM16106->LED_OUT2 = g_DisplayLed.v_f.key_menu_led;
		pSM16106->LED_OUT3 = g_DisplayLed.v_f.key_menu_led;
		pSM16106->LED_OUT4 = g_DisplayLed.v_f.key_menu_led;
		pSM16106->LED_OUT5 = g_DisplayLed.v_f.key_menu_led;
		pSM16106->LED_OUT6 = g_DisplayLed.v_f.key_menu_led;
		pSM16106->LED_OUT7 = g_DisplayLed.v_f.key_menu_led;
		pSM16106->LED_OUT8 = g_DisplayLed.v_f.key_menu_led;
		pSM16106->LED_OUT9 = g_DisplayLed.v_f.key_menu_led;
		pSM16106->LED_OUT10 = g_DisplayLed.v_f.key_menu_led;
		pSM16106->LED_OUT11 = g_DisplayLed.v_f.key_menu_led;

		SM16xx_WriteAll();
	}

	else if(m_LedData.LedCom == AREA_NUM1){
		Port_COM1 = 0;
		Port_COM2 = 1;

		Port_SW1 = 1;			
		Port_SW2 = 1;		
		Port_SW3 = 1;		
		Port_SW4 = 1;			
		Port_SW5 = 1;			
		Port_SW6 = 1;			
		Port_SW7 = 1;		
		Port_SW8 = 1;		
		Port_SW9 = 1;		
		Port_SW10 = 1;			
		Port_SW11 = 1;
		Port_SW12 = 1;			
		Port_SW13 = 1;
		Port_HandMove = 1;

		memset(pSM16106, 0, sizeof(SM16106_T));

		pSM16106->LED_OUT0 = g_DisplayLed.v_f.num1_A_led;
		pSM16106->LED_OUT1 = g_DisplayLed.v_f.num1_F_led;
		pSM16106->LED_OUT2 = g_DisplayLed.v_f.num1_B_led;
		pSM16106->LED_OUT3 = g_DisplayLed.v_f.num1_G_led;
		pSM16106->LED_OUT4 = g_DisplayLed.v_f.num1_E_led;
		pSM16106->LED_OUT5 = g_DisplayLed.v_f.num1_C_led;
		pSM16106->LED_OUT6 = g_DisplayLed.v_f.num1_D_led;
		pSM16106->LED_OUT7 = g_DisplayLed.v_f.point_led;

	
		

		SM16xx_WriteAll();
	}

	else if(m_LedData.LedCom == AREA_NUM2){
		Port_COM1 = 1;
		Port_COM2 = 0;

		Port_SW1 = 1;			
		Port_SW2 = 1;		
		Port_SW3 = 1;		
		Port_SW4 = 1;			
		Port_SW5 = 1;			
		Port_SW6 = 1;			
		Port_SW7 = 1;		
		Port_SW8 = 1;		
		Port_SW9 = 1;		
		Port_SW10 = 1;			
		Port_SW11 = 1;
		Port_SW12 = 1;			
		Port_SW13 = 1;
		Port_HandMove = 1;

		memset(pSM16106, 0, sizeof(SM16106_T));

		pSM16106->LED_OUT0 = g_DisplayLed.v_f.num2_A_led;
		pSM16106->LED_OUT1 = g_DisplayLed.v_f.num2_F_led;
		pSM16106->LED_OUT2 = g_DisplayLed.v_f.num2_B_led;
		pSM16106->LED_OUT3 = g_DisplayLed.v_f.num2_G_led;
		pSM16106->LED_OUT4 = g_DisplayLed.v_f.num2_E_led;
		pSM16106->LED_OUT5 = g_DisplayLed.v_f.num2_C_led;
		pSM16106->LED_OUT6 = g_DisplayLed.v_f.num2_D_led;
		pSM16106->LED_OUT7 = g_DisplayLed.v_f.temper_led;
		
		pSM16106->LED_OUT8 = g_DisplayLed.v_f.process_led;
		pSM16106->LED_OUT9 = g_DisplayLed.v_f.time_led;
		
		

		SM16xx_WriteAll();
	}

	else if(m_LedData.LedCom == AREA_UP){
		Port_COM1 = 1;
		Port_COM2 = 1;

		Port_SW1 = 1;			
		Port_SW2 = 1;		
		Port_SW3 = 1;		
		Port_SW4 = 1;			
		Port_SW5 = 1;			
		Port_SW6 = 1;			
		Port_SW7 = 1;		
		Port_SW8 = 1;		
		Port_SW9 = 1;		
		Port_SW10 = 1;			
		Port_SW11 = 0;
		Port_SW12 = 1;			
		Port_SW13 = 1;
		Port_HandMove = 1;

		memset(pSM16106, 0, sizeof(SM16106_T));

		pSM16106->LED_OUT0 = g_DisplayLed.v_f.key_up_led;
		pSM16106->LED_OUT1 = g_DisplayLed.v_f.key_up_led;
		pSM16106->LED_OUT2 = g_DisplayLed.v_f.key_up_led;
		
		
		

		SM16xx_WriteAll();
	}

	else if(m_LedData.LedCom == AREA_DOWN){
		Port_COM1 = 1;
		Port_COM2 = 1;

		Port_SW1 = 1;			
		Port_SW2 = 1;		
		Port_SW3 = 1;		
		Port_SW4 = 1;			
		Port_SW5 = 1;			
		Port_SW6 = 1;			
		Port_SW7 = 1;		
		Port_SW8 = 1;		
		Port_SW9 = 1;		
		Port_SW10 = 0;			
		Port_SW11 = 1;
		Port_SW12 = 1;			
		Port_SW13 = 1;
		Port_HandMove = 1;

		memset(pSM16106, 0, sizeof(SM16106_T));

		pSM16106->LED_OUT0 = g_DisplayLed.v_f.key_down_led;
		pSM16106->LED_OUT1 = g_DisplayLed.v_f.key_down_led;
		pSM16106->LED_OUT2 = g_DisplayLed.v_f.key_down_led;
		
		
		

		SM16xx_WriteAll();
	}

	else if(m_LedData.LedCom == AREA_HEAT){
		Port_COM1 = 1;
		Port_COM2 = 1;

		Port_SW1 = 1;			
		Port_SW2 = 1;		
		Port_SW3 = 1;		
		Port_SW4 = 1;			
		Port_SW5 = 1;			
		Port_SW6 = 1;			
		Port_SW7 = 1;		
		Port_SW8 = 1;		
		Port_SW9 = 1;		
		Port_SW10 = 1;			
		Port_SW11 = 1;
		Port_SW12 = 0;			
		Port_SW13 = 1;
		Port_HandMove = 1;

		memset(pSM16106, 0, sizeof(SM16106_T));

		pSM16106->LED_OUT0 = g_DisplayLed.v_f.key_heat_led;
		pSM16106->LED_OUT1 = g_DisplayLed.v_f.key_heat_led;
		pSM16106->LED_OUT2 = g_DisplayLed.v_f.key_heat_led;
		pSM16106->LED_OUT3 = g_DisplayLed.v_f.key_heat_led;
		pSM16106->LED_OUT4 = g_DisplayLed.v_f.key_heat_led;
		pSM16106->LED_OUT5 = g_DisplayLed.v_f.key_heat_led;
		pSM16106->LED_OUT6 = g_DisplayLed.v_f.key_heat_led;
		pSM16106->LED_OUT7 = g_DisplayLed.v_f.key_heat_led;
		pSM16106->LED_OUT8 = g_DisplayLed.v_f.key_heat_led;
		pSM16106->LED_OUT9 = g_DisplayLed.v_f.key_heat_led;
		pSM16106->LED_OUT10 = g_DisplayLed.v_f.key_heat_led;
		
		
		

		SM16xx_WriteAll();
	}



	else if(m_LedData.LedCom == AREA_PLAY){
		Port_COM1 = 1;
		Port_COM2 = 1;

		Port_SW1 = 1;			
		Port_SW2 = 1;		
		Port_SW3 = 1;		
		Port_SW4 = 1;			
		Port_SW5 = 1;			
		Port_SW6 = 1;			
		Port_SW7 = 1;		
		Port_SW8 = 1;		
		Port_SW9 = 1;		
		Port_SW10 = 1;			
		Port_SW11 = 1;
		Port_SW12 = 1;			
		Port_SW13 = 0;
		Port_HandMove = 1;

		memset(pSM16106, 0, sizeof(SM16106_T));

		pSM16106->LED_OUT0 = g_DisplayLed.v_f.key_play_led;
		pSM16106->LED_OUT1 = g_DisplayLed.v_f.key_play_led;
		pSM16106->LED_OUT2 = g_DisplayLed.v_f.key_play_led;
		pSM16106->LED_OUT3 = g_DisplayLed.v_f.key_play_led;
		pSM16106->LED_OUT4 = g_DisplayLed.v_f.key_play_led;
		pSM16106->LED_OUT5 = g_DisplayLed.v_f.key_play_led;
		pSM16106->LED_OUT6 = g_DisplayLed.v_f.key_play_led;
		pSM16106->LED_OUT7 = g_DisplayLed.v_f.key_play_led;
		pSM16106->LED_OUT8 = g_DisplayLed.v_f.key_play_led;
		pSM16106->LED_OUT9 = g_DisplayLed.v_f.key_play_led;
		pSM16106->LED_OUT10 = g_DisplayLed.v_f.key_play_led;
		
		
		

		SM16xx_WriteAll();
	}

	else if(m_LedData.LedCom == AREA_HAND){
		Port_COM1 = 1;
		Port_COM2 = 1;

		Port_SW1 = 1;			
		Port_SW2 = 1;		
		Port_SW3 = 1;		
		Port_SW4 = 1;			
		Port_SW5 = 1;			
		Port_SW6 = 1;			
		Port_SW7 = 1;		
		Port_SW8 = 1;		
		Port_SW9 = 1;		
		Port_SW10 = 1;			
		Port_SW11 = 1;
		Port_SW12 = 1;			
		Port_SW13 = 1;
		Port_HandMove = 0;

		memset(pSM16106, 0, sizeof(SM16106_T));

		pSM16106->LED_OUT0 = g_DisplayLed.v_f.hand_left_led;
		pSM16106->LED_OUT1 = g_DisplayLed.v_f.hand_right_led;
	
		
		
		

		SM16xx_WriteAll();
	}

		m_LedData.LedCom++;
		if(m_LedData.LedCom >= 16) m_LedData.LedCom = 0;
	}

	

	

	
}


#endif

#if(1)


void Led_100usPool(uint8 area,uint8 brightness){
	if(g_View.BrightnessTime[0] > 10){
		g_View.BrightnessTime[0] = 0;
	}else{
		g_View.BrightnessTime[0] ++;
	}

	Led_All_Close();

	if(m_LedData.LedCom == AREA_POWER){
		Port_COM1 = 1;
		Port_COM2 = 1;

		Port_SW1 = 0;			
		Port_SW2 = 1;		
		Port_SW3 = 1;		
		Port_SW4 = 1;			
		Port_SW5 = 1;			
		Port_SW6 = 1;			
		Port_SW7 = 1;		
		Port_SW8 = 1;		
		Port_SW9 = 1;		
		Port_SW10 = 1;			
		Port_SW11 = 1;
		Port_SW12 = 1;			
		Port_SW13 = 1;
		Port_HandMove = 1;

		memset(pSM16106, 0, sizeof(SM16106_T));

		if(g_DisplayLed.v_f.key_power_led == SET){
			pSM16106->LED_OUT0 = g_DisplayLed.v_f.key_power_led;
			pSM16106->LED_OUT1 = g_DisplayLed.v_f.key_power_led;
			pSM16106->LED_OUT2 = g_DisplayLed.v_f.key_power_led;
			pSM16106->LED_OUT3 = g_DisplayLed.v_f.key_power_led;
			pSM16106->LED_OUT4 = g_DisplayLed.v_f.key_power_led;
			pSM16106->LED_OUT5 = g_DisplayLed.v_f.key_power_led;
			pSM16106->LED_OUT6 = g_DisplayLed.v_f.key_power_led;
			pSM16106->LED_OUT7 = g_DisplayLed.v_f.key_power_led;
			pSM16106->LED_OUT8 = g_DisplayLed.v_f.key_power_led;
			pSM16106->LED_OUT9 = g_DisplayLed.v_f.key_power_led;
			pSM16106->LED_OUT10 = g_DisplayLed.v_f.key_power_led;
		}
		else if(g_DisplayLed.v_f.key_power_led == SET){
			Led_All_Close();
		}

		SM16xx_WriteAll();
		
	}

	else if(m_LedData.LedCom == AREA_DOOR){
		Port_COM1 = 1;
		Port_COM2 = 1;

		Port_SW1 = 1;			
		Port_SW2 = 0;		
		Port_SW3 = 1;		
		Port_SW4 = 1;			
		Port_SW5 = 1;			
		Port_SW6 = 1;			
		Port_SW7 = 1;		
		Port_SW8 = 1;		
		Port_SW9 = 1;		
		Port_SW10 = 1;			
		Port_SW11 = 1;
		Port_SW12 = 1;			
		Port_SW13 = 1;
		Port_HandMove = 1;

		memset(pSM16106, 0, sizeof(SM16106_T));

		if(g_DisplayLed.v_f.key_door_led == SET){
			pSM16106->LED_OUT0 = g_DisplayLed.v_f.key_door_led;
			pSM16106->LED_OUT1 = g_DisplayLed.v_f.key_door_led;
			pSM16106->LED_OUT2 = g_DisplayLed.v_f.key_door_led;
			pSM16106->LED_OUT3 = g_DisplayLed.v_f.key_door_led;
			pSM16106->LED_OUT4 = g_DisplayLed.v_f.key_door_led;
			pSM16106->LED_OUT5 = g_DisplayLed.v_f.key_door_led;
			pSM16106->LED_OUT6 = g_DisplayLed.v_f.key_door_led;
			pSM16106->LED_OUT7 = g_DisplayLed.v_f.key_door_led;
			pSM16106->LED_OUT8 = g_DisplayLed.v_f.key_door_led;
			pSM16106->LED_OUT9 = g_DisplayLed.v_f.key_door_led;
			pSM16106->LED_OUT10 = g_DisplayLed.v_f.key_door_led;
		}

		

		SM16xx_WriteAll();
	}

	else if(m_LedData.LedCom == AREA_A){
		Port_COM1 = 1;
		Port_COM2 = 1;

		Port_SW1 = 1;			
		Port_SW2 = 1;		
		Port_SW3 = 0;		
		Port_SW4 = 1;			
		Port_SW5 = 1;			
		Port_SW6 = 1;			
		Port_SW7 = 1;		
		Port_SW8 = 1;		
		Port_SW9 = 1;		
		Port_SW10 = 1;			
		Port_SW11 = 1;
		Port_SW12 = 1;			
		Port_SW13 = 1;
		Port_HandMove = 1;

		memset(pSM16106, 0, sizeof(SM16106_T));

		if(g_DisplayLed.v_f.key_A_led == SET){
			pSM16106->LED_OUT0 = g_DisplayLed.v_f.key_A_led;
			pSM16106->LED_OUT1 = g_DisplayLed.v_f.key_A_led;
			pSM16106->LED_OUT2 = g_DisplayLed.v_f.key_A_led;
			pSM16106->LED_OUT3 = g_DisplayLed.v_f.key_A_led;
			pSM16106->LED_OUT4 = g_DisplayLed.v_f.key_A_led;
			pSM16106->LED_OUT5 = g_DisplayLed.v_f.key_A_led;
			pSM16106->LED_OUT6 = g_DisplayLed.v_f.key_A_led;
			pSM16106->LED_OUT7 = g_DisplayLed.v_f.key_A_led;
			pSM16106->LED_OUT8 = g_DisplayLed.v_f.key_A_led;
			pSM16106->LED_OUT9 = g_DisplayLed.v_f.key_A_led;
			pSM16106->LED_OUT10 = g_DisplayLed.v_f.key_A_led;
			pSM16106->LED_OUT11 = g_DisplayLed.v_f.key_A_led;

		}

		SM16xx_WriteAll();
	}

	else if(m_LedData.LedCom == AREA_B){
		Port_COM1 = 1;
		Port_COM2 = 1;

		Port_SW1 = 1;			
		Port_SW2 = 1;		
		Port_SW3 = 1;		
		Port_SW4 = 0;			
		Port_SW5 = 1;			
		Port_SW6 = 1;			
		Port_SW7 = 1;		
		Port_SW8 = 1;		
		Port_SW9 = 1;		
		Port_SW10 = 1;			
		Port_SW11 = 1;
		Port_SW12 = 1;			
		Port_SW13 = 1;
		Port_HandMove = 1;

		memset(pSM16106, 0, sizeof(SM16106_T));

		if(g_DisplayLed.v_f.key_B_led == SET){
			pSM16106->LED_OUT0 = g_DisplayLed.v_f.key_B_led;
			pSM16106->LED_OUT1 = g_DisplayLed.v_f.key_B_led;
			pSM16106->LED_OUT2 = g_DisplayLed.v_f.key_B_led;
			pSM16106->LED_OUT3 = g_DisplayLed.v_f.key_B_led;
			pSM16106->LED_OUT4 = g_DisplayLed.v_f.key_B_led;
			pSM16106->LED_OUT5 = g_DisplayLed.v_f.key_B_led;
			pSM16106->LED_OUT6 = g_DisplayLed.v_f.key_B_led;
			pSM16106->LED_OUT7 = g_DisplayLed.v_f.key_B_led;
			pSM16106->LED_OUT8 = g_DisplayLed.v_f.key_B_led;
			pSM16106->LED_OUT9 = g_DisplayLed.v_f.key_B_led;
			pSM16106->LED_OUT10 = g_DisplayLed.v_f.key_B_led;
			pSM16106->LED_OUT11 = g_DisplayLed.v_f.key_B_led;
		}


		SM16xx_WriteAll();
	}

	else if(m_LedData.LedCom == AREA_C){
		Port_COM1 = 1;
		Port_COM2 = 1;

		Port_SW1 = 1;			
		Port_SW2 = 1;		
		Port_SW3 = 1;		
		Port_SW4 = 1;			
		Port_SW5 = 0;			
		Port_SW6 = 1;			
		Port_SW7 = 1;		
		Port_SW8 = 1;		
		Port_SW9 = 1;		
		Port_SW10 = 1;			
		Port_SW11 = 1;
		Port_SW12 = 1;			
		Port_SW13 = 1;
		Port_HandMove = 1;

		memset(pSM16106, 0, sizeof(SM16106_T));

		if(g_DisplayLed.v_f.key_C_led == SET){
			pSM16106->LED_OUT0 = g_DisplayLed.v_f.key_C_led;
			pSM16106->LED_OUT1 = g_DisplayLed.v_f.key_C_led;
			pSM16106->LED_OUT2 = g_DisplayLed.v_f.key_C_led;
			pSM16106->LED_OUT3 = g_DisplayLed.v_f.key_C_led;
			pSM16106->LED_OUT4 = g_DisplayLed.v_f.key_C_led;
			pSM16106->LED_OUT5 = g_DisplayLed.v_f.key_C_led;
			pSM16106->LED_OUT6 = g_DisplayLed.v_f.key_C_led;
			pSM16106->LED_OUT7 = g_DisplayLed.v_f.key_C_led;
			pSM16106->LED_OUT8 = g_DisplayLed.v_f.key_C_led;
			pSM16106->LED_OUT9 = g_DisplayLed.v_f.key_C_led;
			pSM16106->LED_OUT10 = g_DisplayLed.v_f.key_C_led;
			pSM16106->LED_OUT11 = g_DisplayLed.v_f.key_C_led;
		}

		SM16xx_WriteAll();
	}

	else if(m_LedData.LedCom == AREA_D){
		Port_COM1 = 1;
		Port_COM2 = 1;

		Port_SW1 = 1;			
		Port_SW2 = 1;		
		Port_SW3 = 1;		
		Port_SW4 = 1;			
		Port_SW5 = 1;			
		Port_SW6 = 0;			
		Port_SW7 = 1;		
		Port_SW8 = 1;		
		Port_SW9 = 1;		
		Port_SW10 = 1;			
		Port_SW11 = 1;
		Port_SW12 = 1;			
		Port_SW13 = 1;
		Port_HandMove = 1;

		memset(pSM16106, 0, sizeof(SM16106_T));

		if(g_DisplayLed.v_f.key_D_led == SET){
			pSM16106->LED_OUT0 = g_DisplayLed.v_f.key_D_led;
			pSM16106->LED_OUT1 = g_DisplayLed.v_f.key_D_led;
			pSM16106->LED_OUT2 = g_DisplayLed.v_f.key_D_led;
			pSM16106->LED_OUT3 = g_DisplayLed.v_f.key_D_led;
			pSM16106->LED_OUT4 = g_DisplayLed.v_f.key_D_led;
			pSM16106->LED_OUT5 = g_DisplayLed.v_f.key_D_led;
			pSM16106->LED_OUT6 = g_DisplayLed.v_f.key_D_led;
			pSM16106->LED_OUT7 = g_DisplayLed.v_f.key_D_led;
			pSM16106->LED_OUT8 = g_DisplayLed.v_f.key_D_led;
			pSM16106->LED_OUT9 = g_DisplayLed.v_f.key_D_led;
			pSM16106->LED_OUT10 = g_DisplayLed.v_f.key_D_led;
			pSM16106->LED_OUT11 = g_DisplayLed.v_f.key_D_led;

		}


		SM16xx_WriteAll();
	}

	else if(m_LedData.LedCom == AREA_E){
		Port_COM1 = 1;
		Port_COM2 = 1;

		Port_SW1 = 1;			
		Port_SW2 = 1;		
		Port_SW3 = 1;		
		Port_SW4 = 1;			
		Port_SW5 = 1;			
		Port_SW6 = 1;			
		Port_SW7 = 0;		
		Port_SW8 = 1;		
		Port_SW9 = 1;		
		Port_SW10 = 1;			
		Port_SW11 = 1;
		Port_SW12 = 1;			
		Port_SW13 = 1;
		Port_HandMove = 1;

		memset(pSM16106, 0, sizeof(SM16106_T));

		if(g_DisplayLed.v_f.key_E_led == SET){
			pSM16106->LED_OUT0 = g_DisplayLed.v_f.key_E_led;
			pSM16106->LED_OUT1 = g_DisplayLed.v_f.key_E_led;
			pSM16106->LED_OUT2 = g_DisplayLed.v_f.key_E_led;
			pSM16106->LED_OUT3 = g_DisplayLed.v_f.key_E_led;
			pSM16106->LED_OUT4 = g_DisplayLed.v_f.key_E_led;
			pSM16106->LED_OUT5 = g_DisplayLed.v_f.key_E_led;
			pSM16106->LED_OUT6 = g_DisplayLed.v_f.key_E_led;
			pSM16106->LED_OUT7 = g_DisplayLed.v_f.key_E_led;
			pSM16106->LED_OUT8 = g_DisplayLed.v_f.key_E_led;
			pSM16106->LED_OUT9 = g_DisplayLed.v_f.key_E_led;
			pSM16106->LED_OUT10 = g_DisplayLed.v_f.key_E_led;
			pSM16106->LED_OUT11 = g_DisplayLed.v_f.key_E_led;
		}

		SM16xx_WriteAll();
	}


	else if(m_LedData.LedCom == AREA_DRAIN){
		Port_COM1 = 1;
		Port_COM2 = 1;

		Port_SW1 = 1;			
		Port_SW2 = 1;		
		Port_SW3 = 1;		
		Port_SW4 = 1;			
		Port_SW5 = 1;			
		Port_SW6 = 1;			
		Port_SW7 = 1;		
		Port_SW8 = 0;		
		Port_SW9 = 1;		
		Port_SW10 = 1;			
		Port_SW11 = 1;
		Port_SW12 = 1;			
		Port_SW13 = 1;
		Port_HandMove = 1;

		memset(pSM16106, 0, sizeof(SM16106_T));

		if(g_DisplayLed.v_f.key_drain_led == SET){
			pSM16106->LED_OUT0 = g_DisplayLed.v_f.key_drain_led;
			pSM16106->LED_OUT1 = g_DisplayLed.v_f.key_drain_led;
			pSM16106->LED_OUT2 = g_DisplayLed.v_f.key_drain_led;
			pSM16106->LED_OUT3 = g_DisplayLed.v_f.key_drain_led;
			pSM16106->LED_OUT4 = g_DisplayLed.v_f.key_drain_led;
			pSM16106->LED_OUT5 = g_DisplayLed.v_f.key_drain_led;
			pSM16106->LED_OUT6 = g_DisplayLed.v_f.key_drain_led;
			pSM16106->LED_OUT7 = g_DisplayLed.v_f.key_drain_led;
			pSM16106->LED_OUT8 = g_DisplayLed.v_f.key_drain_led;
			pSM16106->LED_OUT9 = g_DisplayLed.v_f.key_drain_led;
			pSM16106->LED_OUT10 = g_DisplayLed.v_f.key_drain_led;
			pSM16106->LED_OUT11 = g_DisplayLed.v_f.key_drain_led;
		}


		SM16xx_WriteAll();
	}

	else if(m_LedData.LedCom == AREA_MENU){
		Port_COM1 = 1;
		Port_COM2 = 1;

		Port_SW1 = 1;			
		Port_SW2 = 1;		
		Port_SW3 = 1;		
		Port_SW4 = 1;			
		Port_SW5 = 1;			
		Port_SW6 = 1;			
		Port_SW7 = 1;		
		Port_SW8 = 1;		
		Port_SW9 = 0;		
		Port_SW10 = 1;			
		Port_SW11 = 1;
		Port_SW12 = 1;			
		Port_SW13 = 1;
		Port_HandMove = 1;

		memset(pSM16106, 0, sizeof(SM16106_T));

		if(g_DisplayLed.v_f.key_menu_led == SET){
			pSM16106->LED_OUT0 = g_DisplayLed.v_f.key_menu_led;
			pSM16106->LED_OUT1 = g_DisplayLed.v_f.key_menu_led;
			pSM16106->LED_OUT2 = g_DisplayLed.v_f.key_menu_led;
			pSM16106->LED_OUT3 = g_DisplayLed.v_f.key_menu_led;
			pSM16106->LED_OUT4 = g_DisplayLed.v_f.key_menu_led;
			pSM16106->LED_OUT5 = g_DisplayLed.v_f.key_menu_led;
			pSM16106->LED_OUT6 = g_DisplayLed.v_f.key_menu_led;
			pSM16106->LED_OUT7 = g_DisplayLed.v_f.key_menu_led;
			pSM16106->LED_OUT8 = g_DisplayLed.v_f.key_menu_led;
			pSM16106->LED_OUT9 = g_DisplayLed.v_f.key_menu_led;
			pSM16106->LED_OUT10 = g_DisplayLed.v_f.key_menu_led;
			pSM16106->LED_OUT11 = g_DisplayLed.v_f.key_menu_led;
		}

		SM16xx_WriteAll();
	}

	else if(m_LedData.LedCom == AREA_NUM1){
		Port_COM1 = 0;
		Port_COM2 = 1;

		Port_SW1 = 1;			
		Port_SW2 = 1;		
		Port_SW3 = 1;		
		Port_SW4 = 1;			
		Port_SW5 = 1;			
		Port_SW6 = 1;			
		Port_SW7 = 1;		
		Port_SW8 = 1;		
		Port_SW9 = 1;		
		Port_SW10 = 1;			
		Port_SW11 = 1;
		Port_SW12 = 1;			
		Port_SW13 = 1;
		Port_HandMove = 1;

		memset(pSM16106, 0, sizeof(SM16106_T));

		
//		if(g_DisplayLed.v_f.num1_A_led == SET){
		if(g_DisplayLed.v[3] | 0XFF){
			pSM16106->LED_OUT0 = g_DisplayLed.v_f.num1_A_led;
			pSM16106->LED_OUT1 = g_DisplayLed.v_f.num1_F_led;
			pSM16106->LED_OUT2 = g_DisplayLed.v_f.num1_B_led;
			pSM16106->LED_OUT3 = g_DisplayLed.v_f.num1_G_led;
			pSM16106->LED_OUT4 = g_DisplayLed.v_f.num1_E_led;
			pSM16106->LED_OUT5 = g_DisplayLed.v_f.num1_C_led;
			pSM16106->LED_OUT6 = g_DisplayLed.v_f.num1_D_led;
			pSM16106->LED_OUT7 = g_DisplayLed.v_f.point_led;

		}		

		SM16xx_WriteAll();
	}

	else if(m_LedData.LedCom == AREA_NUM2){
		Port_COM1 = 1;
		Port_COM2 = 0;

		Port_SW1 = 1;			
		Port_SW2 = 1;		
		Port_SW3 = 1;		
		Port_SW4 = 1;			
		Port_SW5 = 1;			
		Port_SW6 = 1;			
		Port_SW7 = 1;		
		Port_SW8 = 1;		
		Port_SW9 = 1;		
		Port_SW10 = 1;			
		Port_SW11 = 1;
		Port_SW12 = 1;			
		Port_SW13 = 1;
		Port_HandMove = 1;

		memset(pSM16106, 0, sizeof(SM16106_T));

		if(g_DisplayLed.v[4] | 0XFF){
			pSM16106->LED_OUT0 = g_DisplayLed.v_f.num2_A_led;
			pSM16106->LED_OUT1 = g_DisplayLed.v_f.num2_F_led;
			pSM16106->LED_OUT2 = g_DisplayLed.v_f.num2_B_led;
			pSM16106->LED_OUT3 = g_DisplayLed.v_f.num2_G_led;
			pSM16106->LED_OUT4 = g_DisplayLed.v_f.num2_E_led;
			pSM16106->LED_OUT5 = g_DisplayLed.v_f.num2_C_led;
			pSM16106->LED_OUT6 = g_DisplayLed.v_f.num2_D_led;
			pSM16106->LED_OUT7 = g_DisplayLed.v_f.temper_led;
			
			pSM16106->LED_OUT8 = g_DisplayLed.v_f.process_led;
			pSM16106->LED_OUT9 = g_DisplayLed.v_f.time_led;
		}
		

		SM16xx_WriteAll();
	}

	else if(m_LedData.LedCom == AREA_UP){
		Port_COM1 = 1;
		Port_COM2 = 1;

		Port_SW1 = 1;			
		Port_SW2 = 1;		
		Port_SW3 = 1;		
		Port_SW4 = 1;			
		Port_SW5 = 1;			
		Port_SW6 = 1;			
		Port_SW7 = 1;		
		Port_SW8 = 1;		
		Port_SW9 = 1;		
		Port_SW10 = 1;			
		Port_SW11 = 0;
		Port_SW12 = 1;			
		Port_SW13 = 1;
		Port_HandMove = 1;

		memset(pSM16106, 0, sizeof(SM16106_T));

		if(g_DisplayLed.v_f.key_up_led == SET){
			pSM16106->LED_OUT0 = g_DisplayLed.v_f.key_up_led;
			pSM16106->LED_OUT1 = g_DisplayLed.v_f.key_up_led;
			pSM16106->LED_OUT2 = g_DisplayLed.v_f.key_up_led;
		}		

		SM16xx_WriteAll();
	}

	else if(m_LedData.LedCom == AREA_DOWN){
		Port_COM1 = 1;
		Port_COM2 = 1;

		Port_SW1 = 1;			
		Port_SW2 = 1;		
		Port_SW3 = 1;		
		Port_SW4 = 1;			
		Port_SW5 = 1;			
		Port_SW6 = 1;			
		Port_SW7 = 1;		
		Port_SW8 = 1;		
		Port_SW9 = 1;		
		Port_SW10 = 0;			
		Port_SW11 = 1;
		Port_SW12 = 1;			
		Port_SW13 = 1;
		Port_HandMove = 1;

		memset(pSM16106, 0, sizeof(SM16106_T));

		if(g_DisplayLed.v_f.key_down_led == SET){
			pSM16106->LED_OUT0 = g_DisplayLed.v_f.key_down_led;
			pSM16106->LED_OUT1 = g_DisplayLed.v_f.key_down_led;
			pSM16106->LED_OUT2 = g_DisplayLed.v_f.key_down_led;
		}
		
		

		SM16xx_WriteAll();
	}

	else if(m_LedData.LedCom == AREA_HEAT){
		Port_COM1 = 1;
		Port_COM2 = 1;

		Port_SW1 = 1;			
		Port_SW2 = 1;		
		Port_SW3 = 1;		
		Port_SW4 = 1;			
		Port_SW5 = 1;			
		Port_SW6 = 1;			
		Port_SW7 = 1;		
		Port_SW8 = 1;		
		Port_SW9 = 1;		
		Port_SW10 = 1;			
		Port_SW11 = 1;
		Port_SW12 = 0;			
		Port_SW13 = 1;
		Port_HandMove = 1;

		memset(pSM16106, 0, sizeof(SM16106_T));

		if(g_DisplayLed.v_f.key_heat_led == SET){
			pSM16106->LED_OUT0 = g_DisplayLed.v_f.key_heat_led;
			pSM16106->LED_OUT1 = g_DisplayLed.v_f.key_heat_led;
			pSM16106->LED_OUT2 = g_DisplayLed.v_f.key_heat_led;
			pSM16106->LED_OUT3 = g_DisplayLed.v_f.key_heat_led;
			pSM16106->LED_OUT4 = g_DisplayLed.v_f.key_heat_led;
			pSM16106->LED_OUT5 = g_DisplayLed.v_f.key_heat_led;
			pSM16106->LED_OUT6 = g_DisplayLed.v_f.key_heat_led;
			pSM16106->LED_OUT7 = g_DisplayLed.v_f.key_heat_led;
			pSM16106->LED_OUT8 = g_DisplayLed.v_f.key_heat_led;
			pSM16106->LED_OUT9 = g_DisplayLed.v_f.key_heat_led;
			pSM16106->LED_OUT10 = g_DisplayLed.v_f.key_heat_led;
		}		

		SM16xx_WriteAll();
	}



	else if(m_LedData.LedCom == AREA_PLAY){
		Port_COM1 = 1;
		Port_COM2 = 1;

		Port_SW1 = 1;			
		Port_SW2 = 1;		
		Port_SW3 = 1;		
		Port_SW4 = 1;			
		Port_SW5 = 1;			
		Port_SW6 = 1;			
		Port_SW7 = 1;		
		Port_SW8 = 1;		
		Port_SW9 = 1;		
		Port_SW10 = 1;			
		Port_SW11 = 1;
		Port_SW12 = 1;			
		Port_SW13 = 0;
		Port_HandMove = 1;

		memset(pSM16106, 0, sizeof(SM16106_T));

		if(g_DisplayLed.v_f.key_play_led == SET){
			pSM16106->LED_OUT0 = g_DisplayLed.v_f.key_play_led;
			pSM16106->LED_OUT1 = g_DisplayLed.v_f.key_play_led;
			pSM16106->LED_OUT2 = g_DisplayLed.v_f.key_play_led;
			pSM16106->LED_OUT3 = g_DisplayLed.v_f.key_play_led;
			pSM16106->LED_OUT4 = g_DisplayLed.v_f.key_play_led;
			pSM16106->LED_OUT5 = g_DisplayLed.v_f.key_play_led;
			pSM16106->LED_OUT6 = g_DisplayLed.v_f.key_play_led;
			pSM16106->LED_OUT7 = g_DisplayLed.v_f.key_play_led;
			pSM16106->LED_OUT8 = g_DisplayLed.v_f.key_play_led;
			pSM16106->LED_OUT9 = g_DisplayLed.v_f.key_play_led;
			pSM16106->LED_OUT10 = g_DisplayLed.v_f.key_play_led;
		}
		

		SM16xx_WriteAll();
	}

	else if(m_LedData.LedCom == AREA_HAND){
		Port_COM1 = 1;
		Port_COM2 = 1;

		Port_SW1 = 1;			
		Port_SW2 = 1;		
		Port_SW3 = 1;		
		Port_SW4 = 1;			
		Port_SW5 = 1;			
		Port_SW6 = 1;			
		Port_SW7 = 1;		
		Port_SW8 = 1;		
		Port_SW9 = 1;		
		Port_SW10 = 1;			
		Port_SW11 = 1;
		Port_SW12 = 1;			
		Port_SW13 = 1;
		Port_HandMove = 0;

		memset(pSM16106, 0, sizeof(SM16106_T));

		if(g_DisplayLed.v[1] | 0x60){
			pSM16106->LED_OUT0 = g_DisplayLed.v_f.hand_left_led;
			pSM16106->LED_OUT1 = g_DisplayLed.v_f.hand_right_led;
		}

		SM16xx_WriteAll();
	}

	m_LedData.LedCom++;
	if(m_LedData.LedCom >= 16) m_LedData.LedCom = 0;


	
	
}


#endif
















