#ifndef __TOUCH_MCU_INIT_H__
#define __TOUCH_MCU_INIT_H__

/*��ģ�鹦��Ԥ��������*/
#define	SYSCLK_SEL			0//ϵͳʱ��ѡ��0-12MHz,1-8MHZ,2-4MHz,3-1MHz

#define DELAY_MS_EN 		1//ms��ʱ������			 			1:ʹ�ܱ��룬0:��ʹ�ܱ���
#define DELAY_US_EN 		0//us��ʱ������			 			1:ʹ�ܱ��룬0:��ʹ�ܱ���
#define POW_UP_DELAY 		0//�ϵ���ʱ���أ�		 			1:ʹ�ܱ��룬0:��ʹ�ܱ���


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
	#define SYS_CLK  		0//SYS-����Mhz
	#define SYS_CLK_FRE 16
#endif

//��������������߼Ĵ���ǰ����EA���ȶ������߲�������ٿ�EA����ֹ���������ж������ߵĵ�ַ�����ݱ��ж�,
//����ж��в����������߼Ĵ���ʱ�������ȶ�ȡ�������߼Ĵ�����ַ����������ʱ�����У�������������ɺ�,
//�ٽ��������߼Ĵ�����ַ����ʱ�����л�ԭ��
#define Write_REG(reg_addr,reg_data) {REG_ADDR = reg_addr;REG_DATA =  reg_data;}//д�������߼Ĵ���
#define REG_SET(reg_addr,reg_data) 	 {REG_ADDR = reg_addr;REG_DATA |= reg_data;}//д1
#define REG_CLR(reg_addr,reg_data) 	 {REG_ADDR = reg_addr;REG_DATA &= reg_data;}//��0
#define Read_REG(reg_addr,reg_data)  {REG_ADDR = reg_addr;reg_data =  REG_DATA;}//��

#define SYS_CLK_SET(x)	{SYS_CLK_CFG &= ~(0x0E);SYS_CLK_CFG |= (0x0E&(x<<1));}//(0--12Mhz,1--08Mhz,2--04Mhz,3--01Mhz)
#define SYS_CLK_ON_OFF(x) {SYS_CLK_CFG &= ~(0x01);SYS_CLK_CFG |= (0x01&(x<<0));}//0Ϊ��ϵͳʱ�ӣ�1Ϊ��ϵͳʱ�� 
#define BOR_SET(x) {REG_ADDR = 0x2D;REG_DATA &= ~(0x20);REG_DATA |= (0x20&(x<<5));}//0Ϊ�����縴λ��1�ص��縴λ
#define SYS_WAIT_MODE_SET(x) {SYS_CLK_CFG &= ~(0x10);SYS_CLK_CFG |= (0x10&(x<<4));}//0Ϊ�˳�WAITģʽ��1Ϊ����WAITģʽ
#define PLL_WAKE_TIME_SET(x) {REG_ADDR = 0x30;REG_DATA &= ~(0x07);REG_DATA |= (0x07&(x<<0));}//����PPLʱ������0-7-(0.2ms~1ms)

#define WDT_TIMER(x) WDT_CTRL = x	 //����WDT���ʱ��(0~15--18ms~2.304S)7--2.304S
#define WDT_ON_OFF(x) WDT_EN = x	//������0x55ʱ�رտ��Ź�
#define WDT_IE_SET   IEN1 |= 0x80 	//��WDT�ж�ʹ��
#define WDT_IE_CLR   IEN1 &= ~0x80 	//��WDT�ж�ʹ��
#define WDT_IP_SET   IPL1 |= 0x80 	//����WDT�ж��ż�Ϊ��
#define WDT_IP_CLR   IPL1 &= ~0x80 	//����WDT�ж��ż�Ϊ��
#define WDT_INT_FLAG_CLR IRCON1 &= ~0x80;INT_PE_STAT = ~0x10 // ���WDT�жϱ�־λ

#define PUSH_REG_ADDR_SFR() {addr_bak = REG_ADDR;}
#define POP_REG_ADDR_SFR()  {REG_ADDR = addr_bak;}
//����ж����в����������ߣ���Ҫ�ֳ�����REG_ADDR��ַ�Ĵ���

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
