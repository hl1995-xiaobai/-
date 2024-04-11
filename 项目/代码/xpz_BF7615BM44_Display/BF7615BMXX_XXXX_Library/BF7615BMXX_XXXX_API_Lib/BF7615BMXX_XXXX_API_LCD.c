#include ".\BF7615BMXX_XXXX_Library\Config.h"
	
#if (LCD_EN == 1)
		#pragma message "编译,LCD功能"
		uchar code Lcd_ser_num1[10]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};//0~9
		
		uchar code Lcd_dp1 = 	0x80;
		uchar code Lcd_dp2 = 	0x80;
		uchar code Lcd_dp3 = 	0x80;
		uchar code Lcd_dp4 = 	0x80;
		uchar code Lcd_dp5 = 	0x01;
		uchar code Lcd_dp6 = 	0x02;
	//-----------------------------------------------------------------//
	//函数名称： void LCD_Data(uchar com,ulong seg)
	//函数功能： LCD数据显示函数
	//输入参数： uchar com：0~7,COM口；ulong seg：SEG数据,对应的位为1选中对应SEG
	//输出参数： 无
	//返 回 值： 无
	//-----------------------------------------------------------------//

	void LCD_Data(uchar com,ulong seg)
	{
			uchar i = 0,j = 0;
			for(j = 0; j < 8; j++)
			{
				if(j == com)
				{
					for (i = 0; i < 28; i++)
					{
						if(i < 8)
						{
							XBYTE[0x1000+i] &= ~(0x01<<com);
							if(((seg)&((0x01)<<i)))
							{
								XBYTE[0x1000+i] |= (0x01<<com);
							}
						}
						else if(i < 16)
						{
							XBYTE[0x1000+i] &= ~(0x01<<com);
							if(((seg>>8)&((0x01)<<(i-8))))
							{
								XBYTE[0x1000+i] |= (0x01<<com);
							}
						}
						else if(i < 24)
						{
							XBYTE[0x1000+i] &= ~(0x01<<com);
							if(((seg>>16)&((0x01)<<(i-16))))
							{
								XBYTE[0x1000+i] |= (0x01<<com);
							}
						}
						else if(i < 28)
						{
							XBYTE[0x1000+i] &= ~(0x01<<com);
							if(((seg>>24)&((0x01)<<(i-24))))
							{
								XBYTE[0x1000+i] |= (0x01<<com);
							}
						}
					}							
				}
			}
	}

	//-----------------------------------------------------------------//
	//函数名称： void LCD_Init(void)  
	//函数功能： LCD初始化
	//输入参数： 无
	//输出参数： 无
	//返 回 值： 无
	//-----------------------------------------------------------------//
	void LCD_Init(void) 
	{ 
			uchar i = 0,j = 0;
			EA = 0;//关总中断；
			LCD_IP_SET;//设置LCD中断优级为高，根据实际应运设置优先级
			LCD_INT_FLAG_CLR;//清除LCD中断标志
			LED_LCD_FUN_SET(1);//1为LED_LCD功能开，0为LED_LCD功能关
			LCD_FUN_SET(0);//1为LED功能，0为LCD功能
			LCD_CLK_SET(0);//0为内部RC32K,1为外部晶振32768Hz，2内部RC1MHz
			LCD_RES_SET(0);//0为LCD偏置电阻225K，1为LCD偏置电阻900K
			LCD_COM_WIDTH_SET(32);//当LCD_CLK_SET(2)时，配置有效，LCD时钟为1M，单COM扫描时间设置(SCAN_WIDTH+1)*64,0.064ms~4.096ms
			LCD_CHARGE_SET(0);//充电时间控制：0为1/8 COM周期，1为1/16 COM周期，2为1/32 COM周期，3为1/64 COM周期
			LCD_MODE_SET(1);//驱动模式控制：0为传统电阻模式(225K/900K)，1为传统电阻模式(60K)，2为1/32 COM周期，3为快速充电模式(自动在60K/225K/900K之间切换)
			LCD_CONSTRAT_EN_SET(1);//对比度使能：0为关闭对比控制，1为打开对比控制
			LCD_CONSTRAT_SET(9);//对比度电压选择：(0~15)--(0.531V~1.00V)
			LCD_SEG_SEL_SET(0x00FFFFFF);
			LCD_DUTY_SET(1);//占空比配置：
			
			//0:1/4占空比,1/3 偏置(COM0~COM3)--4*16,SEG0~SEG7,SEG16~SEG23
			//1:1/8占空比,1/4 偏置(COM0~COM7)--8*16,SEG0~SEG7,SEG16~SEG23
			//2:1/4占空比,1/3 偏置(COM0~COM3)--4*20,SEG0~SEG7,SEG16~SEG23,COM4~COM7共享为SEG24~SEG27
			//3:1/5占空比,1/3 偏置(COM0~COM4)--5*19,SEG0~SEG7,SEG16~SEG23,COM5~COM7共享为SEG25~SEG27
			//4:1/6占空比,1/3 偏置(COM0~COM5)--6*18,SEG0~SEG7,SEG16~SEG23,COM6~COM7共享为SEG26~SEG27
			//5:1/6占空比,1/4 偏置(COM0~COM5)--4*18,SEG0~SEG7,SEG16~SEG23，COM6-7 共享为 SEG26-SEG27
			//6/other:1/4占空比,1/3 偏置(COM0~COM3)--4*16,SEG0~SEG7,SEG16~SEG23
			

			LCD_Data(0,0xFFFFFFFF);//0x00000000
			LCD_Data(1,0xFFFFFFFF);
			LCD_Data(2,0xFFFFFFFF);
			LCD_Data(3,0xFFFFFFFF);
			LCD_Data(4,0x00FFFFFF);
			LCD_Data(5,0x00FFFFFF);
			LCD_Data(6,0x00FFFFFF);
			LCD_Data(7,0x00FFFFFF);

			LCD_IE_SET;//开LCD中断使能
			EA = 1;//开总中断
			LCD_START_SET(1);//LCD扫描开始停止控制，0为停止扫描，1为开始扫描
	}
	
	//-----------------------------------------------------------------//
	//函数名称： void LCD_ISR() interrupt 13 
	//函数功能： LCD中断服务函数
	//输入参数： 无
	//输出参数： 无
	//返 回 值： 无
	//-----------------------------------------------------------------//
	void LCD_ISR() interrupt 13
	{
		static uchar xdata addr_bak = 0;
		PUSH_REG_ADDR_SFR();
		LCD_INT_FLAG_CLR;	  // 清除LCD中断标志位
		LCD_START_SET(1);	 //LCD扫描开始停止控制，0为停止扫描，1为开始扫描
		POP_REG_ADDR_SFR();
	}	

#endif