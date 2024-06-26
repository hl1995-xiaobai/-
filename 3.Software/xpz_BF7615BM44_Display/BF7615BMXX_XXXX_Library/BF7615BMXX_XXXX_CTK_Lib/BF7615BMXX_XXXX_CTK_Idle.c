#include ".\BF7615BMXX_XXXX_Library\Config.h"
#if IDLE_MODE
	uint Idle_Cnt = 0;
	bit Idle_Flag = 0;
	uint xdata Idle_Wait_Count = 0;
	uint xdata Idle_Time_Count = 0;
	uint xdata Idle_Time_Count1 = 0;
	uint xdata Step_In_Idle_Time = 0;
	uint xdata Idle_Wake_Up_Time = 0;
	
	unsigned int  xdata raw_data_parallel[1] =  {0};
	unsigned int  xdata base_line_parallel[1] = {0};	
	unsigned char xdata Cnt_Par[4] = 0;
#endif

#if IDLE_MODE

	#pragma message "编译,IDLE功能"

	//-----------------------------------------------------------------//
	//函数名称： Idle_IORecovrey()
	//函数功能： 唤醒后，将使用的应用的IO口设置成需要的状态
	//输入参数： 无
	//输出参数： 无
	//返 回 值： 无
	//-----------------------------------------------------------------//
	void Idle_IORecovrey()
	{
	//根据应用还原IO口状态
	}

	//-----------------------------------------------------------------//
	//函数名称： Idle_IO_Init()
	//函数功能： Idle模式初始化IO,建议将未用到的IO口设置为输出为低
	//输入参数： 无
	//输出参数： 无
	//返 回 值： 无
	//-----------------------------------------------------------------//
	void Idle_IO_Init()
	{
	//根据应用初始化IO	
		
	}

	//-----------------------------------------------------------------//
	//函数名称： void Idle_Wake_Up_Init(uint _Step_In_Idle_Time,uint _Idle_Wake_Up_Time)
	//函数功能： Idle模式初始化设置
	//输入参数： uint _Step_In_Idle_Time为连续无按键触摸_Step_In_Idle_Time毫秒后进入睡眠模式(建议>=5000),该值必须大于一轮keysFlagSN置位的时间
	//			 uint _Idle_Wake_Up_Time为最长等待唤醒时间，范围为0~7，0:18ms,1:36ms,2:72ms,3:144ms,4:288ms,5:576ms,6:1156ms,7:2304ms
	//输出参数： 无
	//返 回 值： 无
	//-----------------------------------------------------------------//
	void Idle_Wake_Up_Init(uint _Step_In_Idle_Time,uint _Idle_Wake_Up_Time)
	{
		Idle_IO_Init();
		Step_In_Idle_Time = _Step_In_Idle_Time;//开启Time0，Timer0中断函数中使用。
		Idle_Wake_Up_Time = _Idle_Wake_Up_Time;

	}
	//-----------------------------------------------------------------//
	//函数名称： void Idle()
	//函数功能： 进入Idle模式函数，配置了手指触摸后进入睡眠的时间以及为触摸时扫描按键的时间
	//输入参数： 无
	//输出参数： 无
	//返 回 值： 无
	//-----------------------------------------------------------------//
	void Idle()
	{
		long differ_para = 0;

		if(Idle_Flag == 1)
		{
			if(ctk_para_done == 1)//中断扫描完一轮
			{
					CTK_IE_CLR;//关CTK中断
					differ_para = ((long)base_line_parallel[0] - (long)raw_data_parallel[0]);
				
					if(differ_para >= 0)
					{
						if(differ_para >= FTH_PARA)
						{
							

								Cnt_Par[0]++;
								if(Cnt_Par[0] >= 0)
								{
										
										Cnt_Par[0]= 0; 
									
										Idle_Flag = 0;
										parallel_mode = 0;
										
									
										differ_para = 0;
										Idle_Time_Count1 = 0;
										Idle_Wait_Count = 0;
											
								}
								Cnt_Par[1] = 0;
								Cnt_Par[2] = 0;
								Cnt_Par[3] = 0;
								
						}
						else if(differ_para >= FTH_PARA/5)
						{
								Cnt_Par[1]++;
								if(Cnt_Par[1] >= PAR_PnoiseRenMaxCnt)
								{
										Cnt_Par[1]= 0; 
										base_line_parallel[0] -= 5;
								}
								Cnt_Par[0] = 0;
								Cnt_Par[2] = 0;
								Cnt_Par[3] = 0;
							
							
						}
						
						else if(differ_para >= 0)
						{
								Cnt_Par[2]++;
								if(Cnt_Par[2] >= PAR_PnoiseRenMaxCnt)
								{
										Cnt_Par[2]= 0; 
										base_line_parallel[0]--;
								}
								Cnt_Par[0] = 0;
								Cnt_Par[1] = 0;
								Cnt_Par[3] = 0;
								
						}
					}
					else
					{

							Cnt_Par[3]++;
							if(Cnt_Par[3] >= PAR_NnoiseRenMaxCnt)
							{
									Cnt_Par[3]= 0; 
									base_line_parallel[0] = raw_data_parallel[0];
							}
							Cnt_Par[0] = 0;
							Cnt_Par[1] = 0;
							Cnt_Par[2] = 0;
					}
					
					#if (TRACEMODE == 0)
						if(Idle_Flag == 1)
						{
					
							EA = 0; //关总中断
							WDT_IE_SET;	//开WDT中断使能
							
							Idle_IO_Init();
							//关闭已打开的所有会产生中断的模块及其中断使能并清除相关中断标志位，仅保留用于唤醒的模块
							T0_STOP; //关闭 Timer0
							T0_IE_CLR; //关闭 Timer0 中断
							T0_INT_FLAG_CLR; //清除 Timer0 中断标志
							
							CTK_STOP;
							CTK_IE_CLR;//关CTK中断
							CTK_PD_SET(1);//0为CTK开，1为CTK关
							
							LVDT_ON_OFF_SET(1);//0为开启LVDT检测模块,1为关闭LVDT检测模块
							LVDT_IE_CLR;//关降压升压检中断
							LVDT_INT_FLAG_CLR;//清除降压升压中断标志位
							LVDT_INT_DOWN_FLAG_CLR;//清除电压下降中断标志位	
							LVDT_INT_UP_FLAG_CLR;//清除电压上升中断标志位	
							
							Delay_Ms(1);//执行PCON = 0x01前延时>=100us
							
							WDT_CTRL = Idle_Wake_Up_Time;//设置看门狗溢出时间
							
							EA = 1; //开总中断
							
							PCON = 0x01;//进入省电模式等待唤醒
							
							EA = 0; //关总中断					
							
							//唤醒后根据实际应用情况来恢复相应模块及其中断使能
							T0_IE_SET;//开定时器0中断,唤醒后根据实际应用开启模块功能
							T0_RUN; //开启 Timer0
							
							CTK_PD_SET(0);//0为CTK开，1为CTK关
							CTK_IE_SET;//开CTK中断
							CTK_START;
							
							LVDT_ON_OFF_SET(0);//0为开启LVDT检测模块,1为关闭LVDT检测模块
							LVDT_IE_SET;//开降压升压检中断
							
							Idle_IORecovrey();
							
							EA = 1; //开总中断
						}
					#endif	
					
					ctk_para_done = 0;
					CTK_IE_SET;//开CTK中断
			}
			
			#if TRACEMODE
		
					raw_data[25] = raw_data_parallel[0];
					base_line[25] = base_line_parallel[0];//查看并联模式数据时，raw_data[25]对应的SNS关闭
					
			#endif
			
		}//IDLE
		else
		{
				#if TRACEMODE
		
					raw_data[25] = raw_data_parallel[0];
					base_line[25] = base_line_parallel[0];//查看并联模式数据时，raw_data[25]对应的SNS关闭
					
				#endif
		}
	
	}	
#endif	
		
