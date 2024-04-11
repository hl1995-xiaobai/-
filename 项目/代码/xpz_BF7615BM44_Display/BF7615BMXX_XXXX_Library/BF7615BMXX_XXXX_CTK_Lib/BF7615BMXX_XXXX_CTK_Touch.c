#include ".\BF7615BMXX_XXXX_Library\Config.h"

#if SNS_NUM
	#pragma message "编译,CTK功能"
	uchar xdata Sns_Count = 0;
	uchar xdata CFG_Rb = 200;
	#if UN_NORMAL_CHECK
	//-----------------------------------------------------------------//
	//函数名称： void Rawdata_Un_Normal(uchar sns_num)
	//函数功能： Rawdata异常判断,注：此函数不能识别所有异常情况
	//输入参数： uchar sns_num：通道索引
	//输出参数： 无
	//返 回 值： 无
	//-----------------------------------------------------------------//
	void Rawdata_Un_Normal(uchar sns_num)
	{
		if(un_normal_flag == 0)
		{
				if(raw_data[sns_num] >= (((unsigned long)(((unsigned long)0x0001)<<(((SNS_SCAN_CFG3>>4)&0x07) + 9)))*8/10))	
				{
						
						un_normal_count++;
						if(un_normal_count >= UN_NORMAL_MAX_COUNT)
						{
								un_normal_count = 0;
					
								if(un_normal_recover_count < UN_NORMAL_RECOVER_MAX_COUNT)//允许异常判断恢复un_normal_recover_max_count次
								{								
										
										EA = 0;											//关总中断
										adjust_done_flag = 0;
										un_normal_recover_count++;
										CTK_IE_SET;
										CTK_ADDR_SET(sensor_open[0]);
										CTK_START;
										EA = 1;											//开总中断

								}
								
								
						}
						
				}
			
		}	

	}
	#endif
#endif
//-----------------------------------------------------------------//
//函数名称： void BF7615BMXX_XXXXX_Set_Touch_Flag(void)
//函数功能： 触摸判断并置位或者清除触摸标志位
//输入参数： 无
//输出参数： 无
//返 回 值： 无
//-----------------------------------------------------------------//

void BF7615BMXX_XXXX_Set_Touch_Flag(void)
{
	#if SNS_NUM	
	
		#if TRACEMODE
		uchar i = 0;
		#endif
	
		#if (IDLE_MODE == 1)
			if(parallel_mode == 0)
			{
				if(ctk_circle_done == 1)//中断模式
				{
					ctk_circle_done = 0;
					CTK_IE_CLR;//关CTK中断
					multi_key_count = 0;
					for(Sns_Count = 0; Sns_Count < SNS_NUM; Sns_Count++)
					{
						if(SNS[Sns_Count] != 255)
						{
							
							CTK_SNS_Renovate(Sns_Count,((ulong)FTH[sensor_open[Sns_Count]]*(CFG_Rb*100/200))/100);
							
							#if (MULTI_KEY_MAX_COUNT != 0)
								if((muli_key_flag_l & (((unsigned long)0x01) << sensor_open[Sns_Count]))||(muli_key_flag_h & (((unsigned long)0x01) << (sensor_open[Sns_Count]-32))))
								{
									multi_key_count++;//多按键计数						
								}
							#endif
							
							CTK_BF7615BMXX_XXXX_Get_KEYS_Touch(Sns_Count);
							
							#if TRACEMODE
								#if (SNS_NUM < 32)
								{
									if(sensor_open[Sns_Count] < 32)
									{
										if(keys_flag_l & ((long)0x01 << sensor_open[Sns_Count]))
										{
											keys_flag_l_Tracemode |= ((long)0x01 << Sns_Count);
										
										}
										else
										{
											keys_flag_l_Tracemode &= ~((long)0x01 << Sns_Count);
										}
									}
									else
									{
										if(keys_flag_h & ((long)0x01 << (sensor_open[Sns_Count]-32)))
										{
											keys_flag_l_Tracemode |= ((long)0x01 << Sns_Count);
										
										}
										else
										{
											keys_flag_l_Tracemode &= ~((long)0x01 << Sns_Count);
										}
									}
								}
								#else
								{
									if(sensor_open[Sns_Count] < 32)
									{
										if(keys_flag_l & ((long)0x01 << sensor_open[Sns_Count]))
										{
											if(Sns_Count<32)
											{
												keys_flag_l_Tracemode |= ((long)0x01 << Sns_Count);
											}
											else
											{
												keys_flag_h_Tracemode |= ((long)0x01 << (Sns_Count-32));
											}
											
										}
										else
										{
											if(Sns_Count<32)
											{
												keys_flag_l_Tracemode &= ~((long)0x01 << Sns_Count);
											}
											else
											{
												keys_flag_h_Tracemode &= ~((long)0x01 << (Sns_Count-32));
											}
										}
									}
									else
									{
										if(keys_flag_h & ((long)0x01 << (sensor_open[Sns_Count] - 32)))
										{
											if(Sns_Count<32)
											{
												keys_flag_l_Tracemode |= ((long)0x01 << Sns_Count);
											}
											else
											{
												keys_flag_h_Tracemode |= ((long)0x01 << (Sns_Count-32));
											}
											
										}
										else
										{
											if(Sns_Count<32)
											{
												keys_flag_l_Tracemode &= ~((long)0x01 << Sns_Count);
											}
											else
											{
												keys_flag_h_Tracemode &= ~((long)0x01 << (Sns_Count-32));
											}
										}
									}
								}
								#endif
							#endif
							
							#if UN_NORMAL_CHECK
								Rawdata_Un_Normal(Sns_Count);
							#endif
						}
						
					}
					#if (MULTI_KEY_MAX_COUNT != 0)
						if(multi_key_count > MULTI_KEY_MAX_COUNT)
						{
								keys_flag_l= 0;
								keys_flag_h= 0;
								multi_key_count = 0;
								multi_key_reset_cnt++;
								if(multi_key_reset_cnt >= MULTI_KEY_RST_COUNT)
								{
									
									multi_key_reset_cnt = 0;
									Base_Line_Init();
								}
						}
						else
						{
							multi_key_reset_cnt = 0;		
						}
					#endif
					CTK_IE_SET;//开CTK中断
				}
			}
			else
			{				
					Idle();				
			}
		#else
				if(ctk_circle_done == 1)//中断模式
				{
					ctk_circle_done = 0;
					CTK_IE_CLR;//关CTK中断
					multi_key_count = 0;
					for(Sns_Count = 0; Sns_Count < SNS_NUM; Sns_Count++)
					{
						if(sensor_open[Sns_Count] != 255)
						{
						
							CTK_SNS_Renovate(Sns_Count,((ulong)FTH[sensor_open[Sns_Count]]*(CFG_Rb*100/200))/100);
							#if (MULTI_KEY_MAX_COUNT != 0)
								if((muli_key_flag_l & (((unsigned long)0x01) << sensor_open[Sns_Count]))||(muli_key_flag_h & (((unsigned long)0x01) << (sensor_open[Sns_Count]-32))))
								{
									multi_key_count++;//多按键计数						
								}
							#endif
							
							CTK_BF7615BMXX_XXXX_Get_KEYS_Touch(Sns_Count);
							#if TRACEMODE
									#if (SNS_NUM < 32)
									{
										if(sensor_open[Sns_Count] < 32)
										{
											if(keys_flag_l & ((long)0x01 << sensor_open[Sns_Count]))
											{
												keys_flag_l_Tracemode |= ((long)0x01 << Sns_Count);
											
											}
											else
											{
												keys_flag_l_Tracemode &= ~((long)0x01 << Sns_Count);
											}
										}
										else
										{
											if(keys_flag_h & ((long)0x01 << (sensor_open[Sns_Count]-32)))
											{
												keys_flag_l_Tracemode |= ((long)0x01 << Sns_Count);
											
											}
											else
											{
												keys_flag_l_Tracemode &= ~((long)0x01 << Sns_Count);
											}
										}
									}
									#else
									{
										if(sensor_open[Sns_Count] < 32)
										{
											if(keys_flag_l & ((long)0x01 << sensor_open[Sns_Count]))
											{
												if(Sns_Count<32)
												{
													keys_flag_l_Tracemode |= ((long)0x01 << Sns_Count);
												}
												else
												{
													keys_flag_h_Tracemode |= ((long)0x01 << (Sns_Count-32));
												}
												
											}
											else
											{
												if(Sns_Count<32)
												{
													keys_flag_l_Tracemode &= ~((long)0x01 << Sns_Count);
												}
												else
												{
													keys_flag_h_Tracemode &= ~((long)0x01 << (Sns_Count-32));
												}
											}
										}
										else
										{
											if(keys_flag_h & ((long)0x01 << (sensor_open[Sns_Count] - 32)))
											{
												if(Sns_Count<32)
												{
													keys_flag_l_Tracemode |= ((long)0x01 << Sns_Count);
												}
												else
												{
													keys_flag_h_Tracemode |= ((long)0x01 << (Sns_Count-32));
												}
												
											}
											else
											{
												if(Sns_Count<32)
												{
													keys_flag_l_Tracemode &= ~((long)0x01 << Sns_Count);
												}
												else
												{
													keys_flag_h_Tracemode &= ~((long)0x01 << (Sns_Count-32));
												}
											}
										}
									}
									#endif

							#endif	
							
							#if UN_NORMAL_CHECK
								Rawdata_Un_Normal(Sns_Count);
							#endif
						}
					}
					#if (MULTI_KEY_MAX_COUNT != 0)
						if(multi_key_count > MULTI_KEY_MAX_COUNT)
						{
								keys_flag_l= 0;
								keys_flag_h= 0;
								multi_key_count = 0;
								multi_key_reset_cnt++;
								if(multi_key_reset_cnt >= MULTI_KEY_RST_COUNT)
								{									
									multi_key_reset_cnt = 0;
									Base_Line_Init();
								}
						}
						else
						{
							multi_key_reset_cnt = 0;		
						}
					#endif
					
					CTK_IE_SET;//开CTK中断
				}
		#endif
		
	#endif
}

