#ifndef __BF7615BMXX_XXXX_API_LED_H__
#define __BF7615BMXX_XXXX_API_LED_H__


#define	LED_SWITCH_EN				0//LED_EN使能配置	 	  1:使能编译，0:不使能编译
#define	LED_SER_ARR_EN			1//LED_SER_ARR_EN	使能配置	1:串行点阵，0:行列矩阵
#define	LED_MODE						1//LED扫描模式选择	1:循环模式；0:中断模式

#define LED_LCD_FUN_SET(x)    {DP_CON &= ~(0x40);DP_CON |= (0x40&(x<<6));}//1为LED_LCD功能开，0为LED_LCD功能关
#define LED_SER_FUN_SET(x)    {DP_CON &= ~(0x04);DP_CON |= (0x04&(x<<2));}//1为LED功能，0为LCD功能
#define LED_SER_COM_SET(x)   	{DP_CON &= ~(0x01);DP_CON |= (0x01&(x<<0));}//COM大电流选择，0为不开启，1为开启(开启后LED/LCD硬件扫描时序无效)
#define LED_SER_MODE_SET(x)   {DP_MODE &= ~(0x80);DP_MODE |= (0x80&(x<<7));}//1为串行点阵模式，0为行列矩阵模式；
#define LED_SER_MATRIX_SET(x) {DP_CON &= ~(0x38);DP_CON |= (0x38&(x<<3));}//LED串行点阵矩阵选择(X*Y) 0-4*5，1-5*6，2-6*7，3-7*8,4-4*5(以PB3为起始端口)
#define LED_SER_CURRENT_SET(x){REG_ADDR = 0x31;REG_DATA &= ~(0x0F);REG_DATA |= (0x0F&(x<<0));}	//LED驱动能力配置(0~15)，参照规格书表格(0-3.7mA),(9-43.7mA),(15-68.7mA)@LED压降2.5V
#define LED_SER_LED1_WIDTH_SET(x)  (SCAN_WIDTH = x)   							//单个灯导通时间1配置，(x+1)*16us
#define LED_SER_LED2_WIDTH_SET(x)  (LED2_WIDTH = x)									//单个灯导通时间2配置，(x+1)*16us
#define LED_SER_SCAN_SET(x)   {DP_CON &= ~(0x02);DP_CON |= (0x02&(x<<1));}//LED扫描模式选择，0为中断模式，1为循环模式 
#define LED_START_SET(x)  		{SCAN_START &= ~(0x01);SCAN_START |= (0x01&(x<<0));}//LED扫描开始停止控制，0为停止扫描，1为开始扫描



#define LED_ARR_FUN_SET(x)    {DP_CON &= ~(0x04);DP_CON |= (0x04&(x<<2));}//1为LED功能，0为LCD功能
#define LED_ARR_SEG_SET(x)    {REG_ADDR = 0x24;REG_DATA &= ~(0xFF);REG_DATA |= (0xFF&(x<<0));}//LED行列矩阵SEG口选择,对应的位为1选择为SEG口功能
#define LED_ARR_CON_EN(x)     {REG_ADDR = 0x23;REG_DATA &= ~(0xFF);REG_DATA |= (0xFF&(x<<0));}//LED行列矩阵COM口选择,对应的位为1选择为COM口功能
#define LED_ARR_COM_SET(x)   	{DP_CON &= ~(0x01);DP_CON |= (0x01&(x<<0));}//COM大电流选择，0为不开启，1为开启(开启后LED/LCD硬件扫描时序无效)
#define LED_ARR_MODE_SET(x)   {DP_MODE &= ~(0x80);DP_MODE |= (0x80&(x<<7));}//1为串行点阵模式，0为行列矩阵模式；
#define LED_ARR_COM_TIME(x) 	(SCAN_WIDTH = x)   							//单个COM导通时间1配置，(x+1)*16us
#define LED_ARR_DUTY_SET(x) 	{DP_CON &= ~(0x38);DP_CON |= (0x38&(x<<3));}//LED行列矩阵COM通道占空比选择(0~7) (x+1)/8
#define LED_ARR_SCAN_SET(x)   {DP_CON &= ~(0x02);DP_CON |= (0x02&(x<<1));}//LED行列矩阵扫描模式选择，0为中断模式，1为循环模式 
#define LED_ARR_START_SET(x)  {SCAN_START &= ~(0x01);SCAN_START |= (0x01&(x<<0));}//LED扫描开始停止控制，0为停止扫描，1为开始扫描


#define LED_IE_SET IEN1 |= 0X40																	//开LED中断使能
#define LED_IE_CLR IEN1 &= ~0X40																//关LED中断使能
#define LED_IP_SET IPL1 |= 0X40																	//设置LED中断优先级为高
#define LED_IP_CLR IPL1 &= ~0X40																//设置LED中断优先级为低
#define LED_INT_FLAG_CLR IRCON1 &= ~0x40;INT_PE_STAT = ~0x01			// 清除LED中断标志位


#if(LED_SWITCH_EN == 1)
	#if (LED_SER_ARR_EN == 1)
		extern void LED_SER_Init(void);
		extern void LED_SER_Data(ulong led_data_h,ulong led_data_l);
		extern void LED_SER_Light_Set(ulong led_width_h,ulong led_width_l);
		#if (LED_MODE == 0)
			extern void LED_SER_Light_Set_Int(ulong led_width_h,ulong led_width_l);
		#endif
		extern void LED_SER_Dis_Num(uchar num,uchar dis_data);

		extern uchar code Led_ser_num[];
		extern uchar code Led_dp1;
		extern uchar code Led_dp2;
		extern uchar code Led_dp3;
		extern uchar code Led_dp4;
		extern uchar code Led_dp5;
		extern uchar code Led_dp6;
		extern ulong xdata LED_H_Tem;
		extern ulong xdata LED_L_Tem;
		extern ulong xdata LED_Light_H_Tem;
		extern ulong xdata LED_Light_L_Tem;
	#endif
	
	#if (LED_SER_ARR_EN == 0)
		extern void LED_ARR_Init(void);
		extern void LED_ARR_Data(uchar com,uchar seg_data);
		extern uchar code Led_arr_num1[];
	#endif

#endif

#endif