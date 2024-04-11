#include ".\BF7615BMXX_XXXX_Library\Config.h"

//-----------------------------------------------------------------//
//�������ƣ� void CFG_Check(void)
//�������ܣ� �����ֶԱ��ж�(��ӦMCU02оƬ)
//��������� ��
//��������� ��
//�� �� ֵ�� ��
//-----------------------------------------------------------------//
		 
void CFG_Check(void)
{   
	unsigned char i = 0;
	unsigned char code add_cfg_Bit[14] = {0x0E,0xFF,0x3F,0xFF,0x3F,0xFF,0x3F,0x1F,0x7E,0xFF,0xFF,0xFF,0x7F,0x07};
	unsigned int code cfg_addr[14] = {0x81FF,0x41FF,0x41FD,0x41FB,0x41F9,0x41F7,0x41F5,0x41F3,0x41F1,0x41EF,0x81FE,0x81FD,0x41ED,0x41EB};
	
	EA = 0;//�����ж�
	for(i = 0; i < 14;i++)
	{
		SPROG_CMD = 0x88;
		SPROG_ADDR_H = cfg_addr[i]>>8;
		SPROG_ADDR_L =  cfg_addr[i];
		REG_ADDR = i;
		if((SPROG_RDATA&add_cfg_Bit[i]) != (REG_DATA&add_cfg_Bit[i]))
		{
			SOFT_RST = 0x55;	
		}	
	}
	
	#if SNS_NUM
		SPROG_CMD = 0x88;
		SPROG_ADDR_H = 0x41DC>>8;
		SPROG_ADDR_L = 0x41DC;
		CFG_Rb = SPROG_RDATA;
	#endif
	
	SPROG_CMD = 0;
	SPROG_ADDR_H = 0;
	SPROG_ADDR_L = 0;
	
	P2_XH = 0;//ʹ��MOVX ����PDATA��ʱ��P2_XH��0
	EA = 1;//�����ж�	
}


//-----------------------------------------------------------------//
//�������ƣ� void Delay_Us(uint us)
//�������ܣ� ��ʱΪ��us
//��������� us
//��������� ��
//�� �� ֵ�� ��
//-----------------------------------------------------------------//
#if(DELAY_US_EN == 1)
#pragma message "���룬void Delay_Us(uint us)"  
void Delay_Us(uint us)//1--2.38us@12MHz;10-11.8us@12MHz;100-106us@12MHz;1000-1.045ms
{
	for (; us > 0; us--)
	{	
		WDT_CTRL = 0x07;
	}		
}
 
#endif
//-----------------------------------------------------------------//
//�������ƣ� void Set_Sys_Clk(void)
//�������ܣ� ϵͳʱ������
//��������� �� 
//��������� ��
//�� �� ֵ�� ��
//-----------------------------------------------------------------//
void Set_Sys_Clk(void) 
{
		SYS_CLK_SET(SYS_CLK);//(SYS_CLK��4,5,6,7�ֱ��Ӧ��SYSCLK_SEL��0--12Mhz,1--08Mhz,2--04Mhz,3--01Mhz)
		SYS_CLK_ON_OFF(0);//0Ϊ��ϵͳʱ�ӣ�1Ϊ��ϵͳʱ�� 
}
 

//-----------------------------------------------------------------//
//�������ƣ� void Pow_Delay(uint t)
//�������ܣ� �ϵ���ʱ����
//��������� t
//��������� ��
//�� �� ֵ�� ��
//-----------------------------------------------------------------//

#if(POW_UP_DELAY == 1)
#pragma message "���룬void Pow_Up_Delay(uint ms)����"
void Pow_Up_Delay(uint ms)//1--1ms@12MHz;10-10.05ms@12MHz;100-100ms@12MHz;1000-1000ms
{  
	uint a = 954,b = ms;
	#if(SWITCH_TRACEMODE == 0)	
	#pragma message "����ģʽ�������ϵ���ʱ"
	for (b = ms; b > 0; b--)
	{
		for (a = 954; a > 0; a--)
		{
			WDT_CTRL = 0x07;
		} 
	}	
	#endif
}
#endif

//-----------------------------------------------------------------//
//�������ƣ� void Delay_Ms(uint t)
//�������ܣ� ms��ʱ����
//��������� t
//��������� ��
//�� �� ֵ�� ��
//-----------------------------------------------------------------//

#if ((DELAY_MS_EN == 1))

#pragma message "���룬void Delay_Ms(uint ms)����"
void Delay_Ms(uint ms)//1--1ms@12MHz;10-10.05ms@12MHz;100-100ms@12MHz;1000-1000ms
{  
	uint a = 954,b = ms;
	for (b = ms; b > 0; b--)
	{
		for (a = 954; a > 0; a--)
		{
			WDT_CTRL = 0x07;
		} 
	}	
}
#endif



//-----------------------------------------------------------------//
//�������ƣ� void WDT_Init(void)
//�������ܣ� ���Ź���ʼ��
//��������� ��
//�� �� ֵ�� ��
//-----------------------------------------------------------------//
void WDT_Init(void)
{
	#if CHIP_BF7615BMXX_XXXX

		EA = 0;//�����жϣ�
		WDT_IP_CLR;//����WDT�ж��ż�Ϊ�ͣ�����ʵ��Ӧ���������ȼ�
		WDT_INT_FLAG_CLR;//������Ź��жϱ�־
		WDT_ON_OFF(0);//������0x55ʱ�رտ��Ź�
		WDT_CTRL = 7;//����WDT���ʱ��(0~15--18ms~2.304S)7--2.304S
		WDT_IE_SET;	//��WDT�ж�ʹ��
		EA = 1;//�����ж�	

	#endif
}




//-----------------------------------------------------------------//
//�������ƣ� void CTK_Init(void)
//�������ܣ� CTK��ʼ��
//��������� ��
//�� �� ֵ�� ��
//-----------------------------------------------------------------//

void CTK_Init(void)
{
	#if SNS_NUM
		#if CHIP_BF7615BMXX_XXXX
		
				EA = 0;	//�����ж�
				//����CTKɨ����������߸��²���
				CTK_Set_Para();
			
				TRISB |= ((open_sns_l << 2)  & 0xFC);
				TRISC |= ((open_sns_l >> 2)  & 0x30);
				TRISE |= ((open_sns_l >> 4)  & 0xF0);
				TRISF |= ((open_sns_l >> 12) & 0xFF);
				TRISG |= ((open_sns_l >> 20) & 0x0F);
				TRISH |= ((open_sns_l >> 24) & 0xFF);//����Ϊ����
				
				TRISA |= ((open_sns_h << 0)  & 0x0F);
				TRISB |= ((open_sns_h >> 4)  & 0x03);
				TRISC |= ((open_sns_h >> 6)  & 0x0F);
				TRISC |= ((open_sns_h >> 4)  & 0xC0);
				TRISE |= ((open_sns_h >> 12) & 0x0F);//����Ϊ����
				

				REG_ADDR = 0x26;REG_DATA |= ((open_sns_l)&0xFF);
				REG_ADDR = 0x27;REG_DATA |= ((open_sns_l>>8)&0xFF);
				REG_ADDR = 0x28;REG_DATA |= ((open_sns_l>>16)&0xFF);
				REG_ADDR = 0x29;REG_DATA |= ((open_sns_l>>24)&0xFF);//����IO��SNS����
				
				REG_ADDR = 0x51;REG_DATA |= ((open_sns_h)&0xFF);
				REG_ADDR = 0x52;REG_DATA |= ((open_sns_h>>8)&0xFF);//����IO��SNS����
		
				CTK_PRS_SW_SET(0);					//ǰ�˳�ŵ翪��,1Ϊ�أ�0Ϊ��
				CTK_LP_EN_SET(0);						//1��CTKģ��͹���;0��CTKģ������ģʽ
				CTK_RESO_SET(CTK_RESO);   	//0~7 CTK����ɨ��ֱ��ʣ�������λ����(CFG_CTK_RESOLUTION+9)λ��
				CTK_PRS_SET(CTK_PRS); 			//PRS(��ŵ�Ƶ��) = 96/2/(x+8)��x = 61ʱ��PRS(��ŵ�Ƶ��) = 400K��x = 62/63��PRS(��ŵ�Ƶ��) = (1~1.5~3)MHz��
				CTK_DS_SET(CTK_DS); 				//����ٶ�0:24MHz,1:12MHz,2:6MHz,3:4MHz
				CTK_PAR_SET(Mode); 					//0Ϊ��ͨ��ģʽ��1Ϊ��ͨ������ģʽ
				CTK_RB_SET(CTK_RB);					//ѡ��RB�����С0:20K,1:40K,2:60K,3:80K,4:150K,5:200K,6:250K,7:300K��
				CTK_VTH_SET(CTK_REF);				//0~7 �ο���ѹ(0:1.79V),(1:2.14V),(2:2.47V),(3:2.81V),(4:3.18V),(5:3.48V),(6:3.86V),(7:4.19V);//ע��VCC-CTK_REF>0.5V
				CTK_BF7615BMXX_XXXX_Set_Para(pull_i_value[0]);			//���õ���Դ����
				CTK_PRE_CH_SET(1);					//Ԥ���ʱ�䣺0Ϊ20us,1Ϊ40us
				CTK_PRE_DISCH_SET(1);				//Ԥ�ŵ�ʱ�䣺0Ϊ2us,1Ϊ10us
				CTK_STOP;										//ֹͣɨ��
				CTK_PD_SET(0);							//����CTK

				CTK_ADDR_SET(sensor_open[0]);
				CTK_IP_CLR;//CTK�����ȼ�
				CTK_IE_SET;
				CTK_START;
				EA = 1;											//�����ж�

		#endif	
	#endif
}



//-----------------------------------------------------------------//
//�������ƣ� void Init_IO(void)
//�������ܣ� IO�ڳ�ʼ��,��û���õ��Ļ����յ�IO�ڣ�����ΪIO���Ϊ��
//��������� ��
//�� �� ֵ�� ��
//-----------------------------------------------------------------//
void Init_IO(void)
{
	#if (TRACEMODE == FALSE) 

		#if CHIP_BF7615BMXX_XXXX
		//IO�ڳ���
		//��:SET_PB0_IO_OUT;
		//��:SET_PB0_H;
		#endif

	#endif

	#if (TRACEMODE == TRUE) 
//		SET_PB3_IO_OUT;
//		SET_PB3_H;
	#endif
}

//-----------------------------------------------------------------//
//�������ƣ� void Default_Set_IO(void)
//�������ܣ� Ĭ��IO������
//��������� ��
//�� �� ֵ�� ��
//-----------------------------------------------------------------//
void Default_Set_IO(void)
{   
	#if CHIP_BF7615BMXX_XXXX
		//����Ϊ�����
		//����Ϊ������ʹ��;
		//Ĭ��PC4/PC5/PE4/PE5�ڿ�©��ʹ�ܣ�
		//����Ϊ�����
		EA = 0;
	
		REG_ADDR = 0x17;
		REG_DATA = 0x00;//PA0_PU_OFF~PA3_PU_OFF
		DATAA = 0x00;
		TRISA = 0x00;
	
		REG_ADDR = 0x18;
		REG_DATA = 0x00;//PB0_PU~PB7_PU
		DATAB = 0x00;
		TRISB = 0x00;
	
		REG_ADDR = 0x19;
		REG_DATA = 0x00;//PC0_PU~PC7_PU
		DATAC = 0x00;
		TRISC = 0x00;
		
		REG_ADDR = 0x1B;
		REG_DATA = 0x00;//PE0_PU~PE7_PU
		DATAE = 0x00;
		TRISE = 0x00;
		
		REG_ADDR = 0x1C;
		REG_DATA = 0x00;//PF4_PU~PF7_PU
		DATAF = 0x00;
		TRISF = 0x00;
		
		REG_ADDR = 0x1D;
		REG_DATA = 0x00;//PG0_PU~PG7_PU
		DATAG = 0x00;
		TRISG = 0x00;

		REG_ADDR = 0x1E;
		REG_DATA = 0x00;//PH0_PU~PH7_PU
		DATAH = 0x00;
		TRISH = 0x00;
		
		EA = 1;
			
	#endif
}

//-----------------------------------------------------------------//
//�������ƣ� void Trace_Mode_Init(void)
//�������ܣ� ����ģʽ��ʼ��
//��������� ��
//�� �� ֵ�� ��
//-----------------------------------------------------------------//

void Trace_Mode_Init(void)
{
	#if (TRACEMODE == TRUE)

		#if CHIP_BF7615BMXX_XXXX
				BF7615BMXX_XXXX_Trace_Mode_Init(0x54,1);
		#endif

	#endif

}



//-----------------------------------------------------------------//
//�������ƣ� void Function_Init(void)
//�������ܣ� ����ģ���ʼ��
//��������� ��
//�� �� ֵ�� ��
//-----------------------------------------------------------------//
void Function_Init(void)
{

#if (TRACEMODE == TRUE)

	#ifdef ADC_IS_OPEN
		#if ADC_IS_OPEN
				ADC_Init();
		#endif
	#endif
	
	#ifdef Timer0_EN
		#if Timer0_EN
			Timer0_Init(1000);//��ʱ��0��ʼ��
		#endif
	#endif
	
	#ifdef UART0_EN
		#if(UART0_EN == 1)
			UART0_Init();//UART0_��ʼ��
		#endif
	#endif
	
	#ifdef UART1_EN
		#if(UART1_EN == 1)	
			UART1_Init();//UART1_��ʼ��
		#endif
	#endif
	
	#ifdef UART2_EN
		#if(UART2_EN == 1)	
			UART2_Init();//UART2_��ʼ��
		#endif
	#endif
	
	#ifdef IDLE_MODE
		#if IDLE_MODE
			Idle_Wake_Up_Init(3000,7);//��Ҫ����Idle_IO_Init()��Idle_IORecovrey()����
		#endif
	#endif
	
	#ifdef Timer1_EN
		#if ((Timer1_EN == 1))
				Timer1_Init(1000);//��ʱ��1��ʼ��
		#endif
	#endif
	
	#ifdef Timer2_EN
		#if Timer2_EN
			Timer2_Init(1,0);//��ʱ��2��ʼ��
		#endif
	#endif
	
	#ifdef Timer3_EN
		#if Timer3_EN
				Timer3_Init(1000,0);//��ʱ��3��ʼ��
		#endif
	#endif
	
	#ifdef ExtInt0_EN
		#if ExtInt0_EN
			ExtInt0_Init(0,0x001);//�ⲿ�ж�0��ʼ��
		#endif
	#endif	
	
	#ifdef ExtInt1_EN
		#if ExtInt1_EN
			ExtInt1_Init(0);//�ⲿ�ж�1��ʼ��
		#endif
	#endif
	
	#ifdef ExtInt2_EN
		#if ExtInt2_EN
			ExtInt2_Init(0);//�ⲿ�ж�2��ʼ��
		#endif
	#endif	
	
	#ifdef ExtInt3_EN
		#if ExtInt3_EN
			ExtInt3_Init(0);//�ⲿ�ж�3��ʼ��
		#endif
	#endif	
	
	#ifdef ExtInt4_EN
		#if ExtInt4_EN
			ExtInt4_Init(0,0x000000);//0xFFFFFF//�ⲿ�ж�4��ʼ��
		#endif
	#endif
	
	#ifdef VolDet_EN
		#if	VolDet_EN
				LVDT_Init();//��ѹ/��ѹ����ʼ��
		#endif
	#endif

	#ifdef LED_SWITCH_EN
		#if	LED_SWITCH_EN
			#if (LED_SER_ARR_EN == 1)
				LED_SER_Init();//LED���е���ɨ���ʼ��
			#else
				LED_ARR_Init();//LED���е���ɨ���ʼ��
			#endif
		#endif
	#endif
	
	#ifdef PWM0_EN
		#if PWM0_EN
			PWM0_Set(0,4000,0,PWM0_PORT);//PWM0��ʼ��
		#endif
	#endif
	
	#ifdef PWM1_EN
		#if PWM1_EN
			PWM1_Set(0,4000,0,PWM1_PORT);//PWM1��ʼ��
		#endif
	#endif
	
	#ifdef PWM2_EN
		#if PWM2_EN
			PWM2_Set(1,4000,1500);//PWM2��ʼ��
		#endif
	#endif
		
		
	#ifdef PWM3_EN
		#if PWM3_EN
			PWM3_Set(0,4000,0);//PWM3��ʼ��
		#endif
	#endif
	
	#ifdef LCD_EN
		#if	LCD_EN
				LCD_Init();//LCD��ʼ��
		#endif
	#endif
	
	#ifdef EEPROM_EN
		#if (EEPROM_EN == 1)
			Eeprom_Init();//EEP��ʼ��
		#endif
	#endif
	
	#ifdef SPI_EN
		#if (SPI_EN == 1)
			SPI_Init();//SPI��ʼ��
		#endif
	#endif
	
#endif


#if (TRACEMODE == FALSE)
	 
		#ifdef UART0_EN
			#if(UART0_EN == 1)
				UART0_Init();//UART0_��ʼ��
			#endif
		#endif
		
		#ifdef UART1_EN
			#if(UART1_EN == 1)
				UART1_Init();//UART1_��ʼ��
			#endif
		#endif
		
		#ifdef UART2_EN
			#if(UART2_EN == 1)	
				UART2_Init();//UART2_��ʼ��
			#endif
		#endif
		
		#ifdef ADC_IS_OPEN
			#if ADC_IS_OPEN
				ADC_Init();//ADC��ʼ��
			#endif
		#endif
		
		#ifdef IDLE_MODE
			#if IDLE_MODE
				Idle_Wake_Up_Init(3000,7);//��Ҫ����dle_IO_Init()��Idle_IORecovrey()���������timer0���ж�ʱʹ�á�
			#endif
		#endif
		
		#ifdef PWM0_EN
			#if PWM0_EN
				PWM0_Set(0,4000,0,PWM0_PORT);//PWM0��ʼ��
			#endif
		#endif
		
		#ifdef PWM1_EN
			#if PWM1_EN
				PWM1_Set(0,4000,0,PWM1_PORT);//PWM1��ʼ��
			#endif
		#endif
		
		#ifdef PWM2_EN
			#if PWM2_EN
				PWM2_Set(0,4000,0);//PWM2��ʼ��
			#endif
		#endif
			
			
		#ifdef PWM3_EN
			#if PWM3_EN
				PWM3_Set(0,4000,0);//PWM3��ʼ��
			#endif
		#endif
	
		#ifdef Timer0_EN
			#if Timer0_EN
				Timer0_Init(1000);//��ʱ��0��ʼ��
			#endif
		#endif

		#ifdef Timer1_EN
			#if ((Timer1_EN == 1))
				Timer1_Init(1000);//��ʱ��1��ʼ��
			#endif
		#endif
		
		#ifdef Timer2_EN
			#if Timer2_EN
				Timer2_Init(1,0);//��ʱ��2��ʼ��
			#endif
		#endif
		
		#ifdef Timer3_EN
			#if Timer3_EN
				Timer3_Init(1000,0);//��ʱ��3��ʼ��
			#endif
		#endif
	
	#ifdef ExtInt0_EN
		#if ExtInt0_EN
			ExtInt0_Init(0,0x001);//�ⲿ�ж�0��ʼ��
		#endif
	#endif	
	
	#ifdef ExtInt1_EN
		#if ExtInt1_EN
			ExtInt1_Init(0);//�ⲿ�ж�1��ʼ��
		#endif
	#endif
	
	#ifdef ExtInt2_EN
		#if ExtInt2_EN
			ExtInt2_Init(0);//�ⲿ�ж�2��ʼ��
		#endif
	#endif	
	
	#ifdef ExtInt3_EN
		#if ExtInt3_EN
			ExtInt3_Init(0);//�ⲿ�ж�3��ʼ��
		#endif
	#endif	
	
	#ifdef ExtInt4_EN
		#if ExtInt4_EN
			ExtInt4_Init(0,0x000200);//0xFFFFFF//�ⲿ�ж�4��ʼ��
		#endif
	#endif

		#ifdef IICS_EN
			#if ((IICS_EN == 1) && (TRACEMODE == FALSE))
				IIC_Slave_Init(0XC1,1);//IIC�ӻ���ʼ��,0-Ϊѡ��PC4/5Ϊ���ڣ�1ѡ��PE4/5Ϊ����	   
			#endif
		#endif

		
		#ifdef VolDet_EN
			#if	VolDet_EN
				LVDT_Init();//��ѹ/��ѹ����ʼ��
			#endif
		#endif
		
		#ifdef LED_SWITCH_EN
			#if	LED_SWITCH_EN
				#if (LED_SER_ARR_EN == 1)
					LED_SER_Init();//LED���е���ɨ���ʼ��
				#else
					LED_ARR_Init();//LED���е���ɨ���ʼ��
				#endif
			#endif
		#endif
		
		#ifdef LCD_EN
			#if	LCD_EN
					LCD_Init();//LCD��ʼ��
			#endif
		#endif
		
		#ifdef EEPROM_EN
			#if (EEPROM_EN == 1)
				Eeprom_Init();//EEP��ʼ��
			#endif
		#endif
		
		#ifdef SPI_EN
			#if (SPI_EN == 1)
				SPI_Init();//SPI��ʼ��
			#endif
		#endif
		
#endif
}

//-----------------------------------------------------------------//
//�������ƣ� void MCU_Init(void)
//��������:		MUC��ʼ��
//��������� ��
//�� �� ֵ�� ��
//-----------------------------------------------------------------//
void MCU_Init(void)
{	 

	BOR_SET(0);//0Ϊ�����縴λ��1�ص��縴λ
	
	//���Ź���ʼ��
	WDT_Init();

	//���ú˹���ʱ��
	Set_Sys_Clk();

	//�����ֶԱ��ж�
	CFG_Check();

	//IO��Ĭ������
	Default_Set_IO();

	//IO�ڳ�ʼ��
	Init_IO();

	//����ģʽ��ʼ��
	Trace_Mode_Init();

	//���ܺ�����ʼ��
	Function_Init(); 
	
	//CTK��ʼ��	
	CTK_Init();

}