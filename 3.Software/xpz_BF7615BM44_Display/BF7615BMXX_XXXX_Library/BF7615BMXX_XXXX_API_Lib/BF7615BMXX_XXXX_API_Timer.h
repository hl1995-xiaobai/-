#ifndef __BF7615BMXX_XXXX_API_TIMER_H__
#define __BF7615BMXX_XXXX_API_TIMER_H__


#define	Timer0_EN				1	//Timer0使能配置，		 			1:使能编译，0:不使能编译
#define	Timer1_EN				1	//Timer1使能配置，		 			1:使能编译，0:不使能编译
#define	Timer2_EN				0	//Timer2使能配置，		 			1:使能编译，0:不使能编译
#define	Timer3_EN				0	//Timer3使能配置，		 			1:使能编译，0:不使能编译


#define T0_IE_SET  IEN0 |= 0x02//开Timer0中断使能 
#define T0_IE_CLR  IEN0 &= ~0x02//关Timer0中断使能
#define T0_IP_SET  IPL0 |= 0x02//设置Timer0中断优级为高
#define T0_IP_CLR  IPL0 &= ~0X02//设置Timer0中断优级为低
#define T0_CT_MODE(x)  {TMOD &= ~(0x08);TMOD |= (0x08&(x<<3));}//Timer0定时/计数模式选择0为定时模式，1为计数模式
#define T0_MODE_SET(x) {TMOD &= ~(0x03);TMOD |= (0x03&(x<<0));}//Timer0定时模式选择：0：13bit定时或计数模式，1：16bit定时或10bit计数模式，2：8bit重载定时或计数模式，3：8bit定时或计数和8bit定时模式 tiemr0_clk=(1/12)*sys_clk
#define T0_INT_FLAG_CLR TCON  &= ~0X20//清除Timer0中断标志
#define T0_RUN TCON |= 0X10// 1为开启Timer0
#define T0_STOP TCON &= ~0X10//0为停止Timer0

#define T1_IE_SET  IEN0 |= 0x08//开Timer1中断使能 
#define T1_IE_CLR  IEN0 &= ~0x08//关Timer1中断使能
#define T1_IP_SET  IPL0  |= 0x08//设置Timer1中断优级为高
#define T1_IP_CLR  IPL0 &= ~0X08//设置Timer1中断优级为低
#define T1_CT_MODE(x)  {TMOD &= ~(0x80);TMOD |= (0x80&(x<<7));}//Timer1定时/计数模式选择0为定时模式，1为计数模式
#define T1_MODE_SET(x) {TMOD &= ~(0x30);TMOD |= (0x30&(x<<4));}//Timer1定时模式选择：0：13bit定时或计数模式，1：16bit定时或计数模式，2：8bit重载定时或计数模式， tiemr1_clk=(1/12)*sys_clk
#define T1_INT_FLAG_CLR TCON &= ~0X80//清除Timer1中断标志
#define T1_RUN TCON |= 0X40//1为开启 Timer1
#define T1_STOP TCON &= ~0X40//0为停止Timer1

#define T2_MODE 0x02
#define T2_SART 0x02
#define T2_CLK  0x04 

#define T2_CLK_SET(x) {TIMER2_CFG &= ~(0x04);TIMER2_CFG |= (0x04&(x<<2));}//Timer2定时时钟选择：0：内部RC32.7KHz，1：外部晶振32768Hz
#define T2_XTAL_SET(x) {REG_ADDR = 0x2D;REG_DATA &= ~(0x10);REG_DATA |= (0x10&(x<<4));}//Timer2 外部晶振开关,1为关，0为开
#define T2_IE_SET IEN1 |= 0x80//开Timer2中断使能 
#define T2_IE_CLR IEN1 &= ~0x80//关Timer2中断使能
#define T2_IP_SET IPL1 |= 0x80//设置Timer2中断优级为高
#define T2_IP_CLR IPL1 &= ~0x80//设置Timer2中断优级为低
#define T2_MODE_SET(x) 		 {TIMER2_CFG &= ~(0x02);TIMER2_CFG |= (0x02&(x<<1));}//Timer2定时模式选择：0：手动重载模式，1：1自动重载模式
#define T2_CNT_MODE_SET(x) {TIMER2_CFG &= ~(0x08);TIMER2_CFG |= (0x08&(x<<3));}//Timer2定时步进模式选择：0：一个时钟步进，1：65536个时钟步进
#define T2_INT_FLAG_CLR IRCON1 &= ~0x80;INT_PE_STAT = ~0x08//清除Timer2中断标志
#define T2_RUN  TIMER2_CFG |= 0X01//1为开启Timer2
#define T2_STOP TIMER2_CFG &= ~0X01//0为停止Timer2


#define T3_CLK_DIV_SET(x) {TIMER3_CFG &= ~(0x04);TIMER3_CFG |= (0x04&(x<<2));}//Timer3定时时钟分频选择：0：24MHz/12，1：24MHz/4
#define T3_IE_SET IEN2 |= 0x10//开Timer3中断使能 
#define T3_IE_CLR IEN2 &= ~0x10//关Timer3中断使能
#define T3_IP_SET IPL2 |= 0x10//设置Timer3中断优级为高
#define T3_IP_CLR IPL2 &= ~0X10//设置Timer3中断优级为低
#define T3_MODE_SET(x) {TIMER3_CFG &= ~(0x02);TIMER3_CFG |= (0x02&(x<<1));}//Timer3定时模式选择：0：手动重载模式，1：1自动重载模式
#define T3_INT_FLAG_CLR IRCON2 &= ~0x10//清除Timer3中断标志
#define T3_RUN  TIMER3_CFG |= 0X01//1为开启Timer3
#define T3_STOP TIMER3_CFG &= ~0X01//0为停止Timer3

#if Timer0_EN
extern void Timer0_Init(uint Timer0Us);
extern uint xdata ctk_soft_reset_max_count;
extern uint xdata sclen_soft_reset_count;
extern uint xdata sclen_soft_reset_max_count;

extern uchar Test;
#endif

#if Timer1_EN
extern void Timer1_Init(uint Timer1Us);
#endif

#if Timer2_EN
extern void Timer2_Init(unsigned int Timer2Ms,bit timer2_clk_sel);
#endif

#if Timer3_EN
extern void Timer3_Init(uint Timer3Us,bit timer3_clk_div);
#endif
#if Timer0_EN
	extern uchar TH0_Reload;
	extern uchar TL0_Reload;
#endif

#if Timer1_EN
	extern uchar TH1_Reload;
	extern uchar TL1_Reload;
#endif

#if Timer2_EN
	extern uchar TH2_Reload;
	extern uchar TL2_Reload;
#endif

#if Timer3_EN
	extern uchar TH3_Reload;
	extern uchar TL3_Reload;
#endif

#endif