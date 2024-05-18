#ifndef __BF7615BMXX_XXXX_API_LVDT_H__
#define __BF7615BMXX_XXXX_API_LVDT_H__


#define	VolDet_EN								1//降压检测使能配置	 				1:使能编译，0:不使能编译
#define	VolDet_COUNT						4	//降压检测计时VolDet_COUNT*time0定时//根据实际调试设置防抖次数

#define LVDT_IE_SET IEN2 |= 0x02												//开LVDT中断使能
#define LVDT_IE_CLR IEN2 &= ~0x02												//关LVDT中断使能
#define LVDT_IP_SET IPL2  |= 0x02												//设置LVDT中断优先级为高
#define LVDT_IP_CLR IPL2 &= ~0x02												//设置LVDT中断优先级为低
#define LVDT_INT_FLAG_CLR 			IRCON2 &= ~0x02						//清除低电压检测中断标志位
#define LVDT_INT_DOWN_FLAG_CLR 	INT_POBO_STAT &= ~0x01		//清除LVDT电压下降中断标志位
#define LVDT_INT_UP_FLAG_CLR 		INT_POBO_STAT &= ~0x02		//清除LVDT电压上升中断标志位
#define LVDT_ON_OFF_SET(x) {REG_ADDR = 0x2D;REG_DATA &= ~(0x40);REG_DATA |= (0x40&(x<<6));}//0为开启LVDT检测模块,1为关闭LVDT检测模块
#define LVDT_VOL_SET(x) 	 {REG_ADDR = 0x2C;REG_DATA &= ~(0x03);REG_DATA |= (0x03&(x<<0));}//设置低电压升检测点:(0-2.7V)-(1-3.0V)-(2-3.8V)


#if	VolDet_EN
	extern bit Low_Volotage_Flag;
	extern bit Low_Volotage_Flag_Confirm;
	extern bit Low_Volotage_Flag_First;
	extern uint xdata Low_Volotage_Flag_Count;
	extern uint xdata Low_Volotage_Flag_Confirm_count;
	extern void LVDT_Init(void);
#endif

#endif