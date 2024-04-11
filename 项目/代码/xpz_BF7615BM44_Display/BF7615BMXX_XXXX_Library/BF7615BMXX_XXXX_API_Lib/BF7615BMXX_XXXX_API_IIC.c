#include ".\BF7615BMXX_XXXX_Library\Config.h"
#if IICS_EN
	uint data  IICS_Soft_Cnt = 0;
	uint xdata SCLEN_SoftCnt = 0; 
#endif

	#if IICS_EN
		#if (TRACEMODE==0)
		#pragma message "编译,IIC从机功能"
		//-----------------------------------------------------------------//
		//函数名称： void IIC_Slave_Init(uchar IICSlaveAddr,uchar iic_port)
		//函数功能： IIC从机初始化
		//输入参数： uchar IICSlaveAddr:IIC从机地址;,uchar iic_port://IIC功能映射选择0-为选择PC4/5为串口，1选择PE4/5为串口
		//输出参数： 无
		//返 回 值： 无
		//-----------------------------------------------------------------//
		void IIC_Slave_Init(uchar IICSlaveAddr,uchar iic_port)
		{
			EA = 0;//关总中断；； 
			IIC_IP_SET; //设置IIC中断优先级为高，根据实际应运设置优先级
			IIC_INT_FLAG_CLR;//清除IIC中断标志位 
			REG_ADDR = 0x50;REG_DATA = 0x02;
			//bit0:IIC模拟滤波选择：1为选择数字滤波，0为不选择数字滤波(Sleep模式时，IIC不能唤醒MCU)
	
			if(iic_port == 1)
			{
//					SET_PE4_PU_ON;//开启上拉
//					SET_PE5_PU_ON;//开启上拉
//				
//				
//					SET_PE4_IO_IN;
//					SET_PE5_IO_IN;
				
						REG_ADDR = 0x1B;REG_DATA |= 0x10;//PE4开启上拉
						REG_ADDR = 0x1B;REG_DATA |= 0x20;//PE5开启上拉
						REG_ADDR = 0x27;REG_DATA &= ~0x01;TRISE |= 0x10;//PE4设置RXD0为输入
						REG_ADDR = 0x27;REG_DATA &= ~0x02;TRISE |= 0x20;//PE5设置TXD0为输入
				
					IIC_PORT_SET(iic_port);
			}
			else
			{
//					SET_PC4_PU_ON;//开启上拉
//					SET_PC5_PU_ON;//开启上拉
//				
//					SET_PC4_IO_IN;
//					SET_PC5_IO_IN;
				
					REG_ADDR = 0x19;REG_DATA |= 0x10;//PC4开启上拉
					REG_ADDR = 0x19;REG_DATA |= 0x20;//PC5开启上拉
					REG_ADDR = 0x26;REG_DATA &= ~0x40;TRISC |= 0x10;//PC4设置RXD0为输入
					REG_ADDR = 0x26;REG_DATA &= ~0x80;TRISC |= 0x20;//PC5设置TXD0为输入
				
					IIC_PORT_SET(iic_port);
			}

			IICADD = IICSlaveAddr;//设置IIC从机地址；
			IICSTAT = 0x00;//清除IIC状态寄存器；
			
			IICCON |= IIC_EN;//IIC工作使能
			IICCON |= (IIC_SR);//IIC转换速率适应100K
			IICCON |= IIC_SCLEN;//SLC时钟正常工作
			IICCON &= (~IIC_W_SCL_EN);//不使能写拉低,根据IIC主机读写时序设置
			IICCON |= (IIC_R_SCL_EN);//使能读拉低，根据IIC主机读写时序设置
			IIC_IE_SET; //开IIC中断使能
			
			EA = 1;//开总中断；
		}
		//-----------------------------------------------------------------//
		//函数名称： void Master_Read_Data()  
		//函数功能： 将发送的数据写入IICBUF
		//输入参数： 无
		//输出参数： 无
		//返 回 值： 无
		//-----------------------------------------------------------------//
		void Master_Read_Data()    
		{   
			uchar tmp;
			IICBUF = tmp;
			SCLEN_SET;
	
		}
		//-----------------------------------------------------------------//
		//函数名称： void Master_Write_Data()  
		//函数功能： 从IICBUF读取数据
		//输入参数： 无
		//输出参数： 无
		//返 回 值： 无
		//-----------------------------------------------------------------//
		void Master_Write_Data() 
		{   
			uchar tmp;
			tmp = IICBUF;
			
		} 
		//-----------------------------------------------------------------//
		//函数名称： void IIC_ISR_PA() interrupt 10 
		//函数功能： PA口IIC中断子函数
		//输入参数： 无
		//输出参数： 无
		//返 回 值： 无
		//-----------------------------------------------------------------//
		void IIC_ISR_PA() interrupt 10
		{
				uchar tmp;
				static uchar xdata addr_bak = 0;
				PUSH_REG_ADDR_SFR();
				IIC_INT_FLAG_CLR;//清除IIC中断标志位
 
				if (IICS_WCOL)//写冲突标志位
				{ 
						IICS_WCOL_CLR;
				}
				if (IICS_RECOV)//读冲突标志位  
				{
						IICS_RECOV_CLR;
						tmp = IICBUF;
				}
				if (IICS_AD == 0)//是地址
				{	 
				
					
						if (IICS_RW)//主机读 
						{
								Master_Read_Data();
								SCLEN_SET; 
						}
						else //主机写
						{

								tmp = IICBUF;
								
						}   
					}
					else 
					{
						if (IICS_RW)//主机读 
						{
								      
								Master_Read_Data();
								SCLEN_SET;	  
						}
						else//主机写  
						{   
					
							if (IICS_BF) 
							{ 
								Master_Write_Data();
							}
						}
				}
				SCLEN_SET;
				POP_REG_ADDR_SFR();
		}
		
		#endif
	#endif//PA_SLAVE