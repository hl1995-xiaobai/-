#ifndef __BF7615BMXX_XXXX_CTK_Touch_H__
#define __BF7615BMXX_XXXX_CTK_Touch_H__
extern void BF7615BMXX_XXXX_Set_Touch_Flag(void);
#if SNS_NUM
	#if UN_NORMAL_CHECK
		extern void Rawdata_Un_Normal(uchar sns_num);
	#endif
	extern uchar xdata Sns_Count;
	extern uchar xdata CFG_Rb;
#endif
#endif
