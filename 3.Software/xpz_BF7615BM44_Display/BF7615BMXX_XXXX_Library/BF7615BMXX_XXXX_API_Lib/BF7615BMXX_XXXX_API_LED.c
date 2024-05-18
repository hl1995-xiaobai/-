#include ".\BF7615BMXX_XXXX_Library\Config.h"

#if(LED_SWITCH_EN == 1)
	#pragma message "编译,LED功能"
	#if (LED_SER_ARR_EN == 1)
	#pragma message "编译,LED 串行点阵功能"
	uchar code Led_ser_num[16]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F,0x77,0x7C,0x39,0x5E,0x79,0x71};//0~9,A,b,c,d,E,F
	uchar code Led_dp1 = 	0x80;
	uchar code Led_dp2 = 	0x80;
	uchar code Led_dp3 = 	0x80;
	uchar code Led_dp4 = 	0x80;
	uchar code Led_dp5 = 	0x01;
	uchar code Led_dp6 = 	0x02;
	
	ulong xdata LED_H_Tem = 0;
	ulong xdata LED_L_Tem = 0;
	
	ulong xdata LED_Light_H_Tem = 0x00FFFFFF;
	ulong xdata LED_Light_L_Tem = 0xFFFFFFFF;
	

	
	#endif
	#if (LED_SER_ARR_EN == 0)
			#pragma message "编译,LED行列矩阵功能"
			uchar code Led_arr_num1[10] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};//0~9
	#endif
#endif


#if (LED_SWITCH_EN == 1)

//-----------------------------------------------------------------//
//函数名称： void LED_ARR_Data(uchar com,uchar seg)
//函数功能： LED行列矩阵数据显示函数
//输入参数： uchar com：0~7,COM口；uchar seg：SEG数据
//输出参数： 无
//返 回 值： 无
//-----------------------------------------------------------------//
#if (LED_SER_ARR_EN == 0)
void LED_ARR_Data(uchar com,uchar seg)
{
		XBYTE[0x1000+com] = seg;

}

//-----------------------------------------------------------------//
//函数名称： void LED_ARR_Init(void)
//函数功能： LED行列矩阵驱动初始化
//输入参数： 无
//输出参数： 无
//返 回 值： 无
//-----------------------------------------------------------------//

void LED_ARR_Init(void)
{
	EA = 0;//关总中断；
	LED_IP_SET; 		 //设置LED中断优先级为高，根据实际应运设置优先级
	LED_INT_FLAG_CLR;	  // 清除LED中断标志位
	LED_LCD_FUN_SET(1);//1为LED_LCD功能开，0为LED_LCD功能关
	LED_ARR_FUN_SET(1);//1为LED功能，0为LCD功能
	LED_ARR_COM_SET(0);//COM大电流选择，0为不开启，1为开启(开启后LED/LCD硬件扫描时序无效)
	LED_ARR_SEG_SET(0xFF);//LED行列矩阵SEG口选择,对应的位为1选择为SEG口功能
	LED_ARR_CON_EN(0x0F);//LED行列矩阵COM口选择,对应的位为1选择为COM口功能
	LED_ARR_MODE_SET(0);//1为串行点阵模式，0为行列矩阵模式；
	LED_ARR_SCAN_SET(LED_MODE);//LED行列矩阵扫描模式选择，0为中断模式，1为循环模式
	LED_ARR_COM_TIME(5);//单个COM导通时间1配置，(x+1)*16us
	LED_ARR_DUTY_SET(4);//LED行列矩阵COM通道占空比选择(0~7) (x+1)/8
	
	
	LED_ARR_Data(4,Led_arr_num1[8]);
	LED_ARR_Data(5,Led_arr_num1[8]);
	LED_ARR_Data(6,Led_arr_num1[8]);
	LED_ARR_Data(7,Led_arr_num1[8]);

	#if (LED_MODE == 0)
		#pragma message "编译,LED中断模式"
		LED_IE_SET;			  //开LED中断使
	#else
		#pragma message "编译,LED循环模式"
		LED_IE_CLR;			  //关LED中断使
	#endif

	LED_ARR_START_SET(1);//LED扫描开始停止控制，0为停止扫描，1为开始扫描

	EA = 1;//开总中断
	
	
}
#endif

#if LED_SER_ARR_EN


/****************************************************************/
//函数名：void LED_SER_Dis_Num(uchar num,uchar dis_data)
//功  能：LED显示函数
//参  数：uchar num:数码管位，uchar dis_data数据
//返回值：无
/****************************************************************/

void LED_SER_Dis_Num(uchar num,uchar dis_data)
{
		if(num == 1)
		{

			
			LED_L_Tem &= ~0x01010101;
			LED_H_Tem &= ~0x00000303;
			LED_L_Tem |= (((ulong)dis_data)<<0) & (0x00000001);//A1
			LED_L_Tem |= (((ulong)dis_data)<<7) & (0x00000100);//B1
			LED_L_Tem |= (((ulong)dis_data)<<14)& (0x00010000);//C1
			LED_L_Tem |= (((ulong)dis_data)<<21)& (0x01000000);//D1
			LED_H_Tem |= (((ulong)dis_data)>>4) & (0x00000001);//E1
			LED_H_Tem |= (((ulong)dis_data)<<3) & (0x00000100);//F1
			LED_H_Tem |= (((ulong)dis_data)<<3) & (0x00000200);//G1
			LED_H_Tem |= (((ulong)dis_data)>>6) & (0x00000002);//H1
			
		}
		if(num == 2)
		{

			LED_L_Tem &= ~0x06060200;
			LED_H_Tem &= ~0x00000C04;
			
			LED_L_Tem |= (((ulong)dis_data)<<25) & (0x02000000);//A2
			LED_L_Tem |= (((ulong)dis_data)<<16) & (0x00020000);//B2
			LED_L_Tem |= (((ulong)dis_data)<<7)  & (0x00000200);//C2
			LED_L_Tem |= (((ulong)dis_data)<<15) & (0x00040000);//D2
			LED_L_Tem |= (((ulong)dis_data)<<22) & (0x04000000);//E2
			LED_H_Tem |= (((ulong)dis_data)>>3)  & (0x00000004);//F2
			LED_H_Tem |= (((ulong)dis_data)<<4)  & (0x00000400);//G2
			LED_H_Tem |= (((ulong)dis_data)<<4)  & (0x00000800);//H2
		}
		if(num == 3)
		{

		
			LED_L_Tem &= ~0x48000000;
			LED_H_Tem &= ~0x00007058;
			

			LED_H_Tem |= (((ulong)dis_data)<<3)  & (0x00000008);//A3
			LED_L_Tem |= (((ulong)dis_data)<<26) & (0x08000000);//B3
			LED_H_Tem |= (((ulong)dis_data)<<2) & (0x00000010);//C3
			LED_H_Tem |= (((ulong)dis_data)<<9) & (0x00001000);//D3
			LED_H_Tem |= (((ulong)dis_data)<<9)  & (0x00002000);//E3
			LED_H_Tem |= (((ulong)dis_data)<<9)  & (0x00004000);//F3
			LED_H_Tem |= (((ulong)dis_data)<<0)  & (0x00000040);//G3
			LED_L_Tem |= (((ulong)dis_data)<<23)  & (0x40000000);//H3

		}
		if(num == 4)
		{
			
			LED_L_Tem &= ~0x20606060;
			LED_H_Tem &= ~0x00000020;

			LED_L_Tem |= (((ulong)dis_data)<<22) & (0x00400000);//A4
			LED_L_Tem |= (((ulong)dis_data)<<13) & (0x00004000);//B4
			LED_L_Tem |= (((ulong)dis_data)<<4)  & (0x00000040);//C4
			LED_H_Tem |= (((ulong)dis_data)<<2)  & (0x00000020);//D4
			LED_L_Tem |= (((ulong)dis_data)<<25) & (0x20000000);//E4
			LED_L_Tem |= (((ulong)dis_data)<<16) & (0x00200000);//F4
			LED_L_Tem |= (((ulong)dis_data)<<7)  & (0x00002000);//G4
			LED_L_Tem |= (((ulong)dis_data)>>2)  & (0x00000020);//H4
			
		}
		if(num == 5)
		{
			LED_L_Tem &= ~0x10100000;
			
			LED_L_Tem |= (((ulong)dis_data)<<28) & (0x10000000);//H5
			LED_L_Tem |= (((ulong)dis_data)<<20) & (0x00100000);//H6
			
		}
}

//-----------------------------------------------------------------//
//函数名称： void LED_SER_Data(ulong led_data_h,ulong led_data_l,ulong led_width_h,ulong led_width_l)
//函数功能： LED串行点阵数据显示函数
//输入参数： ulong led_data_h,LED高24位数据，ulong led_data_l,LED低32位数据,
//输出参数： 无
//返 回 值： 无
//-----------------------------------------------------------------//
void LED_SER_Data(ulong led_data_h,ulong led_data_l)
{

	XBYTE[0x1000] = (uchar)(led_data_l>>0);
	XBYTE[0x1001] = (uchar)(led_data_l>>8);
	XBYTE[0x1002]	= (uchar)(led_data_l>>16);
	XBYTE[0x1003] = (uchar)(led_data_l>>24);
	XBYTE[0x1004] = (uchar)(led_data_h>>0);
	XBYTE[0x1005] = (uchar)(led_data_h>>8);
	XBYTE[0x1006] = (uchar)(led_data_h>>16);
	
}

//-----------------------------------------------------------------//
//函数名称： void LED_SER_Light_Set(ulong led_width_h,ulong led_width_l)
//函数功能： LED串行点阵LED导通时间选择
//输入参数： ulong led_width_h,ulong led_width_l:LED导通时间选择,0为导通时间1，1为导通时间2
//输出参数： 无
//返 回 值： 无
//-----------------------------------------------------------------//
void LED_SER_Light_Set(ulong led_width_h,ulong led_width_l)
{

	XBYTE[0x1007] = (uchar)(led_width_l>>0);
	XBYTE[0x1008] = (uchar)(led_width_l>>8);
	XBYTE[0x1009] = (uchar)(led_width_l>>16);
	XBYTE[0x100A] = (uchar)(led_width_l>>24);
	XBYTE[0x100B] = (uchar)(led_width_h>>0);
	XBYTE[0x100C] = (uchar)(led_width_h>>8);
	XBYTE[0x100D] = (uchar)(led_width_h>>16);

	LED_START_SET(1);
	
}

//-----------------------------------------------------------------//
//函数名称： void LED_SER_Light_Set_Int(ulong led_width_h,ulong led_width_l)
//函数功能： LED串行点阵LED导通时间选择
//输入参数： ulong led_width_h,ulong led_width_l:LED导通时间选择,0为导通时间1，1为导通时间2
//输出参数： 无
//返 回 值： 无
//-----------------------------------------------------------------//
#if (LED_MODE == 0)
void LED_SER_Light_Set_Int(ulong led_width_h,ulong led_width_l)
{

	XBYTE[0x1007] = (uchar)(led_width_l>>0);
	XBYTE[0x1008] = (uchar)(led_width_l>>8);
	XBYTE[0x1009] = (uchar)(led_width_l>>16);
	XBYTE[0x100A] = (uchar)(led_width_l>>24);
	XBYTE[0x100B] = (uchar)(led_width_h>>0);
	XBYTE[0x100C] = (uchar)(led_width_h>>8);
	XBYTE[0x100D] = (uchar)(led_width_h>>16);
	
}
#endif

//-----------------------------------------------------------------//
//函数名称： void LED_SER_Init(void)
//函数功能： LED串行点阵驱动初始化
//输入参数： 无
//输出参数： 无
//返 回 值： 无
//-----------------------------------------------------------------//
//-------------------------------------------------------------------------------------------------------
//|    名称		   		|			    公式													|		     说明 				|
//-------------------------------------------------------------------------------------------------------
//|  T_LED(ms)			|    T_LED(ms) 	= TX_LED(ms)<=17ms		|		LED总亮灯时间			|
//|	导通时间1<导通时间2, TX_LED(ms) = T_LED2(ms)					
//|	导通时间1>导通时间2, TX_LED(ms) = T_LED1(ms)					
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//|  X*Y			    	|	  0-4*5，1-5*6，2-6*7，3-7*8,					|		矩阵行*矩阵列			|
//-------------------------------------------------------------------------------------------------------

void LED_SER_Init(void)
{
	EA = 0;//关总中断；
	LED_IP_SET; 		 //设置LED中断优先级为高，根据实际应运设置优先级
	LED_INT_FLAG_CLR;	// 清除LED中断标志位
	LED_LCD_FUN_SET(1);//1为LED_LCD功能开，0为LED_LCD功能关
	LED_SER_FUN_SET(1);//1为LED功能，0为LCD功能
	LED_SER_COM_SET(0);//COM大电流选择，0为不开启，1为开启(开启后LED/LCD硬件扫描时序无效)
	LED_SER_MODE_SET(1);//1为串行点阵模式，0为行列矩阵模式；
	LED_SER_MATRIX_SET(3);//LED串行点阵矩阵选择(X*Y) 0-4*5，1-5*6，2-6*7，3-7*8,4-4*5(以PB3为起始端口)
	LED_SER_CURRENT_SET(7);//LED驱动能力配置(0~15)，参照规格书表格(0-3.7mA),(9-43.7mA),(15-68.7mA)@LED压降2.5V
	LED_SER_LED1_WIDTH_SET(0);//单个灯导通时间1配置，(x+1)*16us
	LED_SER_LED2_WIDTH_SET(5);//单个灯导通时间2配置，(x+1)*16us
	LED_SER_SCAN_SET(LED_MODE);//LED扫描模式选择，0为中断模式，1为循环模式 
	

	LED_SER_Dis_Num(1,Led_ser_num[8]);
	LED_SER_Dis_Num(2,Led_ser_num[8]);
	LED_SER_Dis_Num(3,Led_ser_num[8]);	
	LED_SER_Dis_Num(4,Led_ser_num[8]);
	
	
	LED_SER_Data(LED_H_Tem,LED_L_Tem);////输入参数： ulong led_data_h,LED高24位数据，ulong led_data_l,LED低32位数据,根据应用进行显示数据初始化，电路上无连接LED对应点设置为0；
	LED_SER_Light_Set(0x00FFFFFF,0xFFFFFFFF);//输入参数： ulong led_width_h,ulong led_width_l:LED导通时间选择,0为导通时间1，1为导通时间2
	#if (LED_MODE == 0)
		LED_IE_SET;			  //开LED中断使
	#else
		LED_IE_CLR;			  //关LED中断使
	#endif
	LED_START_SET(1);//LED扫描开始停止控制，0为停止扫描，1为开始扫描

	EA = 1;//开总中断
	
	
}
#endif


//-----------------------------------------------------------------//
//函数名称： void LED_ISR() interrupt 13 
//函数功能： LED中断服务函数
//输入参数： 无
//输出参数： 无
//返 回 值： 无
//-----------------------------------------------------------------//
#if (LED_MODE == 0)
void LED_ISR() interrupt 13
{
	static uchar xdata addr_bak = 0;
	PUSH_REG_ADDR_SFR();
	LED_INT_FLAG_CLR;	  // 清除LED中断标志位
	#if (LED_SER_ARR_EN == 1)
		LED_SER_Light_Set_Int(LED_Light_H_Tem,LED_Light_L_Tem);
	#endif
	LED_START_SET(1);	 //LED扫描开始停止控制，0为停止扫描，1为开始扫描
	POP_REG_ADDR_SFR();
}
#endif

#endif
