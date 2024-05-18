#include ".\BF7615BMXX_XXXX_Library\Config.h"

	#if ADC_IS_OPEN
		#pragma message "����,ADC����"
		
		#if (ADC_MODE == 0)
			#if ADC_NUM
			uint 	xdata adc_data[ADC_NUM] = {0};
			#endif
			unsigned char code 	ADC_CH[45] ={SCAN_ADC00,SCAN_ADC01,SCAN_ADC02,SCAN_ADC03,SCAN_ADC04,SCAN_ADC05,SCAN_ADC06,SCAN_ADC07,SCAN_ADC08,SCAN_ADC09,SCAN_ADC10,SCAN_ADC11,SCAN_ADC12,SCAN_ADC13,SCAN_ADC14,SCAN_ADC15,\
																			 SCAN_ADC16,SCAN_ADC17,SCAN_ADC18,SCAN_ADC19,SCAN_ADC20,SCAN_ADC21,SCAN_ADC22,SCAN_ADC23,SCAN_ADC24,SCAN_ADC25,SCAN_ADC26,SCAN_ADC27,SCAN_ADC28,SCAN_ADC29,SCAN_ADC30,SCAN_ADC31,\
																			 SCAN_ADC32,SCAN_ADC33,SCAN_ADC34,SCAN_ADC35,SCAN_ADC36,SCAN_ADC37,SCAN_ADC38,SCAN_ADC39,SCAN_ADC40,SCAN_ADC41,SCAN_ADC42,SCAN_ADC43,SCAN_ADC44};
		#endif
		#if (ADC_MODE == 1)//ADC��ѯģʽ
			#pragma message "����,ADC��ѯģʽ����"
			bit ADC_Start_Flag = 0;
			uint  xdata  ADC_Rest_Max_Count = 0;
			uint  xdata  ADC_Start_Count = 0;
			
			void ADC_Unormal_Count(void);
	

			//-----------------------------------------------------------------//
		//�������ƣ� void ADC_Reset_Count()
		//�������ܣ� ADC��ʱ�������ۼӺ���
		//��������� ��
		//��������� ��
		//�� �� ֵ�� ��
		//-----------------------------------------------------------------//
		#if Timer0_EN
			#if ADC_IS_OPEN
				#if ADC_MODE
				void ADC_Reset_Count(void)
				{
					if(ADC_Start_Flag == 1)
					{
						ADC_Start_Count++;
						if(ADC_Start_Count >= ADC_Rest_Max_Count)
						{
							SOFT_RST = 0x55;	
							ADC_Start_Count = 0;
							ADC_Start_Flag = 0;
						}
					}
				}
				#endif
			#endif
		#endif
				
		#endif
	#endif
		

		#if ADC_IS_OPEN
				
		#if (ADC_MODE == 0)
			bit ADC_Done = 0;
			uchar ADC_Index = 0;
			uchar ADC_Index_Start = 0;
			bit adc_scan_done = 0;
			#if ADC_NUM
			uchar xdata ADC_Access_Index[ADC_NUM] = {0x7F};
			#endif
		#endif
		
		//-----------------------------------------------------------------//
		//�������ƣ� void ADC_Find_Next(void)
		//�������ܣ� ADCͨ������
		//��������� ��
		//��������� ��
		//�� �� ֵ�� ��
		//-----------------------------------------------------------------//
		#if (ADC_MODE == 0)	
		#pragma message "����,ADC�����ж�ģʽ"
			#if ADC_NUM
			void  ADC_Find_Next(void)
			{
				while(1)
				{
					ADC_Index++;	
					if(ADC_Index >= ADC_NUM)
					{
							ADC_Index = ADC_Index_Start;
							adc_scan_done = 1;
					}
					if((ADC_Access_Index[ADC_Index]&0x80))//�����һ����ADCͨ����������ADC
					{
						ADC_ADDR_SET((ADC_Access_Index[ADC_Index]&0x7F));
						ADC_SCAN_EN;//����ADCɨ��
						break;
					}
					else
					{
					
					}
				}				
			}
			#endif
		#endif
		//-----------------------------------------------------------------//
		//�������ƣ� uint Get_ADC(uchar adc_ch)
		//�������ܣ� ADC_SELXX��ӦҪ��������ѯģʽ�»�ȡADC adc_ch�����ݣ�(0~43),44Ϊ�ڲ�ADCͨ��
		//��������� ��
		//��������� uint������ADC����
		//�� �� ֵ�� ��
		//-----------------------------------------------------------------// 
		#if (ADC_MODE == 1)		
		uint Get_ADC(uchar adc_ch)
		{
			ADC_IE_CLR;//�ر�ADC�ж�ʹ��
	
			ADC_ADDR_SET(adc_ch);
			ADC_SCAN_EN;//����ADCɨ��
			ADC_Start_Flag = 1;
			ADC_Start_Count = 0;
			while(!(IRCON1&0x10));
			ADC_Start_Flag = 0;
			ADC_INT_FLAG_CLR;

			return ((uint)(ADC_RDATAH&0x0F) << 8) | (uint)ADC_RDATAL;
		}
		#endif

		//-----------------------------------------------------------------//
		//�������ƣ� uint Get_ADC_Vref(uchar vref)
		//�������ܣ� ��ADC�ο���ѹѡ��2V/4Vʱ��Get_ADC_Vref��ȡADC�ο���ѹֵ��
		//��������� uchar vref:0:Ϊ���زο���ѹ2V��ADCУ׼ֵ��1:Ϊ���زο���ѹ4V��ADCУ׼ֵ
		//��������� uint��ADCУ׼ֵmV,���ڼ���ADC�����ѹ
		//�� �� ֵ�� uint
		//-----------------------------------------------------------------// 
	
		uint Get_ADC_Vref(uchar vref)
		{
			uint adc_vref = 0;
			EA = 0;
			if(vref == 0)
			{
				SPROG_CMD = 0x88;
				SPROG_ADDR_H = 0x41D2>>8;
				SPROG_ADDR_L = 0x41D2;
				adc_vref = SPROG_RDATA<<8;
				SPROG_CMD = 0x88;
				SPROG_ADDR_H = 0x41D3>>8;
				SPROG_ADDR_L = 0x41D3;
				adc_vref |= SPROG_RDATA;
				
			}
			else if(vref == 1)
			{
				SPROG_CMD = 0x88;
				SPROG_ADDR_H = 0x41D4>>8;
				SPROG_ADDR_L = 0x41D4;
				adc_vref = SPROG_RDATA<<8;
				SPROG_CMD = 0x88;
				SPROG_ADDR_H = 0x41D5>>8;
				SPROG_ADDR_L = 0x41D5;
				adc_vref |= SPROG_RDATA;
			}
			else
			{
				
			}
			EA = 1;
			return adc_vref;
		}
		
		//-----------------------------------------------------------------//
		//�������ƣ� uint Get_Inner_ADC_Vol(void)
		//�������ܣ� ��ADC�ο���ѹѡ��VCCʱ��Get_Inner_ADC_Vol��ȡADC�ڲ�ͨ�������ѹУ׼ֵ
		//��������� void 
		//��������� uint���AADC�ڲ�ͨ�������ѹֵmV
		//�� �� ֵ�� uint
		//-----------------------------------------------------------------// 
	
		uint Get_Inner_ADC_Vol(void)
		{
			uint inner_adc_vol = 0;
			EA = 0;
			SPROG_CMD = 0x88;
			SPROG_ADDR_H = 0x41CC>>8;
			SPROG_ADDR_L = 0x41CC;
			inner_adc_vol = SPROG_RDATA<<8;
			SPROG_CMD = 0x88;
			SPROG_ADDR_H = 0x41CD>>8;
			SPROG_ADDR_L = 0x41CD;
			inner_adc_vol |= SPROG_RDATA;
			EA = 1;
			return inner_adc_vol;
		}

		
		
		//-----------------------------------------------------------------//
		//�������ƣ� void ADC_Init(void)
		//�������ܣ� ADC��ʼ��,��SetAccessIndexes()֮���ʼ��;
		//��������� ��
		//��������� ��
		//�� �� ֵ�� ��
		//-----------------------------------------------------------------//        
		void ADC_Init(void)
		{
			uchar i = 0;
			uchar j = 0;
			uchar adc_count = 0;
			EA = 0;//�����жϣ�
			ADC_IP_SET;//����ADC�ж��ż�Ϊ�ߣ�����ʵ��Ӧ���������ȼ�
			ADC_INT_FLAG_CLR;//���ADC�жϱ�־λ

			ADC_IO_CGF0(ADC_SEL00);//ADC0~ADC06��IO����ѡ�񣬶�Ӧ��λΪ1ΪADC���ܣ�0ΪIO����		
			ADC_IO_CGF1(ADC_SEL01);//ADC7~ADC14��IO����ѡ�񣬶�Ӧ��λΪ1ΪADC���ܣ�0ΪIO����		
			ADC_IO_CGF2(ADC_SEL02);//ADC15~ADC22��IO����ѡ�񣬶�Ӧ��λΪ1ΪADC���ܣ�0ΪIO����		
			ADC_IO_CGF3(ADC_SEL03);//ADC23~ADC30��IO����ѡ�񣬶�Ӧ��λΪ1ΪADC���ܣ�0ΪIO����		
			ADC_IO_CGF4(ADC_SEL04);//ADC31~ADC38��IO����ѡ�񣬶�Ӧ��λΪ1ΪADC���ܣ�0ΪIO����		
			ADC_IO_CGF5(ADC_SEL05);//ADC39~ADC43��IO����ѡ�񣬶�Ӧ��λΪ1ΪADC���ܣ�0ΪIO����		
		
			ADC_SAMP_SET(ADC_SAMPT);			//ADC����ʱ������ѡ��   	bit[7:0],(0~255)����ʱ��Ϊ(ADC_SPT+1)*4*T_adc_clk
			ADC_FLTER_SET(ADC_FLTER);			//ADC�˲�ѡ��bit[7],(0~1),0:����RC�˲���1����RC�˲���//20-07-20
			ADC_CALW_SET(ADC_CALW); 			//������ʱʱ��ѡ��, bit[5:4](0~3)��0:0(ADC_CLK),1:2(ADC_CLK),1:4(ADC_CLK),2:8(ADC_CLK)//20-07-20
			ADC_CKV_SET(ADC_CKV);					//ģ�������ź�ʱ�ӷ�Ƶѡ��bit[3:2],(0~3)-(12MhHz,8MHz,4MHz,2MHz)
			ADC_ADCK_SET(ADC_ADCK);				//ADC��Ƶѡ��							bit[1:0],(0~3)-(8MHz,6MhHz,4MHz,3MHz)
			ADC_OFFSETI_SET(ADC_OFFSETI);	//ADCƫ�õ�����Сѡ��			bit[1:0],(0~3)(4uA,4uA,5uA,5uA)
			ADC_WNUM_SET(ADC_WAIT);				//ת����Ͼ���ת��ʱ��ѡ��bit[6:2],(0~31)(X+3)*T_adc_clk,��Ҫ(X+3)*T_adc_clk > 4*ADC_ANCK
			ADC_PD(0);//����ADCģ��
			ADC_CTRL(2);//ADC�Ƚ���ʧ��������2Ϊʱ��2,5Ϊʱ��3,����Ϊ2
			ADC_SAMBG_SET(ADC_SAMBG);//����ʱ����Ƚ�ʱ����ѡ��bit[6],(0~1),0:���0(ADC_CLK)��1�����1(ADC_CLK);//20-07-20
			ADC_VIN_SEL(ADC_VIN);//ADC�ڲ�ͨ�������ѹѡ��00��1.362V;01:2.253V;10:3.111V;11:4.082V;//20-09-15
			ADC_VREF_SEL(ADC_VREF);//�ο�Դ��ѹѡ��0��VCC;1:ADC_VREF//20-07-20
			ADC_VREF_VOL_SEL(ADC_VREF_VOL);//�ο���ѹѡ��ADC_VREF��0��2V;1:4V//20-07-20
			
			#if (ADC_MODE == 0)
				#if ADC_NUM
					for (i = 0; i < ADC_NUM; i++) 
					{
							ADC_Access_Index[i] = ADC_CH[i]|0x80;
					}		
					for(ADC_Index_Start = 0;ADC_Index_Start < ADC_NUM;ADC_Index_Start++)//���ҵ�һ��ADCͨ��
					{
						if((ADC_Access_Index[ADC_Index_Start] & 0x80))
						{
							break;
						}
					}				
					ADC_ADDR_SET((ADC_Access_Index[ADC_Index_Start]&0x7F));
					ADC_Index = ADC_Index_Start;
					ADC_SCAN_EN;//����ADCɨ��
					
					ADC_IE_SET;//����ADC�ж�ʹ��
				#endif
			#endif
			
			#if (ADC_MODE == 1)
				ADC_SCAN_CLR;//�ر�ADCɨ��
				ADC_IE_CLR;//�ر�ADC�ж�ʹ��
			#endif
			
			EA = 1;//�����ж�	 
		}
		
		//-----------------------------------------------------------------//
		//�������ƣ� void  ADC_ISR interrupt 11
		//�������ܣ� ADC�ж��Ӻ���
		//��������� ��
		//��������� ��
		//�� �� ֵ�� ��
		//-----------------------------------------------------------------//
		#if ADC_NUM
		void  ADC_ISR() interrupt 11
		{	
			static uchar xdata addr_bak = 0;
			PUSH_REG_ADDR_SFR();
			ADC_INT_FLAG_CLR;//���ADC�жϱ�־λ
			ADC_SCAN_CLR;//�ر�ADCɨ��
		
			#if (ADC_MODE == 0)
		
				EA = 0;
				adc_data[ADC_Index] = ((uint)(ADC_RDATAH&0x0F) << 8) | (uint)ADC_RDATAL;//��ȡADC����				
				EA = 1;
			
				ADC_Find_Next();//������һ��������ADC
		
			#else
				ADC_IE_CLR;//�ر�ADC�ж�ʹ��
				ADC_SCAN_CLR;//�ر�ADCɨ��	
			#endif
			POP_REG_ADDR_SFR();
		}
		#endif
		
		#endif
