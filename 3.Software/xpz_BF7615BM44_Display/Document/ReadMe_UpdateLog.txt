/****************************************************/
BYD_MCU02D_BF7615BMXX_XXXX_V1.1.3
�������ڣ�2023-03-24
1)��void LCD_Init(void) �����е�������䣺
LCD_IE_SET;//����LCD�ж��ż�Ϊ�ߣ�����ʵ��Ӧ���������ȼ�
��Ϊ��
LCD_IP_SET;//����LCD�ж��ż�Ϊ�ߣ�����ʵ��Ӧ���������ȼ�
�������ڣ�2023-03-24
1)ɾ��sleepģ��
2���޸���idle.c�ļ��е�void Idle()�������޸���Touch_MCU_Init.h�ļ��е� DELAY_MS_EN���ֵ
3)��void Function_Init(void)�����е����´��룺
		#ifdef Timer2_EN
			#if Timer3_EN
				Timer3_Init(1000,0);//��ʱ��3��ʼ��
			#endif
		#endif
��Ϊ
		#ifdef Timer3_EN
			#if Timer3_EN
				Timer3_Init(1000,0);//��ʱ��3��ʼ��
			#endif
		#endif
4���޸��˽�IICʹ��IICS_EN������Ϊ1�����Ĵ�
5��ɾ����config.h�ļ����ظ��ĺꡰ#define FTH_PARA 300//����ģʽ��ָ��ֵ��ֻ����һ�� 
6����LCD.h�ͺ�LCD.c�ļ�������ģʽռ�ձȼĴ������ú� LCD_DUTY_SET������ע��
	//0:1/4ռ�ձ�,1/3 ƫ��(COM0~COM3)--4*16,SEG0~SEG7,SEG16~SEG23
	//1:1/8ռ�ձ�,1/4 ƫ��(COM0~COM7)--8*16,SEG0~SEG7,SEG16~SEG23
	//2:1/4ռ�ձ�,1/3 ƫ��(COM0~COM3)--4*20,SEG0~SEG7,SEG16~SEG23,COM4~COM7����ΪSEG24~SEG27
	//3:1/5ռ�ձ�,1/3 ƫ��(COM0~COM4)--5*19,SEG0~SEG7,SEG16~SEG23,COM5~COM7����ΪSEG24~SEG26
	//4:1/6ռ�ձ�,1/3 ƫ��(COM0~COM5)--6*18,SEG0~SEG7,SEG16~SEG23,COM6~COM7����ΪSEG24~SEG25
	//5:1/6ռ�ձ�,1/4 ƫ��(COM0~COM3)--4*16,SEG1~SEG7,SEG16~SEG23
	//6/other:1/4ռ�ձ�,1/3 ƫ��(COM0~COM3)--4*16,SEG1~SEG7,SEG16~SEG23
	�޸�Ϊ
	//0:1/4ռ�ձ�,1/3 ƫ��(COM0~COM3)--4*16,SEG0~SEG7,SEG16~SEG23
	//1:1/8ռ�ձ�,1/4 ƫ��(COM0~COM7)--8*16,SEG0~SEG7,SEG16~SEG23
	//2:1/4ռ�ձ�,1/3 ƫ��(COM0~COM3)--4*20,SEG0~SEG7,SEG16~SEG23,COM4~COM7����ΪSEG24~SEG27
	//3:1/5ռ�ձ�,1/3 ƫ��(COM0~COM4)--5*19,SEG0~SEG7,SEG16~SEG23,COM5~COM7����ΪSEG25~SEG27
	//4:1/6ռ�ձ�,1/3 ƫ��(COM0~COM5)--6*18,SEG0~SEG7,SEG16~SEG23,COM6~COM7����ΪSEG26~SEG27
	//5:1/6ռ�ձ�,1/4 ƫ��(COM0~COM5)--4*18,SEG0~SEG7,SEG16~SEG23��COM6-7 ����Ϊ SEG26-SEG27
	//6/other:1/4ռ�ձ�,1/3 ƫ��(COM0~COM3)--4*16,SEG0~SEG7,SEG16~SEG23
7��ɾ����#define T0_CT_MODE(x)��Ķ����ʹ��
8��ɾ����#define T1_CT_MODE(x)��Ķ����ʹ��
9) ɾ����timer.c��timer.h�ļ��ж�ʱ���������ܵ�����
10)������MCU_Init.c�ļ���SYS_CLK_SET(SYS_CLK);���ı�ע
BYD_MCU02D_BF7615BMXX_XXXX_V1.1.2		
�������ڣ�2022-06-28
1)�޸���CTK_Touch.c�ļ���BF7615BMXX_XXXX_Set_Touch_Flag������#if TRACEMODE���ж��´����־λ�ļ�����룬
����˰���������32ʱ��32���Ժ󰴼����Դ����޴�����־λ��Bug��
�������ڣ�2021-09-26
1)�޸�Read_ROM_Offset����ֵ����Bug��
BYD_MCU02D_BF7615BMXX_XXXX_V1.1.1
�������ڣ�2021-08-12
1)�޸�FTH����>3276����Ӧ���Bug��
BYD_MCU02D_BF7615BMXX_XXXX_V1.1.0
�������ڣ�2021-05-12
1)�޸�ADJUST_LINE�꣬RESOΪ15/16bitʱ����Ӧ���Bug��
BYD_MCU02D_BF7615BMXX_XXXX_V1.0.9
2021-4-19
1)�޸���RENOVATE_MODEΪ1ʱ��differ<=p_noise�����벻ͨ�����⡣��
BYD_MCU02D_BF7615BMXX_XXXX_V1.0.8
2021-3-24
1)����IO��ʼ����CTK֮ǰʱ��CTK��ʼ��Ӱ�� PC4/PC5 IO�����ʼ����
��TRISC |= ((open_sns_h >> 6)  & 0xFF);���޸�Ϊ��TRISC |= ((open_sns_h >> 6)  & 0x0F);TRISC |= ((open_sns_h >> 4)  & 0xC0);��
BYD_MCU02D_BF7615BMXX_XXXX_V1.0.7
2021-3-23
1)�޸ı�ע���õ�IAP����ʱ�����Ӷ�EEP������ȡrom_offsetƫ�Ƶ�ַ����
2)������TRISC |= ((open_sns_h >> 4)  & 0xFF);��Ϊ��TRISC |= ((open_sns_h >> 6)  & 0xFF);��
BYD_MCU02D_BF7615BMXX_XXXX_V1.0.6
2021-2-18
1)����LVDT��ܴ������������󴥲ο���
2���������ߵ�ַ�Ĵ������ֳ���������Ϊ���ж��о�̬������
3��ע��UART��ѯ��ʽ�������ݣ�Ĭ�Ͽ��������жϣ�
4)�õ�IAP����ʱ�����Ӷ�EEP������ȡrom_offsetƫ�Ƶ�ַ��
BYD_MCU02D_BF7615BMXX_XXXX_V1.0.5
2021-1-6
1)�޸�CTK_RBĬ�ϲ���Ϊ60K,ADJUST_LINE-����ӦĿ����Ϊ���ֱ��ʼ�����70%
2)�жϺ���������PUSH_REG_ADDR_SFR,POP_REG_ADDR_SFR
3)�޸�SPI_CS_SET(x)��ΪSPI_CS_SET(),����SPI_CS_CLR()��,����SPI���Ͳο�����
2020-12-9
1)����XXX_API_Timer.h�ļ�T2_IP_CLR�궨��
2)������TRISC |= ((open_sns_h >> 6)  & 0xFF);��Ϊ��TRISC |= ((open_sns_h >> 4)  & 0xFF);��
3)����UART2_INT_IF_XX_CLR(x)��ADC_CTRL(x)����
4)����CTK_VTH_SET(x)ע��
5)�Ż�Idle����
BYD_MCU02D_BF7615BMXX_XXXX_V1.0.4
2020-10-29
1)����Eeprom_Write_Byteb/NVR_Write_Byte����ע�ͣ�
2)����PF0~PF3λ����
3)�޸�BF7615BMXX_XXXX_API_SPI.h�ļ���궨�壻
4)�Ż�CTK_BF7615BMXX_XXXX_Get_KEYS_Touch()����
BYD_MCU02D_BF7615BMXX_XXXX_V1.0.3
20-09-17
1)����T2_IE_SET/CLR,T2_IP_SET/CLR��
2)�޸�IdleģʽCTK������
3)����EEPROM_ERASE_TIMER_SET(X);//ע��
4)����UART2_TRANS_EN_SET(x)//ע��,����UART2_TRANS_ENABLE()��UART2_TRANS_DISABLE()��
5)�Ż��������ж�
6)����ADC_VIN�����ע��
7)����ADC_SEL04/05ע��
8)XXX_API_LibĿ¼����XXX.API_Read_UID.c/h�ļ�,оƬUID��ȡ����
9)�Ż���Get_ADC_Vref������Get_Inner_ADC_Vol����������EA���ء�
20-08-14
1)����"INT4_29_FUN_SET(x)"��Ϊ��INT4_19_FUN_SET(x)��
2)���¹�����Ϊ��BYD_MCU02D_BF7615BMXX_XXXX_V1.0.X��
BYD_MCU02D_BF7615BMXX_XXXX_V1.0.2
1)�޸���ʼ�����Bug,"TRISE |= ((open_sns_h >> 14) & 0x0F);//����Ϊ���롰��
2)���ӡ�Get_ADC_Vref������Get_Inner_ADC_Vol������,ADC�ο���ѹУ׼ֵ��ȡ������ADC�ڲ�ͨ�������ѹ��ȡ������
BYD_MCU02D_BF7615BMXX_V1.0.1
1)����SFR (P2_XH)0xA0��ַ��ʹ��MOVX @Ri,Aָ�� ����PDATA��ʱ��P2_XH��0�����������Ҫ������PDATA��������XDATA����
BYD_MCU02D_BF7615BMXX_V1.0.0
1)���档
/****************************************************************************************/
˵����
���̽����ο�
1�������ײ�����������������������Ի���Ӧ�Ը��ã�ʵ��Ӧ����Ŀ����ʵ�ʿ���������֤Ϊ׼��
2��Keil����������Զ�ջ��С�����ƣ���ջ������DATA��IDATA����������������ж��뺯�������й�
3�����Գ���һ�㽨��Ԥ������50���ֽڣ�������ʵ����ĿӦ�ò�����֤Ϊ׼��
/****************************************************************************************/