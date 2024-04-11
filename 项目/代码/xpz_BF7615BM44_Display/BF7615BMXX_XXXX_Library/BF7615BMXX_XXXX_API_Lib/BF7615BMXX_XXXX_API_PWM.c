#include ".\BF7615BMXX_XXXX_Library\Config.h"
#if (PWM0_EN == 1)
	#pragma message "编译?vvoid PWM0_Set(bit pwm_switch,ulong pwm_fre,ulong pwm_duty,uchar pwm_prot)函数"
	//函数名：void PWM0_Set(bit pwm_switch,uint pwm_fre, uint pwm_duty,uchar pwm_prot);
	//功  能：初始化PWM0标准程序
	//输出周期：Tpwm_data = （PWM_H + PWM_L）*Tmcu_clk；
	//输出占空比：Dpwm_data = PWM_H/（PWM_L + PWM_H）；
	//参  数：bit pwm_switch:PWM功能模块开关控制，0为关，1为开；ulong pwm_fre频率(Hz);ulong pwm_duty:PWM高电平级数pwm_duty/PWM0_RANK(0 <= pwm_duty <= PWMX_RANK);uchar pwm_prot:选择输出IO口
	//返回值：无
	//[pwm_fre,pwm_duty]-[4000-3000]-[4K,100%];[pwm_fre,pwm_duty]-[2000-6000]-[2K,100%];[pwm_fre,pwm_duty]-[200-60000]-[200Hz,100%]
	void PWM0_Set(bit pwm_switch,ulong pwm_fre,ulong pwm_duty,uchar pwm_prot)
	{	
		uint xdata pwm_h = 0X00;
		uint xdata pwm_l = 0X00;	
		ulong xdata pwm_h_l = ((SYS_CLK_FRE*1000000*1.0) / (pwm_fre*1.0));
		if(pwm_switch == 1)
		{
			REG_ADDR = 0x33;REG_DATA |= (0x07 & pwm_prot);//选择PWM输出口
			
			if(pwm_prot & 0x01)
			{
				TRISB &= ~0x10;
			}
			if(pwm_prot & 0x02)
			{
				TRISB &= ~0x40;
			}
			if(pwm_prot & 0x04)
			{
				TRISC &= ~0x04;
					
			}//设置为IO输出
			if(pwm_duty <= pwm_h_l)
			{
				pwm_h = pwm_duty;
				pwm_l = pwm_h_l - (ulong)pwm_h;
			}
			else
			{
				pwm_h = (uint)pwm_h_l;
				pwm_l = 0;
			}
			PWM0_L_L = (uchar)(pwm_l);
			PWM0_L_H = (uchar)(pwm_l >> 8);
			PWM0_H_L = (uchar)(pwm_h);
			PWM0_H_H = (uchar)(pwm_h >> 8);

		}
		else
		{
			REG_ADDR = 0x33;REG_DATA &= ~(0x07 & pwm_prot);//关闭PWM输出口
			if(pwm_prot & 0x01)
			{
					TRISB |= 0x10;
			}
			if(pwm_prot & 0x02)
			{
				TRISB |= 0x40;
			}
			if(pwm_prot & 0x04)
			{
				TRISC |= 0x04;
			}//设置为IO输入
		}	
		REG_ADDR = 0;
	}  
#endif
	
#if (PWM1_EN == 1)
	#pragma message "编译?vvoid PWM1_Set(bit pwm_switch,ulong pwm_fre,ulong pwm_duty,uchar pwm_prot)函数"
	//函数名：void PWM1_Set(bit pwm_switch,uint pwm_fre, uint pwm_duty,uchar pwm_prot);
	//功  能：初始化PWM1标准程序
	//输出周期：Tpwm_data = （PWM_H + PWM_L）*Tmcu_clk；
	//输出占空比：Dpwm_data = PWM_H/（PWM_L + PWM_H）；
	//参  数：bit pwm_switch:PWM功能模块开关控制，0为关，1为开；ulong pwm_fre频率(Hz);ulong pwm_duty:PWM高电平级数pwm_duty/PWM0_RANK(0 <= pwm_duty <= PWMX_RANK);uchar pwm_prot:选择输出IO口
	//返回值：无
	//[pwm_fre,pwm_duty]-[4000-3000]-[4K,100%];[pwm_fre,pwm_duty]-[2000-6000]-[2K,100%];[pwm_fre,pwm_duty]-[200-60000]-[200Hz,100%]
	void PWM1_Set(bit pwm_switch,ulong pwm_fre,ulong pwm_duty,uchar pwm_prot)
	{	
		uint xdata pwm_h = 0X00;
		uint xdata pwm_l = 0X00;	
		ulong xdata pwm_h_l = ((SYS_CLK_FRE*1000000*1.0) / (pwm_fre*1.0));
		if(pwm_switch == 1)
		{
			REG_ADDR = 0x33;REG_DATA |= (0x38 & (pwm_prot<<3));//选择PWM输出口
			if(pwm_prot & 0x01)
			{
				TRISB &= ~0x20;
			}
			if(pwm_prot & 0x02)
			{
				TRISB &= ~0x80;
			}
			if(pwm_prot & 0x04)
			{
				TRISC &= ~0x08;
			}//设置为IO输出
			if(pwm_duty <= pwm_h_l)
			{
				pwm_h = pwm_duty;
				pwm_l = pwm_h_l - (ulong)pwm_h;
			}
			else
			{
				pwm_h = (uint)pwm_h_l;
				pwm_l = 0;
			}
			PWM1_L_L = (uchar)(pwm_l);
			PWM1_L_H = (uchar)(pwm_l >> 8);
			PWM1_H_L = (uchar)(pwm_h);
			PWM1_H_H = (uchar)(pwm_h >> 8);
		}
		else
		{
			REG_ADDR = 0x33;REG_DATA &= ~(0x38 & (pwm_prot<<3));//关闭PWM输出口
			if(pwm_prot & 0x01)
			{
				TRISB |= 0x20;
			}
			if(pwm_prot & 0x02)
			{
				TRISB |= 0x80;
			}
			if(pwm_prot & 0x04)
			{
				TRISC |= 0x08;
			}//设置为IO输入
		}	
		REG_ADDR = 0;
	}  
#endif
	
#if (PWM2_EN == 1)
	#pragma message "编译?vvoid PWM2_Set(bit pwm_switch,ulong pwm_fre,ulong pwm_duty)函数"
	//函数名：void PWM2_Set(bit pwm_switch,uint pwm_fre, uint pwm_duty);
	//功  能：初始化PWM2标准程序
	//输出周期：Tpwm_data = （PWM_H + PWM_L）*Tmcu_clk；
	//输出占空比：Dpwm_data = PWM_H/（PWM_L + PWM_H）；
	//参  数：bit pwm_switch:PWM功能模块开关控制，0为关，1为开；ulong pwm_fre频率(Hz);ulong pwm_duty:PWM高电平级数pwm_duty/PWM0_RANK(0 <= pwm_duty <= PWMX_RANK);uchar pwm_prot:选择输出IO口
	//返回值：无
	//[pwm_fre,pwm_duty]-[4000-3000]-[4K,100%];[pwm_fre,pwm_duty]-[2000-6000]-[2K,100%];[pwm_fre,pwm_duty]-[200-60000]-[200Hz,100%]
	void PWM2_Set(bit pwm_switch,ulong pwm_fre,ulong pwm_duty)
	{	
		uint xdata pwm_h = 0X00;
		uint xdata pwm_l = 0X00;	
		ulong xdata pwm_h_l = ((SYS_CLK_FRE*1000000*1.0) / (pwm_fre*1.0));
		if(pwm_switch == 1)
		{
			REG_ADDR = 0x33;REG_DATA |= (0x40);//选择PWM输出口
			TRISH &= ~0x80;//设置为IO输输出
			if(pwm_duty <= pwm_h_l)
			{
				pwm_h = pwm_duty;
				pwm_l = pwm_h_l - (ulong)pwm_h;
			}
			else
			{
				pwm_h = (uint)pwm_h_l;
				pwm_l = 0;
			}
			PWM2_L_L = (uchar)(pwm_l);
			PWM2_L_H = (uchar)(pwm_l >> 8);
			PWM2_H_L = (uchar)(pwm_h);
			PWM2_H_H = (uchar)(pwm_h >> 8);
		}
		else
		{
			REG_ADDR = 0x33;REG_DATA &= ~(0x40);//关闭PWM输出口
			TRISH |= 0x80;//设置为IO输入
		}	
		REG_ADDR = 0;
	}  
#endif
	
#if (PWM3_EN == 1)
	#pragma message "编译?vvoid PWM3_Set(bit pwm_switch,ulong pwm_fre,ulong pwm_duty)函数"
	//函数名：void PWM3_Set(bit pwm_switch,uint pwm_fre, uint pwm_duty);
	//功  能：初始化PWM3标准程序
	//输出周期：Tpwm_data = （PWM_H + PWM_L）*Tmcu_clk；
	//输出占空比：Dpwm_data = PWM_H/（PWM_L + PWM_H）；
	//参  数：bit pwm_switch:PWM功能模块开关控制，0为关，1为开；ulong pwm_fre频率(Hz);ulong pwm_duty:PWM高电平级数pwm_duty/PWM0_RANK(0 <= pwm_duty <= PWMX_RANK);uchar pwm_prot:选择输出IO口
	//返回值：无
	//[pwm_fre,pwm_duty]-[4000-3000]-[4K,100%];[pwm_fre,pwm_duty]-[2000-6000]-[2K,100%];[pwm_fre,pwm_duty]-[200-60000]-[200Hz,100%]
	void PWM3_Set(bit pwm_switch,ulong pwm_fre,ulong pwm_duty)
	{	
		uint xdata pwm_h = 0X00;
		uint xdata pwm_l = 0X00;	
		ulong xdata pwm_h_l = ((SYS_CLK_FRE*1000000*1.0) / (pwm_fre*1.0));
		if(pwm_switch == 1)
		{
			REG_ADDR = 0x33;REG_DATA |= (0x80);//选择PWM输出口
			TRISA &= ~0x01;//设置为IO输输出
			if(pwm_duty <= pwm_h_l)
			{
				pwm_h = pwm_duty;
				pwm_l = pwm_h_l - (ulong)pwm_h;
			}
			else
			{
				pwm_h = (uint)pwm_h_l;
				pwm_l = 0;
			}
			PWM3_L_L = (uchar)(pwm_l);
			PWM3_L_H = (uchar)(pwm_l >> 8);
			PWM3_H_L = (uchar)(pwm_h);
			PWM3_H_H = (uchar)(pwm_h >> 8);
		}
		else
		{
			REG_ADDR = 0x33;REG_DATA &= ~(0x80);//关闭PWM输出口
			TRISA |= 0x01;//设置为IO输入
		}	
		REG_ADDR = 0;
	}  
#endif

