#ifndef __BF7615BMXX_XXXX_API_LED_H__
#define __BF7615BMXX_XXXX_API_LED_H__


#define	LED_SWITCH_EN				0//LED_ENʹ������	 	  1:ʹ�ܱ��룬0:��ʹ�ܱ���
#define	LED_SER_ARR_EN			1//LED_SER_ARR_EN	ʹ������	1:���е���0:���о���
#define	LED_MODE						1//LEDɨ��ģʽѡ��	1:ѭ��ģʽ��0:�ж�ģʽ

#define LED_LCD_FUN_SET(x)    {DP_CON &= ~(0x40);DP_CON |= (0x40&(x<<6));}//1ΪLED_LCD���ܿ���0ΪLED_LCD���ܹ�
#define LED_SER_FUN_SET(x)    {DP_CON &= ~(0x04);DP_CON |= (0x04&(x<<2));}//1ΪLED���ܣ�0ΪLCD����
#define LED_SER_COM_SET(x)   	{DP_CON &= ~(0x01);DP_CON |= (0x01&(x<<0));}//COM�����ѡ��0Ϊ��������1Ϊ����(������LED/LCDӲ��ɨ��ʱ����Ч)
#define LED_SER_MODE_SET(x)   {DP_MODE &= ~(0x80);DP_MODE |= (0x80&(x<<7));}//1Ϊ���е���ģʽ��0Ϊ���о���ģʽ��
#define LED_SER_MATRIX_SET(x) {DP_CON &= ~(0x38);DP_CON |= (0x38&(x<<3));}//LED���е������ѡ��(X*Y) 0-4*5��1-5*6��2-6*7��3-7*8,4-4*5(��PB3Ϊ��ʼ�˿�)
#define LED_SER_CURRENT_SET(x){REG_ADDR = 0x31;REG_DATA &= ~(0x0F);REG_DATA |= (0x0F&(x<<0));}	//LED������������(0~15)�����չ������(0-3.7mA),(9-43.7mA),(15-68.7mA)@LEDѹ��2.5V
#define LED_SER_LED1_WIDTH_SET(x)  (SCAN_WIDTH = x)   							//�����Ƶ�ͨʱ��1���ã�(x+1)*16us
#define LED_SER_LED2_WIDTH_SET(x)  (LED2_WIDTH = x)									//�����Ƶ�ͨʱ��2���ã�(x+1)*16us
#define LED_SER_SCAN_SET(x)   {DP_CON &= ~(0x02);DP_CON |= (0x02&(x<<1));}//LEDɨ��ģʽѡ��0Ϊ�ж�ģʽ��1Ϊѭ��ģʽ 
#define LED_START_SET(x)  		{SCAN_START &= ~(0x01);SCAN_START |= (0x01&(x<<0));}//LEDɨ�迪ʼֹͣ���ƣ�0Ϊֹͣɨ�裬1Ϊ��ʼɨ��



#define LED_ARR_FUN_SET(x)    {DP_CON &= ~(0x04);DP_CON |= (0x04&(x<<2));}//1ΪLED���ܣ�0ΪLCD����
#define LED_ARR_SEG_SET(x)    {REG_ADDR = 0x24;REG_DATA &= ~(0xFF);REG_DATA |= (0xFF&(x<<0));}//LED���о���SEG��ѡ��,��Ӧ��λΪ1ѡ��ΪSEG�ڹ���
#define LED_ARR_CON_EN(x)     {REG_ADDR = 0x23;REG_DATA &= ~(0xFF);REG_DATA |= (0xFF&(x<<0));}//LED���о���COM��ѡ��,��Ӧ��λΪ1ѡ��ΪCOM�ڹ���
#define LED_ARR_COM_SET(x)   	{DP_CON &= ~(0x01);DP_CON |= (0x01&(x<<0));}//COM�����ѡ��0Ϊ��������1Ϊ����(������LED/LCDӲ��ɨ��ʱ����Ч)
#define LED_ARR_MODE_SET(x)   {DP_MODE &= ~(0x80);DP_MODE |= (0x80&(x<<7));}//1Ϊ���е���ģʽ��0Ϊ���о���ģʽ��
#define LED_ARR_COM_TIME(x) 	(SCAN_WIDTH = x)   							//����COM��ͨʱ��1���ã�(x+1)*16us
#define LED_ARR_DUTY_SET(x) 	{DP_CON &= ~(0x38);DP_CON |= (0x38&(x<<3));}//LED���о���COMͨ��ռ�ձ�ѡ��(0~7) (x+1)/8
#define LED_ARR_SCAN_SET(x)   {DP_CON &= ~(0x02);DP_CON |= (0x02&(x<<1));}//LED���о���ɨ��ģʽѡ��0Ϊ�ж�ģʽ��1Ϊѭ��ģʽ 
#define LED_ARR_START_SET(x)  {SCAN_START &= ~(0x01);SCAN_START |= (0x01&(x<<0));}//LEDɨ�迪ʼֹͣ���ƣ�0Ϊֹͣɨ�裬1Ϊ��ʼɨ��


#define LED_IE_SET IEN1 |= 0X40																	//��LED�ж�ʹ��
#define LED_IE_CLR IEN1 &= ~0X40																//��LED�ж�ʹ��
#define LED_IP_SET IPL1 |= 0X40																	//����LED�ж����ȼ�Ϊ��
#define LED_IP_CLR IPL1 &= ~0X40																//����LED�ж����ȼ�Ϊ��
#define LED_INT_FLAG_CLR IRCON1 &= ~0x40;INT_PE_STAT = ~0x01			// ���LED�жϱ�־λ


#if(LED_SWITCH_EN == 1)
	#if (LED_SER_ARR_EN == 1)
		extern void LED_SER_Init(void);
		extern void LED_SER_Data(ulong led_data_h,ulong led_data_l);
		extern void LED_SER_Light_Set(ulong led_width_h,ulong led_width_l);
		#if (LED_MODE == 0)
			extern void LED_SER_Light_Set_Int(ulong led_width_h,ulong led_width_l);
		#endif
		extern void LED_SER_Dis_Num(uchar num,uchar dis_data);

		extern uchar code Led_ser_num[];
		extern uchar code Led_dp1;
		extern uchar code Led_dp2;
		extern uchar code Led_dp3;
		extern uchar code Led_dp4;
		extern uchar code Led_dp5;
		extern uchar code Led_dp6;
		extern ulong xdata LED_H_Tem;
		extern ulong xdata LED_L_Tem;
		extern ulong xdata LED_Light_H_Tem;
		extern ulong xdata LED_Light_L_Tem;
	#endif
	
	#if (LED_SER_ARR_EN == 0)
		extern void LED_ARR_Init(void);
		extern void LED_ARR_Data(uchar com,uchar seg_data);
		extern uchar code Led_arr_num1[];
	#endif

#endif

#endif