#ifndef __BF7615BMXX_XXXX_API_UART_H__
#define __BF7615BMXX_XXXX_API_UART_H__



#define UART0_EN							1	// 1:使能编译，0:不使能编译
#define UART0_PORT 						UART0_PE//选择UART0映射到UART0A_PE4/5(RXD,TXD),UART0B_PF4/5(RXD,TXD),UART0C_PC4/5(RXD,TXD)
#define UART0_CFG_BAUD_RATE   9600 // 波特率选择2400/4800/9600/14400/19200/38400/57600/115200

#define UART1_EN							1	// 1:使能编译，0:不使能编译
#define UART1_PORT 						UART1_PC//选择UART1映射到UART1A_PH4/5(RXD,TXD),UART1B_PC6/7(RXD,TXD)
#define UART1_CFG_BAUD_RATE   9600 // 波特率选择2400/4800/9600/14400/19200/38400/57600/115200

#define UART2_EN							0	// 1:使能编译，0:不使能编译
#define UART2_CFG_BAUD_RATE   9600 // 波特率选择2400/4800/9600/14400/19200/38400/57600/115200


#define UART0_MUDULE_EN 	0x40//使能UAERT0模块
#define UART0_MULTI 			0x10//使能多处理器通信
#define UART0_RE_EN 			0x20//开启接收使能
#define UART0_STOP_BIT 		0x08//停止位;1:2位；0：1位
#define UART0_SEND_MODE 	0x04//发送数据模式bit[3]：0：八位模式：1：9位模式模式
#define UART0_ODD_EVEN_EN 0x02//奇偶校验使能1：开启奇偶校验；0:关闭奇偶校验
#define UART0_ODD_EVEN_SE 0x01//奇偶校验选择1：奇校验；0:偶校验

#define UART1_MUDULE_EN 	0x40//使能UAERT1模块
#define UART1_MULTI 			0x10//使能多处理器通信
#define UART1_RE_EN 			0x20//开启接收使能
#define UART1_STOP_BIT 		0x08//停止位;1:2位；0：1位
#define UART1_SEND_MODE 	0x04//发送数据模式bit[3]：0：八位模式：1：9位模式模式
#define UART1_ODD_EVEN_EN 0x02//奇偶校验使能1：开启奇偶校验；0:关闭奇偶校验
#define UART1_ODD_EVEN_SE 0x01//奇偶校验选择1：奇校验；0:偶校验



#define UART0_RX_EN 	0x04
#define UART0_TX_EN 	0x08
#define UART0_RI 			0x08
#define UART0_TI 			0x10
#define UART0_PE 			0x01
#define UART0_PF 			0x02
#define UART0_PC 			0x00


#define UART1_RX_EN 	0x04
#define UART1_TX_EN 	0x08
#define UART1_RI 			0x08
#define UART1_TI 			0x10
#define UART1_PH 			0x01
#define UART1_PC 			0x00

#define CFG_BUSCLK    24   // BUSCLK频率

#define _CFG_BUSCLK (CFG_BUSCLK * 1e6)

#define M_HEX_OF_BR(br)     (_CFG_BUSCLK/(16.0*br))


#define UART0_PORT_SET(x) {REG_ADDR = 0x34;REG_DATA &= ~(0x60);REG_DATA |= (0x60&(x<<5));}//串口功能映射选择0-为选择PC4/5为串口，1选择PE4/5为串口，2/3选择PF4/5为串口
#define UART0_ON_OFF(x) {UART0_CON1 &= ~(0x40);UART0_CON1 |= (0x40&(x<<6));}//UAERT模块开关,1为开，0为关
#define UART0_IE_SET IEN2 |= 0x04													//开UART中断使能
#define UART0_IE_CLR IEN2 &= ~0x04												//关UART中断使能
#define UART0_IP_SET IPL2 |= 0x04													//设置UART中断优先级为高
#define UART0_IP_CLR IPL2 &= ~0x04												//设置UART中断优先级为低
#define UART0_INT_FLAG_CLR IRCON2 &= ~0x04								// 清除UART中断标志位

#define UART1_PORT_SET(x) {REG_ADDR = 0x34;REG_DATA &= ~(0x80);REG_DATA |= (0x80&(x<<7));}//串口功能映射选择0-为选择PC6/7为串口，1选择PH4/5为串口
#define UART1_ON_OFF(x) 	{UART1_CON1 &= ~(0x40);UART1_CON1 |= (0x40&(x<<6));}//UAERT模块开关,1为开，0为关
#define UART1_IE_SET IEN2 |= 0x08													//开UART中断使能
#define UART1_IE_CLR IEN2 &= ~0x08												//关UART中断使能
#define UART1_IP_SET IPL2 |= 0x08													//设置UART中断优先级为高
#define UART1_IP_CLR IPL2 &= ~0x08												//设置UART中断优先级为低
#define UART1_INT_FLAG_CLR IRCON2 &= ~0x08								// 清除UART中断标志位


#define UART2_BREAK_CHECK_IE_SET(x) 	{SCI_S2 &= ~(0x08);SCI_S2 |= (0x08&(x<<3));}//UART2间隔段中断使能,1为开间隔段中断使能，0为关间隔段中断使能
#define UART2_RXD_EDGE_IE_SET(x) 			{SCI_S2 &= ~(0x04);SCI_S2 |= (0x04&(x<<2));}//UART2RXD活动边沿中断使能,1为开RXD活动边沿中断使能，0为关RXD活动边沿中断使能

#define UART2_MODE_SET(x) 						{SCI_C1 &= ~(0x80);SCI_C1 |= (0x80&(x<<7));}//UART2模式选择,1为循环模式或单线模式，0为双线模式
#define UART2_STOP_MODE_SET(x) 				{SCI_C1 &= ~(0x40);SCI_C1 |= (0x40&(x<<6));}//UART2STOP位模式选择,1为2bits，0为1bit
#define UART2_SINGLE_MODE_SET(x)			{SCI_C1 &= ~(0x20);SCI_C1 |= (0x20&(x<<5));}//UART2_MODE_SET(1)单线模式时，1为TXD引脚有效，0为TXD引脚无效,用于内部
#define UART2_DATA_MODE_SET(x) 				{SCI_C1 &= ~(0x10);SCI_C1 |= (0x10&(x<<4));}//UART2数据模式选择,1为9位模式(第九位位奇偶校验位)，0为8位模式
#define UART2_PARITY_EN_SET(x) 				{SCI_C1 &= ~(0x08);SCI_C1 |= (0x08&(x<<3));}//UART2奇偶校验位使能,1为使能奇偶校验位，0为不使能奇偶校验位
#define UART2_PARITY_SEL(x) 	 				{SCI_C1 &= ~(0x04);SCI_C1 |= (0x04&(x<<2));}//UART2奇偶校验位选择,1为奇校验，0为偶校验
#define UART2_RATE_MATCH_EN(x) 				{SCI_C1 &= ~(0x02);SCI_C1 |= (0x02&(x<<1));}//UART2同步段(0x55)波特率自动匹配使能,1为自适应波特率更新，0为固定配置波特率
#define UART2_CLK_SEL(x) 	 						{SCI_C1 &= ~(0x01);SCI_C1 |= (0x01&(x<<0));}//UART2模块工作时钟使能,1为打开工作时钟，0为关闭并复位模块


#define UART2_TX_EMPTY_IE_SET(x)			{SCI_C2 &= ~(0x80);SCI_C2 |= (0x80&(x<<7));}//UART2发送缓存空中断使能,1为中断使能，0为中断禁止
#define UART2_TX_FINISH_IE_SET(x)			{SCI_C2 &= ~(0x40);SCI_C2 |= (0x40&(x<<6));}//UART2发送缓存完成中断使能,1为中断使能，0为中断禁止
#define UART2_RX_FULL_IE_SET(x)				{SCI_C2 &= ~(0x20);SCI_C2 |= (0x20&(x<<5));}//UART2接收满中断使能,1为中断使能，0为中断禁止
#define UART2_IDLE_IE_SET(x)					{SCI_C2 &= ~(0x10);SCI_C2 |= (0x10&(x<<4));}//UART2空闲路线中断使能,1为中断使能，0为中断禁止
#define UART2_TRANS_EN_SET(x)					{SCI_C2 &= ~(0x08);SCI_C2 |= (0x08&(x<<3));}//UART2发送器使能,1为打开，0为关闭，清0再写1可以排队发送一个闲置字符
#define UART2_TRANS_DISABLE()					{SCI_C2 &= ~(0x08);}//UART2关闭发送器使能
#define UART2_TRANS_ENABLE()					{SCI_C2 |= (0x08);}//UART2打开发送器使能
#define UART2_RECEIVE_EN_SET(x)				{SCI_C2 &= ~(0x04);SCI_C2 |= (0x04&(x<<2));}//UART2接收器使能,1为打开，0为关闭
#define UART2_RWU_SET(x)							{SCI_C2 &= ~(0x02);SCI_C2 |= (0x02&(x<<1));}//UART2接收器唤醒控制,1为接收器处于待机状态，等待唤醒条件，0为接收器正常运行
#define UART2_BREAK_TRANS_SET(x)			{if(x == 1){SCI_C2 |= (0x01);SCI_C2  &= ~(0x01&(x<<0));}}//UART1发送数据流中排入一个间隔段,1为排入一个间隔段(写1和0到该位)，0为不排入一个间隔段


#define UART2_SINGLE_DIR_SET(x)				{SCI_C3 &= ~(0x20);SCI_C3 |= (0x20&(x<<5));}//UART2_MODE_SET(1)单线模式时，1为TXD输出，0为TXD输入
#define UART2_TXD_INV_SET(x)	 				{SCI_C3 &= ~(0x10);SCI_C3 |= (0x10&(x<<4));}//TXD端数据反相设置，1为TXD发送数据反相，0为TXD发送数据不反相
#define UART2_RXD_INV_SET(x)	 				{SCI_C3 &= ~(0x08);SCI_C3 |= (0x08&(x<<3));}//RXD端数据反相设置，1为RXD接送数据反相，0为RXD接送数据不反相
#define UART2_RWU_IDLE_SEL(x)	 				{SCI_C3 &= ~(0x04);SCI_C3 |= (0x04&(x<<2));}//接收唤醒闲置检测，在接收待机状态(RWU = 1)期间，1为检测到闲置字符时设置IDLE位，0为检测到闲置字符时不设置IDLE位
#define UART2_IDLE_SEL(x)	 		 				{SCI_C3 &= ~(0x02);SCI_C3 |= (0x02&(x<<1));}//闲置线路类型，1为停止位后闲置字符计数开始，0为开始位后闲置字符计数开始，计数10位时间(如果data_mode = 1或stop_mode = 1,则分别增加1位时间)
#define UART2_WAKE_SEL(x)	 	   				{SCI_C3 &= ~(0x01);SCI_C3 |= (0x01&(x<<0));}//接收器唤醒方式选择，1为地址标记唤醒，0为闲置路线唤醒

#define UART2_BREAK_TRANS_SIZE(x)	 	  {SCI_S2 &= ~(0x02);SCI_S2 |= (0x02&(x<<1));}//间隔段生成位长度，1为用13位时间发送长度(如果data_mode = 1或stop_mode = 1,则分别增加1位时间)，0为用10位时间发送长度(如果data_mode = 1或stop_mode = 1,则分别增加1位时间)
#define UART2_BREAK_CHECK_EN(x)	 	   	{SCI_S2 &= ~(0x01);SCI_S2 |= (0x01&(x<<0));}//间隔段检测使能，1为在11位时间长度检测(如果data_mode = 1或stop_mode = 1,则分别增加1位时间)，0为不检测
#define UART2_BDL_SET(x) 							{REG_ADDR = 0x61;REG_DATA &= ~(0xFF);REG_DATA |= (0xFF&(x<<0));}//设置波特率=BUSCLK/(16*(UART2_BDH[4:0],UART2_BDL))
#define UART2_BDH_SET(x) 							{REG_ADDR = 0x60;REG_DATA &= ~(0x1F);REG_DATA |= (0x1F&(x<<0));}//设置UART2_BDH[4:0]高5位

#define UART2_INT_IF_TE_CLR(x)				{SCI_INT_CLR |= (0x80&(x<<7));}//写1清除UART2_TE标志位
#define UART2_INT_IF_TF_CLR(x)				{SCI_INT_CLR |= (0x40&(x<<6));}//写1清除UART2_TF标志位
#define UART2_INT_IF_RF_CLR(x)				{SCI_INT_CLR |= (0x20&(x<<5));}//写1清除UART2_RF标志位
#define UART2_INT_IF_ID_CLR(x)				{SCI_INT_CLR |= (0x10&(x<<4));}//写1清除UART2_闲置线路中断标志位
#define UART2_INT_IF_RO_CLR(x)				{SCI_INT_CLR |= (0x08&(x<<3));}//写1清除UART2_RO接收溢出标志位
#define UART2_INT_IF_NE_CLR(x)				{SCI_INT_CLR |= (0x04&(x<<2));}//写1清除UART2_噪声标志位
#define UART2_INT_IF_FE_CLR(x)				{SCI_INT_CLR |= (0x02&(x<<1));}//写1清除UART2_帧错标志位
#define UART2_INT_IF_PE_CLR(x)				{SCI_INT_CLR |= (0x01&(x<<0));}//写1清除UART2_寄偶校验错误标志位

#define UART2_BDL SCI_BDL
#define UART2_BDH SCI_BDH

#define UART2_BUF SCI_D
#define UART2_TF SCI_TF
#define UART2_TE SCI_TE
#define UART2_RI SCI_RI

#define UART2_IE_SET IEN2 |= 0x01													//开UART2中断使能
#define UART2_IE_CLR IEN2 &= ~0x01												//关UART2中断使能
#define UART2_IP_SET IPL2  |= 0x01												//设置UART2中断优先级为高
#define UART2_IP_CLR IPL2 &= ~0x01												//设置UART2中断优先级为低
#define UART2_INT_FLAG_CLR IRCON2 &= ~0x01								// 清除UART2中断标志位


#if(UART0_EN == 1)
// 配置宏定义
extern void UART0_Init(void);
extern void UART0_Send_Word (unsigned int willSendWord);
extern void UART0_Send_Byte (unsigned char willSendByte);
extern void UART0_Send_NByte(uchar n,uchar *nSendByte);  
#endif


#if(UART1_EN == 1)
// 配置宏定义
extern void UART1_Init(void);
extern void UART1_Send_Word (unsigned int willSendWord);
extern void UART1_Send_Byte (unsigned char willSendByte);
extern void UART1_Send_NByte(uchar n,uchar *nSendByte);  
#endif

#if ((UART0_EN == 1)||(UART1_EN == 1)||(UART2_EN == 1))	

extern uchar UART_Rece_Check(uchar n,uchar *nCheckByte1,uchar *nCheckByte2);  

#endif

#if(UART2_EN == 1)
extern void UART2_Init(void);
extern void UART2_Send_Word (unsigned int willSendWord);
extern void UART2_Send_Byte (unsigned char willSendByte);
extern void UART2_Send_NByte(uchar n,uchar *nSendByte);  
#endif

#endif