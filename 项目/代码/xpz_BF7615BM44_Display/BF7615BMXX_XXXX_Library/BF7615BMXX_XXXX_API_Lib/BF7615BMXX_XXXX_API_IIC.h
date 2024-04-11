#ifndef __BF7615BMXX_XXXX_API_IIC_H__
#define __BF7615BMXX_XXXX_API_IIC_H__


#define IICS_EN					0	//IIC 口从机使能配置， 			1:使能编译，0:不使能编译

#define IICS_WCOL (IICSTAT & 0x02)//写冲突标志位
#define IICS_WCOL_CLR (IICSTAT &= ~0x02)//清除写冲突标志位

#define IICS_RECOV (IICSTAT & 0x01)//读冲突标志位
#define IICS_RECOV_CLR (IICSTAT &= ~0x01)//清除读冲突标志位

#define IICS_AD (IICSTAT & 0x10)//地址或数据标志位
#define IICS_RW (IICSTAT & 0x20)//读写标志位

#define SCLEN 		(IICCON & 0x04)//读时钟使能拉低状态
#define SCLEN_CLR (IICCON &= ~0x04)//不使能时钟拉低状态
#define SCLEN_SET (IICCON |= 0x04)//使能时钟拉低状态
#define IICS_RW   (IICSTAT & 0x20)//读写标志位
#define IICS_BF   (IICSTAT & 0x08)//读IIC_BUF满标志位
#define PSW_P 	  (PSW & 0x01)//PSW寄偶标志位


#define IIC_EN 				0x01       
#define IIC_SR 				0x02      
#define IIC_SCLEN 		0x04    	
#define IIC_W_SCL_EN 	0x08 			
#define IIC_R_SCL_EN 	0x10 			
#define IIC_RST 			0x20

#define IIC_PE 			0x01
#define IIC_PC 			0x00

#define IIC_PORT_SET(x) {REG_ADDR = 0x34;REG_DATA &= ~(0x10);REG_DATA |= (0x10&(x<<4));}//IIC功能映射选择0-为选择PC4/5为串口，1选择PE4/5为串口
#define IIC_AFIL_SET(x) {REG_ADDR = 0x50;REG_DATA &= ~(0x02);REG_DATA |= (0x02&(x<<1));}//IIC模拟滤波选择：1为选择模拟滤波，0为不选择模拟滤波
#define IIC_DFIL_SET(x) {REG_ADDR = 0x50;REG_DATA &= ~(0x01);REG_DATA |= (0x01&(x<<0));}//IIC模拟滤波选择：1为选择数字滤波，0为不选择数字滤波

#define IIC_IE_SET IEN1 |= 0x08												//开IIC中断使能
#define IIC_IE_CLR IEN1 &= ~0x08											//关IIC中断使能
#define IIC_IP_SET IPL1 |= 0x08												//设置IIC中断优先级为高
#define IIC_IP_CLR IPL1 &= ~0x08											//设置IIC中断优先级为低
#define IIC_INT_FLAG_CLR IRCON1 &= ~0x08								// 清除IIC中断标志位


#if IICS_EN
extern uint data IICS_Soft_Cnt;
extern uint xdata SCLEN_SoftCnt;
extern void IIC_Slave_Init(uchar IICSlaveAddr,uchar iic_port);
#endif

#if (TRACEMODE==1)
extern unsigned long xdata keys_flag_Tracemode;	
extern unsigned long xdata keys_flag_Tracemode_H;	
#endif
#endif