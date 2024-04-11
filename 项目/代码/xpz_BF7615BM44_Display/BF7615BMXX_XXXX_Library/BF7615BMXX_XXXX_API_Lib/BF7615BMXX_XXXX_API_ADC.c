#include ".\BF7615BMXX_XXXX_Library\Config.h"

	#if ADC_IS_OPEN
		#pragma message "编译,ADC功能"
		
		#if (ADC_MODE == 0)
			#if ADC_NUM
			uint 	xdata adc_data[ADC_NUM] = {0};
			#endif
			unsigned char code 	ADC_CH[45] ={SCAN_ADC00,SCAN_ADC01,SCAN_ADC02,SCAN_ADC03,SCAN_ADC04,SCAN_ADC05,SCAN_ADC06,SCAN_ADC07,SCAN_ADC08,SCAN_ADC09,SCAN_ADC10,SCAN_ADC11,SCAN_ADC12,SCAN_ADC13,SCAN_ADC14,SCAN_ADC15,\
																			 SCAN_ADC16,SCAN_ADC17,SCAN_ADC18,SCAN_ADC19,SCAN_ADC20,SCAN_ADC21,SCAN_ADC22,SCAN_ADC23,SCAN_ADC24,SCAN_ADC25,SCAN_ADC26,SCAN_ADC27,SCAN_ADC28,SCAN_ADC29,SCAN_ADC30,SCAN_ADC31,\
																			 SCAN_ADC32,SCAN_ADC33,SCAN_ADC34,SCAN_ADC35,SCAN_ADC36,SCAN_ADC37,SCAN_ADC38,SCAN_ADC39,SCAN_ADC40,SCAN_ADC41,SCAN_ADC42,SCAN_ADC43,SCAN_ADC44};
		#endif
		#if (ADC_MODE == 1)//ADC查询模式
			#pragma message "编译,ADC查询模式功能"
			bit ADC_Start_Flag = 0;
			uint  xdata  ADC_Rest_Max_Count = 0;
			uint  xdata  ADC_Start_Count = 0;
			
			void ADC_Unormal_Count(void);
	

			//-----------------------------------------------------------------//
		//函数名称： void ADC_Reset_Count()
		//函数功能： ADC超时计数器累加函数
		//输入参数： 无
		//输出参数： 无
		//返 回 值： 无
		//-----------------------------------------------------------------//
		#if Timer0_EN
			#if ADC_IS_OPEN
				#if ADC_MODE
				void ADC_Reset_Count(void)
				{
					if(ADC_Start_Flag == 1)
					{
						ADC_Start_Count++;
						if(ADC_Start_Count >= ADC_Rest_Max_Count)
						{
							SOFT_RST = 0x55;	
							ADC_Start_Count = 0;
							ADC_Start_Flag = 0;
						}
					}
				}
				#endif
			#endif
		#endif
				
		#endif
	#endif
		

		#if ADC_IS_OPEN
				
		#if (ADC_MODE == 0)
			bit ADC_Done = 0;
			uchar ADC_Index = 0;
			uchar ADC_Index_Start = 0;
			bit adc_scan_done = 0;
			#if ADC_NUM
			uchar xdata ADC_Access_Index[ADC_NUM] = {0x7F};
			#endif
		#endif
		
		//-----------------------------------------------------------------//
		//函数名称： void ADC_Find_Next(void)
		//函数功能： ADC通道查找
		//输入参数： 无
		//输出参数： 无
		//返 回 值： 无
		//-----------------------------------------------------------------//
		#if (ADC_MODE == 0)	
		#pragma message "编译,ADC功能中断模式"
			#if ADC_NUM
			void  ADC_Find_Next(void)
			{
				while(1)
				{
					ADC_Index++;	
					if(ADC_Index >= ADC_NUM)
					{
							ADC_Index = ADC_Index_Start;
							adc_scan_done = 1;
					}
					if((ADC_Access_Index[ADC_Index]&0x80))//如果下一个是ADC通道，开启中ADC
					{
						ADC_ADDR_SET((ADC_Access_Index[ADC_Index]&0x7F));
						ADC_SCAN_EN;//开启ADC扫描
						break;
					}
					else
					{
					
					}
				}				
			}
			#endif
		#endif
		//-----------------------------------------------------------------//
		//函数名称： uint Get_ADC(uchar adc_ch)
		//函数功能： ADC_SELXX对应要开启，查询模式下获取ADC adc_ch的数据；(0~43),44为内部ADC通道
		//输入参数： 无
		//输出参数： uint：返回ADC数据
		//返 回 值： 无
		//-----------------------------------------------------------------// 
		#if (ADC_MODE == 1)		
		uint Get_ADC(uchar adc_ch)
		{
			ADC_IE_CLR;//关闭ADC中断使能
	
			ADC_ADDR_SET(adc_ch);
			ADC_SCAN_EN;//开启ADC扫描
			ADC_Start_Flag = 1;
			ADC_Start_Count = 0;
			while(!(IRCON1&0x10));
			ADC_Start_Flag = 0;
			ADC_INT_FLAG_CLR;

			return ((uint)(ADC_RDATAH&0x0F) << 8) | (uint)ADC_RDATAL;
		}
		#endif

		//-----------------------------------------------------------------//
		//函数名称： uint Get_ADC_Vref(uchar vref)
		//函数功能： 当ADC参考电压选择2V/4V时，Get_ADC_Vref获取ADC参考电压值，
		//输入参数： uchar vref:0:为返回参考电压2V的ADC校准值，1:为返回参考电压4V的ADC校准值
		//输出参数： uint：ADC校准值mV,用于计算ADC输入电压
		//返 回 值： uint
		//-----------------------------------------------------------------// 
	
		uint Get_ADC_Vref(uchar vref)
		{
			uint adc_vref = 0;
			EA = 0;
			if(vref == 0)
			{
				SPROG_CMD = 0x88;
				SPROG_ADDR_H = 0x41D2>>8;
				SPROG_ADDR_L = 0x41D2;
				adc_vref = SPROG_RDATA<<8;
				SPROG_CMD = 0x88;
				SPROG_ADDR_H = 0x41D3>>8;
				SPROG_ADDR_L = 0x41D3;
				adc_vref |= SPROG_RDATA;
				
			}
			else if(vref == 1)
			{
				SPROG_CMD = 0x88;
				SPROG_ADDR_H = 0x41D4>>8;
				SPROG_ADDR_L = 0x41D4;
				adc_vref = SPROG_RDATA<<8;
				SPROG_CMD = 0x88;
				SPROG_ADDR_H = 0x41D5>>8;
				SPROG_ADDR_L = 0x41D5;
				adc_vref |= SPROG_RDATA;
			}
			else
			{
				
			}
			EA = 1;
			return adc_vref;
		}
		
		//-----------------------------------------------------------------//
		//函数名称： uint Get_Inner_ADC_Vol(void)
		//函数功能： 当ADC参考电压选择VCC时，Get_Inner_ADC_Vol获取ADC内部通道输入电压校准值
		//输入参数： void 
		//输出参数： uint：ADC内部通道输入电压值mV
		//返 回 值： uint
		//-----------------------------------------------------------------// 
	
		uint Get_Inner_ADC_Vol(void)
		{
			uint inner_adc_vol = 0;
			EA = 0;
			SPROG_CMD = 0x88;
			SPROG_ADDR_H = 0x41CC>>8;
			SPROG_ADDR_L = 0x41CC;
			inner_adc_vol = SPROG_RDATA<<8;
			SPROG_CMD = 0x88;
			SPROG_ADDR_H = 0x41CD>>8;
			SPROG_ADDR_L = 0x41CD;
			inner_adc_vol |= SPROG_RDATA;
			EA = 1;
			return inner_adc_vol;
		}

		
		
		//-----------------------------------------------------------------//
		//函数名称： void ADC_Init(void)
		//函数功能： ADC初始化,在SetAccessIndexes()之后初始化;
		//输入参数： 无
		//输出参数： 无
		//返 回 值： 无
		//-----------------------------------------------------------------//        
		void ADC_Init(void)
		{
			uchar i = 0;
			uchar j = 0;
			uchar adc_count = 0;
			EA = 0;//关总中断；
			ADC_IP_SET;//设置ADC中断优级为高，根据实际应运设置优先级
			ADC_INT_FLAG_CLR;//清除ADC中断标志位

			ADC_IO_CGF0(ADC_SEL00);//ADC0~ADC06与IO功能选择，对应的位为1为ADC功能，0为IO功能		
			ADC_IO_CGF1(ADC_SEL01);//ADC7~ADC14与IO功能选择，对应的位为1为ADC功能，0为IO功能		
			ADC_IO_CGF2(ADC_SEL02);//ADC15~ADC22与IO功能选择，对应的位为1为ADC功能，0为IO功能		
			ADC_IO_CGF3(ADC_SEL03);//ADC23~ADC30与IO功能选择，对应的位为1为ADC功能，0为IO功能		
			ADC_IO_CGF4(ADC_SEL04);//ADC31~ADC38与IO功能选择，对应的位为1为ADC功能，0为IO功能		
			ADC_IO_CGF5(ADC_SEL05);//ADC39~ADC43与IO功能选择，对应的位为1为ADC功能，0为IO功能		
		
			ADC_SAMP_SET(ADC_SAMPT);			//ADC采样时间配置选择，   	bit[7:0],(0~255)采样时间为(ADC_SPT+1)*4*T_adc_clk
			ADC_FLTER_SET(ADC_FLTER);			//ADC滤波选择，bit[7],(0~1),0:不加RC滤波；1：加RC滤波；//20-07-20
			ADC_CALW_SET(ADC_CALW); 			//采样延时时间选择, bit[5:4](0~3)：0:0(ADC_CLK),1:2(ADC_CLK),1:4(ADC_CLK),2:8(ADC_CLK)//20-07-20
			ADC_CKV_SET(ADC_CKV);					//模拟输入信号时钟分频选择，bit[3:2],(0~3)-(12MhHz,8MHz,4MHz,2MHz)
			ADC_ADCK_SET(ADC_ADCK);				//ADC分频选择，							bit[1:0],(0~3)-(8MHz,6MhHz,4MHz,3MHz)
			ADC_OFFSETI_SET(ADC_OFFSETI);	//ADC偏置电流大小选择，			bit[1:0],(0~3)(4uA,4uA,5uA,5uA)
			ADC_WNUM_SET(ADC_WAIT);				//转换完毕距离转换时间选择，bit[6:2],(0~31)(X+3)*T_adc_clk,需要(X+3)*T_adc_clk > 4*ADC_ANCK
			ADC_PD(0);//开启ADC模块
			ADC_CTRL(2);//ADC比较器失调消除：2为时序2,5为时序3,建议为2
			ADC_SAMBG_SET(ADC_SAMBG);//采样时序与比较时序间隔选择，bit[6],(0~1),0:间隔0(ADC_CLK)；1：间隔1(ADC_CLK);//20-07-20
			ADC_VIN_SEL(ADC_VIN);//ADC内部通道输入电压选择：00：1.362V;01:2.253V;10:3.111V;11:4.082V;//20-09-15
			ADC_VREF_SEL(ADC_VREF);//参考源电压选择：0：VCC;1:ADC_VREF//20-07-20
			ADC_VREF_VOL_SEL(ADC_VREF_VOL);//参考电压选择ADC_VREF：0：2V;1:4V//20-07-20
			
			#if (ADC_MODE == 0)
				#if ADC_NUM
					for (i = 0; i < ADC_NUM; i++) 
					{
							ADC_Access_Index[i] = ADC_CH[i]|0x80;
					}		
					for(ADC_Index_Start = 0;ADC_Index_Start < ADC_NUM;ADC_Index_Start++)//查找第一个ADC通道
					{
						if((ADC_Access_Index[ADC_Index_Start] & 0x80))
						{
							break;
						}
					}				
					ADC_ADDR_SET((ADC_Access_Index[ADC_Index_Start]&0x7F));
					ADC_Index = ADC_Index_Start;
					ADC_SCAN_EN;//开启ADC扫描
					
					ADC_IE_SET;//开启ADC中断使能
				#endif
			#endif
			
			#if (ADC_MODE == 1)
				ADC_SCAN_CLR;//关闭ADC扫描
				ADC_IE_CLR;//关闭ADC中断使能
			#endif
			
			EA = 1;//开总中断	 
		}
		
		//-----------------------------------------------------------------//
		//函数名称： void  ADC_ISR interrupt 11
		//函数功能： ADC中断子函数
		//输入参数： 无
		//输出参数： 无
		//返 回 值： 无
		//-----------------------------------------------------------------//
		#if ADC_NUM
		void  ADC_ISR() interrupt 11
		{	
			static uchar xdata addr_bak = 0;
			PUSH_REG_ADDR_SFR();
			ADC_INT_FLAG_CLR;//清除ADC中断标志位
			ADC_SCAN_CLR;//关闭ADC扫描
		
			#if (ADC_MODE == 0)
		
				EA = 0;
				adc_data[ADC_Index] = ((uint)(ADC_RDATAH&0x0F) << 8) | (uint)ADC_RDATAL;//获取ADC数据				
				EA = 1;
			
				ADC_Find_Next();//查找下一个开启的ADC
		
			#else
				ADC_IE_CLR;//关闭ADC中断使能
				ADC_SCAN_CLR;//关闭ADC扫描	
			#endif
			POP_REG_ADDR_SFR();
		}
		#endif
		
		#endif
