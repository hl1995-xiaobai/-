#ifndef __FLITER_ADC_H__
#define __FLITER_ADC_H__

#define ADC_FLITER_EN 		0		//1为编译"ADC_Obtain()函数"，0为不编译"ADC_Obtain()函数"

#if ADC_OBTAIN_EN
extern unsigned char ADC_Obtain(unsigned char adc_channel);
extern unsigned char Sort(unsigned char *data_array,unsigned char raw_count);

//ADC处理相关变量
extern unsigned char xdata ADC_Tem[];
extern unsigned char channel_get;
#endif

#endif