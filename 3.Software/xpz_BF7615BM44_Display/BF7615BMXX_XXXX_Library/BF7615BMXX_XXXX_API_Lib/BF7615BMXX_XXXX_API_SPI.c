#include ".\BF7615BMXX_XXXX_Library\Config.h"

#if (SPI_EN == 1)

	//-----------------------------------------------------------------//
	//函数名称： void SPI_Init(void)  
	//函数功能： SPI初始化
	//输入参数： 无
	//输出参数： 无
	//返 回 值： 无
	//-----------------------------------------------------------------//
	void SPI_Init(void) 
	{ 
		EA = 0;//关总中断；
		SPI_IP_SET;//设置SPI中断优级为高
		SPI_RE_INT_SET(0);//SPI接收中断使能，1为接收缓存满中断使能，0为禁止中断
		SPI_EN_SET(1);//SPI模块使能，1为模块使能，0为模块关闭
		SPI_TE_INT_SET(0);//SPI发送中断使能，1为发送缓存空中断使能，0为禁止中断
		SPI_MS_SET(1);//SPI主从模式选择，1为主机，0为从机
		SPI_CPO_SET(1);//SPI时钟极性选择，1为SPI时钟低有效,闲置时高，0为SPI时钟高有效,闲置时低
		SPI_CPH_SET(1);//SPI时钟相位选择，1为第一个有效时钟沿发送数据，0为第一个有效时钟沿采样数据
		SPI_LSB_SET(1);//SPI移位方向选择，1为串行数据始于低位，0为串行数据始于高位
		SPI_CS_SET();//SPI片选择，拉高CS
		
		SPI_FEE_SET(0);//CPHA=0时，SPI数据反馈选择，1为发送接收到的数据给主机/从机，0为发送MCU写入的数据给主机/从机
		SPI_HSPE_START(0);//SPI高速模式开启(工作完成硬件自动拉低)，1为SPI高速模式开启，0为高速模式关闭
		SPI_HA_DU_SEL(0);//SPI半/全工模式选择，1为半双工模式，0为全双工模式
		SPI_BIDIR_SEL(1);//SPI半工模式发送/接收方向选择，1为发送，0为接收
		SPI_SPR_SET(2);
		//SPI波特率系数(电高2MHz):
		//{0-SYS_CLK/2};{1-SYS_CLK/4};{2-SYS_CLK/6};{3-SYS_CLK/8};{4-SYS_CLK/10};{5-SYS_CLK/12};{6-SYS_CLK/14};{7-SYS_CLK/16};
		SPI_IE_SET;//开SPI中断使能 
		EA = 1;//开总中断
	}
	
//	void spi_high_speed_comm(uint tx_addr,uint rx_addr,uint comm_num,HIGH_SPEED_MODE_enum high_mode)
//	{
//		uchar tx_addr_buff = (tx_addr >> 4);
//		uchar rx_addr_buff = (rx_addr >> 4);
//		
//		REG_ADDR = SPI_TX_START_ADDR;
//		REG_DATA = tx_addr_buff;

//		REG_ADDR = SPI_RX_START_ADDR;
//		REG_DATA = rx_addr_buff;

//		REG_ADDR = SPI_NUM_L;
//		REG_DATA = (uchar)comm_num;

//		REG_ADDR = SPI_NUM_H;
//		REG_DATA = ((comm_num >> 8) & 0x0f);

//		if(FULL_DUPLEX_MODE==high_mode)
//		{
//			SPI_CFG2 &= ~HALF_DUPLEX;
//		}
//		else if(HALF_DUPLEX_TX==high_mode)
//		{
//			SPI_CFG2 |= HALF_DUPLEX;
//			SPI_CFG2 |= SPI_HALF_DUPLEX_TX;
//		}
//		else if(HALF_DUPLEX_RX==high_mode)
//		{
//			SPI_CFG2 |= HALF_DUPLEX;
//			SPI_CFG2 &= ~SPI_HALF_DUPLEX_TX;
//		}
//		SPI_CFG1 &= ~SPI_CS_N;
//		SPI_CFG2 |= SPI_HIGH_SPEED;

//	}

	/*!
	\brief      wait spi high speed communication complete
	\param[in]  none
	\param[out] none
	\retval     SUCCESS or ERROR 
	*/
//	ErrStatus wait_spi_high_comm_end(void)
//	{	
//		while(SPI_CFG2 & SPI_HIGH_SPEED);
//		while((SPI_STATE & SPI_INT_TX_EMPTY) == 0x00);
//		SPI_CFG1 |= SPI_CS_N;
//		SPI_CFG2 &= ~HALF_DUPLEX;
//		return SUCCESS;
//	}

	/*!
	\brief      spi send and receive a byte
	\param[in]  dat: send data//软件拉低片选时发送数据，发送完成软件拉高片选
	\param[out] none
	\retval     receive data
	*/
	uchar spi_sendbyte(uchar dat)
	{	
		while((SPI_STATE & SPI_INT_TX_EMPTY) == 0x00);
		SPI_SPID = dat;
		while((SPI_STATE & SPI_INT_RX_FULL) == 0x00);
		dat = SPI_SPID;
		SPI_STATE &= ~SPI_INT_RX_FULL;
		return dat;
	}
	
	
	
	/* SPI中断服务子程序 */
	void SPI_ISR() interrupt 20
	{    
		static uchar xdata addr_bak = 0;
		PUSH_REG_ADDR_SFR();
		SPI_INT_FLAG_CLR;//清除SPI中断标志  
		POP_REG_ADDR_SFR();
	}

#endif
