#ifndef __BF7615BMXX_XXXX_API_SPI_H__
#define __BF7615BMXX_XXXX_API_SPI_H__

#define SPI_EN				  0	// 1:使能编译，0:不使能编译

#define SPI_IE_SET  IEN2 |= 0x20//开SPI中断使能 
#define SPI_IE_CLR  IEN2 &= ~0x20//关SPI中断使能
#define SPI_IP_SET  IPL2 |= 0x20//设置SPI中断优级为高
#define SPI_IP_CLR  IPL2 &= ~0x20//设置SPI中断优级为低
#define SPI_INT_FLAG_CLR IRCON2 &= ~0X20//清除SPI中断标志

#define SPI_RE_INT_SET(x) 	{SPI_CFG1 &= ~0x80;SPI_CFG1 |= (0x80&(x<<7));}//SPI接收中断使能，1为接收缓存满中断使能，0为禁止中断
#define SPI_EN_SET(x) 		{SPI_CFG1 &= ~0x40;SPI_CFG1 |= (0x40&(x<<6));}//SPI模块使能，1为模块使能，0为模块关闭
#define SPI_TE_INT_SET(x) 	{SPI_CFG1 &= ~0x20;SPI_CFG1 |= (0x20&(x<<5));}//SPI发送中断使能，1为发送缓存空中断使能，0为禁止中断
#define SPI_MS_SET(x) 		{SPI_CFG1 &= ~0x10;SPI_CFG1 |= (0x10&(x<<4));}//SPI主从模式选择，1为主机，0为从机
#define SPI_CPO_SET(x) 		{SPI_CFG1 &= ~0x08;SPI_CFG1 |= (0x08&(x<<3));}//SPI时钟极性选择，1为SPI时钟低有效,闲置时高，0为SPI时钟高有效,闲置时低
#define SPI_CPH_SET(x) 		{SPI_CFG1 &= ~0x04;SPI_CFG1 |= (0x04&(x<<2));}//SPI时钟相位选择，1为第一个有效时钟沿发送数据，0为第一个有效时钟沿采样数据
#define SPI_LSB_SET(x) 		{SPI_CFG1 &= ~0x02;SPI_CFG1 |= (0x02&(x<<1));}//SPI移位方向选择，1为串行数据始于低位，0为串行数据始于高位
#define SPI_CS_SET() 		  {SPI_CFG1 |= 0x01;}//SPI片选择，拉高CS
#define SPI_CS_CLR() 		  {SPI_CFG1 &= ~0x01;}//SPI片选择，拉低CS


#define SPI_FEE_SET(x) 		{SPI_CFG2 &= ~0x40;SPI_CFG2 |= (0x40&(x<<6));}//CPHA=0时，SPI数据反馈选择，1为发送接收到的数据给主机/从机，0为发送MCU写入的数据给主机/从机
#define SPI_HSPE_START(x) 	{SPI_CFG2 &= ~0x20;SPI_CFG2 |= (0x20&(x<<5));}//SPI高速模式开启(工作完成硬件自动拉低)，1为SPI高速模式开启，0为高速模式关闭
#define SPI_HA_DU_SEL(x) 	{SPI_CFG2 &= ~0x10;SPI_CFG2 |= (0x10&(x<<4));}//SPI半/全工模式选择，1为半双工模式，0为全双工模式
#define SPI_BIDIR_SEL(x) 	{SPI_CFG2 &= ~0x08;SPI_CFG2 |= (0x08&(x<<3));}//SPI半工模式发送/接收方向选择，1为发送，0为接收
#define SPI_SPR_SET(x) 		{SPI_CFG2 &= ~0x07;SPI_CFG2 |= (0x07&(x<<0));}//SPI波特率系数(电高2MHz):
//{0-SYS_CLK/2};{1-SYS_CLK/4};{2-SYS_CLK/6};{3-SYS_CLK/8};{4-SYS_CLK/10};{5-SYS_CLK/12};{6-SYS_CLK/14};{7-SYS_CLK/16};

#define SPI_READ_F(x) 		{SPI_STATE &= ~0x04;SPI_STATE |= (0x04&(x<<2));}//SPI读缓冲器满标记，软件写0清0
#define SPI_ROV(x) 			{SPI_STATE &= ~0x02;SPI_STATE |= (0x02&(x<<1));}//1为SPI普通通讯模式下，读不及时溢出，读信号不产生中断；
//高速模式下，无效(当接收数据个数等于{SPI_NUM_H,SPI_NUM_L}时会结束工作，SPRF置位，产生满中断)
#define SPI_TXE_F(x) 		{SPI_STATE &= ~0x01;SPI_STATE |= (0x01&(x<<0));}//SPI发送缓冲器空标记，写入SPID硬件自动清0
#define SPI_TX_BUF_ADD(x) 	{REG_ADDR = 0x3E;REG_DATA = x;}//SPI高速模式下，发送数据缓存首地址
#define SPI_RX_BUF_ADD(x) 	{REG_ADDR = 0x3F;REG_DATA = x;}//SPI高速模式下，接收数据缓存首地址
#define SPI_NUM(x) 			{REG_ADDR = 0x40;REG_DATA &= ~0x0F;REG_DATA |= (0x0F&(x>>8));REG_ADDR = 0x41;REG_DATA = x;}//SPI数据缓存地址个数
//注1：主机模式下，必须先配置CPOL和CPHA,再拉低片选，否则SCLK_OUT有毛刺；
//注2：从机模式下，片选拉低后，不能关闭SPI_EN，否则重新打开SPI_EN时，片先再次变成低时，内部产生的SCLK有毛刺；
//注3：SPI_FEE_SET(1)返回主机发送的前一笔数据(第一笔发送数据为0xFF，第二笔发送的是接收到的主机第一笔数据，后面的发送数据都是主机发送的前一笔数据，该功能用有CPHA=0的模式)


#define	SPI_TX_START_ADDR  	0x3E
#define	SPI_RX_START_ADDR  	0x3F
#define	SPI_NUM_L          	0x40
#define	SPI_NUM_H           	0x41
#define	ADC_CFG_SEL1			0x42

/* spi device mode define */
#define	SPI_MASTER		(0x01 << 4)
#define	SPI_SLAVE		(0x00)
/* spi clock define */
#define	SYS_CLK_DIVIDE_2	0x00
#define	SYS_CLK_DIVIDE_4	0x01
#define	SYS_CLK_DIVIDE_6	0x02
#define	SYS_CLK_DIVIDE_8	0x03
#define	SYS_CLK_DIVIDE_10	0x04
#define	SYS_CLK_DIVIDE_12	0x05
#define	SYS_CLK_DIVIDE_14	0x06
#define	SYS_CLK_DIVIDE_16	0x07

/* spi duplex define */
#define	FULL_DUPLEX			(0x00)
#define	HALF_DUPLEX			(0x01 << 4)
/* spi endian define */
#define	LSB_FIRST			(0x01 << 1)
#define	MSB_FIRST			(0x00)
/* spi clock polarity define */
#define	CPOL_HIGH			(0x01 << 3)
#define	CPOL_LOW			(0x00)
/* spi clock phase define */
#define	SPI_CPHA_2Edge		(0x01 << 2)
#define SPI_CPHA_1Edge		(0x00)
/* spi communication mode define */
#define	SPI_HIGH_SPEED		(0x01 << 5)	
/* spi interrupt enable define */
#define	SPI_RX_INT_EN		(0x01 << 7)
#define	SPI_TX_INT_EN 		(0x01 << 5)

/* spi interrupt flag define */
#define	SPI_INT_TX_EMPTY	(0x01)
#define	SPI_RX_OVERFLOW		(0x01 << 1)
#define	SPI_INT_RX_FULL		(0x01 << 2)
/* spi half_duplex direct define */
#define	SPI_HALF_DUPLEX_TX	(0x01 << 3)
#define	SPI_HALF_DUPLEX_RX	(0x00)

/* spi cs define */
#define SPI_CS_N			(0x01)


#define SPI_DEVICE_MODE(x)   SPI_CFG1 &= ~0x10;SPI_CFG1 |= (x)
#define SPI_PRESCALE_SET(x)  SPI_CFG2 &= ~0x07;SPI_CFG2 |= (x)
#define SPI_DUPLEX_SET(x)    SPI_CFG2 &= ~0x10;SPI_CFG2 |= (x)
#define SPI_ENDIAN_SET(x)    SPI_CFG1 &= ~0x02;SPI_CFG1 |= (x)
#define SPI_CPOL_SET(x)      SPI_CFG1 &= ~0x08;SPI_CFG1 |= (x)
#define SPI_CPHA_SET(x)      SPI_CFG1 &= ~0x04;SPI_CFG1 |= (x)

#define SPI_TRANSFER_SET(x)  SPI_CFG2 &= ~0x08;SPI_CFG2 |= (x)/* x=SPI_HALF_DUPLEX_TX or SPI_HALF_DUPLEX_RX*/


#define SPI_TX_INT_ENABLE()   SPI_CFG1 |= SPI_TX_INT_EN
#define SPI_TX_INT_DISABLE()  SPI_CFG1 &= ~SPI_TX_INT_EN

#define SPI_RX_INT_ENABLE()   SPI_CFG1 |= SPI_RX_INT_EN
#define SPI_RX_INT_DISABLE()  SPI_CFG1 &= ~SPI_RX_INT_EN

#define SPI_INT_ENABLE()	 IEN2 |= 0x20   /* enable interrupt */
#define SPI_INT_DISABLE()	 IEN2 &= ~0x20  /* disable interrupt */
#define SPI_IPL_SET(x)       IPL2 &= ~0x20;IPL2 |= (x<<5)  /* set interrupt priority */

#define SPI_ENABLE()	 	 SPI_CFG1 |= 0x40   /* enable spi */
#define SPI_DISABLE()	 	 SPI_CFG1 &= ~0x40  /* disable spi */
#define INT_SPI_CLR()        IRCON2 &= ~(0x01 << 5)

/* enum definitions */
typedef enum {DISABLE = 0, ENABLE = !DISABLE} EventStatus, ControlStatus;
typedef enum {RESET = 0, SET = !RESET} FlagStatus;
typedef enum {ERROR = 0, SUCCESS = !ERROR} ErrStatus;
typedef enum {LOW = 0, HIGH = !LOW} IntPrioStatus;

/* high speed mode enum */
typedef enum
{
	FULL_DUPLEX_MODE,	/* full duplex mode */
	HALF_DUPLEX_TX,		/* half duplex tx mode , not receive */
	HALF_DUPLEX_RX		/* half duplex rx mode , not transmit */
}HIGH_SPEED_MODE_enum;

/* function declarations */

/* spi send and receive a byte */
extern uchar spi_sendbyte(uchar dat);
//extern void spi_init(void);
/* spi high speed communication */
extern void spi_high_speed_comm(uint tx_addr,uint rx_addr,uint comm_num,HIGH_SPEED_MODE_enum high_mode);
/* wait for spi high speed communication complete */
extern ErrStatus wait_spi_high_comm_end(void);


extern void SPI_Init(void);
#endif