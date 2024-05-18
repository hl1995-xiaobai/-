#include "include.h"

#include "Display_Function.h"


void DisplayKeyLed(void){
	

	memset(&g_DisplayLed, 0, sizeof(DISPLAY_LED_T));
	
#if(0)
	if(g_View.BrightnessTime[0] == 1){
		g_DisplayLed.v_f.key_power_led = CLE;
	}else if(g_View.BrightnessTime[0] == 0){
		g_DisplayLed.v_f.key_power_led = SET;
	}
#endif

#if(0)

	g_DisplayLed.v_f.key_power_led = SET;

	g_DisplayLed.v_f.key_door_led = SET;

	g_DisplayLed.v_f.key_A_led = SET;

	g_DisplayLed.v_f.key_B_led = SET;

	g_DisplayLed.v_f.key_C_led = SET;

	g_DisplayLed.v_f.key_D_led = SET;

	g_DisplayLed.v_f.key_E_led = SET;

	g_DisplayLed.v_f.key_drain_led = SET;

	g_DisplayLed.v_f.key_menu_led = SET;

	g_DisplayLed.v_f.num1_A_led = SET;

	g_DisplayLed.v_f.point_led = SET;

	g_DisplayLed.v_f.num2_A_led = SET;

	g_DisplayLed.v_f.temper_led = SET;

	g_DisplayLed.v_f.key_up_led = SET;

	g_DisplayLed.v_f.key_down_led = SET;

	g_DisplayLed.v_f.key_heat_led = SET;

	g_DisplayLed.v_f.key_play_led = SET;

	g_DisplayLed.v_f.hand_left_led = SET;

	g_DisplayLed.v_f.hand_right_led = SET;

#endif



}  









