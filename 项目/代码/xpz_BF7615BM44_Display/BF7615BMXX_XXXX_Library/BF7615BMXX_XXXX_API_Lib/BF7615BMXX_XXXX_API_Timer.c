#include ".\BF7615BMXX_XXXX_Library\Config.h"
/****************************************************************/
//timer参考范例：BF7615BMXX_XXXX_API_Timer.c和BF7615BMXX_XXXX_API_Timer.h
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
//函数名称： void Reset_Cnt_Add()
//函数功能： CTK/IIC/外部中断出错计数器累加函数
//输入参数： 无
//输出参数： 无
//返 回 值： 无
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
//函数名称： void Set_SCLEN(void)
//函数功能： 计数判断恢复SCLEN，定时器0开启有效，建议定时时间设置为1Ms
//输入参数： 无
//输出参数： 无
//返 回 值： 无
//-----------------------------------------------------------------//
#if Timer0_EN
	#ifdef IICS_EN
	#if IICS_EN
		void Set_SCLEN(void)
		{
		
				if(SCLEN == 0)
				{
					sclen_soft_reset_count++;//SCLEN未释放计数
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
//函数名称： void Timer0_Init(uint Timer0Us)
//函数功能： 定时器0初始化,根据实际应用配置初始化
//输入参数： 无 
//输出参数： 无
//返 回 值： 无
//-----------------------------------------------------------------//
#if Timer0_EN

	#pragma message "编译，void Timer0_Init(uint Timer0Us)函数"
	void Timer0_Init(uint Timer0Us)
	{
		EA = 0;//关总中断；
		TH0 = 0;
		TL0 = 0;
		T0_IP_SET;//设置Timer0中断优级，根据实际应用配置
		T0_INT_FLAG_CLR;//清除Timer0中断标志
		T0_CT_MODE(0); //Timer0定时/计数模式选择0为定时模式，1为计数模式
		T0_MODE_SET(1); //Timer0定时模式选择：0：13bit定时或计数模式，1：16bit定时，2：8bit自动重载模式定时或计数模式，3：8bit定时或计数和8bit定时模式 tiemr0_clk=(1/12)*sys_clk
		
		TH0_Reload = (65536 - ((uint)((Timer0Us*1.0)*((SYS_CLK_FRE*1.0)/12.0))))>>8;
		TL0_Reload = (65536 - ((uint)((Timer0Us*1.0)*((SYS_CLK_FRE*1.0)/12.0))));
		TH0 = TH0_Reload; 
		TL0 = TL0_Reload;
		
		// //定时125us
		// TH0 = 0x83;//256-125;//256(us)-125(us);//(1/12)SYS_CLK(12MHz)
		// TL0 = 0x83;//256-125;
		
		#if SNS_NUM
			ctk_soft_reset_max_count = (500000 / Timer0Us);//计算定时500ms的次数
		#endif
		
		
		#ifdef IICS_EN
			#if IICS_EN
			sclen_soft_reset_max_count = (500000 / Timer0Us);//计算定时500ms的次数
			#endif
		#endif
		
		#ifdef IDLE_MODE
			#if IDLE_MODE
			Idle_Time_Count =  (1000 / Timer0Us);//计算定时1ms的次数
			#endif
		#endif
		
		#ifdef ADC_IS_OPEN
			#if ADC_IS_OPEN
				#if ADC_MODE
				ADC_Rest_Max_Count = (100000 / Timer0Us);//计算定时100ms的次数
				#endif
			#endif
		#endif


		T0_IE_SET;//使能Timer0中断 
		T0_RUN;//开启Timer0
		EA = 1;//开总中断
		
	}
//-----------------------------------------------------------------//
//函数名称： void Timer0_ISR() interrupt 1
//函数功能： 定时器0中断子函数
//输入参数： 无
//输出参数： 无
//返 回 值： 无
//-----------------------------------------------------------------//
void Timer0_ISR() interrupt 1
{
	static uchar xdata addr_bak = 0;
	PUSH_REG_ADDR_SFR();
	
	TH0 = TH0 + TH0_Reload; 
	TL0 = TL0 + TL0_Reload;//非自动重载模式

	T0_INT_FLAG_CLR;//清除Timer0中断标志

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
						if(Low_Volotage_Flag_Count >= VolDet_COUNT)//VolDet_COUNT*(timer0定时)
						{
							Low_Volotage_Flag_Count = 0;
							Low_Volotage_Flag = 0;
							Low_Volotage_Flag_Confirm = 1;//VolDet_COUNT*(timer0定时)
						}
					}	
				}
				if(Low_Volotage_Flag_Confirm == 1)
				{
					Low_Volotage_Flag_Confirm_count++;
					if(Low_Volotage_Flag_Confirm_count >= 30000)//若定时器定时为1ms，30000对应30s计数清零，Low_Volotage_Flag_Confirm清0，根据实际项目调试
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
//函数名称： void Timer1_Init(uint Timer1Us)
//函数功能： 定时器0初始化
//输入参数： uint Timer1Us:定时Timer1Us us时间，Timer1Us取值范围1~10000 
//输出参数： 无
//返 回 值： 无
//-----------------------------------------------------------------//
#if ((Timer1_EN == 1))
#pragma message "编译，void Timer1_Init(uint Timer1Us)函数"
void Timer1_Init(uint Timer1Us)
{
	EA = 0;//关总中断；
	T1_IP_SET;//设置Timer1中断优级为高，根据实际应运设置优先级
	T1_INT_FLAG_CLR;//清除Timer1中断标志
	T1_MODE_SET(1); //设置为16位计算器，tiemr1_clk=(1/12)*sys_clk

	TH1_Reload = (65536 - ((uint)((Timer1Us*1.0)*((SYS_CLK_FRE*1.0)/12.0))))>>8;
	TL1_Reload = (65536 - ((uint)((Timer1Us*1.0)*((SYS_CLK_FRE*1.0)/12.0))));
		
	TH1 = TH1_Reload; 
	TL1 = TL1_Reload;

	T1_IE_SET;//开Timer1中断使能 
	T1_RUN;//开启Timer1
	EA = 1;//开总中断	  
}
//-----------------------------------------------------------------//
//函数名称： void Timer1_ISR() interrupt 3
//函数功能： 定时器1中断子函数
//输入参数： 无
//输出参数： 无
//返 回 值： 无
//-----------------------------------------------------------------//
void Timer1_ISR() interrupt 3
{	
	static uchar xdata addr_bak = 0;
	PUSH_REG_ADDR_SFR();
	T1_INT_FLAG_CLR;//清除Timer1中断标志
	TH1 = TH1_Reload;   
	TL1 = TL1_Reload; 

	POP_REG_ADDR_SFR();
} 
#endif



//-----------------------------------------------------------------//
//函数名称： void Timer2_Init(unsigned int Timer2Ms)
//函数功能： 定时器2初始化
//输入参数： unsigned int Timer2Ms:定时ims时间，i取值范围1~1999;,bit timer2_clk_sel:时钟源选择：0：内部RC32.7KHz，1：外部晶振32768Hz
//输出参数： 无
//返 回 值： 无
//-----------------------------------------------------------------//
#if Timer2_EN

	#pragma message "编译，void Timer2_Init(uint Timer2Ms,bit timer2_clk_sel)函数"
	void Timer2_Init(unsigned int Timer2Ms,bit timer2_clk_sel)
	{
		unsigned int data dat;
				
		EA = 0;//关总中断；
		
		T2_IP_SET;//设置Timer1中断优级为高，根据实际应运设置优先级
		T2_INT_FLAG_CLR;//清除Timer2中断标志
		T2_STOP;//bit0为0时停止计时，bit0为1时开启计时
		dat = (Timer2Ms * 32.768)-1;//内部RC32.7KHz
		TIMER2_SET_H = (dat / 256);//设置Timer2定时初值高8位
		TIMER2_SET_L = (dat % 256);//设置Timer2定时初值低8位
		T2_CNT_MODE_SET(0);//Timer2定时步进模式选择：0：一个时钟步进，1：65536个时钟步进
		T2_MODE_SET(1);//bit1为0时手动重载模式，bit[1] 1为时自动重载模式  
		
		if (timer2_clk_sel == 0)//0为内部RC32K
		{
			T2_XTAL_SET(1);//Timer2 外部晶振开关,1为关，0为开
			T2_CLK_SET(0);//Timer2定时时钟选择：0：内部RC32.7KHz，1：外部晶振32768Hz
		}
		else//1为外部晶振32768Hz
		{
			TRISA |= 0x0C;
			T2_XTAL_SET(0);//Timer2 外部晶振开关,1为关，0为开
			T2_CLK_SET(1);//Timer2定时时钟选择：0：内部RC32.7KHz，1：外部晶振32768Hz
		}
		

		T2_IE_SET;//开启Timer2中断使能
		T2_RUN;//开启Timer2
		EA = 1;//开总中断	
	
	}
	#endif
//-----------------------------------------------------------------//
//函数名称： void Timer2_WDT_ISR() interrupt 14
//函数功能： 定时器0中断子函数
//输入参数： 无
//输出参数： 无
//返 回 值： 无
//-----------------------------------------------------------------//
void Timer2_WDT_ISR() interrupt 14
{
	static uchar xdata addr_bak = 0;
	PUSH_REG_ADDR_SFR();
	T2_INT_FLAG_CLR;//清除Timer2中断标志
	POP_REG_ADDR_SFR();
}


//-----------------------------------------------------------------//
//函数名称： void Timer3_Init(uint Timer3Us,bit timer3_clk_div)
//函数功能： 定时器0初始化
//输入参数： uint Timer3Us:定时Timer3Us us时间，Timer3Us取值范围1~10000;bit timer3_clk_div: 0：24MHz/12，1：24MHz/4
//输出参数： 无
//返 回 值： 无
//-----------------------------------------------------------------//
#if ((Timer3_EN == 1))
#pragma message "编译，void Timer3_Init(uint Timer3Us,bit timer3_clk_div)函数"
void Timer3_Init(uint Timer3Us,bit timer3_clk_div)
{
	EA = 0;//关总中断；
	T3_IP_SET;//设置Timer1中断优级为高，根据实际应运设置优先级
	T3_INT_FLAG_CLR;//清除Timer1中断标志
	T3_CLK_DIV_SET((uchar)timer3_clk_div);//Timer3定时时钟分频选择：0：24MHz/12，1：24MHz/4
	T3_MODE_SET(1); //Timer3定时模式选择：0：手动重载模式，1：1自动重载模式
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

	T3_IE_SET;//开Timer1中断使能 
	T3_RUN;//开启Timer1
	EA = 1;//开总中断	  
}
//-----------------------------------------------------------------//
//函数名称： void Timer3_ISR() interrupt 19
//函数功能： 定时器1中断子函数
//输入参数： 无
//输出参数： 无
//返 回 值： 无
//-----------------------------------------------------------------//
void Timer3_ISR() interrupt 19
{	
	static uchar xdata addr_bak = 0;
	PUSH_REG_ADDR_SFR();
	T3_INT_FLAG_CLR;//清除Timer1中断标志
	POP_REG_ADDR_SFR();
} 
#endif
		
