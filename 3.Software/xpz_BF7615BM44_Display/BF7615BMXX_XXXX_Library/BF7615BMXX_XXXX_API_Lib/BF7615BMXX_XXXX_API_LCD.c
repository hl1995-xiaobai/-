#include ".\BF7615BMXX_XXXX_Library\Config.h"
	
#if (LCD_EN == 1)
		#pragma message "����,LCD����"
		uchar code Lcd_ser_num1[10]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};//0~9
		
		uchar code Lcd_dp1 = 	0x80;
		uchar code Lcd_dp2 = 	0x80;
		uchar code Lcd_dp3 = 	0x80;
		uchar code Lcd_dp4 = 	0x80;
		uchar code Lcd_dp5 = 	0x01;
		uchar code Lcd_dp6 = 	0x02;
	//-----------------------------------------------------------------//
	//�������ƣ� void LCD_Data(uchar com,ulong seg)
	//�������ܣ� LCD������ʾ����
	//��������� uchar com��0~7,COM�ڣ�ulong seg��SEG����,��Ӧ��λΪ1ѡ�ж�ӦSEG
	//��������� ��
	//�� �� ֵ�� ��
	//-----------------------------------------------------------------//

	void LCD_Data(uchar com,ulong seg)
	{
			uchar i = 0,j = 0;
			for(j = 0; j < 8; j++)
			{
				if(j == com)
				{
					for (i = 0; i < 28; i++)
					{
						if(i < 8)
						{
							XBYTE[0x1000+i] &= ~(0x01<<com);
							if(((seg)&((0x01)<<i)))
							{
								XBYTE[0x1000+i] |= (0x01<<com);
							}
						}
						else if(i < 16)
						{
							XBYTE[0x1000+i] &= ~(0x01<<com);
							if(((seg>>8)&((0x01)<<(i-8))))
							{
								XBYTE[0x1000+i] |= (0x01<<com);
							}
						}
						else if(i < 24)
						{
							XBYTE[0x1000+i] &= ~(0x01<<com);
							if(((seg>>16)&((0x01)<<(i-16))))
							{
								XBYTE[0x1000+i] |= (0x01<<com);
							}
						}
						else if(i < 28)
						{
							XBYTE[0x1000+i] &= ~(0x01<<com);
							if(((seg>>24)&((0x01)<<(i-24))))
							{
								XBYTE[0x1000+i] |= (0x01<<com);
							}
						}
					}							
				}
			}
	}

	//-----------------------------------------------------------------//
	//�������ƣ� void LCD_Init(void)  
	//�������ܣ� LCD��ʼ��
	//��������� ��
	//��������� ��
	//�� �� ֵ�� ��
	//-----------------------------------------------------------------//
	void LCD_Init(void) 
	{ 
			uchar i = 0,j = 0;
			EA = 0;//�����жϣ�
			LCD_IP_SET;//����LCD�ж��ż�Ϊ�ߣ�����ʵ��Ӧ���������ȼ�
			LCD_INT_FLAG_CLR;//���LCD�жϱ�־
			LED_LCD_FUN_SET(1);//1ΪLED_LCD���ܿ���0ΪLED_LCD���ܹ�
			LCD_FUN_SET(0);//1ΪLED���ܣ�0ΪLCD����
			LCD_CLK_SET(0);//0Ϊ�ڲ�RC32K,1Ϊ�ⲿ����32768Hz��2�ڲ�RC1MHz
			LCD_RES_SET(0);//0ΪLCDƫ�õ���225K��1ΪLCDƫ�õ���900K
			LCD_COM_WIDTH_SET(32);//��LCD_CLK_SET(2)ʱ��������Ч��LCDʱ��Ϊ1M����COMɨ��ʱ������(SCAN_WIDTH+1)*64,0.064ms~4.096ms
			LCD_CHARGE_SET(0);//���ʱ����ƣ�0Ϊ1/8 COM���ڣ�1Ϊ1/16 COM���ڣ�2Ϊ1/32 COM���ڣ�3Ϊ1/64 COM����
			LCD_MODE_SET(1);//����ģʽ���ƣ�0Ϊ��ͳ����ģʽ(225K/900K)��1Ϊ��ͳ����ģʽ(60K)��2Ϊ1/32 COM���ڣ�3Ϊ���ٳ��ģʽ(�Զ���60K/225K/900K֮���л�)
			LCD_CONSTRAT_EN_SET(1);//�Աȶ�ʹ�ܣ�0Ϊ�رնԱȿ��ƣ�1Ϊ�򿪶Աȿ���
			LCD_CONSTRAT_SET(9);//�Աȶȵ�ѹѡ��(0~15)--(0.531V~1.00V)
			LCD_SEG_SEL_SET(0x00FFFFFF);
			LCD_DUTY_SET(1);//ռ�ձ����ã�
			
			//0:1/4ռ�ձ�,1/3 ƫ��(COM0~COM3)--4*16,SEG0~SEG7,SEG16~SEG23
			//1:1/8ռ�ձ�,1/4 ƫ��(COM0~COM7)--8*16,SEG0~SEG7,SEG16~SEG23
			//2:1/4ռ�ձ�,1/3 ƫ��(COM0~COM3)--4*20,SEG0~SEG7,SEG16~SEG23,COM4~COM7����ΪSEG24~SEG27
			//3:1/5ռ�ձ�,1/3 ƫ��(COM0~COM4)--5*19,SEG0~SEG7,SEG16~SEG23,COM5~COM7����ΪSEG25~SEG27
			//4:1/6ռ�ձ�,1/3 ƫ��(COM0~COM5)--6*18,SEG0~SEG7,SEG16~SEG23,COM6~COM7����ΪSEG26~SEG27
			//5:1/6ռ�ձ�,1/4 ƫ��(COM0~COM5)--4*18,SEG0~SEG7,SEG16~SEG23��COM6-7 ����Ϊ SEG26-SEG27
			//6/other:1/4ռ�ձ�,1/3 ƫ��(COM0~COM3)--4*16,SEG0~SEG7,SEG16~SEG23
			

			LCD_Data(0,0xFFFFFFFF);//0x00000000
			LCD_Data(1,0xFFFFFFFF);
			LCD_Data(2,0xFFFFFFFF);
			LCD_Data(3,0xFFFFFFFF);
			LCD_Data(4,0x00FFFFFF);
			LCD_Data(5,0x00FFFFFF);
			LCD_Data(6,0x00FFFFFF);
			LCD_Data(7,0x00FFFFFF);

			LCD_IE_SET;//��LCD�ж�ʹ��
			EA = 1;//�����ж�
			LCD_START_SET(1);//LCDɨ�迪ʼֹͣ���ƣ�0Ϊֹͣɨ�裬1Ϊ��ʼɨ��
	}
	
	//-----------------------------------------------------------------//
	//�������ƣ� void LCD_ISR() interrupt 13 
	//�������ܣ� LCD�жϷ�����
	//��������� ��
	//��������� ��
	//�� �� ֵ�� ��
	//-----------------------------------------------------------------//
	void LCD_ISR() interrupt 13
	{
		static uchar xdata addr_bak = 0;
		PUSH_REG_ADDR_SFR();
		LCD_INT_FLAG_CLR;	  // ���LCD�жϱ�־λ
		LCD_START_SET(1);	 //LCDɨ�迪ʼֹͣ���ƣ�0Ϊֹͣɨ�裬1Ϊ��ʼɨ��
		POP_REG_ADDR_SFR();
	}	

#endif