#ifndef __BF7615BMXX_XXXX_API_LCD_H__
#define __BF7615BMXX_XXXX_API_LCD_H__

#define LCD_EN									0// 1:使能编译，0:不使能编译
#if LCD_EN
	#define LED_LCD_FUN_SET(x)  		{DP_CON &= ~(0x40);DP_CON 	|= (0x40&(x<<6));}//1为LED_LCD功能开，0为LED_LCD功能关
	#define LCD_FUN_SET(x)    			{DP_CON &= ~(0x04);DP_CON 	|= (0x04&(x<<2));}//1为LED功能，0为LCD功能
	#define LCD_CLK_SET(x)    			{DP_MODE &= ~(0x60);DP_MODE |= (0x60&(x<<5));}//0为内部RC32K,1为外部晶振32768Hz，2内部RC1MHz
	#define LCD_RES_SET(x)    			{DP_MODE &= ~(0x10);DP_MODE |= (0x10&(x<<4));}//0为LCD偏置电阻225K，1为LCD偏置电阻900K
	#define LCD_COM_WIDTH_SET(x)    {SCAN_WIDTH &= ~(0xFF);SCAN_WIDTH |= (0xFF&(x<<0));}//LCD时钟为1M时，单COM扫描时间设置(SCAN_WIDTH+1)*64,0.064ms~4.096ms
	#define LCD_CHARGE_SET(x)    		{DP_MODE &= ~(0x0C);DP_MODE |= (0x0C&(x<<2));}//充电时间控制：0为1/8 COM周期，1为1/16 COM周期，2为1/32 COM周期，3为1/64 COM周期
	#define LCD_MODE_SET(x)    			{DP_MODE &= ~(0x03);DP_MODE |= (0x03&(x<<0));}//驱动模式控制：0为传统电阻模式(225K/900K)，1为传统电阻模式(60K)，2为1/32 COM周期，3为快速充电模式(自动在60K/225K/900K之间切换)
	#define LCD_CONSTRAT_EN_SET(x)  {DP_CON1 &= ~(0x10);DP_CON1 |= (0x10&(x<<4));}//对比度使能：0为关闭对比控制，1为打开对比控制
	#define LCD_CONSTRAT_SET(x)  		{DP_CON1 &= ~(0x0F);DP_CON1 |= (0x0F&(x<<0));}//对比度电压选择：(0~15)--(0.531V~1.00V)
	#define LCD_SEG_SEL_SET(x)  		{REG_ADDR = 0x1F;REG_DATA &= ~(0xFF);REG_DATA |= (0xFF&(x));REG_ADDR = 0x20;REG_DATA &= ~(0xFF);REG_DATA |= (0xFF&(x>>8));REG_ADDR = 0x21;REG_DATA &= ~(0xFF);REG_DATA |= (0xFF&(x>>16));REG_ADDR = 0x22;REG_DATA &= ~(0xFF);REG_DATA |= (0x0F&(x>>24));}//对应的位为1时选择为LCD功能,SEG0~SEG27
	//SEG口选择，SEG0~SEG27,对应的位为1,选择为SEG口功能
	#define LCD_DUTY_SET(x)  				{DP_CON &= ~(0x38);DP_CON 	|= (0x38&(x<<3));}//占空比配置：

	//0:1/4占空比,1/3 偏置(COM0~COM3)--4*16,SEG0~SEG7,SEG16~SEG23
	//1:1/8占空比,1/4 偏置(COM0~COM7)--8*16,SEG0~SEG7,SEG16~SEG23
	//2:1/4占空比,1/3 偏置(COM0~COM3)--4*20,SEG0~SEG7,SEG16~SEG23,COM4~COM7共享为SEG24~SEG27
	//3:1/5占空比,1/3 偏置(COM0~COM4)--5*19,SEG0~SEG7,SEG16~SEG23,COM5~COM7共享为SEG25~SEG27
	//4:1/6占空比,1/3 偏置(COM0~COM5)--6*18,SEG0~SEG7,SEG16~SEG23,COM6~COM7共享为SEG26~SEG27
	//5:1/6占空比,1/4 偏置(COM0~COM5)--4*18,SEG0~SEG7,SEG16~SEG23，COM6-7 共享为 SEG26-SEG27
	//6/other:1/4占空比,1/3 偏置(COM0~COM3)--4*16,SEG0~SEG7,SEG16~SEG23

	#define LCD_START_SET(x)  			{SCAN_START &= ~(0x01);SCAN_START |= (0x01&(x<<0));}//LCD扫描开始停止控制，0为停止扫描，1为开始扫描


	#define LCD_IE_SET IEN1 |= 0X40																	//开LCD中断使能
	#define LCD_IE_CLR IEN1 &= ~0X40																//关LCD中断使能
	#define LCD_IP_SET IPL1 |= 0X40																	//设置LCD中断优先级为高
	#define LCD_IP_CLR IPL1 &= ~0X40																//设置LCD中断优先级为低
	#define LCD_INT_FLAG_CLR IRCON1 &= ~0x40;INT_PE_STAT = ~0x02		// 清除LCD中断标志位

	extern void LCD_Data(uchar com,ulong seg);
	extern void LCD_Init(void);


	extern uchar code Lcd_ser_num1[];
					
	extern uchar code Lcd_dp1;
	extern uchar code Lcd_dp2;
	extern uchar code Lcd_dp3;
	extern uchar code Lcd_dp4;
	extern uchar code Lcd_dp5;
	extern uchar code Lcd_dp6;

#endif

#endif