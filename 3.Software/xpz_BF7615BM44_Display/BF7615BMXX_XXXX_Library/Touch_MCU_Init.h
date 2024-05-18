#ifndef __TOUCH_MCU_INIT_H__
#define __TOUCH_MCU_INIT_H__

/*各模块功能预编译配置*/
#define	SYSCLK_SEL			0//系统时钟选择0-12MHz,1-8MHZ,2-4MHz,3-1MHz

#define DELAY_MS_EN 		1//ms延时函数，			 			1:使能编译，0:不使能编译
#define DELAY_US_EN 		0//us延时函数，			 			1:使能编译，0:不使能编译
#define POW_UP_DELAY 		0//上电延时开关，		 			1:使能编译，0:不使能编译


#if   (SYSCLK_SEL == 0)//SYS-12Mhz
	#define SYS_CLK 4
	#define SYS_CLK_FRE 12
#elif (SYSCLK_SEL == 1)//SYS-08Mhz
	#define SYS_CLK 5
	#define SYS_CLK_FRE 8
#elif (SYSCLK_SEL == 2)//SYS-04Mhz
	#define SYS_CLK 6
	#define SYS_CLK_FRE 4
#elif (SYSCLK_SEL == 3)//SYS-01Mhz
	#define SYS_CLK 7
	#define SYS_CLK_FRE 1
#else
	#define SYS_CLK  		0//SYS-其它Mhz
	#define SYS_CLK_FRE 16
#endif

//建议操作二级总线寄存器前，关EA，等二级总线操作完成再开EA，防止操作过程中二级总线的地址或数据被中断,
//如果中断中操作二级总线寄存器时，建议先读取二级总线寄存器地址，保存在临时变量中，操作级总线完成后,
//再将二级总线寄存器地址从临时变量中还原。
#define Write_REG(reg_addr,reg_data) {REG_ADDR = reg_addr;REG_DATA =  reg_data;}//写二级总线寄存器
#define REG_SET(reg_addr,reg_data) 	 {REG_ADDR = reg_addr;REG_DATA |= reg_data;}//写1
#define REG_CLR(reg_addr,reg_data) 	 {REG_ADDR = reg_addr;REG_DATA &= reg_data;}//清0
#define Read_REG(reg_addr,reg_data)  {REG_ADDR = reg_addr;reg_data =  REG_DATA;}//读

#define SYS_CLK_SET(x)	{SYS_CLK_CFG &= ~(0x0E);SYS_CLK_CFG |= (0x0E&(x<<1));}//(0--12Mhz,1--08Mhz,2--04Mhz,3--01Mhz)
#define SYS_CLK_ON_OFF(x) {SYS_CLK_CFG &= ~(0x01);SYS_CLK_CFG |= (0x01&(x<<0));}//0为开系统时钟，1为关系统时钟 
#define BOR_SET(x) {REG_ADDR = 0x2D;REG_DATA &= ~(0x20);REG_DATA |= (0x20&(x<<5));}//0为开掉电复位，1关掉电复位
#define SYS_WAIT_MODE_SET(x) {SYS_CLK_CFG &= ~(0x10);SYS_CLK_CFG |= (0x10&(x<<4));}//0为退出WAIT模式，1为进入WAIT模式
#define PLL_WAKE_TIME_SET(x) {REG_ADDR = 0x30;REG_DATA &= ~(0x07);REG_DATA |= (0x07&(x<<0));}//唤醒PPL时间设置0-7-(0.2ms~1ms)

#define WDT_TIMER(x) WDT_CTRL = x	 //设置WDT溢出时间(0~15--18ms~2.304S)7--2.304S
#define WDT_ON_OFF(x) WDT_EN = x	//仅等于0x55时关闭看门狗
#define WDT_IE_SET   IEN1 |= 0x80 	//开WDT中断使能
#define WDT_IE_CLR   IEN1 &= ~0x80 	//关WDT中断使能
#define WDT_IP_SET   IPL1 |= 0x80 	//设置WDT中断优级为高
#define WDT_IP_CLR   IPL1 &= ~0x80 	//设置WDT中断优级为低
#define WDT_INT_FLAG_CLR IRCON1 &= ~0x80;INT_PE_STAT = ~0x10 // 清除WDT中断标志位

#define PUSH_REG_ADDR_SFR() {addr_bak = REG_ADDR;}
#define POP_REG_ADDR_SFR()  {REG_ADDR = addr_bak;}
//如果中断中有操作二级总线，需要现场备份REG_ADDR地址寄存器

extern void Set_Sys_Clk(void);


extern void CFG_Check(void);	

#if ((DELAY_MS_EN == 1))
extern void Delay_Ms(uint ms);//1-1ms
#endif

#if(DELAY_US_EN == 1)
extern void Delay_Us(uint us);
#endif

#if(POW_UP_DELAY == 1)
extern void Pow_Up_Delay(uint ms);
#endif


extern void WDT_Init(void);
extern void Init_IO(void);
extern void Default_Set_IO(void);

extern void Trace_Mode_Init(void);
extern void Function_Init(void);
extern void MCU_Init(void);
extern void CTK_Init(void);

#endif  
