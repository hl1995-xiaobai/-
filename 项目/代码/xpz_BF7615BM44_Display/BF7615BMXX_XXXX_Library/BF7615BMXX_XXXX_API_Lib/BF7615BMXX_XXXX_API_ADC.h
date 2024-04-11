#ifndef __BF7615BMXX_XXXX_API_ADC_H__
#define __BF7615BMXX_XXXX_API_ADC_H__



/******************************************ADC参数配置************************************/

#define	ADC_MODE		1		//ADC获取数据模式						1:查询模式，0:中断模式
#define ADC_NUM 	 	0//ADC_NUM//1~45：配置最多ADC开启数,ADC_NUM数要与ADC_SELXX开启的数对应

#define ADC_SEL00 0x00//[bit0-bit6]-ADC00~ADC06
#define ADC_SEL01 0x00//[bit0-bit7]-ADC07~ADC14
#define ADC_SEL02 0x00//[bit0-bit7]-ADC15~ADC22
#define ADC_SEL03 0x00//[bit0-bit7]-ADC23~ADC30
#define ADC_SEL04 0x00//[bit0-bit7]-ADC31~ADC38
#define ADC_SEL05 0x00//[bit0-bit4]-ADC39~ADC43

#define ADC_SAMPT					255	//ADC采样时间配置选择，   	bit[7:0],(0~255)采样时间为(ADC_SPT+1)*4*T_adc_clk
#define ADC_FLTER					1		//0:不加RC滤波；1：加RC滤波；//20-07-20
#define ADC_CALW					3		//采样延时时间选择, bit[5:4](0~3)：0:0(ADC_CLK),1:2(ADC_CLK),1:4(ADC_CLK),2:8(ADC_CLK)//20-07-20
#define ADC_CKV						3		//模拟输入信号时钟分频选择，bit[3:2],(0~3)-(12MhHz,8MHz,4MHz,2MHz)
#define ADC_ADCK					3		//ADC分频选择，							bit[1:0],(0~3)-(8MHz,6MhHz,4MHz,3MHz)
#define ADC_WAIT					31	//转换完毕距离转换时间选择，bit[6:2],(0~31)(X+3)*T_adc_clk,需要(X+3)T_adc_clk > 4*T_ADC_ANCK
#define ADC_OFFSETI					3		//ADC偏置电流大小选择，			bit[1:0],(0~3)(4uA,4uA,5uA,5uA)
#define ADC_SAMBG					1		//采样时序与比较时序间隔选择，bit[6],(0~1),0:间隔0(ADC_CLK)；1：间隔1(ADC_CLK);//20-07-20
#define ADC_VIN						1		//ADC内部通道输入电压选择：00：1.362V;01:2.253V;10:3.111V;11:4.082V;//20-09-15
#define ADC_VREF					1		//参考源电压选择：0：VCC;1:ADC_VREF
#define ADC_VREF_VOL			1		//参考电压选择ADC_VREF：0：2V;1:4V

#if (ADC_MODE == 0)

/***ADC中断模式时,SCAN_ADCXX扫描排序<=ADC_NUM,SCAN_ADCXX:0~44****44为ADC内部通道，ADC_NUM通道内有效*****/
#define SCAN_ADC00 7
#define SCAN_ADC01 5
#define SCAN_ADC02 6
#define SCAN_ADC03 7
                
#define SCAN_ADC04 44
#define SCAN_ADC05 5
#define SCAN_ADC06 6
#define SCAN_ADC07 7

#define SCAN_ADC08 8
#define SCAN_ADC09 9
#define SCAN_ADC10 10
#define SCAN_ADC11 11

#define SCAN_ADC12 16
#define SCAN_ADC13 17
#define SCAN_ADC14 18
#define SCAN_ADC15 19
#define SCAN_ADC16 20
#define SCAN_ADC17 21
#define SCAN_ADC18 22
#define SCAN_ADC19 23

#define SCAN_ADC20 24
#define SCAN_ADC21 25
#define SCAN_ADC22 26
#define SCAN_ADC23 27

#define SCAN_ADC24 28
#define SCAN_ADC25 29
#define SCAN_ADC26 30
#define SCAN_ADC27 31

#define SCAN_ADC28 32
#define SCAN_ADC29 33
#define SCAN_ADC30 34
#define SCAN_ADC31 35

#define SCAN_ADC32 36
#define SCAN_ADC33 37
#define SCAN_ADC34 38
#define SCAN_ADC35 39
#define SCAN_ADC36 40
#define SCAN_ADC37 41
#define SCAN_ADC38 42
#define SCAN_ADC39 43

#define SCAN_ADC40 44
#define SCAN_ADC41 45
#define SCAN_ADC42 46
#define SCAN_ADC43 47
#define SCAN_ADC44 44
#endif



/******************************************ADC参数配置************************************/


#define ADC_IE_SET IEN1 |= 0x10																	//开ADC中断使能
#define ADC_IE_CLR IEN1 &= ~0x10																//关ADC中断使能
#define ADC_IP_SET IPL1  |= 0x10																//设置ADC中断优先级为高
#define ADC_IP_CLR IPL1 &= ~0x10																//设置ADC中断优先级为低
#define ADC_INT_FLAG_CLR IRCON1 &= ~0x10												// 清除ADC中断标志位


#define ADC_IO_CGF0(x)	 			{REG_ADDR = 0x2A;REG_DATA &= ~(0x7F);REG_DATA |= (0x7F&x);TRISH |= (0x7F&(x>>0));}//ADC0~ADC6与IO功能选择，对应的位为1为ADC功能，0为IO功能
#define ADC_IO_CGF1(x)	 			{REG_ADDR = 0x53;REG_DATA &= ~(0xFF);REG_DATA |= (0xFF&x);TRISH |= (0x80&(x<<7));TRISA |= (0x0F&(x>>1));TRISB |= (0x07&(x>>5));}//ADC7~ADC14与IO功能选择，对应的位为1为ADC功能，0为IO功能
#define ADC_IO_CGF2(x)	 			{REG_ADDR = 0x54;REG_DATA &= ~(0xFF);REG_DATA |= (0xFF&x);TRISB |= (0xF8&(x<<3));TRISC |= (0x07&(x>>5));}//ADC15~ADC22与IO功能选择，对应的位为1为ADC功能，0为IO功能
#define ADC_IO_CGF3(x)	 			{REG_ADDR = 0x55;REG_DATA &= ~(0xFF);REG_DATA |= (0xFF&x);TRISC |= (0xF8&(x<<3));TRISE |= (0x07&(x>>5));}//ADC23~ADC30与IO功能选择，对应的位为1为ADC功能，0为IO功能
#define ADC_IO_CGF4(x)	 			{REG_ADDR = 0x56;REG_DATA &= ~(0xFF);REG_DATA |= (0xFF&x);TRISE |= (0xF8&(x<<3));TRISF |= (0x70&(x>>1));}//ADC31~ADC38与IO功能选择，对应的位为1为ADC功能，0为IO功能
#define ADC_IO_CGF5(x)	 			{REG_ADDR = 0x57;REG_DATA &= ~(0x1F);REG_DATA |= (0x1F&x);TRISF |= (0x80&(x<<7));TRISG |= (0x0F&(x>>1));}//ADC39~ADC43与IO功能选择，对应的位为1为ADC功能，0为IO功能

#define ADC_SAMP_SET(x)			ADC_SPT = x																			//ADC采样时间配置选择，     bit[7:0]，(0~255)采样时间为(ADC_SPT+1)*4*T_adc_clk
#define ADC_FLTER_SET(x)		{ADCCKC &= ~(0x80);ADCCKC |= (0x80&(x<<7));}		//ADC滤波选择，bit[7],(0~1),0:不加RC滤波；1：加RC滤波；//20-07-20
#define ADC_SAMBG_SET(x)		{ADCCKC &= ~(0x40);ADCCKC |= (0x40&(x<<6));}		//采样时序与比较时序间隔选择，bit[6],(0~1),0:间隔0(ADC_CLK)；1：间隔1(ADC_CLK);//20-07-20

#define ADC_WNUM_SET(x)			{REG_ADDR = 0x32;REG_DATA &= ~(0x7C);REG_DATA |= (0x7C&(x<<2));}//转换完毕距离转换时间选择，bit[6:2],(0~31)(X+3)*T_adc_clk,需要(X+3)*T_adc_clk > 4*ADC_ANCK
#define ADC_CALW_SET(x) 		{ADCCKC &= ~(0x30);ADCCKC |= (0x30&(x<<4));}		//采样延时时间选择, bit[5:4](0~3)：0:0(ADC_CLK),1:2(ADC_CLK),1:4(ADC_CLK),2:8(ADC_CLK)//20-07-20
#define ADC_CKV_SET(x) 			{ADCCKC &= ~(0x0C);ADCCKC |= (0x0C&(x<<2));}		//模拟输入信号时钟分频选择，bit[3:2],(0~3)-(12MHz,8MhHz,4MHz,2MHz)
#define ADC_ADCK_SET(x) 		{ADCCKC &= ~(0x03);ADCCKC |= (0x03&(x<<0));}		//ADC分频选择，							bit[1:0],(0~3)-(8MHz,6MhHz,4MHz,3MHz)
#define ADC_OFFSETI_SET(x) 	{REG_ADDR = 0x32;REG_DATA &= ~(0x03);REG_DATA |= (0x03&(x<<0));}//ADC偏置电流大小选择，			bit[1:0],(0~3)(4uA,4uA,5uA,5uA)
#define ADC_PD(x) 					{REG_ADDR = 0x2D;REG_DATA &= ~(0x01);REG_DATA |= (0x01&x);}//0为正常工作；1为不工作
#define ADC_CTRL(x) 				{REG_ADDR = 0x42;REG_DATA &= ~(0x03);REG_DATA |= (0x03&x);}//ADC比较器失调消除：1为时序1，2为时序2,5为时序3
#define ADC_VIN_SEL(x) 			{REG_ADDR = 0x42;REG_DATA &= ~(0x0C);REG_DATA |= (0x0C&(x<<2));}//ADC内部通道输入电压选择：00：1.362V;01:2.253V;10:3.111V;11:4.082V//20-07-20
#define ADC_VREF_VOL_SEL(x) {REG_ADDR = 0x42;REG_DATA &= ~(0x10);REG_DATA |= (0x10&(x<<4));}//参考电压选择：0：2V;1:4V//20-07-20
#define ADC_VREF_SEL(x) 		{REG_ADDR = 0x42;REG_DATA &= ~(0x20);REG_DATA |= (0x20&(x<<5));}//参考源电压选择：0：VCC;1:ADC_RREF//20-07-20


#define ADC_ADDR_SET(x)	 {ADC_SCAN_CFG &= ~(0x7E);ADC_SCAN_CFG |= (0x7E&(x<<1));}//ADC通道地址选择，			bit[6:1],(0~43)-(ADC0~ADC43)//20-07-20
#define ADC_SCAN_EN	 	 	 {ADC_SCAN_CFG &= ~0x01;ADC_SCAN_CFG |= 0x01;}									//ADC扫描开启，				bit[0],1为开启，硬件清零
#define ADC_SCAN_CLR	 	 ADC_SCAN_CFG &= ~0x01								//ADC扫描关闭，				bit[0],0为关闭，硬件清零

#define ADC_IS_OPEN ((ADC_SEL00 != 0)||(ADC_SEL01 != 0)||(ADC_SEL02 != 0)||(ADC_SEL03 != 0)||(ADC_SEL04 != 0)||(ADC_SEL05 != 0))


#if ADC_IS_OPEN

	extern void ADC_Init(void);

	#if (ADC_MODE == 1)	
	extern uint Get_ADC(uchar adc_ch);
	#endif

	extern bit adc_scan_done;
#endif


#if ADC_IS_OPEN

	
	#if ADC_MODE
	extern bit ADC_Start_Flag;
	extern uint  xdata ADC_Rest_Max_Count;
	extern uint  xdata ADC_Start_Count;
	extern void ADC_Reset_Count(void);
	#endif
	
	#if (ADC_MODE == 0)
		#if ADC_NUM
		extern uint 	xdata adc_data[];
		extern unsigned char code 	ADC_CH[];
		#endif
	#endif
	
	extern uint Get_ADC_Vref(uchar vref);
	extern uint Get_Inner_ADC_Vol(void);
	
#endif

#endif