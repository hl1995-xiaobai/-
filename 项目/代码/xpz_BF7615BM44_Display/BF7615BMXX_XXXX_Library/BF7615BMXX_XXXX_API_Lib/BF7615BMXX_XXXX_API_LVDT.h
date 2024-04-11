#ifndef __BF7615BMXX_XXXX_API_LVDT_H__
#define __BF7615BMXX_XXXX_API_LVDT_H__


#define	VolDet_EN								1//��ѹ���ʹ������	 				1:ʹ�ܱ��룬0:��ʹ�ܱ���
#define	VolDet_COUNT						4	//��ѹ����ʱVolDet_COUNT*time0��ʱ//����ʵ�ʵ������÷�������

#define LVDT_IE_SET IEN2 |= 0x02												//��LVDT�ж�ʹ��
#define LVDT_IE_CLR IEN2 &= ~0x02												//��LVDT�ж�ʹ��
#define LVDT_IP_SET IPL2  |= 0x02												//����LVDT�ж����ȼ�Ϊ��
#define LVDT_IP_CLR IPL2 &= ~0x02												//����LVDT�ж����ȼ�Ϊ��
#define LVDT_INT_FLAG_CLR 			IRCON2 &= ~0x02						//����͵�ѹ����жϱ�־λ
#define LVDT_INT_DOWN_FLAG_CLR 	INT_POBO_STAT &= ~0x01		//���LVDT��ѹ�½��жϱ�־λ
#define LVDT_INT_UP_FLAG_CLR 		INT_POBO_STAT &= ~0x02		//���LVDT��ѹ�����жϱ�־λ
#define LVDT_ON_OFF_SET(x) {REG_ADDR = 0x2D;REG_DATA &= ~(0x40);REG_DATA |= (0x40&(x<<6));}//0Ϊ����LVDT���ģ��,1Ϊ�ر�LVDT���ģ��
#define LVDT_VOL_SET(x) 	 {REG_ADDR = 0x2C;REG_DATA &= ~(0x03);REG_DATA |= (0x03&(x<<0));}//���õ͵�ѹ������:(0-2.7V)-(1-3.0V)-(2-3.8V)


#if	VolDet_EN
	extern bit Low_Volotage_Flag;
	extern bit Low_Volotage_Flag_Confirm;
	extern bit Low_Volotage_Flag_First;
	extern uint xdata Low_Volotage_Flag_Count;
	extern uint xdata Low_Volotage_Flag_Confirm_count;
	extern void LVDT_Init(void);
#endif

#endif