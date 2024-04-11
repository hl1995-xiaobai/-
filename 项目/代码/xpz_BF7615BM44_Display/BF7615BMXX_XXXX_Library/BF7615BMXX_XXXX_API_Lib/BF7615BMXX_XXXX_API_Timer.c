#include ".\BF7615BMXX_XXXX_Library\Config.h"
/****************************************************************/
//timer�ο�������BF7615BMXX_XXXX_API_Timer.c��BF7615BMXX_XXXX_API_Timer.h
/****************************************************************/


uchar Test = 0;


#if Timer0_EN
	uchar TH0_Reload = 0;
	uchar TL0_Reload = 0;
	#if SNS_NUM
	uint xdata ctk_soft_reset_max_count = 30000;
	#endif

	uint xdata sclen_soft_reset_count = 0;
	uint xdata sclen_soft_reset_max_count = 0;

#endif 

#if Timer1_EN
	uchar TH1_Reload = 0;
	uchar TL1_Reload = 0;
#endif

#if Timer2_EN
	uchar TH2_Reload = 0;
	uchar TL2_Reload = 0;
#endif

#if Timer3_EN
	uchar TH3_Reload = 0;
	uchar TL3_Reload = 0;
#endif


//-----------------------------------------------------------------//
//�������ƣ� void Reset_Cnt_Add()
//�������ܣ� CTK/IIC/�ⲿ�жϳ���������ۼӺ���
//��������� ��
//��������� ��
//�� �� ֵ�� ��
//-----------------------------------------------------------------//
#if Timer0_EN
	#if SNS_NUM
	void Reset_Cnt_Add()
	{
			ctk_soft_reset_count++;
	
			if(ctk_soft_reset_count >= ctk_soft_reset_max_count)
			{
				ctk_soft_reset_count = 0;
				SOFT_RST = 0x55;
			}
	}
	#endif
#endif

//-----------------------------------------------------------------//
//�������ƣ� void Set_SCLEN(void)
//�������ܣ� �����жϻָ�SCLEN����ʱ��0������Ч�����鶨ʱʱ������Ϊ1Ms
//��������� ��
//��������� ��
//�� �� ֵ�� ��
//-----------------------------------------------------------------//
#if Timer0_EN
	#ifdef IICS_EN
	#if IICS_EN
		void Set_SCLEN(void)
		{
		
				if(SCLEN == 0)
				{
					sclen_soft_reset_count++;//SCLENδ�ͷż���
					if(sclen_soft_reset_count >= sclen_soft_reset_max_count)
					{
						SCLEN_SET;
						sclen_soft_reset_count = 0;							
					}					
				}
				else
				{
					sclen_soft_reset_count = 0;	
				}	
		}
	#endif
	#endif
#endif


//-----------------------------------------------------------------//
//�������ƣ� void Timer0_Init(uint Timer0Us)
//�������ܣ� ��ʱ��0��ʼ��,����ʵ��Ӧ�����ó�ʼ��
//��������� �� 
//��������� ��
//�� �� ֵ�� ��
//-----------------------------------------------------------------//
#if Timer0_EN

	#pragma message "���룬void Timer0_Init(uint Timer0Us)����"
	void Timer0_Init(uint Timer0Us)
	{
		EA = 0;//�����жϣ�
		TH0 = 0;
		TL0 = 0;
		T0_IP_SET;//����Timer0�ж��ż�������ʵ��Ӧ������
		T0_INT_FLAG_CLR;//���Timer0�жϱ�־
		T0_CT_MODE(0); //Timer0��ʱ/����ģʽѡ��0Ϊ��ʱģʽ��1Ϊ����ģʽ
		T0_MODE_SET(1); //Timer0��ʱģʽѡ��0��13bit��ʱ�����ģʽ��1��16bit��ʱ��2��8bit�Զ�����ģʽ��ʱ�����ģʽ��3��8bit��ʱ�������8bit��ʱģʽ tiemr0_clk=(1/12)*sys_clk
		
		TH0_Reload = (65536 - ((uint)((Timer0Us*1.0)*((SYS_CLK_FRE*1.0)/12.0))))>>8;
		TL0_Reload = (65536 - ((uint)((Timer0Us*1.0)*((SYS_CLK_FRE*1.0)/12.0))));
		TH0 = TH0_Reload; 
		TL0 = TL0_Reload;
		
		// //��ʱ125us
		// TH0 = 0x83;//256-125;//256(us)-125(us);//(1/12)SYS_CLK(12MHz)
		// TL0 = 0x83;//256-125;
		
		#if SNS_NUM
			ctk_soft_reset_max_count = (500000 / Timer0Us);//���㶨ʱ500ms�Ĵ���
		#endif
		
		
		#ifdef IICS_EN
			#if IICS_EN
			sclen_soft_reset_max_count = (500000 / Timer0Us);//���㶨ʱ500ms�Ĵ���
			#endif
		#endif
		
		#ifdef IDLE_MODE
			#if IDLE_MODE
			Idle_Time_Count =  (1000 / Timer0Us);//���㶨ʱ1ms�Ĵ���
			#endif
		#endif
		
		#ifdef ADC_IS_OPEN
			#if ADC_IS_OPEN
				#if ADC_MODE
				ADC_Rest_Max_Count = (100000 / Timer0Us);//���㶨ʱ100ms�Ĵ���
				#endif
			#endif
		#endif


		T0_IE_SET;//ʹ��Timer0�ж� 
		T0_RUN;//����Timer0
		EA = 1;//�����ж�
		
	}
//-----------------------------------------------------------------//
//�������ƣ� void Timer0_ISR() interrupt 1
//�������ܣ� ��ʱ��0�ж��Ӻ���
//��������� ��
//��������� ��
//�� �� ֵ�� ��
//-----------------------------------------------------------------//
void Timer0_ISR() interrupt 1
{
	static uchar xdata addr_bak = 0;
	PUSH_REG_ADDR_SFR();
	
	TH0 = TH0 + TH0_Reload; 
	TL0 = TL0 + TL0_Reload;//���Զ�����ģʽ

	T0_INT_FLAG_CLR;//���Timer0�жϱ�־

	Test =~Test;

	#if SNS_NUM
			Reset_Cnt_Add();
			if((keys_flag_l != 0)||(keys_flag_h != 0))
			{
				long_key_clear_count++;	
			}
			else
			{
				long_key_clear_count = 0;
			}
	#endif
	
		#ifdef IICS_EN
			#if IICS_EN
				Set_SCLEN();
			#endif
		#endif

		#ifdef ADC_IS_OPEN
			#if ADC_IS_OPEN
				#if ADC_MODE
					ADC_Reset_Count();
				#endif
			#endif
		#endif

		#ifdef IDLE_MODE
			#if IDLE_MODE
				if((keys_flag_l == 0) && ((keys_flag_h == 0)))
				{
					if(Idle_Flag == 0)
					{
						Idle_Time_Count1++;
						
						if(Idle_Time_Count1 >= Idle_Time_Count)
						{
							Idle_Time_Count1 = 0;
							Idle_Wait_Count++;
							if(Idle_Wait_Count > (Step_In_Idle_Time-50))
							{							
									parallel_mode = 1;							
							}
							if(Idle_Wait_Count > Step_In_Idle_Time)
							{
								
								Idle_Wait_Count = 0;
								Idle_Flag = 1;
																						
							}
						}
					}
					else
					{
							
					}
				}
				else
				{
					Idle_Flag = 0;
					Idle_Time_Count1 = 0;
					Idle_Wait_Count = 0;
				}
			#endif
		#endif
		
		#ifdef VolDet_EN				
			#if(VolDet_EN == 1)
	
				if(Low_Volotage_Flag == 1)
				{
					if(Low_Volotage_Flag_Count < 10000)
					{
						Low_Volotage_Flag_Count++;
						if(Low_Volotage_Flag_Count >= VolDet_COUNT)//VolDet_COUNT*(timer0��ʱ)
						{
							Low_Volotage_Flag_Count = 0;
							Low_Volotage_Flag = 0;
							Low_Volotage_Flag_Confirm = 1;//VolDet_COUNT*(timer0��ʱ)
						}
					}	
				}
				if(Low_Volotage_Flag_Confirm == 1)
				{
					Low_Volotage_Flag_Confirm_count++;
					if(Low_Volotage_Flag_Confirm_count >= 30000)//����ʱ����ʱΪ1ms��30000��Ӧ30s�������㣬Low_Volotage_Flag_Confirm��0������ʵ����Ŀ����
					{
						Low_Volotage_Flag_Confirm_count = 0;
						Low_Volotage_Flag_Confirm = 0;
					}
				}
			#endif
		#endif
		POP_REG_ADDR_SFR();
}
#endif

//-----------------------------------------------------------------//
//�������ƣ� void Timer1_Init(uint Timer1Us)
//�������ܣ� ��ʱ��0��ʼ��
//��������� uint Timer1Us:��ʱTimer1Us usʱ�䣬Timer1Usȡֵ��Χ1~10000 
//��������� ��
//�� �� ֵ�� ��
//-----------------------------------------------------------------//
#if ((Timer1_EN == 1))
#pragma message "���룬void Timer1_Init(uint Timer1Us)����"
void Timer1_Init(uint Timer1Us)
{
	EA = 0;//�����жϣ�
	T1_IP_SET;//����Timer1�ж��ż�Ϊ�ߣ�����ʵ��Ӧ���������ȼ�
	T1_INT_FLAG_CLR;//���Timer1�жϱ�־
	T1_MODE_SET(1); //����Ϊ16λ��������tiemr1_clk=(1/12)*sys_clk

	TH1_Reload = (65536 - ((uint)((Timer1Us*1.0)*((SYS_CLK_FRE*1.0)/12.0))))>>8;
	TL1_Reload = (65536 - ((uint)((Timer1Us*1.0)*((SYS_CLK_FRE*1.0)/12.0))));
		
	TH1 = TH1_Reload; 
	TL1 = TL1_Reload;

	T1_IE_SET;//��Timer1�ж�ʹ�� 
	T1_RUN;//����Timer1
	EA = 1;//�����ж�	  
}
//-----------------------------------------------------------------//
//�������ƣ� void Timer1_ISR() interrupt 3
//�������ܣ� ��ʱ��1�ж��Ӻ���
//��������� ��
//��������� ��
//�� �� ֵ�� ��
//-----------------------------------------------------------------//
void Timer1_ISR() interrupt 3
{	
	static uchar xdata addr_bak = 0;
	PUSH_REG_ADDR_SFR();
	T1_INT_FLAG_CLR;//���Timer1�жϱ�־
	TH1 = TH1_Reload;   
	TL1 = TL1_Reload; 

	POP_REG_ADDR_SFR();
} 
#endif



//-----------------------------------------------------------------//
//�������ƣ� void Timer2_Init(unsigned int Timer2Ms)
//�������ܣ� ��ʱ��2��ʼ��
//��������� unsigned int Timer2Ms:��ʱimsʱ�䣬iȡֵ��Χ1~1999;,bit timer2_clk_sel:ʱ��Դѡ��0���ڲ�RC32.7KHz��1���ⲿ����32768Hz
//��������� ��
//�� �� ֵ�� ��
//-----------------------------------------------------------------//
#if Timer2_EN

	#pragma message "���룬void Timer2_Init(uint Timer2Ms,bit timer2_clk_sel)����"
	void Timer2_Init(unsigned int Timer2Ms,bit timer2_clk_sel)
	{
		unsigned int data dat;
				
		EA = 0;//�����жϣ�
		
		T2_IP_SET;//����Timer1�ж��ż�Ϊ�ߣ�����ʵ��Ӧ���������ȼ�
		T2_INT_FLAG_CLR;//���Timer2�жϱ�־
		T2_STOP;//bit0Ϊ0ʱֹͣ��ʱ��bit0Ϊ1ʱ������ʱ
		dat = (Timer2Ms * 32.768)-1;//�ڲ�RC32.7KHz
		TIMER2_SET_H = (dat / 256);//����Timer2��ʱ��ֵ��8λ
		TIMER2_SET_L = (dat % 256);//����Timer2��ʱ��ֵ��8λ
		T2_CNT_MODE_SET(0);//Timer2��ʱ����ģʽѡ��0��һ��ʱ�Ӳ�����1��65536��ʱ�Ӳ���
		T2_MODE_SET(1);//bit1Ϊ0ʱ�ֶ�����ģʽ��bit[1] 1Ϊʱ�Զ�����ģʽ  
		
		if (timer2_clk_sel == 0)//0Ϊ�ڲ�RC32K
		{
			T2_XTAL_SET(1);//Timer2 �ⲿ���񿪹�,1Ϊ�أ�0Ϊ��
			T2_CLK_SET(0);//Timer2��ʱʱ��ѡ��0���ڲ�RC32.7KHz��1���ⲿ����32768Hz
		}
		else//1Ϊ�ⲿ����32768Hz
		{
			TRISA |= 0x0C;
			T2_XTAL_SET(0);//Timer2 �ⲿ���񿪹�,1Ϊ�أ�0Ϊ��
			T2_CLK_SET(1);//Timer2��ʱʱ��ѡ��0���ڲ�RC32.7KHz��1���ⲿ����32768Hz
		}
		

		T2_IE_SET;//����Timer2�ж�ʹ��
		T2_RUN;//����Timer2
		EA = 1;//�����ж�	
	
	}
	#endif
//-----------------------------------------------------------------//
//�������ƣ� void Timer2_WDT_ISR() interrupt 14
//�������ܣ� ��ʱ��0�ж��Ӻ���
//��������� ��
//��������� ��
//�� �� ֵ�� ��
//-----------------------------------------------------------------//
void Timer2_WDT_ISR() interrupt 14
{
	static uchar xdata addr_bak = 0;
	PUSH_REG_ADDR_SFR();
	T2_INT_FLAG_CLR;//���Timer2�жϱ�־
	POP_REG_ADDR_SFR();
}


//-----------------------------------------------------------------//
//�������ƣ� void Timer3_Init(uint Timer3Us,bit timer3_clk_div)
//�������ܣ� ��ʱ��0��ʼ��
//��������� uint Timer3Us:��ʱTimer3Us usʱ�䣬Timer3Usȡֵ��Χ1~10000;bit timer3_clk_div: 0��24MHz/12��1��24MHz/4
//��������� ��
//�� �� ֵ�� ��
//-----------------------------------------------------------------//
#if ((Timer3_EN == 1))
#pragma message "���룬void Timer3_Init(uint Timer3Us,bit timer3_clk_div)����"
void Timer3_Init(uint Timer3Us,bit timer3_clk_div)
{
	EA = 0;//�����жϣ�
	T3_IP_SET;//����Timer1�ж��ż�Ϊ�ߣ�����ʵ��Ӧ���������ȼ�
	T3_INT_FLAG_CLR;//���Timer1�жϱ�־
	T3_CLK_DIV_SET((uchar)timer3_clk_div);//Timer3��ʱʱ�ӷ�Ƶѡ��0��24MHz/12��1��24MHz/4
	T3_MODE_SET(1); //Timer3��ʱģʽѡ��0���ֶ�����ģʽ��1��1�Զ�����ģʽ
	if(timer3_clk_div == 0)
	{

		TH3_Reload = ((uint)((Timer3Us*1.0)*((2.0))))>>8;
		TL3_Reload = ((uint)((Timer3Us*1.0)*((2.0))));
			
		TIMER3_SET_H = TH3_Reload; 
		TIMER3_SET_L = TL3_Reload;
		
	}
	else
	{
		TH3_Reload = ((uint)((Timer3Us*1.0)*((6.0))))>>8;
		TL3_Reload = ((uint)((Timer3Us*1.0)*((6.0))))-1;
			
		TIMER3_SET_H = TH3_Reload; 
		TIMER3_SET_L = TL3_Reload;
	}

	T3_IE_SET;//��Timer1�ж�ʹ�� 
	T3_RUN;//����Timer1
	EA = 1;//�����ж�	  
}
//-----------------------------------------------------------------//
//�������ƣ� void Timer3_ISR() interrupt 19
//�������ܣ� ��ʱ��1�ж��Ӻ���
//��������� ��
//��������� ��
//�� �� ֵ�� ��
//-----------------------------------------------------------------//
void Timer3_ISR() interrupt 19
{	
	static uchar xdata addr_bak = 0;
	PUSH_REG_ADDR_SFR();
	T3_INT_FLAG_CLR;//���Timer1�жϱ�־
	POP_REG_ADDR_SFR();
} 
#endif
		
