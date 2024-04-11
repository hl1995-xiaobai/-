/****************************************************/
BYD_MCU02D_BF7615BMXX_XXXX_V1.1.3
更新日期：2023-03-24
1)将void LCD_Init(void) 函数中的以下语句：
LCD_IE_SET;//设置LCD中断优级为高，根据实际应运设置优先级
改为：
LCD_IP_SET;//设置LCD中断优级为高，根据实际应运设置优先级
更新日期：2023-03-24
1)删除sleep模块
2）修改了idle.c文件中的void Idle()函数，修改了Touch_MCU_Init.h文件中的 DELAY_MS_EN宏的值
3)将void Function_Init(void)函数中的以下代码：
		#ifdef Timer2_EN
			#if Timer3_EN
				Timer3_Init(1000,0);//定时器3初始化
			#endif
		#endif
改为
		#ifdef Timer3_EN
			#if Timer3_EN
				Timer3_Init(1000,0);//定时器3初始化
			#endif
		#endif
4）修复了将IIC使能IICS_EN宏设置为1所报的错
5）删除了config.h文件中重复的宏“#define FTH_PARA 300//并联模式手指阈值”只保留一个 
6）将LCD.h和和LCD.c文件中驱动模式占空比寄存器配置宏 LCD_DUTY_SET的以下注释
	//0:1/4占空比,1/3 偏置(COM0~COM3)--4*16,SEG0~SEG7,SEG16~SEG23
	//1:1/8占空比,1/4 偏置(COM0~COM7)--8*16,SEG0~SEG7,SEG16~SEG23
	//2:1/4占空比,1/3 偏置(COM0~COM3)--4*20,SEG0~SEG7,SEG16~SEG23,COM4~COM7共享为SEG24~SEG27
	//3:1/5占空比,1/3 偏置(COM0~COM4)--5*19,SEG0~SEG7,SEG16~SEG23,COM5~COM7共享为SEG24~SEG26
	//4:1/6占空比,1/3 偏置(COM0~COM5)--6*18,SEG0~SEG7,SEG16~SEG23,COM6~COM7共享为SEG24~SEG25
	//5:1/6占空比,1/4 偏置(COM0~COM3)--4*16,SEG1~SEG7,SEG16~SEG23
	//6/other:1/4占空比,1/3 偏置(COM0~COM3)--4*16,SEG1~SEG7,SEG16~SEG23
	修改为
	//0:1/4占空比,1/3 偏置(COM0~COM3)--4*16,SEG0~SEG7,SEG16~SEG23
	//1:1/8占空比,1/4 偏置(COM0~COM7)--8*16,SEG0~SEG7,SEG16~SEG23
	//2:1/4占空比,1/3 偏置(COM0~COM3)--4*20,SEG0~SEG7,SEG16~SEG23,COM4~COM7共享为SEG24~SEG27
	//3:1/5占空比,1/3 偏置(COM0~COM4)--5*19,SEG0~SEG7,SEG16~SEG23,COM5~COM7共享为SEG25~SEG27
	//4:1/6占空比,1/3 偏置(COM0~COM5)--6*18,SEG0~SEG7,SEG16~SEG23,COM6~COM7共享为SEG26~SEG27
	//5:1/6占空比,1/4 偏置(COM0~COM5)--4*18,SEG0~SEG7,SEG16~SEG23，COM6-7 共享为 SEG26-SEG27
	//6/other:1/4占空比,1/3 偏置(COM0~COM3)--4*16,SEG0~SEG7,SEG16~SEG23
7）删除了#define T0_CT_MODE(x)宏的定义和使用
8）删除了#define T1_CT_MODE(x)宏的定义和使用
9) 删除了timer.c和timer.h文件中定时器计数功能的描述
10)更新了MCU_Init.c文件中SYS_CLK_SET(SYS_CLK);语句的备注
BYD_MCU02D_BF7615BMXX_XXXX_V1.1.2		
更新日期：2022-06-28
1)修复了CTK_Touch.c文件中BF7615BMXX_XXXX_Set_Touch_Flag函数中#if TRACEMODE宏判断下传输标志位的计算代码，
解决了按键数大于32时，32及以后按键调试窗口无触摸标志位的Bug。
更新日期：2021-09-26
1)修复Read_ROM_Offset返回值不对Bug。
BYD_MCU02D_BF7615BMXX_XXXX_V1.1.1
更新日期：2021-08-12
1)修复FTH设置>3276计算应溢出Bug。
BYD_MCU02D_BF7615BMXX_XXXX_V1.1.0
更新日期：2021-05-12
1)修复ADJUST_LINE宏，RESO为15/16bit时自适应溢出Bug。
BYD_MCU02D_BF7615BMXX_XXXX_V1.0.9
2021-4-19
1)修复“RENOVATE_MODE为1时，differ<=p_noise，编译不通过问题。”
BYD_MCU02D_BF7615BMXX_XXXX_V1.0.8
2021-3-24
1)修正IO初始化在CTK之前时，CTK初始化影响 PC4/PC5 IO方向初始化。
“TRISC |= ((open_sns_h >> 6)  & 0xFF);”修改为“TRISC |= ((open_sns_h >> 6)  & 0x0F);TRISC |= ((open_sns_h >> 4)  & 0xC0);”
BYD_MCU02D_BF7615BMXX_XXXX_V1.0.7
2021-3-23
1)修改备注“用到IAP功能时，增加读EEP函数读取rom_offset偏移地址；”
2)修正“TRISC |= ((open_sns_h >> 4)  & 0xFF);”为“TRISC |= ((open_sns_h >> 6)  & 0xFF);”
BYD_MCU02D_BF7615BMXX_XXXX_V1.0.6
2021-2-18
1)增加LVDT规避触摸按键掉电误触参考；
2）二级总线地址寄存器，现场保护更新为在中断中静态变量；
3）注释UART查询方式发送数据，默认开启发送中断；
4)用到IAP功能时，增加读EEP函数读取rom_offset偏移地址；
BYD_MCU02D_BF7615BMXX_XXXX_V1.0.5
2021-1-6
1)修改CTK_RB默认参数为60K,ADJUST_LINE-自适应目标线为最大分辨率计数的70%
2)中断函数中增加PUSH_REG_ADDR_SFR,POP_REG_ADDR_SFR
3)修改SPI_CS_SET(x)宏为SPI_CS_SET(),增加SPI_CS_CLR()宏,增加SPI发送参考函数
2020-12-9
1)修正XXX_API_Timer.h文件T2_IP_CLR宏定义
2)修正“TRISC |= ((open_sns_h >> 6)  & 0xFF);”为“TRISC |= ((open_sns_h >> 4)  & 0xFF);”
3)修正UART2_INT_IF_XX_CLR(x)、ADC_CTRL(x)定义
4)更新CTK_VTH_SET(x)注释
5)优化Idle计数
BYD_MCU02D_BF7615BMXX_XXXX_V1.0.4
2020-10-29
1)更新Eeprom_Write_Byteb/NVR_Write_Byte函数注释；
2)增加PF0~PF3位定义
3)修复BF7615BMXX_XXXX_API_SPI.h文件里宏定义；
4)优化CTK_BF7615BMXX_XXXX_Get_KEYS_Touch()函数
BYD_MCU02D_BF7615BMXX_XXXX_V1.0.3
20-09-17
1)修正T2_IE_SET/CLR,T2_IP_SET/CLR宏
2)修复Idle模式CTK无数据
3)更新EEPROM_ERASE_TIMER_SET(X);//注释
4)更新UART2_TRANS_EN_SET(x)//注释,增加UART2_TRANS_ENABLE()、UART2_TRANS_DISABLE()宏
5)优化长按键判断
6)更新ADC_VIN宏相关注释
7)更新ADC_SEL04/05注释
8)XXX_API_Lib目录增加XXX.API_Read_UID.c/h文件,芯片UID读取函数
9)优化“Get_ADC_Vref”、“Get_Inner_ADC_Vol”函数增加EA开关。
20-08-14
1)修正"INT4_29_FUN_SET(x)"宏为“INT4_19_FUN_SET(x)”
2)更新工和名为“BYD_MCU02D_BF7615BMXX_XXXX_V1.0.X”
BYD_MCU02D_BF7615BMXX_XXXX_V1.0.2
1)修复初始化语句Bug,"TRISE |= ((open_sns_h >> 14) & 0x0F);//设置为输入“。
2)增加“Get_ADC_Vref”、“Get_Inner_ADC_Vol”函数,ADC参考电压校准值读取函数和ADC内部通道输入电压读取函数。
BYD_MCU02D_BF7615BMXX_V1.0.1
1)增加SFR (P2_XH)0xA0地址，使用MOVX @Ri,A指令 操作PDATA区时，P2_XH清0，建议变量不要定义在PDATA区，定义XDATA区。
BYD_MCU02D_BF7615BMXX_V1.0.0
1)初版。
/****************************************************************************************/
说明：
例程仅供参考
1、开发底层软件包，尽可能做到兼容性或适应性更好，实际应用项目中以实际开发测试验证为准。
2、Keil编译器不会对堆栈大小作限制，堆栈分配在DATA或IDATA区向上增涨与程序中断与函数调用有关
3、所以程序一般建议预留至少50个字节，具体以实际项目应用测试验证为准。
/****************************************************************************************/