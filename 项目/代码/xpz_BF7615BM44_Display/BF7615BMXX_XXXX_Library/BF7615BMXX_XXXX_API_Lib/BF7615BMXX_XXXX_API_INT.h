#ifndef __BF7615BMXX_XXXX_API_INT_H__
#define __BF7615BMXX_XXXX_API_INT_H__



#define	ExtInt0_EN			0	//�ⲿ�ж�0ʹ������		 			1:ʹ�ܱ��룬0:��ʹ�ܱ���
#define	ExtInt1_EN			0	//�ⲿ�ж�1ʹ������		 			1:ʹ�ܱ��룬0:��ʹ�ܱ���
#define	ExtInt2_EN			0	//�ⲿ�ж�2ʹ������		 			1:ʹ�ܱ��룬0:��ʹ�ܱ���
#define	ExtInt3_EN			0	//�ⲿ�ж�3ʹ������		 			1:ʹ�ܱ��룬0:��ʹ�ܱ���
#define	ExtInt4_EN			0	//�ⲿ�ж�4ʹ������		 			1:ʹ�ܱ��룬0:��ʹ�ܱ���

#define INT0_00_FUN_SET(x) {TRISH |= 0x01;DATAH |= 0x01;{REG_ADDR = 0x35;REG_DATA &= ~(0x01);REG_DATA |= (0x01&(x<<0));}}//0ѡ��ΪIO�ڹ��ܣ�1ѡ��ΪINT�жϹ��� 
#define INT0_01_FUN_SET(x) {TRISH |= 0x02;DATAH |= 0x02;{REG_ADDR = 0x35;REG_DATA &= ~(0x02);REG_DATA |= (0x02&(x<<1));}}//0ѡ��ΪIO�ڹ��ܣ�1ѡ��ΪINT�жϹ��� 
#define INT0_02_FUN_SET(x) {TRISH |= 0x04;DATAH |= 0x04;{REG_ADDR = 0x35;REG_DATA &= ~(0x04);REG_DATA |= (0x04&(x<<2));}}//0ѡ��ΪIO�ڹ��ܣ�1ѡ��ΪINT�жϹ��� 
#define INT0_03_FUN_SET(x) {TRISH |= 0x08;DATAH |= 0x08;{REG_ADDR = 0x35;REG_DATA &= ~(0x08);REG_DATA |= (0x08&(x<<3));}}//0ѡ��ΪIO�ڹ��ܣ�1ѡ��ΪINT�жϹ��� 
#define INT0_04_FUN_SET(x) {TRISH |= 0x10;DATAH |= 0x10;{REG_ADDR = 0x35;REG_DATA &= ~(0x10);REG_DATA |= (0x10&(x<<4));}}//0ѡ��ΪIO�ڹ��ܣ�1ѡ��ΪINT�жϹ��� 
#define INT0_05_FUN_SET(x) {TRISH |= 0x20;DATAH |= 0x20;{REG_ADDR = 0x35;REG_DATA &= ~(0x20);REG_DATA |= (0x20&(x<<5));}}//0ѡ��ΪIO�ڹ��ܣ�1ѡ��ΪINT�жϹ��� 
#define INT0_06_FUN_SET(x) {TRISH |= 0x40;DATAH |= 0x40;{REG_ADDR = 0x35;REG_DATA &= ~(0x40);REG_DATA |= (0x40&(x<<6));}}//0ѡ��ΪIO�ڹ��ܣ�1ѡ��ΪINT�жϹ��� 
#define INT0_07_FUN_SET(x) {TRISH |= 0x80;DATAH |= 0x80;{REG_ADDR = 0x35;REG_DATA &= ~(0x80);REG_DATA |= (0x80&(x<<7));}}//0ѡ��ΪIO�ڹ��ܣ�1ѡ��ΪINT�жϹ��� 
#define INT0_08_FUN_SET(x) {TRISB |= 0x01;DATAB |= 0x01;{REG_ADDR = 0x34;REG_DATA &= ~(0x01);REG_DATA |= (0x01&(x<<0));}}//0ѡ��ΪIO�ڹ��ܣ�1ѡ��ΪINT�жϹ��� 

#define INT0_IE_SET 	IEN0 |= 0x01//��INT0�ж�ʹ�� 
#define INT0_IE_CLR 	IEN0 &= ~0x01//��INT0�ж�ʹ��
#define INT0_IP_SET 	IPL0 |= 0x01//����INT0�ж��ż�Ϊ��
#define INT0_IP_CLR 	IPL0 &= ~0X01//����INT0�ж��ż�Ϊ��
#define INT0_INT_FLAG_CLR TCON  &= ~0X02//���INT0�жϱ�־
#define INT0_POLO_SET(x) 		{REG_ADDR = 0x3A;REG_DATA &= ~(0x03);REG_DATA |= (0x03&x);}//0Ϊ˫�ش�����1Ϊ�½��ش�����2Ϊ�����ش�����
#define INT0_08_POLO_SET(x) {REG_ADDR = 0x39;REG_DATA &= ~(0x03);REG_DATA |= (0x03&x);}//0Ϊ˫�ش�����1Ϊ�½��ش�����2Ϊ�����ش�����

#define INT0_00_INT_FLAG_CLR EXINT_STAT  &= ~0X01//���INT0_00�жϱ�־
#define INT0_01_INT_FLAG_CLR EXINT_STAT  &= ~0X02//���INT0_01�жϱ�־
#define INT0_02_INT_FLAG_CLR EXINT_STAT  &= ~0X04//���INT0_02�жϱ�־
#define INT0_03_INT_FLAG_CLR EXINT_STAT  &= ~0X08//���INT0_03�жϱ�־
#define INT0_04_INT_FLAG_CLR EXINT_STAT  &= ~0X10//���INT0_04�жϱ�־
#define INT0_05_INT_FLAG_CLR EXINT_STAT  &= ~0X20//���INT0_05�жϱ�־
#define INT0_06_INT_FLAG_CLR EXINT_STAT  &= ~0X40//���INT0_06�жϱ�־
#define INT0_07_INT_FLAG_CLR EXINT_STAT  &= ~0X80//���INT0_07�жϱ�־
#define INT0_08_INT_FLAG_CLR INT_PE_STAT &= ~0X20//���INT0_08�жϱ�־

#define GET_INT0_FLAG(x) (EXINT_STAT&(0x01<<x))//Get INT0_07�жϱ�־
#define GET_INT0_08_FLAG() (INT_PE_STAT&0x20)//Get INT0_08�жϱ�־


#define INT1_FUN_SET(x) {TRISB |= 0x02;DATAB |= 0x02;{REG_ADDR = 0x34;REG_DATA &= ~(0x02);REG_DATA |= (0x02&(x<<1));}}//0ѡ��ΪIO�ڹ��ܣ�1ѡ��ΪINT�жϹ��� 
#define INT1_IE_SET 	IEN0 |= 0x04//��INT1�ж�ʹ�� 
#define INT1_IE_CLR 	IEN0 &= ~0x04//��INT1�ж�ʹ��
#define INT1_IP_SET 	IPL0 |= 0x04//����INT1�ж��ż�Ϊ��
#define INT1_IP_CLR 	IPL0 &= ~0x04//����INT1�ж��ż�Ϊ��
#define INT1_INT_FLAG_CLR TCON  &= ~0x08//���INT1�жϱ�־
#define INT1_POLO_SET(x) {REG_ADDR = 0x39;REG_DATA &= ~(0x0C);REG_DATA |= (0x0C&(x<<2));}//0Ϊ˫�ش�����1Ϊ�½��ش�����2Ϊ�����ش�����
#define GET_INT1_FLAG() (TCON&0x08)//Get INT1�жϱ�־


#define INT2_FUN_SET(x) {TRISB |= 0x04;DATAB |= 0x04;{REG_ADDR = 0x34;REG_DATA &= ~(0x04);REG_DATA |= (0x04&(x<<2));}}//0ѡ��ΪIO�ڹ��ܣ�1ѡ��ΪINT�жϹ��� 
#define INT2_IE_SET 	IEN1 |= 0x04//��INT2�ж�ʹ�� 
#define INT2_IE_CLR 	IEN1 &= ~0x04//��INT2�ж�ʹ��
#define INT2_IP_SET 	IPL1 |= 0x04//����INT2�ж��ż�Ϊ��
#define INT2_IP_CLR 	IPL1 &= ~0X04//����INT2�ж��ż�Ϊ��
#define INT2_INT_FLAG_CLR IRCON1  &= ~0X04//���INT2�жϱ�־
#define INT2_POLO_SET(x) {REG_ADDR = 0x39;REG_DATA &= ~(0x30);REG_DATA |= (0x30&(x<<4));}//0Ϊ˫�ش�����1Ϊ�½��ش�����2Ϊ�����ش�����


#define INT3_FUN_SET(x) {TRISB |= 0x08;DATAB |= 0x08;{REG_ADDR = 0x34;REG_DATA &= ~(0x08);REG_DATA |= (0x08&(x<<3));}}//0ѡ��ΪIO�ڹ��ܣ�1ѡ��ΪINT�жϹ��� 
#define INT3_IE_SET 	IEN2 |= 0x40//��INT3�ж�ʹ�� 
#define INT3_IE_CLR 	IEN2 &= ~0x40//��INT3�ж�ʹ��
#define INT3_IP_SET 	IPL2 |= 0x40//����INT3�ж��ż�Ϊ��
#define INT3_IP_CLR 	IPL2 &= ~0X40//����INT3�ж��ż�Ϊ��
#define INT3_INT_FLAG_CLR IRCON2  &= ~0X40//���INT3�жϱ�־
#define INT3_POLO_SET(x) {REG_ADDR = 0x39;REG_DATA &= ~(0xC0);REG_DATA |= (0xC0&(x<<6));}//0Ϊ˫�ش�����1Ϊ�½��ش�����2Ϊ�����ش�����


#define INT4_07_FUN_SET(x) {TRISE |= 0x10;DATAE |= 0x10;{REG_ADDR = 0x36;REG_DATA &= ~(0x80);REG_DATA |= (0x80&(x<<7));}}//0ѡ��ΪIO�ڹ��ܣ�1ѡ��ΪINT�жϹ��� 

#define INT4_08_FUN_SET(x) {TRISE |= 0x20;DATAE |= 0x20;{REG_ADDR = 0x37;REG_DATA &= ~(0x01);REG_DATA |= (0x01&(x<<0));}}//0ѡ��ΪIO�ڹ��ܣ�1ѡ��ΪINT�жϹ��� 
#define INT4_09_FUN_SET(x) {TRISE |= 0x40;DATAE |= 0x40;{REG_ADDR = 0x37;REG_DATA &= ~(0x02);REG_DATA |= (0x02&(x<<1));}}//0ѡ��ΪIO�ڹ��ܣ�1ѡ��ΪINT�жϹ��� 
#define INT4_10_FUN_SET(x) {TRISE |= 0x80;DATAE |= 0x80;{REG_ADDR = 0x37;REG_DATA &= ~(0x04);REG_DATA |= (0x04&(x<<2));}}//0ѡ��ΪIO�ڹ��ܣ�1ѡ��ΪINT�жϹ��� 
#define INT4_15_FUN_SET(x) {TRISF |= 0x10;DATAF |= 0x10;{REG_ADDR = 0x37;REG_DATA &= ~(0x80);REG_DATA |= (0x80&(x<<7));}}//0ѡ��ΪIO�ڹ��ܣ�1ѡ��ΪINT�жϹ��� 

#define INT4_16_FUN_SET(x) {TRISF |= 0x20;DATAF |= 0x20;{REG_ADDR = 0x38;REG_DATA &= ~(0x01);REG_DATA |= (0x01&(x<<0));}}//0ѡ��ΪIO�ڹ��ܣ�1ѡ��ΪINT�жϹ��� 
#define INT4_17_FUN_SET(x) {TRISF |= 0x40;DATAF |= 0x40;{REG_ADDR = 0x38;REG_DATA &= ~(0x02);REG_DATA |= (0x02&(x<<1));}}//0ѡ��ΪIO�ڹ��ܣ�1ѡ��ΪINT�жϹ��� 
#define INT4_18_FUN_SET(x) {TRISF |= 0x80;DATAF |= 0x80;{REG_ADDR = 0x38;REG_DATA &= ~(0x04);REG_DATA |= (0x04&(x<<2));}}//0ѡ��ΪIO�ڹ��ܣ�1ѡ��ΪINT�жϹ��� 
#define INT4_19_FUN_SET(x) {TRISG |= 0x01;DATAG |= 0x01;{REG_ADDR = 0x38;REG_DATA &= ~(0x08);REG_DATA |= (0x08&(x<<3));}}//0ѡ��ΪIO�ڹ��ܣ�1ѡ��ΪINT�жϹ��� 
#define INT4_20_FUN_SET(x) {TRISG |= 0x02;DATAG |= 0x02;{REG_ADDR = 0x38;REG_DATA &= ~(0x10);REG_DATA |= (0x10&(x<<4));}}//0ѡ��ΪIO�ڹ��ܣ�1ѡ��ΪINT�жϹ��� 
#define INT4_21_FUN_SET(x) {TRISG |= 0x04;DATAG |= 0x04;{REG_ADDR = 0x38;REG_DATA &= ~(0x20);REG_DATA |= (0x20&(x<<5));}}//0ѡ��ΪIO�ڹ��ܣ�1ѡ��ΪINT�жϹ��� 
#define INT4_22_FUN_SET(x) {TRISG |= 0x08;DATAG |= 0x08;{REG_ADDR = 0x38;REG_DATA &= ~(0x40);REG_DATA |= (0x40&(x<<6));}}//0ѡ��ΪIO�ڹ��ܣ�1ѡ��ΪINT�жϹ��� 

#define INT4_IE_SET 	IEN2 |= 0x80//��INT4�ж�ʹ�� 
#define INT4_IE_CLR 	IEN2 &= ~0x80//��INT4�ж�ʹ��
#define INT4_IP_SET 	IPL2 |= 0x80//����INT4�ж��ż�Ϊ��
#define INT4_IP_CLR 	IPL2 &= ~0X80//����INT4�ж��ż�Ϊ��
#define INT4_INT_FLAG_CLR IRCON2  &= ~0X80//���INT4�жϱ�־
#define INT4_POLO_SET(x) {REG_ADDR = 0x3A;REG_DATA &= ~(0x04);REG_DATA |= (0x04&(x<<2));}//1Ϊ����������0Ϊ�½��ش�����


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