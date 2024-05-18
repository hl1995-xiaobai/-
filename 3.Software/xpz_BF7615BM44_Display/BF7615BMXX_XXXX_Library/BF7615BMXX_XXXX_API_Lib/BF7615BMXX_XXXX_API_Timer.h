#ifndef __BF7615BMXX_XXXX_API_TIMER_H__
#define __BF7615BMXX_XXXX_API_TIMER_H__


#define	Timer0_EN				1	//Timer0ʹ�����ã�		 			1:ʹ�ܱ��룬0:��ʹ�ܱ���
#define	Timer1_EN				1	//Timer1ʹ�����ã�		 			1:ʹ�ܱ��룬0:��ʹ�ܱ���
#define	Timer2_EN				0	//Timer2ʹ�����ã�		 			1:ʹ�ܱ��룬0:��ʹ�ܱ���
#define	Timer3_EN				0	//Timer3ʹ�����ã�		 			1:ʹ�ܱ��룬0:��ʹ�ܱ���


#define T0_IE_SET  IEN0 |= 0x02//��Timer0�ж�ʹ�� 
#define T0_IE_CLR  IEN0 &= ~0x02//��Timer0�ж�ʹ��
#define T0_IP_SET  IPL0 |= 0x02//����Timer0�ж��ż�Ϊ��
#define T0_IP_CLR  IPL0 &= ~0X02//����Timer0�ж��ż�Ϊ��
#define T0_CT_MODE(x)  {TMOD &= ~(0x08);TMOD |= (0x08&(x<<3));}//Timer0��ʱ/����ģʽѡ��0Ϊ��ʱģʽ��1Ϊ����ģʽ
#define T0_MODE_SET(x) {TMOD &= ~(0x03);TMOD |= (0x03&(x<<0));}//Timer0��ʱģʽѡ��0��13bit��ʱ�����ģʽ��1��16bit��ʱ��10bit����ģʽ��2��8bit���ض�ʱ�����ģʽ��3��8bit��ʱ�������8bit��ʱģʽ tiemr0_clk=(1/12)*sys_clk
#define T0_INT_FLAG_CLR TCON  &= ~0X20//���Timer0�жϱ�־
#define T0_RUN TCON |= 0X10// 1Ϊ����Timer0
#define T0_STOP TCON &= ~0X10//0ΪֹͣTimer0

#define T1_IE_SET  IEN0 |= 0x08//��Timer1�ж�ʹ�� 
#define T1_IE_CLR  IEN0 &= ~0x08//��Timer1�ж�ʹ��
#define T1_IP_SET  IPL0  |= 0x08//����Timer1�ж��ż�Ϊ��
#define T1_IP_CLR  IPL0 &= ~0X08//����Timer1�ж��ż�Ϊ��
#define T1_CT_MODE(x)  {TMOD &= ~(0x80);TMOD |= (0x80&(x<<7));}//Timer1��ʱ/����ģʽѡ��0Ϊ��ʱģʽ��1Ϊ����ģʽ
#define T1_MODE_SET(x) {TMOD &= ~(0x30);TMOD |= (0x30&(x<<4));}//Timer1��ʱģʽѡ��0��13bit��ʱ�����ģʽ��1��16bit��ʱ�����ģʽ��2��8bit���ض�ʱ�����ģʽ�� tiemr1_clk=(1/12)*sys_clk
#define T1_INT_FLAG_CLR TCON &= ~0X80//���Timer1�жϱ�־
#define T1_RUN TCON |= 0X40//1Ϊ���� Timer1
#define T1_STOP TCON &= ~0X40//0ΪֹͣTimer1

#define T2_MODE 0x02
#define T2_SART 0x02
#define T2_CLK  0x04 

#define T2_CLK_SET(x) {TIMER2_CFG &= ~(0x04);TIMER2_CFG |= (0x04&(x<<2));}//Timer2��ʱʱ��ѡ��0���ڲ�RC32.7KHz��1���ⲿ����32768Hz
#define T2_XTAL_SET(x) {REG_ADDR = 0x2D;REG_DATA &= ~(0x10);REG_DATA |= (0x10&(x<<4));}//Timer2 �ⲿ���񿪹�,1Ϊ�أ�0Ϊ��
#define T2_IE_SET IEN1 |= 0x80//��Timer2�ж�ʹ�� 
#define T2_IE_CLR IEN1 &= ~0x80//��Timer2�ж�ʹ��
#define T2_IP_SET IPL1 |= 0x80//����Timer2�ж��ż�Ϊ��
#define T2_IP_CLR IPL1 &= ~0x80//����Timer2�ж��ż�Ϊ��
#define T2_MODE_SET(x) 		 {TIMER2_CFG &= ~(0x02);TIMER2_CFG |= (0x02&(x<<1));}//Timer2��ʱģʽѡ��0���ֶ�����ģʽ��1��1�Զ�����ģʽ
#define T2_CNT_MODE_SET(x) {TIMER2_CFG &= ~(0x08);TIMER2_CFG |= (0x08&(x<<3));}//Timer2��ʱ����ģʽѡ��0��һ��ʱ�Ӳ�����1��65536��ʱ�Ӳ���
#define T2_INT_FLAG_CLR IRCON1 &= ~0x80;INT_PE_STAT = ~0x08//���Timer2�жϱ�־
#define T2_RUN  TIMER2_CFG |= 0X01//1Ϊ����Timer2
#define T2_STOP TIMER2_CFG &= ~0X01//0ΪֹͣTimer2


#define T3_CLK_DIV_SET(x) {TIMER3_CFG &= ~(0x04);TIMER3_CFG |= (0x04&(x<<2));}//Timer3��ʱʱ�ӷ�Ƶѡ��0��24MHz/12��1��24MHz/4
#define T3_IE_SET IEN2 |= 0x10//��Timer3�ж�ʹ�� 
#define T3_IE_CLR IEN2 &= ~0x10//��Timer3�ж�ʹ��
#define T3_IP_SET IPL2 |= 0x10//����Timer3�ж��ż�Ϊ��
#define T3_IP_CLR IPL2 &= ~0X10//����Timer3�ж��ż�Ϊ��
#define T3_MODE_SET(x) {TIMER3_CFG &= ~(0x02);TIMER3_CFG |= (0x02&(x<<1));}//Timer3��ʱģʽѡ��0���ֶ�����ģʽ��1��1�Զ�����ģʽ
#define T3_INT_FLAG_CLR IRCON2 &= ~0x10//���Timer3�жϱ�־
#define T3_RUN  TIMER3_CFG |= 0X01//1Ϊ����Timer3
#define T3_STOP TIMER3_CFG &= ~0X01//0ΪֹͣTimer3

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