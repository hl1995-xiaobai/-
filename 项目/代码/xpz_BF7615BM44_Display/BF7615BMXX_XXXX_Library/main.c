#include ".\BF7615BMXX_XXXX_Library\Config.h"

void main(void)
{
	//MCU_Init()��ʼ������
	MCU_Init();

	while(1)
	{
		//�忴�Ź���
		WDT_CTRL = 7;
		
#if(0)		
		if(Low_Volotage_Flag_Confirm == 0)//����͵�ѹ�ж�ʱ����ʱVolDet_COUNT*(timer0��ʱ)��ȷ��Ϊ�͵�ѹLow_Volotage_Flag_Confirm = 1
		{
			//��ȡ������־λ
			BF7615BMXX_XXXX_Set_Touch_Flag();
		}
#endif		
		
		//���齫��Ŀ���ܺ���������Project.c�л��½�c�ļ���
		Project();
	
	}			
}