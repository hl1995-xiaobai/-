#include "include.h"

#include ".\BF7615BMXX_XXXX_Library\Config.h"

#if ((UART0_EN == 1)||(UART1_EN == 1))	
/****************************************************************/
//函数名：uchar UART_Rece_Check(uchar n,uchar *nSendByte)  
//功  能：UART接送校验
//参  数：uchar n:接送校验字节数；uchar *nSendByte：发送数据指针
//返回值：uchar 返回校验值
/****************************************************************/

uchar UART_Rece_Check(uchar n,uchar *nCheckByte1,uchar *nCheckByte2)  
{
		uchar i = 0;
		for(i = 0; i < n; i++)
		{
			if((*(nCheckByte1 + i)) != (*(nCheckByte2 + i)))
			{
					return 1;
			}
		}	
		return 0;
}
#endif

#if UART0_EN
#pragma message "编译,UART0功能"
/****************************************************************/
//函数名：void UART0_Send_NByte(uchar n,uchar *nSendByte)  
//功  能：UART0发送N BYTES
//参  数：uchar n:发送字节数；uchar *nSendByte：发送数据指针
//返回值：无
/****************************************************************/

//void UART0_Send_NByte(uchar n,uchar *nSendByte)  
//{
//		uchar i = 0;
//		for(i = 0; i < n; i++)
//		{
//			UART0_Send_Byte(*(nSendByte + i));
//		}		
//}
#endif	

#if UART1_EN
#pragma message "编译,UART1功能"
/****************************************************************/
//函数名：void UART1_Send_NByte(uchar n,uchar *nSendByte)  
//功  能：UART1发送N BYTES
//参  数：uchar n:发送字节数；uchar *nSendByte：发送数据指针
//返回值：无
/****************************************************************/

//void UART1_Send_NByte(uchar n,uchar *nSendByte)  
//{
//		uchar i = 0;
//		for(i = 0; i < n; i++)
//		{
//			UART1_Send_Byte(*(nSendByte + i));
//		}		
//}
#endif


#if (UART0_EN == 1)

	

	
	//-----------------------------------------------------------------//
	//函数名称： void UART0_Init(void)  
	//函数功能： UART0初始化
	//输入参数： 无
	//输出参数： 无
	//返 回 值： 无
	//-----------------------------------------------------------------//
	void UART0_Init(void) 
	{ 
			EA = 0;//关总中断；
			UART0_IP_SET;//设置UART0中断优级为高，根据实际应运设置优先级
			UART0_INT_FLAG_CLR;//清除UART0中断标志
			UART0_PORT_SET(UART0_PORT);//UART_PC(RXD0C-TXD0C)映射为PC4/5为串口，UART_PE(RXD0A-TXD0A)射为PE4/5为串口，UART_PF(RXD0B-TXD0B)射为PF4/5为串口
			
		#if (UART0_PORT == UART0_PC)
			REG_ADDR = 0x19;REG_DATA |= 0x10;//PC4开启上拉
			REG_ADDR = 0x19;REG_DATA |= 0x20;//PC5开启上拉
			
			REG_ADDR = 0x26;REG_DATA &= ~0x40;TRISC |= 0x10;//PC4设置RXD0为输入
			REG_ADDR = 0x26;REG_DATA &= ~0x80;TRISC &= ~0x20;//PC5设置TXD0为输出
		#elif(UART0_PORT == UART0_PE)

			REG_ADDR = 0x1B;REG_DATA |= 0x10;//PE4开启上拉
			REG_ADDR = 0x1B;REG_DATA |= 0x20;//PE5开启上拉
			REG_ADDR = 0x27;REG_DATA &= ~0x01;TRISE |= 0x10;//PE4设置RXD0为输入
			REG_ADDR = 0x27;REG_DATA &= ~0x02;TRISE &= ~0x20;//PE5设置TXD0为输出
			
		#elif(UART0_PORT == UART0_PF)
			REG_ADDR = 0x1C;REG_DATA |= 0x10;//PF4开启上拉
			REG_ADDR = 0x1C;REG_DATA |= 0x20;//PF5开启上拉
			REG_ADDR = 0x28;REG_DATA &= ~0x01;TRISF |= 0x10;//PF4设置RXD0为输入
			REG_ADDR = 0x28;REG_DATA &= ~0x02;TRISF &= ~0x20;//PF5设置TXD0为输出
		#else

		#endif

		UART0_BDL = (uchar)M_HEX_OF_BR(UART0_CFG_BAUD_RATE);//设置波特率=BUSCLK/(16*(UART0_BDH[0:1],UART0_BDL))
		UART0_CON2 = ((((uint)(M_HEX_OF_BR(UART0_CFG_BAUD_RATE)))>>8)&0x03);//设置UART0_BDH[0:1]高两位
		UART0_CON2 |= (UART0_TX_EN);//发送中断使能，0为禁止发送中断，1为允许发送中断
		UART0_CON2 |= (UART0_RX_EN);//接收中断使能，0为禁止接收中断，1为允许接收中断
		UART0_CON1 |= (UART0_MUDULE_EN);//使能UAERT0模块
		UART0_CON1 &= (~UART0_MULTI);//1:使能多处理器通信,0:不使能多处理器通信
		UART0_CON1 |= (UART0_RE_EN);//开启接收使能
		UART0_CON1 &= (~UART0_SEND_MODE); //发送数据模式bit[3]：0：八位模式：1：9位模式模式
		UART0_CON1 |= (UART0_STOP_BIT);//停止位;1:2位；0：1位
		UART0_CON1 &= (~UART0_ODD_EVEN_EN);//奇偶校验使能1：开启奇偶校验；0:关闭奇偶校验
		UART0_CON1 |= (UART0_ODD_EVEN_SE);//奇偶校验选择1：奇校验；0:偶校验
		UART0_STATE &= ((~UART0_RI)&(~UART0_TI));//清除接收中断标志位//清除发送中断标志位
		UART0_IE_SET;//开UART中断使能				
		EA = 1;//开总中断
	}
	
//	#pragma disable //发送不允许其它中断打断
//	void UART0_Send_Word(uint willSendWord)   
//	{
//			UART0_Send_Byte(willSendWord>>8);
//			UART0_Send_Byte((uchar)willSendWord);
//	}
	
//	#pragma disable //发送不允许其它中断打断 
//	void UART0_Send_Byte(uchar willSendByte)  
//	{
//			UART0_STATE = 0x0F;//清除发送中断标志位，发送8位模式
//			UART0_BUF = willSendByte;

//			while (!(UART0_STATE & UART0_TI));

//			UART0_STATE = 0x0F;//清除发送中断标志位，发送8位模式
//	}
	
	
	/* 串口0中断服务子程序 */
	void UART0_ISR() interrupt 17
	{    
			unsigned char temp = 0;	
			static uchar xdata addr_bak = 0;
			PUSH_REG_ADDR_SFR();
			UART0_INT_FLAG_CLR;//清除UART0中断标志  
			if ((UART0_STATE & UART0_RI))
			{
					UART0_STATE = 0x17;//清除接收中断标志位，发送8位模式
					temp = UART0_BUF;
					
			}
			if((UART0_STATE & 0x01))
			{
					UART0_STATE = 0x1E;//奇偶校验错误
			} 
			if((UART0_STATE & 0x02))
			{
					UART0_STATE = 0x1D;//帧错误
			}
			if((UART0_STATE & 0x04))
			{
					UART0_STATE = 0x1B;//接收溢出
			}
			if((UART0_STATE & 0x10))
			{
				UART0_STATE = 0x0F;//清除发送中断标志
				//在此添加发送数据
			}
			POP_REG_ADDR_SFR();
	}

#endif
	
#if (UART1_EN == 1)

	

	
	//-----------------------------------------------------------------//
	//函数名称： void UART1_Init(void)  
	//函数功能： UART1初始化
	//输入参数： 无
	//输出参数： 无
	//返 回 值： 无
	//-----------------------------------------------------------------//
	void UART1_Init(void) 
	{ 
			EA = 0;//关总中断；
			UART1_IP_SET;//设置UART0中断优级为高，根据实际应运设置优先级
			UART1_INT_FLAG_CLR;//清除UART0中断标志
			UART1_PORT_SET(UART1_PORT);//串口功能映射选择0-为选择PC6/7为串口，1选择PH4/5为串口
			
		#if (UART1_PORT == UART1_PH)

			REG_ADDR = 0x1E;REG_DATA |= 0x10;//PH4开启上拉
			REG_ADDR = 0x1E;REG_DATA |= 0x20;//PH5开启上拉
			REG_ADDR = 0x29;REG_DATA &= ~0x10;TRISH |= 0x10;//PH4设置RXD0为输入
			REG_ADDR = 0x29;REG_DATA &= ~0x20;TRISH &= ~0x20;//PH5设置TXD0为输出
		
		#elif(UART1_PORT == UART1_PC)

			REG_ADDR = 0x19;REG_DATA |= 0x40;//PC6开启上拉
			REG_ADDR = 0x19;REG_DATA |= 0x80;//PC7开启上拉
			REG_ADDR = 0x52;REG_DATA &= ~0x04;TRISC |= 0x40;//PC6设置RXD0为输入
			REG_ADDR = 0x52;REG_DATA &= ~0x08;TRISC &= ~0x80;//PC7设置TXD0为输出
		#else

		#endif

		UART1_BDL = (uchar)M_HEX_OF_BR(UART1_CFG_BAUD_RATE);//设置波特率=BUSCLK/(16*(UART1_BDH[0:1],UART1_BDL))
		UART1_CON2 = ((((uint)(M_HEX_OF_BR(UART1_CFG_BAUD_RATE)))>>8)&0x03);//设置UART1_BDH[0:1]高两位
		UART1_CON2 |= (UART1_TX_EN);//发送中断使能，0为禁止发送中断，1为允许发送中断
		UART1_CON2 |=(UART1_RX_EN);//接收中断使能，0为禁止接收中断，1为允许接收中断
		UART1_CON1 |= (UART1_MUDULE_EN);//使能UAERT0模块
		UART1_CON1 &= (~UART1_MULTI);//1:使能多处理器通信,0:不使能多处理器通信
		UART1_CON1 |= (UART1_RE_EN);//开启接收使能
		UART1_CON1 &=(~UART1_SEND_MODE); //发送数据模式bit[3]：0：八位模式：1：9位模式模式
		UART1_CON1 |= (UART1_STOP_BIT);//停止位;1:2位；0：1位
		UART1_CON1 &= (~UART1_ODD_EVEN_EN);//奇偶校验使能1：开启奇偶校验；0:关闭奇偶校验
		UART1_CON1 |= (UART1_ODD_EVEN_SE);//奇偶校验选择1：奇校验；0:偶校验
		UART1_STATE &= ((~UART1_RI)&(~UART1_TI));//清除接收中断标志位//清除发送中断标志位
		UART1_IE_SET;//开UART中断使能							
		EA = 1;//开总中断
	}
	
//	#pragma disable //发送不允许其它中断打断
//	void UART1_Send_Word(uint willSendWord)   
//	{
//			UART1_Send_Byte(willSendWord>>8);
//			UART1_Send_Byte((uchar)willSendWord);
//	}
	
//	#pragma disable 
//	void UART1_Send_Byte(uchar willSendByte)  
//	{
//			UART1_STATE = 0x0F;//清除发送中断标志位，发送8位模式
//			UART1_BUF = willSendByte;

//			while (!(UART1_STATE & UART1_TI));
//			UART1_STATE = 0x0F;//清除发送中断标志位，发送8位模式
//	}
	
	
	/* 串口1中断服务子程序 */
	void UART1_ISR() interrupt 18
	{    
			unsigned char temp;	
			static uchar xdata addr_bak = 0;
			PUSH_REG_ADDR_SFR();
			UART1_INT_FLAG_CLR;//清除UART1中断标志	   
			if ((UART1_STATE & UART1_RI))
			{
					UART1_STATE = 0x17;//清除接收中断标志位，发送8位模式
//					temp = UART1_BUF;	
					
			} 
			if((UART1_STATE & 0x01))
			{
					UART1_STATE = 0x1E;//奇偶校验错误
			} 
			if((UART1_STATE & 0x02))
			{
					UART1_STATE = 0x1D;//帧错误
			}
			if((UART1_STATE & 0x04))
			{
					UART1_STATE = 0x1B;//接收溢出
			}
			
			if((UART1_STATE & 0x10))
			{
					UART1_STATE = 0x0F;//清除发送中断标志
					//在此添加发送数据
//					UART1_BUF = 0xFF;
					g_View.SendingState = SET;
			}
			POP_REG_ADDR_SFR();
	}

#endif
	
#if (UART2_EN == 1)
		#pragma message "编译,UART2功能"
		/****************************************************************/
		//函数名：void UART2_Send_NByte(uchar n,uchar *nSendByte)  
		//功  能：UART2发送N BYTES
		//参  数：uchar n:发送字节数；uchar *nSendByte：发送数据指针
		//返回值：无
		/****************************************************************/

//		void UART2_Send_NByte(uchar n,uchar *nSendByte)  
//		{
//				uchar i = 0;
//				for(i = 0; i < n; i++)
//				{
//					UART2_Send_Byte(*(nSendByte + i));
//				}		
//		}

	
	//-----------------------------------------------------------------//
	//函数名称： void UART2_Init(void)  
	//函数功能： UART2初始化
	//输入参数： 无
	//输出参数： 无
	//返 回 值： 无
	//-----------------------------------------------------------------//
	void UART2_Init(void) 
	{ 

			EA = 0;//关总中断；
			UART2_IP_SET;//设置UART1中断优级为高，根据实际应运设置优先级
			UART2_INT_FLAG_CLR;//清除UART2中断标志
			REG_ADDR = 0x51;REG_DATA &= ~0x20;TRISB &= ~0x02;//PB1设置为输出
			REG_ADDR = 0x51;REG_DATA &= ~0x10;TRISB |= 0x01; //PB0设置为输入
			UART2_BREAK_CHECK_IE_SET(0);//UART2间隔段中断使能,1为开间隔段中断使能，0为关间隔段中断使能
			UART2_RXD_EDGE_IE_SET(0);//UART2RXD活动边沿中断使能,1为开RXD活动边沿中断使能，0为关RXD活动边沿中断使能
		
			UART2_MODE_SET(0);//UART2模式选择,1为循环模式或单线模式，0为双线模式
			UART2_STOP_MODE_SET(1);//UART2 STOP位模式选择,1为2bits，0为1bit
			UART2_SINGLE_MODE_SET(1);//UART2_MODE_SET(1)单线模式时，1为TXD引脚有效，0为TXD引脚无效
			UART2_DATA_MODE_SET(0);//UART2数据模式选择,1为9位模式(第九位位奇偶校验位)，0为8位模式
			UART2_PARITY_EN_SET(0);//UART2奇偶校验位使能,1为使能奇偶校验位，0为不使能奇偶校验位
			UART2_PARITY_SEL(0);//UART2奇偶校验位选择,1为奇校验，0为偶校验
			UART2_RATE_MATCH_EN(0);//UART2同步段(0x55)波特率自动匹配使能,1为自适应波特率更新，0为固定配置波特率
			UART2_CLK_SEL(1);//UART2模块工作时钟使能,1为打开工作时钟，0为关闭并复位模块

			UART2_TX_EMPTY_IE_SET(0);	//UART2发送缓存空中断使能,1为中断使能，0为中断禁止
			UART2_TX_FINISH_IE_SET(1);//UART2发送缓存完成中断使能,1为中断使能，0为中断禁止	
			UART2_RX_FULL_IE_SET(1);//UART2接收满中断使能,1为中断使能，0为中断禁止	
			UART2_IDLE_IE_SET(0);//UART2空闲路线中断使能,1为中断使能，0为中断禁止		
			UART2_TRANS_EN_SET(1);//UART2发送器使能,1为打开，0为关闭，清0再写1可以排队发送一个闲置字符		
			UART2_RECEIVE_EN_SET(1);//UART2接收器使能,1为打开，0为关闭		
			UART2_RWU_SET(0);//UART2接收器唤醒控制,1为接收器处于待机状态，等待唤醒条件，0为接收器正常运行					
			UART2_BREAK_TRANS_SET(0);//UART2发送数据流中排入一个间隔段,1为排入一个间隔段(写1后再写0到该位)，0为不排入一个间隔段	


			UART2_SINGLE_DIR_SET(1);//UART2_MODE_SET(1)单线模式时，1为TXD输出，0为TXD输入		
			UART2_TXD_INV_SET(0);	//TXD端数据反相设置，1为TXD发送数据反相，0为TXD发送数据不反相 		
			UART2_RXD_INV_SET(0);//RXD端数据反相设置，1为RXD接送数据反相，0为RXD接送数据不反相	 		
			UART2_RWU_IDLE_SEL(0);//接收唤醒闲置检测，在接收待机状态(RWU = 1)期间，1为检测到闲置字符时设置IDLE位，0为检测到闲置字符时不设置IDLE位	 		
			UART2_IDLE_SEL(0);//闲置线路类型，1为停止位后闲置字符计数开始，0为开始位后闲置字符计数开始，计数10位时间(如果data_mode = 1或stop_mode = 1,则分别增加1位时间)	 		 		
			UART2_WAKE_SEL(0);//接收器唤醒方式选择，1为地址标记唤醒，0为闲置路线唤醒	 	   		

			UART2_BREAK_TRANS_SIZE(0);//间隔段生成位长度，1为用13位时间发送长度(如果data_mode = 1或stop_mode = 1,则分别增加1位时间)，0为用10位时间发送长度(如果data_mode = 1或stop_mode = 1,则分别增加1位时间)
			UART2_BREAK_CHECK_EN(0);//间隔段检测使能，1为在11位时间长度检测(如果data_mode = 1或stop_mode = 1,则分别增加1位时间)，0为不检测	 

			UART2_BDL_SET((uchar)M_HEX_OF_BR(UART2_CFG_BAUD_RATE));//设置波特率=BUSCLK/(16*(UART2_BDH[4:0],UART2_BDL))
			UART2_BDH_SET(((((uint)(M_HEX_OF_BR(UART2_CFG_BAUD_RATE)))>>8)&0x1F));//设置UART2_BDH[4:0]高5位
			UART2_IE_SET;//开UART2中断使能				
			EA = 1;//开总中断
	}
	
//	#pragma disable //发送不允许其它中断打断
//	void UART2_Send_Word(uint willSendWord)   
//	{
//			UART2_Send_Byte(willSendWord>>8);
//			UART2_Send_Byte((uchar)willSendWord);
//	}
	
//	#pragma disable //发送不允许其它中断打断 
//	void UART2_Send_Byte(uchar willSendByte)  
//	{
//			UART2_INT_IF_TF_CLR(1);//写1清除UART2_TF标志位
//			UART2_INT_IF_TE_CLR(1);//写1清除UART2_TE标志位
//			UART2_INT_IF_RF_CLR(1);//写1清除UART2_RF标志位
//			UART2_TRANS_ENABLE();//UART2发送器使能,1为打开，0为关闭，清0再写1可以排队发送一个闲置字符	
//			UART2_TX_EMPTY_IE_SET(0);	//UART2发送缓存空中断使能,1为中断使能，0为中断禁止
//			if(SCI_C2 & 0x08)
//			{
//				
//				UART2_BUF = willSendByte;
//				while(UART2_TF == 0);
//				
//				UART2_INT_IF_TF_CLR(1);//写1清除UART2_TF标志位
//				UART2_INT_IF_TE_CLR(1);//写1清除UART2_TE标志位
//				UART2_INT_IF_RF_CLR(1);//写1清除UART2_RF标志位
//				
//			}
//			
//	}
	
	
	/* 串口2中断服务子程序 */
	void UART2_ISR() interrupt 15
	{    
			unsigned char temp;	
			static uchar xdata addr_bak = 0;
			PUSH_REG_ADDR_SFR();
			UART2_INT_FLAG_CLR;//清除UART2中断标志		
				
			if(SCI_C2 & 0x20)
			{
				if(UART2_RI != 0)
				{
						UART2_INT_IF_RF_CLR(1);//写1清除UART2_RF标志位
						temp = UART2_BUF;
						
				}
			}
			
			if(SCI_C2 & 0x80)//开启了发送缓存空为中断
			{
				if(UART2_TE != 0)
				{
						UART2_INT_IF_TE_CLR(1);//写1清除UART2_TE标志位
						if(UART2_TE != 0)
						{
								UART2_INT_IF_TE_CLR(1);//写1清除UART2_TF标志位6
								//在此添加发送数据
						}  
				} 
			}
			
			if(SCI_C2 & 0x40)//开启了发送缓完成为中断
			{
				if(UART2_TF != 0)
				{
						UART2_INT_IF_TF_CLR(1);//写1清除UART2_TF标志位6
						//在此添加发送数据
				}   
			}
			POP_REG_ADDR_SFR();
	}

#endif
