#include ".\BF7615BMXX_XXXX_Library\Config.h"

//-----------------------------------------------------------------//
//函数名称： void ExtInt0_Init(uchar TriggerMode,uchar int0_sel)
//函数功能： 外部中断0初始化
//输入参数：
//外部中断0触发方式选择，uchar TriggerMode
//			 TriggerMode = 0，触发方式为双边沿触发
//			 TriggerMode = 1，触发方式为下降沿触发
//			 TriggerMode = 2，触发方式为上降沿触发
//			 uchar int0_sel,	对应的位为1选择为INT功能，为0选择为IO口功能
//输出参数： 无
//返 回 值： 无
//-----------------------------------------------------------------// 
#if ExtInt0_EN
#pragma message "编译，void ExtInt0_Init(uchar TriggerMode,uchar int0_sel)函数"
void ExtInt0_Init(uchar TriggerMode,uint int0_sel)
{
	EA = 0;//关总中断；
	INT0_IP_SET;//设置IN0中断优级为高	，根据实际应运设置优先级
	INT0_INT_FLAG_CLR;//清除INT0中断标志
	EXINT_STAT = 0;//清除INT0_0x中断标志
	
	REG_ADDR = 0x35;
	REG_DATA |= int0_sel;//对应位为0选择为IO口功能，1选择为INT中断功能
	TRISH |= (uchar)int0_sel;//设置为输入
	DATAH |= (uchar)int0_sel;//数据设置为高
	INT0_POLO_SET(TriggerMode);//0为双沿触发；1为下降沿触发；2为上升沿触发；
	
	REG_ADDR = 0x34;
	REG_DATA |= (int0_sel>>8)&0x01;//对应位为0选择为IO口功能，1选择为INT中断功能
	TRISB |= ((int0_sel >> 8)&0x01);//设置为输入
	DATAB |= ((int0_sel >> 8)&0x01);//数据设置为高
	
	INT0_08_INT_FLAG_CLR;//清除INT0_08中断标志
	INT0_08_POLO_SET(TriggerMode);//0为双沿触发；1为下降沿触发；2为上升沿触发；
	
	REG_ADDR = 0x00;
	INT0_IE_SET;//使能外部INT0中断 
	EA = 1;//开总中断	
}
//-----------------------------------------------------------------//
//函数名称： void Ext0_ISR() interrupt 0
//函数功能： 外部中断0中断子函数
//输入参数： 无
//输出参数： 无
//返 回 值： 无
//-----------------------------------------------------------------// 
void Ext0_ISR() interrupt 0 
{
	static uchar xdata addr_bak = 0;
	PUSH_REG_ADDR_SFR();
	INT0_INT_FLAG_CLR;//清除INT0中断标志
	
	if(GET_INT0_FLAG(0))
	{
		INT0_00_INT_FLAG_CLR;//清除INT0_00中断标志
	}
	
	/*********INT0_0x**********/
	if(GET_INT0_FLAG(1))
	{
		INT0_01_INT_FLAG_CLR;
	}

	if(GET_INT0_FLAG(2))
	{
				
		INT0_02_INT_FLAG_CLR;
		
	}
	if(GET_INT0_FLAG(3))
	{
		INT0_03_INT_FLAG_CLR;
		
	}
	if(GET_INT0_FLAG(4))
	{
		INT0_04_INT_FLAG_CLR;
		
	}
	if(GET_INT0_FLAG(5))
	{
		INT0_05_INT_FLAG_CLR;
			
	}
	if(GET_INT0_FLAG(6))
	{
		INT0_06_INT_FLAG_CLR;
		
	}
	if(GET_INT0_FLAG(7))
	{
		INT0_07_INT_FLAG_CLR;
		
	}
	
	
	if(GET_INT0_08_FLAG())
	{
		INT0_08_INT_FLAG_CLR;//清除INT0_08中断标志
		
	}			
	POP_REG_ADDR_SFR();
	/*********INT0_0x**********/

} 
#endif

//-----------------------------------------------------------------//
//函数名称： void ExtInt1_Init(uchar TriggerMode)
//函数功能： 外部中断1初始化
//输入参数： 
//外部中断1触发方式选择，uchar TriggerMode
//			 TriggerMode = 0，触发方式为双边沿触发
//			 TriggerMode = 1，触发方式为下降沿触发
//			 TriggerMode = 2，触发方式为上降沿触发

//输出参数： 无
//返 回 值： 无
//-----------------------------------------------------------------// 
#if ExtInt1_EN
#pragma message "编译，void ExtInt1_Init(uchar TriggerMode)函数"
void ExtInt1_Init(uchar TriggerMode)
{
	EA = 0;//关总中断；
	INT1_IP_SET;//设置IN1中断优级为高	，根据实际应运设置优先级
	INT1_INT_FLAG_CLR;//清除INT1中断标志
	INT1_FUN_SET(1);//0选择为IO口功能，1选择为INT中断功能
	INT1_POLO_SET(TriggerMode);//0为双沿触发；1为下降沿触发；2为上升沿触发；
	REG_ADDR = 0x00;
	INT1_IE_SET;//使能外部INT1中断 
	EA = 1;//开总中断		
}
//-----------------------------------------------------------------//
//函数名称： void Ext1_ISR() interrupt 2
//函数功能： 外部中断1中断子函数
//输入参数： 无
//输出参数： 无
//返 回 值： 无
//-----------------------------------------------------------------// 
void Ext1_ISR() interrupt 2 
{
	static uchar xdata addr_bak = 0;
	PUSH_REG_ADDR_SFR();
	INT1_INT_FLAG_CLR;//清除INT1中断标志
	POP_REG_ADDR_SFR();
}
#endif


//-----------------------------------------------------------------//
//函数名称： void ExtInt2_Init(uchar TriggerMode)
//函数功能： 外部中断2初始化
//输入参数： 
//外部中断1触发方式选择，uchar TriggerMode
//			 TriggerMode = 0，触发方式为下降沿触发
//			 TriggerMode = 1，触发方式为上升沿触发
//			 TriggerMode = 2，触发方式为双边沿触发
//输出参数： 无
//返 回 值： 无
//-----------------------------------------------------------------// 
#if ExtInt2_EN
#pragma message "编译，void ExtInt2_Init(uchar TriggerMode)函数"
void ExtInt2_Init(uchar TriggerMode)
{
	EA = 0;//关总中断；
	INT2_IP_SET;//设置IN1中断优级为高	，根据实际应运设置优先级
	INT2_INT_FLAG_CLR;//清除INT1中断标志
	INT2_FUN_SET(1);//0选择为IO口功能，1选择为INT中断功能 

	INT2_POLO_SET(TriggerMode);//0为双沿触发；1为下降沿触发；2为上升沿触发；
	INT2_IE_SET;//使能外部INT1中断 
	EA = 1;//开总中断			
}
//-----------------------------------------------------------------//
//函数名称： void Ext2_ISR() interrupt 9
//函数功能： 外部中断2中断子函数
//输入参数： 无
//输出参数： 无
//返 回 值： 无
//-----------------------------------------------------------------// 
void Ext2_ISR() interrupt 9 
{
	static uchar xdata addr_bak = 0;
	PUSH_REG_ADDR_SFR();
	INT2_INT_FLAG_CLR;//清除INT2中断标志
	POP_REG_ADDR_SFR();	
}
#endif

//-----------------------------------------------------------------//
//函数名称： void ExtInt3_Init(uchar TriggerMode)
//函数功能： 外部中断3初始化
//输入参数： 
//外部中断1触发方式选择，uchar TriggerMode
//			 TriggerMode = 0，触发方式为下降沿触发
//			 TriggerMode = 1，触发方式为上升沿触发
//			 TriggerMode = 2，触发方式为双边沿触发
//输出参数： 无
//返 回 值： 无
//-----------------------------------------------------------------// 
#if ExtInt3_EN
#pragma message "编译，void ExtInt3_Init(uchar TriggerMode)函数"
void ExtInt3_Init(uchar TriggerMode)
{
	EA = 0;//关总中断；
	INT3_IP_SET;//设置IN1中断优级为高	，根据实际应运设置优先级
	INT3_INT_FLAG_CLR;//清除INT1中断标志
	INT3_FUN_SET(1);//0选择为IO口功能，1选择为INT中断功能 
	INT3_POLO_SET(TriggerMode);//0为双沿触发；1为下降沿触发；2为上升沿触发；
	INT3_IE_SET;//使能外部INT1中断 
	EA = 1;//开总中断			
}
//-----------------------------------------------------------------//
//函数名称： void Ext3_ISR() interrupt 21
//函数功能： 外部中断3中断子函数
//输入参数： 无
//输出参数： 无
//返 回 值： 无
//-----------------------------------------------------------------// 
void Ext3_ISR() interrupt 21 
{
	static uchar xdata addr_bak = 0;
	PUSH_REG_ADDR_SFR();
	INT3_INT_FLAG_CLR;//清除INT2中断标志	
	POP_REG_ADDR_SFR();
}
#endif

//-----------------------------------------------------------------//
//函数名称： void ExtInt4_Init(uchar TriggerMode,ulong int4_sel)
//函数功能： 外部中断4初始化
//输入参数： 
//外部中断1触发方式选择，uchar TriggerMode
//			 TriggerMode = 0，触发方式为下降沿触发
//			 TriggerMode = 1，触发方式为上升沿触发
//			 ulong int4_sel:对应的位为1时，选择为INT功能，为0时为IO口功能
//输出参数： 无
//返 回 值： 无
//-----------------------------------------------------------------// 
#if ExtInt4_EN
#pragma message "编译，void ExtInt4_Init(uchar TriggerMode,ulong int4_sel)函数"
void ExtInt4_Init(uchar TriggerMode,ulong int4_sel)
{
	EA = 0;//关总中断；
	INT4_IP_SET;//设置IN4中断优级为高	，根据实际应运设置优先级
	INT4_INT_FLAG_CLR;//清除INT4中断标志
	
	REG_ADDR = 0x36;
	REG_DATA = (uchar)int4_sel;//PE4,对应位为0选择为IO口功能，1选择为INT中断功能


	REG_ADDR = 0x37;
	REG_DATA = (uchar)(int4_sel>>8);//PE5~PE7,PF4,对应位为0选择为IO口功能，1选择为INT中断功能
		
	REG_ADDR = 0x38;
	REG_DATA = (uchar)(int4_sel>>16);//PF5~PF7,PG0~PG3,对应位为0选择为IO口功能，1选择为INT中断功能
	
	TRISE |= (0xF0 & ((uchar)(int4_sel >> 3)));//设置为输入
	DATAE |= (0xF0 & ((uchar)(int4_sel >> 3)));//数据设置为高
	
	TRISF |= (0xF0 & ((uchar)(int4_sel >> 11)));//设置为输入
	DATAF |= (0xF0 & ((uchar)(int4_sel >> 11)));//数据设置为高
	
	TRISG |= (0x0F & ((uchar)(int4_sel >> 19)));//设置为输入
	DATAG |= (0x0F & ((uchar)(int4_sel >> 19)));//数据设置为高
	
	INT4_POLO_SET(TriggerMode);//1为上升触发；0为下降沿触发；

	INT4_IE_SET;//使能外部INT1中断 
	EA = 1;//开总中断			
}
//-----------------------------------------------------------------//
//函数名称： void Ext4_ISR() interrupt 22
//函数功能： 外部中断4中断子函数,通过获取对应IO口DATAX数据来判断INT4XX的中断引脚来源
//输入参数： 无
//输出参数： 无
//返 回 值： 无
//-----------------------------------------------------------------// 
void Ext4_ISR() interrupt 22 
{
	static uchar xdata addr_bak = 0;
	PUSH_REG_ADDR_SFR();
	INT4_INT_FLAG_CLR;//清除INT4中断标志
	if((DATAE&0x40) == 0x00)//PE6下降沿
	{

	}				
	else//PE6上升沿
	{
		
	}
	
	if((DATAE&0x80)  == 0x00)//PE7下降沿
	{

	}				
	else//PE7上升沿
	{

	}
	
	if((DATAF&0x10)  == 0x00)//PF4下降沿
	{
	
	}				
	else//PF4上升沿
	{

	}
	if((DATAF&0x20)  == 0x00)//PF5下降沿
	{
		
	}				
	else//PF5上升沿
	{

	}
	if((DATAF&0x40)  == 0x00)//PF6下降沿
	{
		
	}				
	else//PF6上升沿
	{

	}
	if((DATAF&0x80)  == 0x00)//PF7下降沿
	{
		
	}				
	else//PF7上升沿
	{
			
	}
	POP_REG_ADDR_SFR();
}
#endif
