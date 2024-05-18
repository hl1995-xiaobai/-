#include ".\CTK_Library\Config.h"		
#if ADC_FLITER_EN

	unsigned char ADC_Obtain(unsigned char adc_channel);
	unsigned char Sort(unsigned char *data_array,unsigned char raw_count);

	//ADC处理相关变量
	unsigned char xdata ADC_Tem[21] = {0};//存储ADC数据,如果开启了多个ADC口,则按照ADC序号先后顺序分别存放21个.
	unsigned char channel_get = 0xff;		//需要获取的ADC序号
	
	//-----------------------------------------------------------------//
	//函数名称： unsigned char ADC_Obtain(unsigned char adc_channel)
	//函数功能： 获取每21次的采样处理后的ADC值,采用ADC的查询模式，获取21个数据时间= 21 * ADC出点时间间隔
	//输入参数： unsigned char adc_channel：获取ADC的序号，取值0~6
	//输出参数： 无
	//返 回 值： 输出处理后的8位ADC值,如果ADC序号超出范围则固定输出0
	//-----------------------------------------------------------------//

	unsigned char ADC_Obtain(unsigned char adc_channel)
	{
		unsigned char ADC_Tem_Count = 0;	//ADC个数累加器	

		if(adc_channel < 7)								//如果输入的序号合法才进行ADC滤波处理
		{
			channel_get = adc_channel;			//需要获取的ADC序号转移到channel_get里面
			
			for(ADC_Tem_Count=0;ADC_Tem_Count<21;ADC_Tem_Count++)
			{
			
				ADC_Tem[ADC_Tem_Count] = (unsigned char)(Get_ADC(channel_get) >> 4);	//ADC转化为8位,存储到数组对应位置处	
				ADC_Delay_us(9);

			}
			
			ADC_SCAN_CLR;//在21次取数完成后关闭ADC扫描

			return Sort(ADC_Tem,21);	//冒泡排序并取中间的均值作为初始上电ADC平均值
		}
		else//如果输入的序号不合法的则直接返回0
		{
			return 0;
		}
	}


	//-----------------------------------------------------------------//
	//函数名称： unsigned char Sort(unsigned char *data_array,unsigned char raw_count)
	//函数功能： 把采到的数据排序，去头尾各3个后求平均值
	//输入参数： uchar *data_array:数组
	//输出参数： 返回Sort处理值
	//返 回 值： 无
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
		for(i = 3; i < raw_count-3; i++)//改成去掉最大最小各3个值
		{
			avg_tem += (*(data_array+i));
		}
		
		return (unsigned char)(avg_tem/(raw_count-6));
	}
#endif