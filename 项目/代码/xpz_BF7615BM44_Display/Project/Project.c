#include ".\BF7615BMXX_XXXX_Library\Config.h"
/****************************************************************/
//�ο�������Project.c��Project.h
/****************************************************************/
bit IsTouch = 0;
uchar xdata Key_Data = 0x00;


	
/****************************************************************/
//��������void Project(void)
//��  �ܣ���Ŀ��Ŀ���ܺ���
//��  ������
//����ֵ����
/****************************************************************/
void Project(void)//����
{
#if(0)
    if((keys_flag_l != 0) || (keys_flag_h != 0))
	{
			if(IsTouch == 0)
			{
				IsTouch = 1;
				//��������
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

			
				
			
			}
		}

		if(g_SysHardware.SysTime10ms == SET){
			g_SysHardware.SysTime10ms = CLE;
			SysTime10msPool();
			if(g_SysHardware.sysInit == SET){
//				Gpio20MsPool();
//				ScanKey();
				
				
			
				if(Low_Volotage_Flag_Confirm == 0)//����͵�ѹ�ж�ʱ����ʱVolDet_COUNT*(timer0��ʱ)��ȷ��Ϊ�͵�ѹLow_Volotage_Flag_Confirm = 1
				{
					//��ȡ������־λ
					BF7615BMXX_XXXX_Set_Touch_Flag();
				}
			
				
			}
		}

		
		if(g_SysHardware.SysTime20ms == SET){
			g_SysHardware.SysTime20ms = CLE;
			SysTime20msPool();
			if(g_SysHardware.sysInit == SET){
//				Gpio20MsPool();
//				ScanKey();

				
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

				g_View.PowerOn = ~g_View.PowerOn;
				if(g_View.PowerOn){
					SET_PB6_H;
				}else{
					SET_PB6_L;
				}
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