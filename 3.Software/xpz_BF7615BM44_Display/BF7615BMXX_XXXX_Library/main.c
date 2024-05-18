#include "include.h"

#include ".\BF7615BMXX_XXXX_Library\Config.h"




void main(void)
{
	//MCU_Init()��ʼ������
	MCU_Init();

	g_View.VersionNumber = HOST_FIRMWARE_VERSION_NUMBER;
		
	Led_init();
	SM16xx_Init();
	CmdInit();

	UART1_BUF = 0x5A;
	
	while(1)
	{
		//�忴�Ź���
		WDT_CTRL = 7;
		
#if(1)		
		if(Low_Volotage_Flag_Confirm == 0)//����͵�ѹ�ж�ʱ����ʱVolDet_COUNT*(timer0��ʱ)��ȷ��Ϊ�͵�ѹLow_Volotage_Flag_Confirm = 1
		{
			//��ȡ������־λ
			BF7615BMXX_XXXX_Set_Touch_Flag();
		}
#endif		
		
		//���齫��Ŀ���ܺ���������Project.c�л��½�c�ļ���
		Project();

#if(0)
		if(g_View.PowerOn){
			SET_PB6_H;
		}else{
			SET_PB6_L;
		}
#endif
//		m_LedData.LedCom++;
//		if(m_LedData.LedCom >= 20) m_LedData.LedCom = 0;

		
	}			
}
