#include ".\BF7615BMXX_XXXX_Library\Config.h"
#if	VolDet_EN
	bit Low_Volotage_Flag = 0;
	bit Low_Volotage_Flag_Confirm = 0;
	bit Low_Volotage_Flag_First = 0;
	uint xdata Low_Volotage_Flag_Count = 0;
	uint xdata Low_Volotage_Flag_Confirm_count = 0;
#endif

 #if ((VolDet_EN == 1))
	#pragma message "����,LVDT����"
	//-----------------------------------------------------------------//
	//�������ƣ� void LVDT_Init(void)
	//�������ܣ� ��ѹ��ѹ����ʼ��
	//��������� ��
	//��������� ��
	//�� �� ֵ�� ��
	//-----------------------------------------------------------------//
	#if ((VolDet_EN == 1))
	void LVDT_Init(void)
	{
		EA = 0;//�����жϣ�
		LVDT_IP_SET;//���ý�ѹ��ѹ���ж��ż�Ϊ�ߣ�����ʵ��Ӧ���������ȼ�
		LVDT_INT_FLAG_CLR;//����͵�ѹ����жϱ�־λ
		LVDT_INT_DOWN_FLAG_CLR;//�����ѹ�½��жϱ�־λ	
		LVDT_INT_UP_FLAG_CLR;//�����ѹ�����жϱ�־λLVDT_ON;//�����͵�ѹ���ģ��
		LVDT_ON_OFF_SET(0);//0Ϊ����LVDT���ģ��,1Ϊ�ر�LVDT���ģ��
		LVDT_VOL_SET(2);//2���õ͵�ѹ������:(0-2.7V)-(1-3.0V)-(2-3.8V)
		LVDT_IE_SET;//ʹ�ܽ�ѹ��ѹ���ж�
		EA = 1;//�����ж�	   
	}
	#endif
	//-----------------------------------------------------------------//
	//�������ƣ� void LVDT_ISR() interrupt 16
	//�������ܣ� ��ѹ��ѹ����жϣ�LVDTģ��
	//��������� ��
	//��������� ��
	//�� �� ֵ�� ��
	//-----------------------------------------------------------------//	
	void LVDT_ISR() interrupt 16
	{	
		static uchar xdata addr_bak = 0;
		PUSH_REG_ADDR_SFR();
		LVDT_INT_FLAG_CLR;//�����ѹ��ѹ�жϱ�־λ

		if(INT_POBO_STAT&0x01)
		{
			Low_Volotage_Flag = 1;
			LVDT_INT_DOWN_FLAG_CLR;//�����ѹ�½��жϱ�־λ	
		}
		if(INT_POBO_STAT&0x02)
		{
			LVDT_INT_UP_FLAG_CLR;//�����ѹ�����жϱ�־λ	
			Low_Volotage_Flag = 0;
			Low_Volotage_Flag_Confirm = 0;
			Low_Volotage_Flag_Count = 0;
		}		
		POP_REG_ADDR_SFR();	
	}
		 
	#endif
