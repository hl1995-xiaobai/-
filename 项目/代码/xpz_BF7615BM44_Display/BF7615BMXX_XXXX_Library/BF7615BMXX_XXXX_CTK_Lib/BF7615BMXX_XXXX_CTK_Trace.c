#include ".\BF7615BMXX_XXXX_Library\Config.h"

#if (TRACEMODE == TRUE)
void TraceMode_Master_Read_Data(unsigned int xdata *p_rawData,unsigned int xdata *p_baseline,unsigned long  t_keysFlagSN,unsigned long  t_keysFlagSN_H);   
unsigned char xdata ReadCnt = 0;
unsigned char xdata ReceData = 0;
unsigned char xdata DataNum = 0;
bit OddCheck = 0,NeedCheckOdd = 0;
unsigned int xdata raw = 0;
unsigned int xdata bas = 0;

#if (TRACEMODE==1)
	#pragma message "编译,TRACEMODE功能"
	unsigned long xdata keys_flag_l_Tracemode = 0;	
	unsigned long xdata keys_flag_h_Tracemode = 0;	
	//-----------------------------------------------------------------//
	//函数名称： void Trace_Mode_IIC_ISR_PA() interrupt 10 
	//函数功能： PA口IIC中断子函数
	//输入参数： 无
	//输出参数： 无
	//返 回 值： 无
	//-----------------------------------------------------------------//

	void Trace_Mode_IIC_ISR_PA() interrupt 10
	{
			uchar tmp;
			static uchar xdata addr_bak = 0;
			PUSH_REG_ADDR_SFR();
			EA = 0;
			IRCON1 &= ~0x08;
			if ((IICSTAT & 0x02))//写冲突标志位
			{ 
					IICSTAT &= ~0x02;
			}
			if ((IICSTAT & 0x01))//读冲突标志位  
			{
					
					IICSTAT &= ~0x01;
					tmp = IICBUF;
			}
			if ((IICSTAT & 0x10) == 0)//是地址
			{	 
			
					if((IICSTAT & 0x20))//主机读 
					{
							
							ReadCnt = 0;
							OddCheck = 0;
							DataNum = 0;
							
							TraceMode_Master_Read_Data(&raw_data[0],&base_line[0],keys_flag_l_Tracemode,keys_flag_h_Tracemode);

							IICCON |= 0x04; 
					}
					else //主机写
					{
							tmp = IICBUF;
					}   
				}
				else 
				{
					if ((IICSTAT & 0x20))//主机读 
					{
							       
							TraceMode_Master_Read_Data(&raw_data[0],&base_line[0],keys_flag_l_Tracemode,keys_flag_h_Tracemode);
							IICCON |= 0x04;	  
					}
					else//主机写  
					{   
				
						if ((IICSTAT & 0x08)) 
						{ 
							TraceMode_Master_Write_Data();
						}
					}
					
			}
			IICCON |= 0x04;
			POP_REG_ADDR_SFR();
			EA = 1;
	}

	#endif

//-----------------------------------------------------------------//
//函数名称： void BF7615BMXX_XXXX_Trace_Mode_Init(unsigned char IICSlaveAddr,unsigned char iic_port)
//函数功能： BF7615BMXX_XXXX_Trace_Mode_Init初始化
//输入参数： unsigned char IICSlaveAddr:IIC从机地址;,unsigned char iic_port://IIC功能映射选择0-为选择PC4/5为串口，1选择PE4/5为串口
//输出参数： 无
//返 回 值： 无
//-----------------------------------------------------------------//

void BF7615BMXX_XXXX_Trace_Mode_Init(unsigned char IICSlaveAddr,unsigned char iic_port)
{
	
		EA = 0;		//关总中断
		IPL1 |= 0x08;			//设置IIC中断优先级
		IRCON1 &= ~0x08;	// 清除IIC中断标志位
	
		REG_ADDR = 0x50;REG_DATA = 0x03;//bit1:IIC模拟滤波选择：1为选择模拟滤波，0为不选择模拟滤波;bit0:IIC模拟滤波选择：1为选择数字滤波，0为不选择数字滤波(Sleep模式时，IIC不能唤醒MCU)
	
		if(iic_port == 1)
		{

				REG_ADDR = 0x1B;REG_DATA |= 0x10;//PE4开启上拉
				REG_ADDR = 0x1B;REG_DATA |= 0x20;//PE5开启上拉
				

				TRISE |= 0x10;//PE4设置为输入
				TRISE |= 0x20;//PE5设置为输入
			
				{REG_ADDR = 0x34;REG_DATA &= ~(0x10);REG_DATA |= (0x10&(iic_port<<4));}
		}
		else
		{
	
				REG_ADDR = 0x19;REG_DATA |= 0x10;//PC4开启上拉
				REG_ADDR = 0x19;REG_DATA |= 0x20;//PC5开启上拉
				TRISC |= 0x10;//PC4设置为输入
				TRISC |= 0x20;//PC5设置为输入
			
				{REG_ADDR = 0x34;REG_DATA &= ~(0x10);REG_DATA |= (0x10&(iic_port<<4));}
		}
		IICADD 		= IICSlaveAddr;		//设置IIC从机地址；
		IICSTAT 	= 0x00;						//清除IIC状态寄存器；
		IICCON	  |= 0x01;					//IIC工作使能
		IICCON 		|= (0x02);				//IIC转换速率适应100K
		IICCON 		|= 0x04;					//SLC时钟正常工作
		IICCON 		&= (~0x08);				//不使能写拉低,根据IIC主机读写时序设置
		IICCON 		|= (0x10);				//使能读拉低，根据IIC主机读写时序
		IEN1 			|= 0x08;					//开IIC中断使能
		EA = 1; 										//开总中断			
}
//-----------------------------------------------------------------//
//函数名称： void TraceMode_Master_Read_Data(uint *p_rawData,uint *p_baseline,ulong  t_keysFlagSN,unsigned long  t_keysFlagSN_H)   
//函数功能： 将发送的数据写入IICBUF
//输入参数： 无
//输出参数： 无
//返 回 值： 无
//-----------------------------------------------------------------//
#pragma disable
void TraceMode_Master_Read_Data(unsigned int xdata *p_rawData,unsigned int xdata *p_baseline,unsigned long  t_keysFlagSN,unsigned long  t_keysFlagSN_H)     
{   
	unsigned char data tmp = 0;

	if(ReceData == 0xb2)
	{
		if(ReadCnt == 0)
		{
			tmp = 0xae;
		}
		else if(ReadCnt == 1)
		{
			tmp = CH_MAX;
			
		}			
	}
	else if(ReceData == 0xb3)
	{
		
		if(ReadCnt < 1)			//发送头码0XAE
		{
			tmp = 0xae;	
		
		}
		else if(ReadCnt < ((CH_MAX<<1) + 1))	//发送RAWDATA
		{
			NeedCheckOdd = 1;
			if(ReadCnt % 2)	
			{
				
				raw = *(p_rawData + DataNum);
				
				
				tmp = (raw >> 8);
			}
			else
			{
				tmp = raw;
				DataNum ++;	
			}
		}
		else if(ReadCnt == ((CH_MAX << 1) + 1))  //发送BASELINE[0]高8位
		{
			NeedCheckOdd = 1;
			DataNum = 0;
			
			bas = *(p_baseline + DataNum);
			
			tmp = (bas >> 8);
			
		}
		else if(ReadCnt < ((CH_MAX << 2) + 1))		//发送BASELINE
		{
			
			NeedCheckOdd = 1;
			
			if(ReadCnt % 2)	
			{
				bas = *(p_baseline + DataNum);
				
				tmp = (bas >> 8);
			}
			else
			{
				tmp = bas; 
				DataNum++;	
			}
			
		} 
		else if(ReadCnt == ((CH_MAX << 2) + 1))		//发送奇偶校验位
		{
			tmp = OddCheck;
			
		}
		else if(ReadCnt == ((CH_MAX << 2) + 2))		//发送有效数据长度
		{						
			tmp = (CH_MAX << 2);
		}		
		
		else if(ReadCnt == ((CH_MAX << 2) + 3))		//触摸标志位bit31:17
		{ 						
			tmp = (unsigned char )(t_keysFlagSN >> 24);
		}
		else if(ReadCnt == ((CH_MAX << 2) + 4))		//触摸标志位bit23:16
		{						 
			tmp = (unsigned char )(t_keysFlagSN >> 16);		
		}
		else if(ReadCnt == ((CH_MAX << 2) + 5))		//触摸标志位bit15:8
		{						
			tmp = (unsigned char )(t_keysFlagSN >> 8);
		}					
		else if(ReadCnt == ((CH_MAX << 2) + 6))//触摸标志位bit7:0
		{						
			tmp = (unsigned char )t_keysFlagSN;	
		}
		
		else if(ReadCnt == ((CH_MAX << 2) + 7))		//触摸标志位bit63:56
		{ 						
			tmp = (unsigned char )(t_keysFlagSN_H >> 24);
		}
		else if(ReadCnt == ((CH_MAX << 2) + 8))		//触摸标志位bit55:48
		{						 
			tmp = (unsigned char )(t_keysFlagSN_H >> 16);		
		}
		else if(ReadCnt == ((CH_MAX << 2) + 9))		//触摸标志位bit47:40
		{						
			tmp = (unsigned char )(t_keysFlagSN_H >> 8);
		}					
		else if(ReadCnt == ((CH_MAX << 2) + 10))//触摸标志位bit39:32
		{						
			tmp = (unsigned char )t_keysFlagSN_H;	
		}
	
		else //发送结束码0xff、0xff
		{			
			ReadCnt = 0;
			tmp = 0xFF;	
			
		}
	}
	
	IICBUF = tmp;//将IICBUF = tmp;放在“else if(ReceData == 0xb3)”判断外
	
	if(NeedCheckOdd)		//当前数据是否需要进行奇偶校验
	{
		NeedCheckOdd = 0;
		
		ACC = tmp;
		if((PSW & 0x01))
			OddCheck = !OddCheck;
	}
	ReadCnt++;
	
}

		
//-----------------------------------------------------------------//
//函数名称： void TraceMode_Master_Write_Data(void)  
//函数功能： 从IICBUF读取数据
//输入参数： 无
//输出参数： 无
//返 回 值： 无
//-----------------------------------------------------------------//
#pragma disable
void TraceMode_Master_Write_Data(void) 
{   
	ReceData = IICBUF;
}
#endif