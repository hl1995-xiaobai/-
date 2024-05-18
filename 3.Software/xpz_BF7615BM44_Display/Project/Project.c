#include "include.h"

#include ".\BF7615BMXX_XXXX_Library\Config.h"
/****************************************************************/
//参考范例：Project.c和Project.h
/****************************************************************/
bit IsTouch = 0;
uchar xdata Key_Data = 0x00;


	
/****************************************************************/
//函数名：void Project(void)
//功  能：项目项目功能函数
//参  数：无
//返回值：无
/****************************************************************/

#if(0)

void Project(void)//范例
{
#if(0)
    if((keys_flag_l != 0) || (keys_flag_h != 0))
	{
			if(IsTouch == 0)
			{
				IsTouch = 1;
				//按键处理
				if(keys_flag_l == 0x00000001)
				{
					Key_Data = 0x01;
				}
			}
	}
	else
	{
			if(IsTouch == 1)
			{
				IsTouch = 0;
			}
	}
#endif
	if(g_SysHardware.SysCnt > 10){
//		g_SysHardware.SysMode = SYSMODE_TEST;
	}
	else{
		g_SysHardware.SysMode = SYSMODE_NORMAL;
	}
	
	if(g_SysHardware.SysMode == SYSMODE_TEST){
//		TestPool();	
	}
	else{
		
		if(g_SysHardware.SysTime1ms == SET){
			g_SysHardware.SysTime1ms = CLE;
			if(g_SysHardware.sysInit == SET){
//				CmdRecvPool();
//				SM16xx_WriteAll();

#if(0)				
				if(Low_Volotage_Flag_Confirm == 0)//进入低电压中断时，定时VolDet_COUNT*(timer0定时)后确认为低电压Low_Volotage_Flag_Confirm = 1
				{
					//获取按键标志位
					BF7615BMXX_XXXX_Set_Touch_Flag();
				}
#endif				
			
			}
		}

		if(g_SysHardware.SysTime10ms == SET){
			g_SysHardware.SysTime10ms = CLE;
			SysTime10msPool();
			if(g_SysHardware.sysInit == SET){
//				Gpio20MsPool();
//				ScanKey();
				
				
#if(1)			
				if(Low_Volotage_Flag_Confirm == 0)//进入低电压中断时，定时VolDet_COUNT*(timer0定时)后确认为低电压Low_Volotage_Flag_Confirm = 1
				{
					//获取按键标志位
					BF7615BMXX_XXXX_Set_Touch_Flag();
				}
#endif			
				
			}
		}

		
		if(g_SysHardware.SysTime20ms == SET){
			g_SysHardware.SysTime20ms = CLE;
			SysTime20msPool();
			if(g_SysHardware.sysInit == SET){
//				Gpio20MsPool();
				

				Key_Function_Deal();

				
			}
		}

		if(g_SysHardware.SysTime100ms == SET){
			g_SysHardware.SysTime100ms = CLE;
			SysTime100msPool();
			
			if(g_SysHardware.sysInit == SET){
//				SteamOven100msPool();
//				RangeHoodDataDispose();
//				DisplayChangeData();
//				TM1629_Driver();
//				KeyManage();

				
			}
		}

		if(g_SysHardware.SysTime500ms == SET){
			g_SysHardware.SysTime500ms = CLE;
			SysTime500msPool();

			

			if(g_SysHardware.sysInit == SET){
//				SteamOven500msPool();
			}
		}

		if(g_SysHardware.SysTime1S == SET){
			g_SysHardware.SysTime1S = CLE;

			if(g_SysHardware.sysInit == CLE) g_SysHardware.sysInit = SET;


#if(1)
			g_View.PowerOn = ~g_View.PowerOn;
			if(g_View.PowerOn){
				SET_PB6_H;
			}else{
				SET_PB6_L;
			}
#endif

#if(0)
			if(g_View.SendingState){
				g_View.SendingState = CLE;
					
				UART1_BUF = 0x5A;				
			}

#endif			
			
//			SteamOven1sPool();
//			RangeHood1sPool();
			if(g_SysHardware.SysCnt < 20){
				g_SysHardware.SysCnt++;
					if(g_SysHardware.SysCnt == 3){
#ifdef _DEBUG_WORK
//						SysUart0Init();
#else
//						SysUart1Init();
#endif
						
					}
			}


		}	
	}	
}

#endif

#if(1)

void Project(void)//范例
{
	if(g_SysHardware.SysCnt > 10){
//		g_SysHardware.SysMode = SYSMODE_TEST;
	}
	else{
		g_SysHardware.SysMode = SYSMODE_NORMAL;
	}
	
	if(g_SysHardware.SysMode == SYSMODE_TEST){
//		TestPool();	
	}
	else{
//		DisplayKeyLed();

		

#if(0)
	
		if(g_SysHardware.SysTime100us == SET){
			g_SysHardware.SysTime100us = CLE;
			SysTime100us();
			Led_100usPool();
		}

		if(g_SysHardware.SysTime1ms == SET){
			g_SysHardware.SysTime1ms = CLE;
			g_View.PowerOn = ~g_View.PowerOn;
			if(g_View.PowerOn){
				SET_PB6_H;
			}else{
				SET_PB6_L;
			}	
		}

#endif

		if(g_SysHardware.Time_4ms_cnt == 0){
			g_SysHardware.Time_4ms_cnt = 1;

#if(0)
			if(Low_Volotage_Flag_Confirm == 0)//进入低电压中断时，定时VolDet_COUNT*(timer0定时)后确认为低电压Low_Volotage_Flag_Confirm = 1
			{
				//获取按键标志位
				BF7615BMXX_XXXX_Set_Touch_Flag();
			}
#endif
			

//			Key_Function_Deal();

			
			
		}

		if (g_SysHardware.Time_20ms_cnt == 0) {
			//50ms
			g_SysHardware.Time_20ms_cnt = 20;

			
			
			Key_Function_Deal();
//			DisplayKeyLed();
		}


		if (g_SysHardware.Time_100ms_cnt  == 0) {
			g_SysHardware.Time_100ms_cnt 	= 100;

			memset(&g_DisplayLed, 0, sizeof(DISPLAY_LED_T));

			
#if(0)			
			if(g_View.Flash){
				g_DisplayLed.v_f.key_power_led = SET;
			}

#endif	
//			 (g_DisplayLed.v_f.key_power_led = SET,)

//			 (g_DisplayLed.v_f.key_door_led = SET,)

			 DisplayKeyLed();
#if(0)
			
			
			
			
			
			g_DisplayLed.v_f.key_A_led = SET;

			g_DisplayLed.v_f.key_B_led = SET;

			g_DisplayLed.v_f.key_C_led = SET;

			g_DisplayLed.v_f.key_D_led = SET;

			g_DisplayLed.v_f.key_E_led = SET;

			g_DisplayLed.v_f.key_drain_led = SET;

			g_DisplayLed.v_f.key_menu_led = SET;

			g_DisplayLed.v_f.num1_A_led = SET;

			g_DisplayLed.v_f.num1_F_led = SET;

			g_DisplayLed.v_f.num1_B_led = SET;

			g_DisplayLed.v_f.num1_G_led = SET;

			g_DisplayLed.v_f.num1_E_led = SET;

			g_DisplayLed.v_f.num1_C_led = SET;

			g_DisplayLed.v_f.num1_D_led = SET;

			g_DisplayLed.v_f.point_led = SET;

			g_DisplayLed.v_f.num2_A_led = SET;

			g_DisplayLed.v_f.num2_F_led = SET;

			g_DisplayLed.v_f.num2_B_led = SET;

			g_DisplayLed.v_f.num2_G_led = SET;

			g_DisplayLed.v_f.num2_E_led = SET;

			g_DisplayLed.v_f.num2_C_led = SET;

			g_DisplayLed.v_f.num2_D_led = SET;

			g_DisplayLed.v_f.temper_led = SET;

			g_DisplayLed.v_f.process_led = SET;
			
			g_DisplayLed.v_f.time_led = SET;

			g_DisplayLed.v_f.key_up_led = SET;

			g_DisplayLed.v_f.key_down_led = SET;

			g_DisplayLed.v_f.key_heat_led = SET;

			g_DisplayLed.v_f.key_play_led = SET;

			g_DisplayLed.v_f.hand_left_led = SET;
			
			g_DisplayLed.v_f.hand_right_led = SET;

#endif
			
		}


		if (g_SysHardware.Time_500ms_cnt == 0) {
			g_SysHardware.Time_500ms_cnt 	= 500;

			
			
		}


		

		if (g_SysHardware.Time_1000ms_cnt == 0) {
			g_SysHardware.Time_1000ms_cnt	= 1000;

#if(0)		
			g_View.PowerOn = ~g_View.PowerOn;
			if(g_View.PowerOn){
				SET_PB6_H;
			}else{
				SET_PB6_L;
			}

			
#endif
			g_View.Flash =~g_View.Flash;


#if(0)
			if(g_View.SendingState){
				g_View.SendingState = CLE;
					
				UART1_BUF = 0x5A;				
			}
#endif
			CmdSend1sLoop();
			
		}
		
	}

}

#endif
