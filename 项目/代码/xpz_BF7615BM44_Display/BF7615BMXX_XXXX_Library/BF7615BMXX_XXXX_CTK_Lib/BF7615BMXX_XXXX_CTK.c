#include ".\BF7615BMXX_XXXX_Library\Config.h"

unsigned int  xdata raw_data[CH_MAX] ={0};
unsigned int  xdata base_line[CH_MAX] = {1};

#if SNS_NUM
	unsigned char xdata Mode = 0;
	unsigned char  sns_next = 0;
	static unsigned char xdata adjust_count = 0;

	#if (CS_SW == 1)
		uint cs_noise = 0;
	#endif

	bit adjust_done_flag = 0;
	bit ctk_circle_done = 0;
	bit ctk_start_flag = 0;

	unsigned int xdata pull_i_value_parallel = 255;
	unsigned long xdata open_sns_l = 0;
	unsigned long xdata open_sns_h = 0;

	unsigned char xdata parallel_mode = 0;
	bit parallel_init_flag = 1;
	bit ctk_para_done = 0;
	unsigned int 	xdata ctk_soft_reset_count = 0;

	unsigned long xdata muli_key_flag_l = 0;
	unsigned long xdata muli_key_flag_h = 0;
	
	unsigned long xdata keys_flag_l = 0;	
	unsigned long xdata keys_flag_h = 0;	
	unsigned long xdata mode_flag_l = 0;
	unsigned long xdata mode_flag_h = 0;	
	
	unsigned long xdata sensor_flag_l = 0;	
	unsigned long xdata sensor_flag_h = 0;	
	unsigned int  xdata long_key_clear_count = 0;		

	
	unsigned char xdata multi_key_count = 0;
	unsigned char xdata multi_key_reset_cnt = 0;

	#if (RENOVATE_MODE == 1)
	bit water_flow_flag = 0;	
	unsigned int 	xdata water_flow_left_count = 0;	
	unsigned char xdata water_flow_key_count = 0;	
	unsigned char xdata water_flow_key_reset_cnt = 0;
	#endif
	

	#if UN_NORMAL_CHECK
			unsigned char xdata un_normal_count = 0;
			unsigned char xdata un_normal_recover_count = 0;
			bit un_normal_flag = 0;
			unsigned long xdata adjust_flag = 0;
	#endif
	
	void CTK_BF7615BMXX_XXXX_Adjust_Int(void);
	void CTK_BF7615BMXX_XXXX_Para_Adjust_Int(void);
	void CTK_BF7615BMXX_XXXX_Get_KEYS_Touch(unsigned char sns);
	void Base_Line_Init();
	void Set_Next_SNS(void);

#if IDLE_MODE
	
	//-----------------------------------------------------------------//
	//函数名称： void Set_Para_SNS(void)
	//函数功能： 设置并联模式通道
	//输入参数： 无
	//输出参数： 无
	//返 回 值： 无
	//-----------------------------------------------------------------//	
	void Set_Para_SNS(void)
	{
			CTK_PAR_SET(1); 					//0为单通道模式，1为多通道并联模式
			CTK_PULL_I_SET(pull_i_value_parallel);//设置级数
			CTK_RESO_SET(CTK_PARA_RESO); 
			CTK_PRS_SET(CTK_PARA_PRS);
			CTK_RB_SET(CTK_PARA_RB);	
			CTK_VTH_SET(CTK_PARA_REF);	
			CTK_ADDR_SET(sensor_open[0]);
			CTK_START;
	}
	
	//-----------------------------------------------------------------//
	//函数名称： void CTK_BF7615BMXX_XXXX_Para_Adjust_Int(void)
	//函数功能：并联模式通道电流源自适应
	//输入参数： 无
	//输出参数： 无
	//返 回 值： 无
	//-----------------------------------------------------------------//        

	void CTK_BF7615BMXX_XXXX_Para_Adjust_Int(void)
	{
		if(adjust_count < 3)
		{
			while(1)
			{
				WDT_CTRL = 7;
				
				if((raw_data_parallel[0] >= ADJUST_PARA_LINE))
				{
					if(pull_i_value_parallel < (511 - ADJUST_STE))
					{
						pull_i_value_parallel += (1 + ADJUST_STE);
						
						
						Set_Para_SNS();
						return;
					}	
					else
					{
						parallel_init_flag = 1;
						base_line_parallel[0] = raw_data_parallel[0];						
						Set_Next_SNS();
						return;
					}
				}
				else
				{	
						if(adjust_count < 3)
						{
							adjust_count++;
						}

						if(pull_i_value_parallel > (0))
						{
							pull_i_value_parallel-= (1);
							
							Set_Para_SNS();
							
							return;
						}
						else
						{
								Set_Para_SNS();
								return;
						}	
				}
			}
		}
		
		if(adjust_count >= 3)
		{
			while(1)
			{
				WDT_CTRL = 7;
				
				if((raw_data_parallel[0] <= ADJUST_PARA_LINE))
				{
					if(pull_i_value_parallel > (0))
					{
						pull_i_value_parallel -= (1);
					
						Set_Para_SNS();
						return;
					}	
					else
					{
						parallel_init_flag = 1;
						base_line_parallel[0] = raw_data_parallel[0];
						Set_Next_SNS();
						return;
					}
				}
				else
				{	
						if(adjust_count < 6)
						{
							adjust_count++;
						}
						if(adjust_count >= 6)
						{
							adjust_count = 0;
							parallel_init_flag = 1;
							base_line_parallel[0] = raw_data_parallel[0];						
							Set_Next_SNS();
							return;
						}

						if(pull_i_value_parallel < (511 - ADJUST_STE))
						{
							pull_i_value_parallel += (1 + ADJUST_STE);

							Set_Para_SNS();
							return;
						}
						else
						{
								Set_Para_SNS();
								return;
						}	
				}
			}
		}
	}
	#endif
	
//-----------------------------------------------------------------//
//函数名称： void CTK_Set_Para(void)
//函数功能： 设置CTK扫描参数及基线更新参数
//输入参数： 无
//输出参数： 无
//返 回 值： 无
//-----------------------------------------------------------------//
void CTK_Set_Para(void)
{

		unsigned char i = 0;
			
		for (i = 0; i < SNS_NUM; i++)
		{
				sensor_open[i] = SNS[i];
				
				if(sensor_open[i] < 32)
				{
					open_sns_l |= ((ulong)0x01)<<sensor_open[i];
				}
				else
				{
					open_sns_h |= ((ulong)0x01)<<(sensor_open[i] - 32);
				}
				//通道配置
			
				pull_i_value[i] = PUIV[sensor_open[i]];//电流源级数;
				raw_data[i] = 0;
				//上拉电流源初始化
		}

		
}
//-----------------------------------------------------------------//
//函数名称： void Set_Next_SNS(void)
//函数功能： 设置下一个通道
//输入参数： 无
//输出参数： 无
//返 回 值： 无
//-----------------------------------------------------------------//	
void Set_Next_SNS(void)
{
	CTK_BF7615BMXX_XXXX_Set_Para(pull_i_value[sns_next]);
	CTK_ADDR_SET(sensor_open[sns_next]);
	#if IDLE_MODE
		CTK_PAR_SET(0); 					//0为单通道模式，1为多通道并联模式
		CTK_RESO_SET(CTK_RESO); 
		CTK_PRS_SET(CTK_PRS); 
		CTK_VTH_SET(CTK_REF);	
		CTK_RB_SET(CTK_RB);	
	#endif
	
	CTK_START;
}

//-----------------------------------------------------------------//
//函数名称： void CTK_ISR() interrupt 12
//函数功能： CTK中断服务函数
//输入参数： 无
//输出参数： 无
//返 回 值： 无
//-----------------------------------------------------------------//	
void CTK_ISR() interrupt 12
{
			static uchar xdata addr_bak = 0;
		 	PUSH_REG_ADDR_SFR();
			CTK_INT_FLAG_CLR;//清除CTK中断标志位

			CTK_STOP;	
			ctk_soft_reset_count = 0;
			
			if(parallel_mode == 0)
			{
				
					#if (CS_SW == 1)
					if(adjust_done_flag == 0)
					#endif		
					{					
						EA = 0;
						raw_data[sns_next] = ((unsigned int)CSD_RAWDATAH << 8) | (unsigned int)CSD_RAWDATAL;//获取CTK数据
						EA = 1;	
					}
					
					
					if(adjust_done_flag == 0)
					{

						#if IDLE_MODE
							parallel_init_flag = 0;
						#endif
						
						CTK_BF7615BMXX_XXXX_Adjust_Int();
						
					}
					else
					{
							if(parallel_init_flag == 1)
							{

								#if (CS_SW == 1)	
									cs_noise = Data_Deal(8,0,SNS_NUM); 
									Set_Next_SNS();
								#else
								
								sns_next++;
								while(sensor_open[sns_next] == 0xFF)
								{
										CTK_STOP;	
										sns_next++;
										if(sns_next >= SNS_NUM)
										{
												sns_next = 0;
												ctk_circle_done = 1;
												break;
										}
								}
								if(sns_next >= SNS_NUM)
								{
										sns_next = 0;
										ctk_circle_done = 1;
								}
						
								Set_Next_SNS();
								#endif
							
							}
							#if IDLE_MODE
							else
							{
										EA = 0;
										raw_data_parallel[0] = ((unsigned int)CSD_RAWDATAH << 8) | (unsigned int)CSD_RAWDATAL;//获取CTK数据
										EA = 1;
										
										CTK_BF7615BMXX_XXXX_Para_Adjust_Int();
							}
							#endif
					}
			}
			#if IDLE_MODE
			else
			{
					EA = 0;
					raw_data_parallel[0] = ((unsigned int)CSD_RAWDATAH << 8) | (unsigned int)CSD_RAWDATAL;//获取CTK数据
					EA = 1;
				
					ctk_para_done = 1;
					Set_Para_SNS();
					
			}
			#endif
			POP_REG_ADDR_SFR();
}


//-----------------------------------------------------------------//
//函数名称： void Base_Line_Init()
//函数功能： 基线初始化
//输入参数： 无
//输出参数： 无
//返 回 值： 无
//-----------------------------------------------------------------//

void Base_Line_Init()
{   
		unsigned char xdata i;
		for (i = 0; i < SNS_NUM; i++) 
		{
			#if (KEYS_RENOVATE_FLAG_L || KEYS_RENOVATE_FLAG_H)
					EA = 0;
					base_line[i] = raw_data[i];
					EA = 1;
			#endif
		}	
}

//-----------------------------------------------------------------//
//函数名称： void CTK_BF7615BMXX_XXXX_Get_KEYS_Touch(unsigned char sns)
//函数功能： 获取按键标志，长按超时清除
//输入参数： unsigned char sns:对应的Sensor通道
//输出参数： 无
//返 回 值： 无
//-----------------------------------------------------------------//
void CTK_BF7615BMXX_XXXX_Get_KEYS_Touch(unsigned char sns)
{

	if(sensor_open[sns] < 32)
	{
		if(((sensor_flag_l & (((unsigned long)0x01) << sensor_open[sns]))==0))
		{
			touch_left_count[sns]++;
			
			if(touch_left_count[sns] >= TK_LEFT_COUNT)
			{
					touch_left_count[sns] = 0;
					keys_flag_l &= ~(((unsigned long)0x01) << sensor_open[sns]);
			}
		}
		else
		{
			touch_left_count[sns] = 0;
		}
	}
	else
	{
		if(((sensor_flag_h & (((unsigned long)0x01) << (sensor_open[sns]-32)))==0))
		{
			touch_left_count[sns]++;
			
			if(touch_left_count[sns] >= TK_LEFT_COUNT)
			{
					touch_left_count[sns] = 0;
					keys_flag_h &= ~(((unsigned long)0x01) << (sensor_open[sns]-32));
			}
		}
		else
		{
			touch_left_count[sns] = 0;
		}
	}
	
	
	if((sensor_flag_l != 0)||(sensor_flag_h != 0))
	{
		#if(LONG_KEY_COUNT != 0)
			if(long_key_clear_count >= LONG_KEY_COUNT)
			{
				Base_Line_Init();
				long_key_clear_count = 0;
				keys_flag_l = sensor_flag_l = 0;
				keys_flag_h = sensor_flag_h = 0;
			}
			
		#endif	
	}
	else
	{
		long_key_clear_count = 0;
	}
			

}	

//-----------------------------------------------------------------//
//函数名称： void CTK_SNS_Renovate(unsigned char addr,unsigned int fth)
//函数功能： SNS基线更新
//输入参数： unsigned char addr：SNS通道;unsigned int fth:手指阈值
//输出参数： 无
//返 回 值： 无
//-----------------------------------------------------------------//
void CTK_SNS_Renovate(unsigned char addr,unsigned int fth)
{
	uchar i = 0;
	long differ = 0;
	long differ_mode1 = 0;
	long fth_tem = 0;
	fth_tem = fth;
	differ = (long)base_line[addr] - (long)raw_data[addr];
	
	#if (CS_SW == 1)
		if(cs_noise >= CS_NOISE)
		{
			fth_tem = (CS_FTH_RATE*fth_tem)/10;
		}
		if(sensor_open[addr] < 32)
		{
			if((keys_flag_l & ((ulong)0x01 << sensor_open[addr])))
			{
				fth_tem = (FTHD_HY_RATE*fth_tem)/10;
			}
		}
		else
		{
			if((keys_flag_h & ((ulong)0x01 << (sensor_open[addr]-32))))
			{
				fth_tem = (FTHD_HY_RATE*fth_tem)/10;
			}
		}

	#endif
	
	
	
	#if (RENOVATE_MODE == 1)
		//模式1
		
			if(water_flow_flag == 1)
			{
				if(sensor_open[addr] < 32)
				{
					if((mode_flag_l & (((unsigned long)0x01) << sensor_open[addr])))
					{
							fth_tem = (fth_tem*RENOVATE_MODE1_FTH_RATE/10);//模式1手指阈值	
					}
				}
				else
				{
					if((mode_flag_h & (((unsigned long)0x01) << (sensor_open[addr]-32))))
					{
							fth_tem = (fth_tem*RENOVATE_MODE1_FTH_RATE/10);//模式1手指阈值	
					}
				}
			}
	#endif
		if(sensor_open[addr] < 32)
		{
			if((keys_flag_l & ((ulong)0x01 << sensor_open[addr])))
			{
				fth_tem = (TK_RATE_HY*fth_tem)/10;
			}
		}
		else
		{
			if((keys_flag_h & ((ulong)0x01 << (sensor_open[addr]-32))))
			{
				fth_tem = (TK_RATE_HY*fth_tem)/10;
			}
		}
	
		#if (MULTI_KEY_MAX_COUNT != 0)
		if(differ >= 0)
		{
			if(differ >= (((int)fth)*RENOVATE_NTH_RATE/10))//多按键标志判断
			{
					if(sensor_open[addr] < 32)
					{
						muli_key_flag_l |= ((long)0x01 << sensor_open[addr]);	
					}
					else
					{
						muli_key_flag_h |= ((long)0x01 << (sensor_open[addr]-32));	
					}
			}
			else
			{
					if(sensor_open[addr] < 32)
					{
						muli_key_flag_l &= ~((long)0x01 << sensor_open[addr]);	
					}
					else
					{
						muli_key_flag_h &= ~((long)0x01 << (sensor_open[addr]-32));	
					}	
			}
		}
		else
		{
				if(sensor_open[addr] < 32)
				{
					muli_key_flag_l &= ~((long)0x01 << sensor_open[addr]);	
				}
				else
				{
					muli_key_flag_h &= ~((long)0x01 << (sensor_open[addr]-32));	
				}		
		}
		#endif
		
		#if (RENOVATE_MODE == 1)
		//模式1
		differ_mode1 = (long)n_base_line[addr] - (long)base_line[addr];

		if(differ_mode1 >= 0)//模式1differ判断
		{
			if(differ_mode1 >= (((int)fth)*WATER_FLOW_RATE/10))//模式1标志判断
			{
					if(sensor_open[addr] < 32)
					{
						mode_flag_l |= ((long)0x01 << sensor_open[addr]);	
					}
					else
					{
						mode_flag_h |= ((long)0x01 << (sensor_open[addr]-32));	
					}
					n_base_line_reno_count[addr] = 0;
			}
			else
			{
					n_base_line_reno_count[addr]++;
					if(n_base_line_reno_count[addr] >= N_BASE_LINE_RENO_MAX_COUNT)
					{
							n_base_line[addr] -= differ_mode1/10;
							n_base_line_reno_count[addr] = 0;
						
							if(sensor_open[addr] < 32)
							{
								if(KEYS_RENOVATE_FLAG_L &(((unsigned long)0x01)<<sensor_open[addr]))
								{
									mode_flag_l &= ~((long)0x01 << sensor_open[addr]);
								}						
							}
							else
							{
								if(KEYS_RENOVATE_FLAG_H &(((unsigned long)0x01)<< (sensor_open[addr]-32)))
								{
									mode_flag_h &= ~((long)0x01 << (sensor_open[addr]-32));
								}
							}
					}
			}
		}
		else
		{
				if(sensor_open[addr] < 32)
				{
					if(KEYS_RENOVATE_FLAG_L &(((unsigned long)0x01)<<sensor_open[addr]))
					{
				
						n_base_line[addr] -= differ_mode1/10;
						
					}
				}
				else
				{
					if(KEYS_RENOVATE_FLAG_H &(((unsigned long)0x01)<<(sensor_open[addr]-32)))
					{
				
						n_base_line[addr] -= differ_mode1/10;
						
					}
				}

				if(sensor_open[addr] <32)
				{
					mode_flag_l &= ~((long)0x01 << sensor_open[addr]);
				}
				else
				{
					mode_flag_h &= ~((long)0x01 << (sensor_open[addr]-32));
				}
		}

		water_flow_key_count = 0;
		for(i = 0; i < SNS_NUM;i++)//模式1多按键判断
		{
			if(sensor_open[i] < 32)
			{
				if((mode_flag_l & (((unsigned long)0x01) << sensor_open[i])))
				{
					water_flow_key_count++;//模式1溢水计数
				}
			}
			else
			{
				if((mode_flag_h & (((unsigned long)0x01) << (sensor_open[i]-32))))
				{
					water_flow_key_count++;//模式1溢水计数
				}
			}
		}
	
		if(water_flow_key_count > WATER_FLOW_MAX_COUNT)//模式1溢水判断
		{
				
				water_flow_key_count = 0;
				water_flow_key_reset_cnt++;
				if(water_flow_key_reset_cnt >= WATER_FLOW_RST_COUNT)
				{
					water_flow_key_reset_cnt = 0;		
					if(water_flow_flag == 0)
					{
						Base_Line_Init();
						water_flow_flag = 1;
						
					}
				}
		}
		else
		{
			if(water_flow_flag == 1)//模式1溢水标志判断计数清除
			{
					water_flow_left_count++;
					if(water_flow_left_count >= WATER_FLOW_LEFT_MAX_COUNT)
					{
						water_flow_flag = 0;
						water_flow_left_count = 0;
					}
			}
			else
			{
				water_flow_left_count = 0;
			}
		}
	#endif

	if(differ >= 0)//differ大于0情况
	{
		#if (RENOVATE_MODE == 1)
			//模式1
			if(sensor_open[addr] < 32)
			{
				if((mode_flag_l & (((unsigned long)0x01) << sensor_open[addr])))
				{
						fth_tem = (fth_tem*RENOVATE_MODE1_FTH_RATE/10);//模式1手指阈值	
				}
			}
			else
			{
				if((mode_flag_h & (((unsigned long)0x01) << (sensor_open[addr]-32))))
				{
						fth_tem = (fth_tem*RENOVATE_MODE1_FTH_RATE/10);//模式1手指阈值	
				}
			}
		#endif
			
		if(differ >= (fth_tem*RENOVATE_FTH_RATE/10))
		{
				//不作基线更新
		}
		else if(differ >= (((int)fth)*RENOVATE_NTH_RATE/10))//>=p_noise基线更新
		{
				#if(RENOVATE_MODE == 0)//模式0基线更新
				
						over_p_noise_count[addr]++;
						
						under_p_noise_count[addr] = 0;
						over_n_noise_count[addr] = 0;
						under_n_noise_count[addr] = 0;
						under_2n_noise_count[addr] = 0;
						if(over_p_noise_count[addr] >= OVER_P_NOISE_MAX_COUNT)
						{
							over_p_noise_count[addr] = 0;
							
							#if (KEYS_RENOVATE_FLAG_L || KEYS_RENOVATE_FLAG_H)
							if(sensor_open[addr] < 32)
							{
								if(KEYS_RENOVATE_FLAG_L &(((unsigned long)0x01)<<sensor_open[addr]))
								{
									if(base_line[addr] >= (((int)fth)*RENOVATE_NTH_RATE/10/5))
									{
										base_line[addr] -= differ/5;
									}
								}
							}
							else
							{
								if(KEYS_RENOVATE_FLAG_H &(((unsigned long)0x01)<<(sensor_open[addr]-32)))
								{
									if(base_line[addr] >= (((int)fth)*RENOVATE_NTH_RATE/10/5))
									{
					
										base_line[addr] -= differ/5;
										
									}
								}
							}
							#endif

						}
				
				#endif
						
				#if(RENOVATE_MODE == 1)//模式1基线更新
				
						over_p_noise_count[addr]++;
						
						under_p_noise_count[addr] = 0;
						over_n_noise_count[addr] = 0;
						under_n_noise_count[addr] = 0;
						under_2n_noise_count[addr] = 0;
						if(over_p_noise_count[addr] >= WATER_OVER_P_NOISE_MAX_COUNT)
						{
							over_p_noise_count[addr] = 0;
							#if (KEYS_RENOVATE_FLAG_L || KEYS_RENOVATE_FLAG_H)
							if(sensor_open[addr] < 32)
							{
								if(KEYS_RENOVATE_FLAG_L &(((unsigned long)0x01)<<sensor_open[addr]))
								{
									if(base_line[addr] >= (((int)fth)*RENOVATE_NTH_RATE/10/5))
									{
					
										base_line[addr] -= differ/5;
										
									}
								}
							}
							else
							{
								if(KEYS_RENOVATE_FLAG_H &(((unsigned long)0x01)<<(sensor_open[addr]-32)))
								{
									if(base_line[addr] >= (((int)fth)*RENOVATE_NTH_RATE/10/5))
									{
					
										base_line[addr] -= differ/5;
										
									}
								}
							}
							#endif
						}
				
				#endif
						
				
		}
		else//differ<=p_noise基线更新
		{
				#if(RENOVATE_MODE == 0)//模式0基线更新
				
						over_p_noise_count[addr] = 0;
						under_p_noise_count[addr]++;
						over_n_noise_count[addr] = 0;
						under_n_noise_count[addr] = 0;
						under_2n_noise_count[addr] = 0;
						if(under_p_noise_count[addr] >= UNDER_P_NOISE_MAX_COUNT)
						{
							under_p_noise_count[addr] = 0;
							
							#if (KEYS_RENOVATE_FLAG_L || KEYS_RENOVATE_FLAG_H)
							if(sensor_open[addr] < 32)
							{
								if(KEYS_RENOVATE_FLAG_L &(((unsigned long)0x01)<<sensor_open[addr]))
								{
									base_line[addr] = raw_data[addr];
								}
							}
							else
							{
								if(KEYS_RENOVATE_FLAG_H &(((unsigned long)0x01)<<(sensor_open[addr]-32)))
								{
									base_line[addr] = raw_data[addr];
								}
							}
							#endif
							
						}
				
				#endif
				#if (RENOVATE_MODE == 1)
				//模式1基线更新
				
						over_p_noise_count[addr] = 0;
						under_p_noise_count[addr]++;
						over_n_noise_count[addr] = 0;
						under_n_noise_count[addr] = 0;
						under_2n_noise_count[addr] = 0;
						if(under_p_noise_count[addr] >= UNDER_P_NOISE_MAX_COUNT)
						{
							under_p_noise_count[addr] = 0;
							if(sensor_open[addr] < 32)
							{
								if(KEYS_RENOVATE_FLAG_L &(((unsigned long)0x01)<<sensor_open[addr]))
								{
									base_line[addr] = raw_data[addr];
								}
							}
							else
							{
								if(KEYS_RENOVATE_FLAG_H &(((unsigned long)0x01)<<(sensor_open[addr]-32)))
								{
									base_line[addr] = raw_data[addr];

								}
							}
						}
				
				#endif
		}
	}
	else//differ<0的情况
	{
		
		if(differ >= (-(((int)fth)*RENOVATE_NTH_RATE/10)))//>= n_poise情况
		{
				#if(RENOVATE_MODE == 0)//模式0基线更新
					over_p_noise_count[addr] = 0;
					under_p_noise_count[addr] = 0;
					over_n_noise_count[addr]++;
					under_n_noise_count[addr] = 0;
					under_2n_noise_count[addr] = 0;
					if(over_n_noise_count[addr] >= OVER_N_NOISE_MAX_COUNT)
					{
						over_n_noise_count[addr] = 0;
						
						#if (KEYS_RENOVATE_FLAG_L || KEYS_RENOVATE_FLAG_H)
						if(sensor_open[addr] < 32)
						{
							if(KEYS_RENOVATE_FLAG_L &(((unsigned long)0x01)<<sensor_open[addr]))
							{
								base_line[addr] = raw_data[addr];
							}
						}
						else
						{
							if(KEYS_RENOVATE_FLAG_H &(((unsigned long)0x01)<<(sensor_open[addr]-32)))
							{
								base_line[addr] = raw_data[addr];
							}
						}
						#endif
			
					}
			
				#endif
					
				#if (RENOVATE_MODE == 1)
				//模式1基线更新
				
					over_p_noise_count[addr] = 0;
					under_p_noise_count[addr] = 0;
					over_n_noise_count[addr]++;
					under_n_noise_count[addr] = 0;
					if(over_n_noise_count[addr] >= OVER_N_NOISE_MAX_COUNT)
					{
						over_n_noise_count[addr] = 0;
						if(sensor_open[addr] < 32)
						{
							if(KEYS_RENOVATE_FLAG_L &(((unsigned long)0x01)<<sensor_open[addr]))
							{
								base_line[addr] = raw_data[addr];
							}
						}
						else
						{
							if(KEYS_RENOVATE_FLAG_H &(((unsigned long)0x01)<<(sensor_open[addr]-32)))
							{
								base_line[addr] = raw_data[addr];

							}
						}
					}
				
				#endif
		}
		else if((differ >= -(UNDER_N*((int)fth)*RENOVATE_FTH_RATE/10)))
		{
					#if(RENOVATE_MODE == 0)//模式0基线更新
						over_p_noise_count[addr] = 0;
						under_p_noise_count[addr] = 0;
						over_n_noise_count[addr] = 0;
						under_n_noise_count[addr]++;
						under_2n_noise_count[addr] = 0;
				
						if(under_n_noise_count[addr] >= UNDER_N_NOISE_MAX_COUNT)
						{
							under_n_noise_count[addr] = 0;
							
							
							#if (KEYS_RENOVATE_FLAG_L || KEYS_RENOVATE_FLAG_H)
							if(sensor_open[addr] < 32)
							{
								if(KEYS_RENOVATE_FLAG_L &(((unsigned long)0x01)<<sensor_open[addr]))
								{
									base_line[addr] -= differ/2;						
								}
							}
							else
							{
								if(KEYS_RENOVATE_FLAG_H &(((unsigned long)0x01)<<(sensor_open[addr]-32)))
								{
									base_line[addr] -= differ/2;						
								}
							}
							#endif					
						
						}
				#endif
					
				#if(RENOVATE_MODE == 1)//模式1基线更新
						over_p_noise_count[addr] = 0;
						under_p_noise_count[addr] = 0;
						over_n_noise_count[addr] = 0;
						under_n_noise_count[addr]++;
						under_2n_noise_count[addr] = 0;
				
						if(under_n_noise_count[addr] >= UNDER_N_NOISE_MAX_COUNT)
						{
							under_n_noise_count[addr] = 0;
							#if (KEYS_RENOVATE_FLAG_L || KEYS_RENOVATE_FLAG_H)
							if(sensor_open[addr] < 32)
							{
								if(KEYS_RENOVATE_FLAG_L &(((unsigned long)0x01)<<sensor_open[addr]))
								{
										base_line[addr] -= differ/2;				
								}
							}
							else
							{
								if(KEYS_RENOVATE_FLAG_H &(((unsigned long)0x01)<<(sensor_open[addr]-32)))
								{
										base_line[addr] -= differ/2;				
								}
							}
							#endif					
							
						}
				#endif
			}
			else
			{
					#if(RENOVATE_MODE == 0)//模式0基线更新
					over_p_noise_count[addr] = 0;
					under_p_noise_count[addr] = 0;
					over_n_noise_count[addr] = 0;
			    under_n_noise_count[addr] = 0;
					under_2n_noise_count[addr]++;			
					if(under_2n_noise_count[addr] >= UNDER_2N_NOISE_MAX_COUNT)
					{
						under_2n_noise_count[addr] = 0;
						
						#if (KEYS_RENOVATE_FLAG_L || KEYS_RENOVATE_FLAG_H)
							if(sensor_open[addr] < 32)
							{
								if(KEYS_RENOVATE_FLAG_L &(((unsigned long)0x01)<<sensor_open[addr]))
								{
									base_line[addr] -= differ/5;							
								}
							}
							else
							{
								if(KEYS_RENOVATE_FLAG_H &(((unsigned long)0x01)<<(sensor_open[addr]-32)))
								{
									base_line[addr] -= differ/5;							
								}
							}
						#endif
						
					}	
					#endif
					
					#if(RENOVATE_MODE == 1)//模式1基线更新
					over_p_noise_count[addr] = 0;
					under_p_noise_count[addr] = 0;
					over_n_noise_count[addr] = 0;
			    under_n_noise_count[addr] = 0;
					under_2n_noise_count[addr]++;			
					if(under_2n_noise_count[addr] >= UNDER_2N_NOISE_MAX_COUNT)
					{
						under_2n_noise_count[addr] = 0;
						
						#if (KEYS_RENOVATE_FLAG_L || KEYS_RENOVATE_FLAG_H)
							if(sensor_open[addr] < 32)
							{
								if(KEYS_RENOVATE_FLAG_L &(((unsigned long)0x01)<<sensor_open[addr]))
								{
									base_line[addr] -= differ/5;						
								}
							}
							else
							{
								if(KEYS_RENOVATE_FLAG_H &(((unsigned long)0x01)<<(sensor_open[addr]-32)))
								{
									base_line[addr] -= differ/5;						
								}
							}
						#endif
						
					}	
					#endif
			}
	}
	
	if(differ >= 0)
	{
		#if(TK_EOT != 0)
		
		if(differ < (fth_tem*TK_EOT))//在消顶值以下
		{
			
			if(differ < (fth_tem*RENOVATE_FTH_RATE/10))//无按键
			{
				if(sensor_open[addr] < 32)
				{
					sensor_flag_l &= ~(((unsigned long)0x01) << sensor_open[addr]);
				}
				else
				{
					sensor_flag_h &= ~(((unsigned long)0x01) << (sensor_open[addr]-32));
				}
				touch_confirm_count[addr] = 0;
			}
			else//有按键
			{
					touch_left_count[addr] = 0;
					touch_confirm_count[addr]++;
			}
		}
		else//无按键
		{

				if(sensor_open[addr] < 32)
				{
					sensor_flag_l &= ~(((unsigned long)0x01) << sensor_open[addr]);
				}
				else
				{
					sensor_flag_h &= ~(((unsigned long)0x01) << (sensor_open[addr]-32));
				}

				touch_confirm_count[addr] = 0;
		}
		
		#else//无消顶判断
		
		if(differ < (fth_tem*RENOVATE_FTH_RATE/10))
		{
			
			if(sensor_open[addr] < 32)
			{
				sensor_flag_l &= ~(((unsigned long)0x01) << sensor_open[addr]);
			}
			else
			{
				sensor_flag_h &= ~(((unsigned long)0x01) << (sensor_open[addr]-32));
			}
			touch_confirm_count[addr] = 0;	
		}
		else
		{
				touch_confirm_count[addr]++;
		}
		
		#endif
	}//Differ<0
	else
	{
		
			if(sensor_open[addr] < 32)
			{
				sensor_flag_l &= ~(((unsigned long)0x01) << sensor_open[addr]);
			}
			else
			{
				sensor_flag_h &= ~(((unsigned long)0x01) << (sensor_open[addr]-32));
			}
			
			touch_confirm_count[addr] = 0;
	}


	if(touch_confirm_count[addr] > TK_COMFIRM_COUNT)
	{
		if(sensor_open[addr] < 32)
		{
			keys_flag_l |= sensor_flag_l |= (((unsigned long)0x01) << sensor_open[addr]);
			touch_confirm_count[addr] = 0;
		}
		else
		{
			keys_flag_h |= sensor_flag_h |= (((unsigned long)0x01) << (sensor_open[addr]-32));
			touch_confirm_count[addr] = 0;
		}
	}
	else
	{
		
		
	}
}



//-----------------------------------------------------------------//
//函数名称： void CTK_BF7615BMXX_XXXX_Set_Para(unsigned int i_rank)
//函数功能： 配置所有通道参数
//输入参数： 
//unsigned int i_rank:电流源级数;
//输出参数： 无
//返 回 值： 无
//-----------------------------------------------------------------//        
void CTK_BF7615BMXX_XXXX_Set_Para(unsigned int i_rank)
{
		CTK_PULL_I_SET(i_rank);			//设置电流源级数
}

//-----------------------------------------------------------------//
//函数名称： void CTK_BF7615BMXX_XXXX_Adjust_Int(void)
//函数功能：通道电流源自适应
//输入参数： 无
//输出参数： 无
//返 回 值： 无
//-----------------------------------------------------------------//        

void CTK_BF7615BMXX_XXXX_Adjust_Int(void)
{
	if(adjust_count < 3)
	{
		while(1)
		{
			WDT_CTRL = 7;
			
			if((raw_data[sns_next] >= ADJUST_LINE))
			{
				if(pull_i_value[sns_next] < (511 - ADJUST_STE))
				{
					pull_i_value[sns_next] += (1 + ADJUST_STE);
					CTK_PULL_I_SET(pull_i_value[sns_next]);//设置级数

					Set_Next_SNS();
					return;
				}	
				else
				{
					
					sns_next++;
					if(sns_next >= SNS_NUM)
					{
							sns_next = 0;
							adjust_count = 0;
							adjust_done_flag = 1;
					}
					
					Set_Next_SNS();
					return;
				}
			}
			else
			{	
					n_base_line[sns_next] = base_line[sns_next] = raw_data[sns_next];
					sns_next++;
					if(sns_next >= SNS_NUM)
					{
							if(adjust_count < 3)
							{
								adjust_count++;
							}

							sns_next = 0;
							if(pull_i_value[sns_next] > (0))
							{
								pull_i_value[sns_next] -= (1);
								CTK_PULL_I_SET(pull_i_value[sns_next]);//设置级数
								Set_Next_SNS();
								return;
							}
						
							Set_Next_SNS();
							break;
					}

					if(pull_i_value[sns_next] > (0))
					{
						pull_i_value[sns_next] -= (1);
						CTK_PULL_I_SET(pull_i_value[sns_next]);//设置级数
						Set_Next_SNS();
						return;
					}
					else
					{
							Set_Next_SNS();
							return;
					}	
			}
		}
	}
	
	if(adjust_count >= 3)
	{
		while(1)
		{
			WDT_CTRL = 7;
			
			if((raw_data[sns_next] <= ADJUST_LINE))
			{
				if(pull_i_value[sns_next] > (0))
				{
					pull_i_value[sns_next] -= (1);
					CTK_PULL_I_SET(pull_i_value[sns_next]);//设置级数

					Set_Next_SNS();
					return;
				}	
				else
				{
					sns_next++;
					if(sns_next >= SNS_NUM)
					{
							sns_next = 0;
							adjust_count = 0;
							adjust_done_flag = 1;
					}
					Set_Next_SNS();
					return;
				}
			}
			else
			{	
					n_base_line[sns_next] = base_line[sns_next] = raw_data[sns_next];
					sns_next++;
					if(sns_next >= SNS_NUM)
					{
							sns_next = 0;

							
							if(adjust_count < 6)
							{
								adjust_count++;
							}
							if(adjust_count >= 6)
							{
								adjust_count = 0;
								adjust_done_flag = 1;
							}
							Set_Next_SNS();
							break;
					}

					if(pull_i_value[sns_next] < (511 - ADJUST_STE))
					{
						pull_i_value[sns_next] += (1 + ADJUST_STE);
						CTK_PULL_I_SET(pull_i_value[sns_next]);//设置级数
						Set_Next_SNS();
						return;
					}
					else
					{
							Set_Next_SNS();
							return;
					}	
			}
		}
	}
}
#endif