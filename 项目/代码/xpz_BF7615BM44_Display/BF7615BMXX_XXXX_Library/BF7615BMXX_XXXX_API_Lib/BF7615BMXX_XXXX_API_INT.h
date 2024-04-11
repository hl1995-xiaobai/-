#ifndef __BF7615BMXX_XXXX_API_INT_H__
#define __BF7615BMXX_XXXX_API_INT_H__



#define	ExtInt0_EN			0	//外部中断0使能配置		 			1:使能编译，0:不使能编译
#define	ExtInt1_EN			0	//外部中断1使能配置		 			1:使能编译，0:不使能编译
#define	ExtInt2_EN			0	//外部中断2使能配置		 			1:使能编译，0:不使能编译
#define	ExtInt3_EN			0	//外部中断3使能配置		 			1:使能编译，0:不使能编译
#define	ExtInt4_EN			0	//外部中断4使能配置		 			1:使能编译，0:不使能编译

#define INT0_00_FUN_SET(x) {TRISH |= 0x01;DATAH |= 0x01;{REG_ADDR = 0x35;REG_DATA &= ~(0x01);REG_DATA |= (0x01&(x<<0));}}//0选择为IO口功能，1选择为INT中断功能 
#define INT0_01_FUN_SET(x) {TRISH |= 0x02;DATAH |= 0x02;{REG_ADDR = 0x35;REG_DATA &= ~(0x02);REG_DATA |= (0x02&(x<<1));}}//0选择为IO口功能，1选择为INT中断功能 
#define INT0_02_FUN_SET(x) {TRISH |= 0x04;DATAH |= 0x04;{REG_ADDR = 0x35;REG_DATA &= ~(0x04);REG_DATA |= (0x04&(x<<2));}}//0选择为IO口功能，1选择为INT中断功能 
#define INT0_03_FUN_SET(x) {TRISH |= 0x08;DATAH |= 0x08;{REG_ADDR = 0x35;REG_DATA &= ~(0x08);REG_DATA |= (0x08&(x<<3));}}//0选择为IO口功能，1选择为INT中断功能 
#define INT0_04_FUN_SET(x) {TRISH |= 0x10;DATAH |= 0x10;{REG_ADDR = 0x35;REG_DATA &= ~(0x10);REG_DATA |= (0x10&(x<<4));}}//0选择为IO口功能，1选择为INT中断功能 
#define INT0_05_FUN_SET(x) {TRISH |= 0x20;DATAH |= 0x20;{REG_ADDR = 0x35;REG_DATA &= ~(0x20);REG_DATA |= (0x20&(x<<5));}}//0选择为IO口功能，1选择为INT中断功能 
#define INT0_06_FUN_SET(x) {TRISH |= 0x40;DATAH |= 0x40;{REG_ADDR = 0x35;REG_DATA &= ~(0x40);REG_DATA |= (0x40&(x<<6));}}//0选择为IO口功能，1选择为INT中断功能 
#define INT0_07_FUN_SET(x) {TRISH |= 0x80;DATAH |= 0x80;{REG_ADDR = 0x35;REG_DATA &= ~(0x80);REG_DATA |= (0x80&(x<<7));}}//0选择为IO口功能，1选择为INT中断功能 
#define INT0_08_FUN_SET(x) {TRISB |= 0x01;DATAB |= 0x01;{REG_ADDR = 0x34;REG_DATA &= ~(0x01);REG_DATA |= (0x01&(x<<0));}}//0选择为IO口功能，1选择为INT中断功能 

#define INT0_IE_SET 	IEN0 |= 0x01//开INT0中断使能 
#define INT0_IE_CLR 	IEN0 &= ~0x01//关INT0中断使能
#define INT0_IP_SET 	IPL0 |= 0x01//设置INT0中断优级为高
#define INT0_IP_CLR 	IPL0 &= ~0X01//设置INT0中断优级为低
#define INT0_INT_FLAG_CLR TCON  &= ~0X02//清除INT0中断标志
#define INT0_POLO_SET(x) 		{REG_ADDR = 0x3A;REG_DATA &= ~(0x03);REG_DATA |= (0x03&x);}//0为双沿触发；1为下降沿触发；2为上升沿触发；
#define INT0_08_POLO_SET(x) {REG_ADDR = 0x39;REG_DATA &= ~(0x03);REG_DATA |= (0x03&x);}//0为双沿触发；1为下降沿触发；2为上升沿触发；

#define INT0_00_INT_FLAG_CLR EXINT_STAT  &= ~0X01//清除INT0_00中断标志
#define INT0_01_INT_FLAG_CLR EXINT_STAT  &= ~0X02//清除INT0_01中断标志
#define INT0_02_INT_FLAG_CLR EXINT_STAT  &= ~0X04//清除INT0_02中断标志
#define INT0_03_INT_FLAG_CLR EXINT_STAT  &= ~0X08//清除INT0_03中断标志
#define INT0_04_INT_FLAG_CLR EXINT_STAT  &= ~0X10//清除INT0_04中断标志
#define INT0_05_INT_FLAG_CLR EXINT_STAT  &= ~0X20//清除INT0_05中断标志
#define INT0_06_INT_FLAG_CLR EXINT_STAT  &= ~0X40//清除INT0_06中断标志
#define INT0_07_INT_FLAG_CLR EXINT_STAT  &= ~0X80//清除INT0_07中断标志
#define INT0_08_INT_FLAG_CLR INT_PE_STAT &= ~0X20//清除INT0_08中断标志

#define GET_INT0_FLAG(x) (EXINT_STAT&(0x01<<x))//Get INT0_07中断标志
#define GET_INT0_08_FLAG() (INT_PE_STAT&0x20)//Get INT0_08中断标志


#define INT1_FUN_SET(x) {TRISB |= 0x02;DATAB |= 0x02;{REG_ADDR = 0x34;REG_DATA &= ~(0x02);REG_DATA |= (0x02&(x<<1));}}//0选择为IO口功能，1选择为INT中断功能 
#define INT1_IE_SET 	IEN0 |= 0x04//开INT1中断使能 
#define INT1_IE_CLR 	IEN0 &= ~0x04//关INT1中断使能
#define INT1_IP_SET 	IPL0 |= 0x04//设置INT1中断优级为高
#define INT1_IP_CLR 	IPL0 &= ~0x04//设置INT1中断优级为低
#define INT1_INT_FLAG_CLR TCON  &= ~0x08//清除INT1中断标志
#define INT1_POLO_SET(x) {REG_ADDR = 0x39;REG_DATA &= ~(0x0C);REG_DATA |= (0x0C&(x<<2));}//0为双沿触发；1为下降沿触发；2为上升沿触发；
#define GET_INT1_FLAG() (TCON&0x08)//Get INT1中断标志


#define INT2_FUN_SET(x) {TRISB |= 0x04;DATAB |= 0x04;{REG_ADDR = 0x34;REG_DATA &= ~(0x04);REG_DATA |= (0x04&(x<<2));}}//0选择为IO口功能，1选择为INT中断功能 
#define INT2_IE_SET 	IEN1 |= 0x04//开INT2中断使能 
#define INT2_IE_CLR 	IEN1 &= ~0x04//关INT2中断使能
#define INT2_IP_SET 	IPL1 |= 0x04//设置INT2中断优级为高
#define INT2_IP_CLR 	IPL1 &= ~0X04//设置INT2中断优级为低
#define INT2_INT_FLAG_CLR IRCON1  &= ~0X04//清除INT2中断标志
#define INT2_POLO_SET(x) {REG_ADDR = 0x39;REG_DATA &= ~(0x30);REG_DATA |= (0x30&(x<<4));}//0为双沿触发；1为下降沿触发；2为上升沿触发；


#define INT3_FUN_SET(x) {TRISB |= 0x08;DATAB |= 0x08;{REG_ADDR = 0x34;REG_DATA &= ~(0x08);REG_DATA |= (0x08&(x<<3));}}//0选择为IO口功能，1选择为INT中断功能 
#define INT3_IE_SET 	IEN2 |= 0x40//开INT3中断使能 
#define INT3_IE_CLR 	IEN2 &= ~0x40//关INT3中断使能
#define INT3_IP_SET 	IPL2 |= 0x40//设置INT3中断优级为高
#define INT3_IP_CLR 	IPL2 &= ~0X40//设置INT3中断优级为低
#define INT3_INT_FLAG_CLR IRCON2  &= ~0X40//清除INT3中断标志
#define INT3_POLO_SET(x) {REG_ADDR = 0x39;REG_DATA &= ~(0xC0);REG_DATA |= (0xC0&(x<<6));}//0为双沿触发；1为下降沿触发；2为上升沿触发；


#define INT4_07_FUN_SET(x) {TRISE |= 0x10;DATAE |= 0x10;{REG_ADDR = 0x36;REG_DATA &= ~(0x80);REG_DATA |= (0x80&(x<<7));}}//0选择为IO口功能，1选择为INT中断功能 

#define INT4_08_FUN_SET(x) {TRISE |= 0x20;DATAE |= 0x20;{REG_ADDR = 0x37;REG_DATA &= ~(0x01);REG_DATA |= (0x01&(x<<0));}}//0选择为IO口功能，1选择为INT中断功能 
#define INT4_09_FUN_SET(x) {TRISE |= 0x40;DATAE |= 0x40;{REG_ADDR = 0x37;REG_DATA &= ~(0x02);REG_DATA |= (0x02&(x<<1));}}//0选择为IO口功能，1选择为INT中断功能 
#define INT4_10_FUN_SET(x) {TRISE |= 0x80;DATAE |= 0x80;{REG_ADDR = 0x37;REG_DATA &= ~(0x04);REG_DATA |= (0x04&(x<<2));}}//0选择为IO口功能，1选择为INT中断功能 
#define INT4_15_FUN_SET(x) {TRISF |= 0x10;DATAF |= 0x10;{REG_ADDR = 0x37;REG_DATA &= ~(0x80);REG_DATA |= (0x80&(x<<7));}}//0选择为IO口功能，1选择为INT中断功能 

#define INT4_16_FUN_SET(x) {TRISF |= 0x20;DATAF |= 0x20;{REG_ADDR = 0x38;REG_DATA &= ~(0x01);REG_DATA |= (0x01&(x<<0));}}//0选择为IO口功能，1选择为INT中断功能 
#define INT4_17_FUN_SET(x) {TRISF |= 0x40;DATAF |= 0x40;{REG_ADDR = 0x38;REG_DATA &= ~(0x02);REG_DATA |= (0x02&(x<<1));}}//0选择为IO口功能，1选择为INT中断功能 
#define INT4_18_FUN_SET(x) {TRISF |= 0x80;DATAF |= 0x80;{REG_ADDR = 0x38;REG_DATA &= ~(0x04);REG_DATA |= (0x04&(x<<2));}}//0选择为IO口功能，1选择为INT中断功能 
#define INT4_19_FUN_SET(x) {TRISG |= 0x01;DATAG |= 0x01;{REG_ADDR = 0x38;REG_DATA &= ~(0x08);REG_DATA |= (0x08&(x<<3));}}//0选择为IO口功能，1选择为INT中断功能 
#define INT4_20_FUN_SET(x) {TRISG |= 0x02;DATAG |= 0x02;{REG_ADDR = 0x38;REG_DATA &= ~(0x10);REG_DATA |= (0x10&(x<<4));}}//0选择为IO口功能，1选择为INT中断功能 
#define INT4_21_FUN_SET(x) {TRISG |= 0x04;DATAG |= 0x04;{REG_ADDR = 0x38;REG_DATA &= ~(0x20);REG_DATA |= (0x20&(x<<5));}}//0选择为IO口功能，1选择为INT中断功能 
#define INT4_22_FUN_SET(x) {TRISG |= 0x08;DATAG |= 0x08;{REG_ADDR = 0x38;REG_DATA &= ~(0x40);REG_DATA |= (0x40&(x<<6));}}//0选择为IO口功能，1选择为INT中断功能 

#define INT4_IE_SET 	IEN2 |= 0x80//开INT4中断使能 
#define INT4_IE_CLR 	IEN2 &= ~0x80//关INT4中断使能
#define INT4_IP_SET 	IPL2 |= 0x80//设置INT4中断优级为高
#define INT4_IP_CLR 	IPL2 &= ~0X80//设置INT4中断优级为低
#define INT4_INT_FLAG_CLR IRCON2  &= ~0X80//清除INT4中断标志
#define INT4_POLO_SET(x) {REG_ADDR = 0x3A;REG_DATA &= ~(0x04);REG_DATA |= (0x04&(x<<2));}//1为上升触发；0为下降沿触发；


#if ExtInt0_EN
extern void ExtInt0_Init(uchar TriggerMode,uint int0_sel);
#endif

#if ExtInt1_EN
extern void ExtInt1_Init(uchar TriggerMode);
#endif

#if ExtInt2_EN
extern void ExtInt2_Init(uchar TriggerMode);
#endif

#if ExtInt3_EN
extern void ExtInt3_Init(uchar TriggerMode);
#endif

#if ExtInt4_EN
extern void ExtInt4_Init(uchar TriggerMode,ulong int4_sel);
#endif

#endif