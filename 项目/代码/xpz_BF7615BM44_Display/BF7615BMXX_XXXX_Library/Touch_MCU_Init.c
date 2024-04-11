#include ".\BF7615BMXX_XXXX_Library\Config.h"

//-----------------------------------------------------------------//
//函数名称： void CFG_Check(void)
//函数功能： 配置字对比判断(对应MCU02芯片)
//输入参数： 无
//输出参数： 无
//返 回 值： 无
//-----------------------------------------------------------------//
		 
void CFG_Check(void)
{   
	unsigned char i = 0;
	unsigned char code add_cfg_Bit[14] = {0x0E,0xFF,0x3F,0xFF,0x3F,0xFF,0x3F,0x1F,0x7E,0xFF,0xFF,0xFF,0x7F,0x07};
	unsigned int code cfg_addr[14] = {0x81FF,0x41FF,0x41FD,0x41FB,0x41F9,0x41F7,0x41F5,0x41F3,0x41F1,0x41EF,0x81FE,0x81FD,0x41ED,0x41EB};
	
	EA = 0;//关总中断
	for(i = 0; i < 14;i++)
	{
		SPROG_CMD = 0x88;
		SPROG_ADDR_H = cfg_addr[i]>>8;
		SPROG_ADDR_L =  cfg_addr[i];
		REG_ADDR = i;
		if((SPROG_RDATA&add_cfg_Bit[i]) != (REG_DATA&add_cfg_Bit[i]))
		{
			SOFT_RST = 0x55;	
		}	
	}
	
	#if SNS_NUM
		SPROG_CMD = 0x88;
		SPROG_ADDR_H = 0x41DC>>8;
		SPROG_ADDR_L = 0x41DC;
		CFG_Rb = SPROG_RDATA;
	#endif
	
	SPROG_CMD = 0;
	SPROG_ADDR_H = 0;
	SPROG_ADDR_L = 0;
	
	P2_XH = 0;//使用MOVX 操作PDATA区时，P2_XH清0
	EA = 1;//开总中断	
}


//-----------------------------------------------------------------//
//函数名称： void Delay_Us(uint us)
//函数功能： 延时为几us
//输入参数： us
//输出参数： 无
//返 回 值： 无
//-----------------------------------------------------------------//
#if(DELAY_US_EN == 1)
#pragma message "编译，void Delay_Us(uint us)"  
void Delay_Us(uint us)//1--2.38us@12MHz;10-11.8us@12MHz;100-106us@12MHz;1000-1.045ms
{
	for (; us > 0; us--)
	{	
		WDT_CTRL = 0x07;
	}		
}
 
#endif
//-----------------------------------------------------------------//
//函数名称： void Set_Sys_Clk(void)
//函数功能： 系统时钟设置
//输入参数： 无 
//输出参数： 无
//返 回 值： 无
//-----------------------------------------------------------------//
void Set_Sys_Clk(void) 
{
		SYS_CLK_SET(SYS_CLK);//(SYS_CLK：4,5,6,7分别对应宏SYSCLK_SEL：0--12Mhz,1--08Mhz,2--04Mhz,3--01Mhz)
		SYS_CLK_ON_OFF(0);//0为开系统时钟，1为关系统时钟 
}
 

//-----------------------------------------------------------------//
//函数名称： void Pow_Delay(uint t)
//函数功能： 上电延时函数
//输入参数： t
//输出参数： 无
//返 回 值： 无
//-----------------------------------------------------------------//

#if(POW_UP_DELAY == 1)
#pragma message "编译，void Pow_Up_Delay(uint ms)函数"
void Pow_Up_Delay(uint ms)//1--1ms@12MHz;10-10.05ms@12MHz;100-100ms@12MHz;1000-1000ms
{  
	uint a = 954,b = ms;
	#if(SWITCH_TRACEMODE == 0)	
	#pragma message "工作模式，开启上电延时"
	for (b = ms; b > 0; b--)
	{
		for (a = 954; a > 0; a--)
		{
			WDT_CTRL = 0x07;
		} 
	}	
	#endif
}
#endif

//-----------------------------------------------------------------//
//函数名称： void Delay_Ms(uint t)
//函数功能： ms延时函数
//输入参数： t
//输出参数： 无
//返 回 值： 无
//-----------------------------------------------------------------//

#if ((DELAY_MS_EN == 1))

#pragma message "编译，void Delay_Ms(uint ms)函数"
void Delay_Ms(uint ms)//1--1ms@12MHz;10-10.05ms@12MHz;100-100ms@12MHz;1000-1000ms
{  
	uint a = 954,b = ms;
	for (b = ms; b > 0; b--)
	{
		for (a = 954; a > 0; a--)
		{
			WDT_CTRL = 0x07;
		} 
	}	
}
#endif



//-----------------------------------------------------------------//
//函数名称： void WDT_Init(void)
//函数功能： 看门狗初始化
//输入参数： 无
//返 回 值： 无
//-----------------------------------------------------------------//
void WDT_Init(void)
{
	#if CHIP_BF7615BMXX_XXXX

		EA = 0;//关总中断；
		WDT_IP_CLR;//设置WDT中断优级为低，根据实际应运设置优先级
		WDT_INT_FLAG_CLR;//清除看门狗中断标志
		WDT_ON_OFF(0);//仅等于0x55时关闭看门狗
		WDT_CTRL = 7;//设置WDT溢出时间(0~15--18ms~2.304S)7--2.304S
		WDT_IE_SET;	//开WDT中断使能
		EA = 1;//开总中断	

	#endif
}




//-----------------------------------------------------------------//
//函数名称： void CTK_Init(void)
//函数功能： CTK初始化
//输入参数： 无
//返 回 值： 无
//-----------------------------------------------------------------//

void CTK_Init(void)
{
	#if SNS_NUM
		#if CHIP_BF7615BMXX_XXXX
		
				EA = 0;	//关总中断
				//设置CTK扫描参数及基线更新参数
				CTK_Set_Para();
			
				TRISB |= ((open_sns_l << 2)  & 0xFC);
				TRISC |= ((open_sns_l >> 2)  & 0x30);
				TRISE |= ((open_sns_l >> 4)  & 0xF0);
				TRISF |= ((open_sns_l >> 12) & 0xFF);
				TRISG |= ((open_sns_l >> 20) & 0x0F);
				TRISH |= ((open_sns_l >> 24) & 0xFF);//设置为输入
				
				TRISA |= ((open_sns_h << 0)  & 0x0F);
				TRISB |= ((open_sns_h >> 4)  & 0x03);
				TRISC |= ((open_sns_h >> 6)  & 0x0F);
				TRISC |= ((open_sns_h >> 4)  & 0xC0);
				TRISE |= ((open_sns_h >> 12) & 0x0F);//设置为输入
				

				REG_ADDR = 0x26;REG_DATA |= ((open_sns_l)&0xFF);
				REG_ADDR = 0x27;REG_DATA |= ((open_sns_l>>8)&0xFF);
				REG_ADDR = 0x28;REG_DATA |= ((open_sns_l>>16)&0xFF);
				REG_ADDR = 0x29;REG_DATA |= ((open_sns_l>>24)&0xFF);//配置IO与SNS功能
				
				REG_ADDR = 0x51;REG_DATA |= ((open_sns_h)&0xFF);
				REG_ADDR = 0x52;REG_DATA |= ((open_sns_h>>8)&0xFF);//配置IO与SNS功能
		
				CTK_PRS_SW_SET(0);					//前端充放电开关,1为关，0为开
				CTK_LP_EN_SET(0);						//1：CTK模块低功耗;0：CTK模块正常模式
				CTK_RESO_SET(CTK_RESO);   	//0~7 CTK电容扫描分辨率，计数器位数：(CFG_CTK_RESOLUTION+9)位。
				CTK_PRS_SET(CTK_PRS); 			//PRS(充放电频率) = 96/2/(x+8)；x = 61时，PRS(充放电频率) = 400K；x = 62/63，PRS(充放电频率) = (1~1.5~3)MHz。
				CTK_DS_SET(CTK_DS); 				//检测速度0:24MHz,1:12MHz,2:6MHz,3:4MHz
				CTK_PAR_SET(Mode); 					//0为单通道模式，1为多通道并联模式
				CTK_RB_SET(CTK_RB);					//选择RB电阻大小0:20K,1:40K,2:60K,3:80K,4:150K,5:200K,6:250K,7:300K。
				CTK_VTH_SET(CTK_REF);				//0~7 参考电压(0:1.79V),(1:2.14V),(2:2.47V),(3:2.81V),(4:3.18V),(5:3.48V),(6:3.86V),(7:4.19V);//注：VCC-CTK_REF>0.5V
				CTK_BF7615BMXX_XXXX_Set_Para(pull_i_value[0]);			//设置电流源级数
				CTK_PRE_CH_SET(1);					//预充电时间：0为20us,1为40us
				CTK_PRE_DISCH_SET(1);				//预放电时间：0为2us,1为10us
				CTK_STOP;										//停止扫描
				CTK_PD_SET(0);							//开启CTK

				CTK_ADDR_SET(sensor_open[0]);
				CTK_IP_CLR;//CTK中优先级
				CTK_IE_SET;
				CTK_START;
				EA = 1;											//开总中断

		#endif	
	#endif
}



//-----------------------------------------------------------------//
//函数名称： void Init_IO(void)
//函数功能： IO口初始化,将没有用到的或悬空的IO口，设置为IO输出为低
//输入参数： 无
//返 回 值： 无
//-----------------------------------------------------------------//
void Init_IO(void)
{
	#if (TRACEMODE == FALSE) 

		#if CHIP_BF7615BMXX_XXXX
		//IO口初化
		//例:SET_PB0_IO_OUT;
		//例:SET_PB0_H;
		#endif

	#endif

	#if (TRACEMODE == TRUE) 
//		SET_PB3_IO_OUT;
//		SET_PB3_H;
	#endif
}

//-----------------------------------------------------------------//
//函数名称： void Default_Set_IO(void)
//函数功能： 默认IO口设置
//输入参数： 无
//返 回 值： 无
//-----------------------------------------------------------------//
void Default_Set_IO(void)
{   
	#if CHIP_BF7615BMXX_XXXX
		//设置为输出；
		//设置为上拉不使能;
		//默认PC4/PC5/PE4/PE5口开漏不使能；
		//设置为输出低
		EA = 0;
	
		REG_ADDR = 0x17;
		REG_DATA = 0x00;//PA0_PU_OFF~PA3_PU_OFF
		DATAA = 0x00;
		TRISA = 0x00;
	
		REG_ADDR = 0x18;
		REG_DATA = 0x00;//PB0_PU~PB7_PU
		DATAB = 0x00;
		TRISB = 0x00;
	
		REG_ADDR = 0x19;
		REG_DATA = 0x00;//PC0_PU~PC7_PU
		DATAC = 0x00;
		TRISC = 0x00;
		
		REG_ADDR = 0x1B;
		REG_DATA = 0x00;//PE0_PU~PE7_PU
		DATAE = 0x00;
		TRISE = 0x00;
		
		REG_ADDR = 0x1C;
		REG_DATA = 0x00;//PF4_PU~PF7_PU
		DATAF = 0x00;
		TRISF = 0x00;
		
		REG_ADDR = 0x1D;
		REG_DATA = 0x00;//PG0_PU~PG7_PU
		DATAG = 0x00;
		TRISG = 0x00;

		REG_ADDR = 0x1E;
		REG_DATA = 0x00;//PH0_PU~PH7_PU
		DATAH = 0x00;
		TRISH = 0x00;
		
		EA = 1;
			
	#endif
}

//-----------------------------------------------------------------//
//函数名称： void Trace_Mode_Init(void)
//函数功能： 调试模式初始化
//输入参数： 无
//返 回 值： 无
//-----------------------------------------------------------------//

void Trace_Mode_Init(void)
{
	#if (TRACEMODE == TRUE)

		#if CHIP_BF7615BMXX_XXXX
				BF7615BMXX_XXXX_Trace_Mode_Init(0x54,1);
		#endif

	#endif

}



//-----------------------------------------------------------------//
//函数名称： void Function_Init(void)
//函数功能： 功能模块初始化
//输入参数： 无
//返 回 值： 无
//-----------------------------------------------------------------//
void Function_Init(void)
{

#if (TRACEMODE == TRUE)

	#ifdef ADC_IS_OPEN
		#if ADC_IS_OPEN
				ADC_Init();
		#endif
	#endif
	
	#ifdef Timer0_EN
		#if Timer0_EN
			Timer0_Init(1000);//定时器0初始化
		#endif
	#endif
	
	#ifdef UART0_EN
		#if(UART0_EN == 1)
			UART0_Init();//UART0_初始化
		#endif
	#endif
	
	#ifdef UART1_EN
		#if(UART1_EN == 1)	
			UART1_Init();//UART1_初始化
		#endif
	#endif
	
	#ifdef UART2_EN
		#if(UART2_EN == 1)	
			UART2_Init();//UART2_初始化
		#endif
	#endif
	
	#ifdef IDLE_MODE
		#if IDLE_MODE
			Idle_Wake_Up_Init(3000,7);//需要设置Idle_IO_Init()及Idle_IORecovrey()函数
		#endif
	#endif
	
	#ifdef Timer1_EN
		#if ((Timer1_EN == 1))
				Timer1_Init(1000);//定时器1初始化
		#endif
	#endif
	
	#ifdef Timer2_EN
		#if Timer2_EN
			Timer2_Init(1,0);//定时器2初始化
		#endif
	#endif
	
	#ifdef Timer3_EN
		#if Timer3_EN
				Timer3_Init(1000,0);//定时器3初始化
		#endif
	#endif
	
	#ifdef ExtInt0_EN
		#if ExtInt0_EN
			ExtInt0_Init(0,0x001);//外部中断0初始化
		#endif
	#endif	
	
	#ifdef ExtInt1_EN
		#if ExtInt1_EN
			ExtInt1_Init(0);//外部中断1初始化
		#endif
	#endif
	
	#ifdef ExtInt2_EN
		#if ExtInt2_EN
			ExtInt2_Init(0);//外部中断2初始化
		#endif
	#endif	
	
	#ifdef ExtInt3_EN
		#if ExtInt3_EN
			ExtInt3_Init(0);//外部中断3初始化
		#endif
	#endif	
	
	#ifdef ExtInt4_EN
		#if ExtInt4_EN
			ExtInt4_Init(0,0x000000);//0xFFFFFF//外部中断4初始化
		#endif
	#endif
	
	#ifdef VolDet_EN
		#if	VolDet_EN
				LVDT_Init();//升压/降压检测初始化
		#endif
	#endif

	#ifdef LED_SWITCH_EN
		#if	LED_SWITCH_EN
			#if (LED_SER_ARR_EN == 1)
				LED_SER_Init();//LED串行点阵扫描初始化
			#else
				LED_ARR_Init();//LED行列点阵扫描初始化
			#endif
		#endif
	#endif
	
	#ifdef PWM0_EN
		#if PWM0_EN
			PWM0_Set(0,4000,0,PWM0_PORT);//PWM0初始化
		#endif
	#endif
	
	#ifdef PWM1_EN
		#if PWM1_EN
			PWM1_Set(0,4000,0,PWM1_PORT);//PWM1初始化
		#endif
	#endif
	
	#ifdef PWM2_EN
		#if PWM2_EN
			PWM2_Set(1,4000,1500);//PWM2初始化
		#endif
	#endif
		
		
	#ifdef PWM3_EN
		#if PWM3_EN
			PWM3_Set(0,4000,0);//PWM3初始化
		#endif
	#endif
	
	#ifdef LCD_EN
		#if	LCD_EN
				LCD_Init();//LCD初始化
		#endif
	#endif
	
	#ifdef EEPROM_EN
		#if (EEPROM_EN == 1)
			Eeprom_Init();//EEP初始化
		#endif
	#endif
	
	#ifdef SPI_EN
		#if (SPI_EN == 1)
			SPI_Init();//SPI初始化
		#endif
	#endif
	
#endif


#if (TRACEMODE == FALSE)
	 
		#ifdef UART0_EN
			#if(UART0_EN == 1)
				UART0_Init();//UART0_初始化
			#endif
		#endif
		
		#ifdef UART1_EN
			#if(UART1_EN == 1)
				UART1_Init();//UART1_初始化
			#endif
		#endif
		
		#ifdef UART2_EN
			#if(UART2_EN == 1)	
				UART2_Init();//UART2_初始化
			#endif
		#endif
		
		#ifdef ADC_IS_OPEN
			#if ADC_IS_OPEN
				ADC_Init();//ADC初始化
			#endif
		#endif
		
		#ifdef IDLE_MODE
			#if IDLE_MODE
				Idle_Wake_Up_Init(3000,7);//需要设置dle_IO_Init()及Idle_IORecovrey()函数，配合timer0进行定时使用。
			#endif
		#endif
		
		#ifdef PWM0_EN
			#if PWM0_EN
				PWM0_Set(0,4000,0,PWM0_PORT);//PWM0初始化
			#endif
		#endif
		
		#ifdef PWM1_EN
			#if PWM1_EN
				PWM1_Set(0,4000,0,PWM1_PORT);//PWM1初始化
			#endif
		#endif
		
		#ifdef PWM2_EN
			#if PWM2_EN
				PWM2_Set(0,4000,0);//PWM2初始化
			#endif
		#endif
			
			
		#ifdef PWM3_EN
			#if PWM3_EN
				PWM3_Set(0,4000,0);//PWM3初始化
			#endif
		#endif
	
		#ifdef Timer0_EN
			#if Timer0_EN
				Timer0_Init(1000);//定时器0初始化
			#endif
		#endif

		#ifdef Timer1_EN
			#if ((Timer1_EN == 1))
				Timer1_Init(1000);//定时器1初始化
			#endif
		#endif
		
		#ifdef Timer2_EN
			#if Timer2_EN
				Timer2_Init(1,0);//定时器2初始化
			#endif
		#endif
		
		#ifdef Timer3_EN
			#if Timer3_EN
				Timer3_Init(1000,0);//定时器3初始化
			#endif
		#endif
	
	#ifdef ExtInt0_EN
		#if ExtInt0_EN
			ExtInt0_Init(0,0x001);//外部中断0初始化
		#endif
	#endif	
	
	#ifdef ExtInt1_EN
		#if ExtInt1_EN
			ExtInt1_Init(0);//外部中断1初始化
		#endif
	#endif
	
	#ifdef ExtInt2_EN
		#if ExtInt2_EN
			ExtInt2_Init(0);//外部中断2初始化
		#endif
	#endif	
	
	#ifdef ExtInt3_EN
		#if ExtInt3_EN
			ExtInt3_Init(0);//外部中断3初始化
		#endif
	#endif	
	
	#ifdef ExtInt4_EN
		#if ExtInt4_EN
			ExtInt4_Init(0,0x000200);//0xFFFFFF//外部中断4初始化
		#endif
	#endif

		#ifdef IICS_EN
			#if ((IICS_EN == 1) && (TRACEMODE == FALSE))
				IIC_Slave_Init(0XC1,1);//IIC从机初始化,0-为选择PC4/5为串口，1选择PE4/5为串口	   
			#endif
		#endif

		
		#ifdef VolDet_EN
			#if	VolDet_EN
				LVDT_Init();//升压/降压检测初始化
			#endif
		#endif
		
		#ifdef LED_SWITCH_EN
			#if	LED_SWITCH_EN
				#if (LED_SER_ARR_EN == 1)
					LED_SER_Init();//LED串行点阵扫描初始化
				#else
					LED_ARR_Init();//LED行列点阵扫描初始化
				#endif
			#endif
		#endif
		
		#ifdef LCD_EN
			#if	LCD_EN
					LCD_Init();//LCD初始化
			#endif
		#endif
		
		#ifdef EEPROM_EN
			#if (EEPROM_EN == 1)
				Eeprom_Init();//EEP初始化
			#endif
		#endif
		
		#ifdef SPI_EN
			#if (SPI_EN == 1)
				SPI_Init();//SPI初始化
			#endif
		#endif
		
#endif
}

//-----------------------------------------------------------------//
//函数名称： void MCU_Init(void)
//函数功能:		MUC初始化
//输入参数： 无
//返 回 值： 无
//-----------------------------------------------------------------//
void MCU_Init(void)
{	 

	BOR_SET(0);//0为开掉电复位，1关掉电复位
	
	//看门狗初始化
	WDT_Init();

	//配置核工作时钟
	Set_Sys_Clk();

	//配置字对比判断
	CFG_Check();

	//IO口默认设置
	Default_Set_IO();

	//IO口初始化
	Init_IO();

	//调试模式初始化
	Trace_Mode_Init();

	//功能函数初始化
	Function_Init(); 
	
	//CTK初始化	
	CTK_Init();

}