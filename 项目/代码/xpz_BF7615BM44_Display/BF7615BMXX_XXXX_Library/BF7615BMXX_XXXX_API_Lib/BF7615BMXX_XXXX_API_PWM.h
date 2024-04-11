#ifndef __BF7615BMXX_XXXX_API_PWM_H__
#define __BF7615BMXX_XXXX_API_PWM_H__


#define PWM0_EN					0	//PWM0ʹ�����ã�		 	 				1:ʹ�ܱ��룬0:��ʹ�ܱ���
#define PWM1_EN					0	//PWM1ʹ�����ã�		 	 				1:ʹ�ܱ��룬0:��ʹ�ܱ���
#define PWM2_EN					0	//PWM2ʹ�����ã�		 	 				1:ʹ�ܱ��룬0:��ʹ�ܱ���
#define PWM3_EN					0	//PWM3ʹ�����ã�		 	 				1:ʹ�ܱ��룬0:��ʹ�ܱ���

#define PWM0_FRE 				4000//��λHz:	[183Hz~1200000Hz]--��Ӧ֧�ּ���[65535~10]
#define PWM0_RANK 			((SYS_CLK_FRE*1000000*1.0)/(PWM0_FRE*1.0))//��λHz:	[183Hz~1200000Hz]--��Ӧ֧�ּ���[65535~10]

#define PWM1_FRE 				4000//��λHz:	[183Hz~1200000Hz]--��Ӧ֧�ּ���[65535~10]
#define PWM1_RANK 			((SYS_CLK_FRE*1000000*1.0)/(PWM1_FRE*1.0))//��λHz:	[183Hz~1200000Hz]--��Ӧ֧�ּ���[65535~10]

#define PWM2_FRE 				4000//��λHz:	[183Hz~1200000Hz]--��Ӧ֧�ּ���[65535~10]
#define PWM2_RANK 			((SYS_CLK_FRE*1000000*1.0)/(PWM2_FRE*1.0))//��λHz:	[183Hz~1200000Hz]--��Ӧ֧�ּ���[65535~10]

#define PWM3_FRE 				4000//��λHz:	[183Hz~1200000Hz]--��Ӧ֧�ּ���[65535~10]
#define PWM3_RANK 			((SYS_CLK_FRE*1000000*1.0)/(PWM3_FRE*1.0))//��λHz:	[183Hz~1200000Hz]--��Ӧ֧�ּ���[65535~10]

#define PWM0_PORT 			0x01//bit[2:0]--[PWM0C_PC2,PWM0B_PB6,PWM0A_PB4],��Ӧ��λΪ1��PWM0�������Ӧ��λΪ0��PWM0�����
#define PWM1_PORT 			0x01//bit[2:0]--[PWM1C_PC3,PWM1B_PB7,PWM1A_PB5],��Ӧ��λΪ1��PWM1�������Ӧ��λΪ0��PWM1�����


#if (PWM0_EN == 1)
extern void PWM0_Set(bit pwm_switch,ulong pwm_fre,ulong pwm_duty,uchar pwm_prot);
#endif

#if (PWM1_EN == 1)
extern void PWM1_Set(bit pwm_switch,ulong pwm_fre, ulong pwm_duty,uchar pwm_prot);
#endif

#if (PWM2_EN == 1)
extern void PWM2_Set(bit pwm_switch,ulong pwm_fre, ulong pwm_duty);
#endif

#if (PWM3_EN == 1)
extern void PWM3_Set(bit pwm_switch,ulong pwm_fre, ulong pwm_duty);
#endif

#endif