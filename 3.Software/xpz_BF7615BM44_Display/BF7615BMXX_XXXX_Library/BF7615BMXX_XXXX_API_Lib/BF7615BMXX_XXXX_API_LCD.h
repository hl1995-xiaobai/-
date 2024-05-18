#ifndef __BF7615BMXX_XXXX_API_LCD_H__
#define __BF7615BMXX_XXXX_API_LCD_H__

#define LCD_EN									0// 1:ʹ�ܱ��룬0:��ʹ�ܱ���
#if LCD_EN
	#define LED_LCD_FUN_SET(x)  		{DP_CON &= ~(0x40);DP_CON 	|= (0x40&(x<<6));}//1ΪLED_LCD���ܿ���0ΪLED_LCD���ܹ�
	#define LCD_FUN_SET(x)    			{DP_CON &= ~(0x04);DP_CON 	|= (0x04&(x<<2));}//1ΪLED���ܣ�0ΪLCD����
	#define LCD_CLK_SET(x)    			{DP_MODE &= ~(0x60);DP_MODE |= (0x60&(x<<5));}//0Ϊ�ڲ�RC32K,1Ϊ�ⲿ����32768Hz��2�ڲ�RC1MHz
	#define LCD_RES_SET(x)    			{DP_MODE &= ~(0x10);DP_MODE |= (0x10&(x<<4));}//0ΪLCDƫ�õ���225K��1ΪLCDƫ�õ���900K
	#define LCD_COM_WIDTH_SET(x)    {SCAN_WIDTH &= ~(0xFF);SCAN_WIDTH |= (0xFF&(x<<0));}//LCDʱ��Ϊ1Mʱ����COMɨ��ʱ������(SCAN_WIDTH+1)*64,0.064ms~4.096ms
	#define LCD_CHARGE_SET(x)    		{DP_MODE &= ~(0x0C);DP_MODE |= (0x0C&(x<<2));}//���ʱ����ƣ�0Ϊ1/8 COM���ڣ�1Ϊ1/16 COM���ڣ�2Ϊ1/32 COM���ڣ�3Ϊ1/64 COM����
	#define LCD_MODE_SET(x)    			{DP_MODE &= ~(0x03);DP_MODE |= (0x03&(x<<0));}//����ģʽ���ƣ�0Ϊ��ͳ����ģʽ(225K/900K)��1Ϊ��ͳ����ģʽ(60K)��2Ϊ1/32 COM���ڣ�3Ϊ���ٳ��ģʽ(�Զ���60K/225K/900K֮���л�)
	#define LCD_CONSTRAT_EN_SET(x)  {DP_CON1 &= ~(0x10);DP_CON1 |= (0x10&(x<<4));}//�Աȶ�ʹ�ܣ�0Ϊ�رնԱȿ��ƣ�1Ϊ�򿪶Աȿ���
	#define LCD_CONSTRAT_SET(x)  		{DP_CON1 &= ~(0x0F);DP_CON1 |= (0x0F&(x<<0));}//�Աȶȵ�ѹѡ��(0~15)--(0.531V~1.00V)
	#define LCD_SEG_SEL_SET(x)  		{REG_ADDR = 0x1F;REG_DATA &= ~(0xFF);REG_DATA |= (0xFF&(x));REG_ADDR = 0x20;REG_DATA &= ~(0xFF);REG_DATA |= (0xFF&(x>>8));REG_ADDR = 0x21;REG_DATA &= ~(0xFF);REG_DATA |= (0xFF&(x>>16));REG_ADDR = 0x22;REG_DATA &= ~(0xFF);REG_DATA |= (0x0F&(x>>24));}//��Ӧ��λΪ1ʱѡ��ΪLCD����,SEG0~SEG27
	//SEG��ѡ��SEG0~SEG27,��Ӧ��λΪ1,ѡ��ΪSEG�ڹ���
	#define LCD_DUTY_SET(x)  				{DP_CON &= ~(0x38);DP_CON 	|= (0x38&(x<<3));}//ռ�ձ����ã�

	//0:1/4ռ�ձ�,1/3 ƫ��(COM0~COM3)--4*16,SEG0~SEG7,SEG16~SEG23
	//1:1/8ռ�ձ�,1/4 ƫ��(COM0~COM7)--8*16,SEG0~SEG7,SEG16~SEG23
	//2:1/4ռ�ձ�,1/3 ƫ��(COM0~COM3)--4*20,SEG0~SEG7,SEG16~SEG23,COM4~COM7����ΪSEG24~SEG27
	//3:1/5ռ�ձ�,1/3 ƫ��(COM0~COM4)--5*19,SEG0~SEG7,SEG16~SEG23,COM5~COM7����ΪSEG25~SEG27
	//4:1/6ռ�ձ�,1/3 ƫ��(COM0~COM5)--6*18,SEG0~SEG7,SEG16~SEG23,COM6~COM7����ΪSEG26~SEG27
	//5:1/6ռ�ձ�,1/4 ƫ��(COM0~COM5)--4*18,SEG0~SEG7,SEG16~SEG23��COM6-7 ����Ϊ SEG26-SEG27
	//6/other:1/4ռ�ձ�,1/3 ƫ��(COM0~COM3)--4*16,SEG0~SEG7,SEG16~SEG23

	#define LCD_START_SET(x)  			{SCAN_START &= ~(0x01);SCAN_START |= (0x01&(x<<0));}//LCDɨ�迪ʼֹͣ���ƣ�0Ϊֹͣɨ�裬1Ϊ��ʼɨ��


	#define LCD_IE_SET IEN1 |= 0X40																	//��LCD�ж�ʹ��
	#define LCD_IE_CLR IEN1 &= ~0X40																//��LCD�ж�ʹ��
	#define LCD_IP_SET IPL1 |= 0X40																	//����LCD�ж����ȼ�Ϊ��
	#define LCD_IP_CLR IPL1 &= ~0X40																//����LCD�ж����ȼ�Ϊ��
	#define LCD_INT_FLAG_CLR IRCON1 &= ~0x40;INT_PE_STAT = ~0x02		// ���LCD�жϱ�־λ

	extern void LCD_Data(uchar com,ulong seg);
	extern void LCD_Init(void);


	extern uchar code Lcd_ser_num1[];
					
	extern uchar code Lcd_dp1;
	extern uchar code Lcd_dp2;
	extern uchar code Lcd_dp3;
	extern uchar code Lcd_dp4;
	extern uchar code Lcd_dp5;
	extern uchar code Lcd_dp6;

#endif

#endif