#ifndef __BF7615BMXX_XXXX_API_PWM_H__
#define __BF7615BMXX_XXXX_API_PWM_H__


#define PWM0_EN					0	//PWM0使能配置，		 	 				1:使能编译，0:不使能编译
#define PWM1_EN					0	//PWM1使能配置，		 	 				1:使能编译，0:不使能编译
#define PWM2_EN					0	//PWM2使能配置，		 	 				1:使能编译，0:不使能编译
#define PWM3_EN					0	//PWM3使能配置，		 	 				1:使能编译，0:不使能编译

#define PWM0_FRE 				4000//单位Hz:	[183Hz~1200000Hz]--对应支持级数[65535~10]
#define PWM0_RANK 			((SYS_CLK_FRE*1000000*1.0)/(PWM0_FRE*1.0))//单位Hz:	[183Hz~1200000Hz]--对应支持级数[65535~10]

#define PWM1_FRE 				4000//单位Hz:	[183Hz~1200000Hz]--对应支持级数[65535~10]
#define PWM1_RANK 			((SYS_CLK_FRE*1000000*1.0)/(PWM1_FRE*1.0))//单位Hz:	[183Hz~1200000Hz]--对应支持级数[65535~10]

#define PWM2_FRE 				4000//单位Hz:	[183Hz~1200000Hz]--对应支持级数[65535~10]
#define PWM2_RANK 			((SYS_CLK_FRE*1000000*1.0)/(PWM2_FRE*1.0))//单位Hz:	[183Hz~1200000Hz]--对应支持级数[65535~10]

#define PWM3_FRE 				4000//单位Hz:	[183Hz~1200000Hz]--对应支持级数[65535~10]
#define PWM3_RANK 			((SYS_CLK_FRE*1000000*1.0)/(PWM3_FRE*1.0))//单位Hz:	[183Hz~1200000Hz]--对应支持级数[65535~10]

#define PWM0_PORT 			0x01//bit[2:0]--[PWM0C_PC2,PWM0B_PB6,PWM0A_PB4],对应的位为1，PWM0输出，对应的位为0，PWM0不输出
#define PWM1_PORT 			0x01//bit[2:0]--[PWM1C_PC3,PWM1B_PB7,PWM1A_PB5],对应的位为1，PWM1输出，对应的位为0，PWM1不输出


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