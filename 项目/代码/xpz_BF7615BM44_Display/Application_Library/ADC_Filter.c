#include ".\CTK_Library\Config.h"		
#if ADC_FLITER_EN

	unsigned char ADC_Obtain(unsigned char adc_channel);
	unsigned char Sort(unsigned char *data_array,unsigned char raw_count);

	//ADC������ر���
	unsigned char xdata ADC_Tem[21] = {0};//�洢ADC����,��������˶��ADC��,����ADC����Ⱥ�˳��ֱ���21��.
	unsigned char channel_get = 0xff;		//��Ҫ��ȡ��ADC���
	
	//-----------------------------------------------------------------//
	//�������ƣ� unsigned char ADC_Obtain(unsigned char adc_channel)
	//�������ܣ� ��ȡÿ21�εĲ���������ADCֵ,����ADC�Ĳ�ѯģʽ����ȡ21������ʱ��= 21 * ADC����ʱ����
	//��������� unsigned char adc_channel����ȡADC����ţ�ȡֵ0~6
	//��������� ��
	//�� �� ֵ�� ���������8λADCֵ,���ADC��ų�����Χ��̶����0
	//-----------------------------------------------------------------//

	unsigned char ADC_Obtain(unsigned char adc_channel)
	{
		unsigned char ADC_Tem_Count = 0;	//ADC�����ۼ���	

		if(adc_channel < 7)								//����������źϷ��Ž���ADC�˲�����
		{
			channel_get = adc_channel;			//��Ҫ��ȡ��ADC���ת�Ƶ�channel_get����
			
			for(ADC_Tem_Count=0;ADC_Tem_Count<21;ADC_Tem_Count++)
			{
			
				ADC_Tem[ADC_Tem_Count] = (unsigned char)(Get_ADC(channel_get) >> 4);	//ADCת��Ϊ8λ,�洢�������Ӧλ�ô�	
				ADC_Delay_us(9);

			}
			
			ADC_SCAN_CLR;//��21��ȡ����ɺ�ر�ADCɨ��

			return Sort(ADC_Tem,21);	//ð������ȡ�м�ľ�ֵ��Ϊ��ʼ�ϵ�ADCƽ��ֵ
		}
		else//����������Ų��Ϸ�����ֱ�ӷ���0
		{
			return 0;
		}
	}


	//-----------------------------------------------------------------//
	//�������ƣ� unsigned char Sort(unsigned char *data_array,unsigned char raw_count)
	//�������ܣ� �Ѳɵ�����������ȥͷβ��3������ƽ��ֵ
	//��������� uchar *data_array:����
	//��������� ����Sort����ֵ
	//�� �� ֵ�� ��
	//-----------------------------------------------------------------//
	unsigned char Sort(unsigned char *data_array,unsigned char raw_count)
	{
		unsigned char i = 0,j = 0;
		unsigned char tem  = 0;
		unsigned int avg_tem  = 0;
		for(i = 0; i < raw_count; i++)
		{
			for(j = i; j < raw_count-1;j++ )
			{
				if((*(data_array+i)) >= (*(data_array+j+1)))
				{
					tem = (*(data_array+i));
					(*(data_array+i)) = (*(data_array+j+1));
					(*(data_array+j+1)) = tem;
				}
			}
			
		}
		for(i = 3; i < raw_count-3; i++)//�ĳ�ȥ�������С��3��ֵ
		{
			avg_tem += (*(data_array+i));
		}
		
		return (unsigned char)(avg_tem/(raw_count-6));
	}
#endif