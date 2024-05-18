#include "include.h"

#include ".\BF7615BMXX_XXXX_Library\Config.h"

#if ((UART0_EN == 1)||(UART1_EN == 1))	
/****************************************************************/
//��������uchar UART_Rece_Check(uchar n,uchar *nSendByte)  
//��  �ܣ�UART����У��
//��  ����uchar n:����У���ֽ�����uchar *nSendByte����������ָ��
//����ֵ��uchar ����У��ֵ
/****************************************************************/

uchar UART_Rece_Check(uchar n,uchar *nCheckByte1,uchar *nCheckByte2)  
{
		uchar i = 0;
		for(i = 0; i < n; i++)
		{
			if((*(nCheckByte1 + i)) != (*(nCheckByte2 + i)))
			{
					return 1;
			}
		}	
		return 0;
}
#endif

#if UART0_EN
#pragma message "����,UART0����"
/****************************************************************/
//��������void UART0_Send_NByte(uchar n,uchar *nSendByte)  
//��  �ܣ�UART0����N BYTES
//��  ����uchar n:�����ֽ�����uchar *nSendByte����������ָ��
//����ֵ����
/****************************************************************/

//void UART0_Send_NByte(uchar n,uchar *nSendByte)  
//{
//		uchar i = 0;
//		for(i = 0; i < n; i++)
//		{
//			UART0_Send_Byte(*(nSendByte + i));
//		}		
//}
#endif	

#if UART1_EN
#pragma message "����,UART1����"
/****************************************************************/
//��������void UART1_Send_NByte(uchar n,uchar *nSendByte)  
//��  �ܣ�UART1����N BYTES
//��  ����uchar n:�����ֽ�����uchar *nSendByte����������ָ��
//����ֵ����
/****************************************************************/

//void UART1_Send_NByte(uchar n,uchar *nSendByte)  
//{
//		uchar i = 0;
//		for(i = 0; i < n; i++)
//		{
//			UART1_Send_Byte(*(nSendByte + i));
//		}		
//}
#endif


#if (UART0_EN == 1)

	

	
	//-----------------------------------------------------------------//
	//�������ƣ� void UART0_Init(void)  
	//�������ܣ� UART0��ʼ��
	//��������� ��
	//��������� ��
	//�� �� ֵ�� ��
	//-----------------------------------------------------------------//
	void UART0_Init(void) 
	{ 
			EA = 0;//�����жϣ�
			UART0_IP_SET;//����UART0�ж��ż�Ϊ�ߣ�����ʵ��Ӧ���������ȼ�
			UART0_INT_FLAG_CLR;//���UART0�жϱ�־
			UART0_PORT_SET(UART0_PORT);//UART_PC(RXD0C-TXD0C)ӳ��ΪPC4/5Ϊ���ڣ�UART_PE(RXD0A-TXD0A)��ΪPE4/5Ϊ���ڣ�UART_PF(RXD0B-TXD0B)��ΪPF4/5Ϊ����
			
		#if (UART0_PORT == UART0_PC)
			REG_ADDR = 0x19;REG_DATA |= 0x10;//PC4��������
			REG_ADDR = 0x19;REG_DATA |= 0x20;//PC5��������
			
			REG_ADDR = 0x26;REG_DATA &= ~0x40;TRISC |= 0x10;//PC4����RXD0Ϊ����
			REG_ADDR = 0x26;REG_DATA &= ~0x80;TRISC &= ~0x20;//PC5����TXD0Ϊ���
		#elif(UART0_PORT == UART0_PE)

			REG_ADDR = 0x1B;REG_DATA |= 0x10;//PE4��������
			REG_ADDR = 0x1B;REG_DATA |= 0x20;//PE5��������
			REG_ADDR = 0x27;REG_DATA &= ~0x01;TRISE |= 0x10;//PE4����RXD0Ϊ����
			REG_ADDR = 0x27;REG_DATA &= ~0x02;TRISE &= ~0x20;//PE5����TXD0Ϊ���
			
		#elif(UART0_PORT == UART0_PF)
			REG_ADDR = 0x1C;REG_DATA |= 0x10;//PF4��������
			REG_ADDR = 0x1C;REG_DATA |= 0x20;//PF5��������
			REG_ADDR = 0x28;REG_DATA &= ~0x01;TRISF |= 0x10;//PF4����RXD0Ϊ����
			REG_ADDR = 0x28;REG_DATA &= ~0x02;TRISF &= ~0x20;//PF5����TXD0Ϊ���
		#else

		#endif

		UART0_BDL = (uchar)M_HEX_OF_BR(UART0_CFG_BAUD_RATE);//���ò�����=BUSCLK/(16*(UART0_BDH[0:1],UART0_BDL))
		UART0_CON2 = ((((uint)(M_HEX_OF_BR(UART0_CFG_BAUD_RATE)))>>8)&0x03);//����UART0_BDH[0:1]����λ
		UART0_CON2 |= (UART0_TX_EN);//�����ж�ʹ�ܣ�0Ϊ��ֹ�����жϣ�1Ϊ�������ж�
		UART0_CON2 |= (UART0_RX_EN);//�����ж�ʹ�ܣ�0Ϊ��ֹ�����жϣ�1Ϊ��������ж�
		UART0_CON1 |= (UART0_MUDULE_EN);//ʹ��UAERT0ģ��
		UART0_CON1 &= (~UART0_MULTI);//1:ʹ�ܶദ����ͨ��,0:��ʹ�ܶദ����ͨ��
		UART0_CON1 |= (UART0_RE_EN);//��������ʹ��
		UART0_CON1 &= (~UART0_SEND_MODE); //��������ģʽbit[3]��0����λģʽ��1��9λģʽģʽ
		UART0_CON1 |= (UART0_STOP_BIT);//ֹͣλ;1:2λ��0��1λ
		UART0_CON1 &= (~UART0_ODD_EVEN_EN);//��żУ��ʹ��1��������żУ�飻0:�ر���żУ��
		UART0_CON1 |= (UART0_ODD_EVEN_SE);//��żУ��ѡ��1����У�飻0:żУ��
		UART0_STATE &= ((~UART0_RI)&(~UART0_TI));//��������жϱ�־λ//��������жϱ�־λ
		UART0_IE_SET;//��UART�ж�ʹ��				
		EA = 1;//�����ж�
	}
	
//	#pragma disable //���Ͳ����������жϴ��
//	void UART0_Send_Word(uint willSendWord)   
//	{
//			UART0_Send_Byte(willSendWord>>8);
//			UART0_Send_Byte((uchar)willSendWord);
//	}
	
//	#pragma disable //���Ͳ����������жϴ�� 
//	void UART0_Send_Byte(uchar willSendByte)  
//	{
//			UART0_STATE = 0x0F;//��������жϱ�־λ������8λģʽ
//			UART0_BUF = willSendByte;

//			while (!(UART0_STATE & UART0_TI));

//			UART0_STATE = 0x0F;//��������жϱ�־λ������8λģʽ
//	}
	
	
	/* ����0�жϷ����ӳ��� */
	void UART0_ISR() interrupt 17
	{    
			unsigned char temp = 0;	
			static uchar xdata addr_bak = 0;
			PUSH_REG_ADDR_SFR();
			UART0_INT_FLAG_CLR;//���UART0�жϱ�־  
			if ((UART0_STATE & UART0_RI))
			{
					UART0_STATE = 0x17;//��������жϱ�־λ������8λģʽ
					temp = UART0_BUF;
					
			}
			if((UART0_STATE & 0x01))
			{
					UART0_STATE = 0x1E;//��żУ�����
			} 
			if((UART0_STATE & 0x02))
			{
					UART0_STATE = 0x1D;//֡����
			}
			if((UART0_STATE & 0x04))
			{
					UART0_STATE = 0x1B;//�������
			}
			if((UART0_STATE & 0x10))
			{
				UART0_STATE = 0x0F;//��������жϱ�־
				//�ڴ���ӷ�������
			}
			POP_REG_ADDR_SFR();
	}

#endif
	
#if (UART1_EN == 1)

	

	
	//-----------------------------------------------------------------//
	//�������ƣ� void UART1_Init(void)  
	//�������ܣ� UART1��ʼ��
	//��������� ��
	//��������� ��
	//�� �� ֵ�� ��
	//-----------------------------------------------------------------//
	void UART1_Init(void) 
	{ 
			EA = 0;//�����жϣ�
			UART1_IP_SET;//����UART0�ж��ż�Ϊ�ߣ�����ʵ��Ӧ���������ȼ�
			UART1_INT_FLAG_CLR;//���UART0�жϱ�־
			UART1_PORT_SET(UART1_PORT);//���ڹ���ӳ��ѡ��0-Ϊѡ��PC6/7Ϊ���ڣ�1ѡ��PH4/5Ϊ����
			
		#if (UART1_PORT == UART1_PH)

			REG_ADDR = 0x1E;REG_DATA |= 0x10;//PH4��������
			REG_ADDR = 0x1E;REG_DATA |= 0x20;//PH5��������
			REG_ADDR = 0x29;REG_DATA &= ~0x10;TRISH |= 0x10;//PH4����RXD0Ϊ����
			REG_ADDR = 0x29;REG_DATA &= ~0x20;TRISH &= ~0x20;//PH5����TXD0Ϊ���
		
		#elif(UART1_PORT == UART1_PC)

			REG_ADDR = 0x19;REG_DATA |= 0x40;//PC6��������
			REG_ADDR = 0x19;REG_DATA |= 0x80;//PC7��������
			REG_ADDR = 0x52;REG_DATA &= ~0x04;TRISC |= 0x40;//PC6����RXD0Ϊ����
			REG_ADDR = 0x52;REG_DATA &= ~0x08;TRISC &= ~0x80;//PC7����TXD0Ϊ���
		#else

		#endif

		UART1_BDL = (uchar)M_HEX_OF_BR(UART1_CFG_BAUD_RATE);//���ò�����=BUSCLK/(16*(UART1_BDH[0:1],UART1_BDL))
		UART1_CON2 = ((((uint)(M_HEX_OF_BR(UART1_CFG_BAUD_RATE)))>>8)&0x03);//����UART1_BDH[0:1]����λ
		UART1_CON2 |= (UART1_TX_EN);//�����ж�ʹ�ܣ�0Ϊ��ֹ�����жϣ�1Ϊ�������ж�
		UART1_CON2 |=(UART1_RX_EN);//�����ж�ʹ�ܣ�0Ϊ��ֹ�����жϣ�1Ϊ��������ж�
		UART1_CON1 |= (UART1_MUDULE_EN);//ʹ��UAERT0ģ��
		UART1_CON1 &= (~UART1_MULTI);//1:ʹ�ܶദ����ͨ��,0:��ʹ�ܶദ����ͨ��
		UART1_CON1 |= (UART1_RE_EN);//��������ʹ��
		UART1_CON1 &=(~UART1_SEND_MODE); //��������ģʽbit[3]��0����λģʽ��1��9λģʽģʽ
		UART1_CON1 |= (UART1_STOP_BIT);//ֹͣλ;1:2λ��0��1λ
		UART1_CON1 &= (~UART1_ODD_EVEN_EN);//��żУ��ʹ��1��������żУ�飻0:�ر���żУ��
		UART1_CON1 |= (UART1_ODD_EVEN_SE);//��żУ��ѡ��1����У�飻0:żУ��
		UART1_STATE &= ((~UART1_RI)&(~UART1_TI));//��������жϱ�־λ//��������жϱ�־λ
		UART1_IE_SET;//��UART�ж�ʹ��							
		EA = 1;//�����ж�
	}
	
//	#pragma disable //���Ͳ����������жϴ��
//	void UART1_Send_Word(uint willSendWord)   
//	{
//			UART1_Send_Byte(willSendWord>>8);
//			UART1_Send_Byte((uchar)willSendWord);
//	}
	
//	#pragma disable 
//	void UART1_Send_Byte(uchar willSendByte)  
//	{
//			UART1_STATE = 0x0F;//��������жϱ�־λ������8λģʽ
//			UART1_BUF = willSendByte;

//			while (!(UART1_STATE & UART1_TI));
//			UART1_STATE = 0x0F;//��������жϱ�־λ������8λģʽ
//	}
	
	
	/* ����1�жϷ����ӳ��� */
	void UART1_ISR() interrupt 18
	{    
			unsigned char temp;	
			static uchar xdata addr_bak = 0;
			PUSH_REG_ADDR_SFR();
			UART1_INT_FLAG_CLR;//���UART1�жϱ�־	   
			if ((UART1_STATE & UART1_RI))
			{
					UART1_STATE = 0x17;//��������жϱ�־λ������8λģʽ
//					temp = UART1_BUF;	
					
			} 
			if((UART1_STATE & 0x01))
			{
					UART1_STATE = 0x1E;//��żУ�����
			} 
			if((UART1_STATE & 0x02))
			{
					UART1_STATE = 0x1D;//֡����
			}
			if((UART1_STATE & 0x04))
			{
					UART1_STATE = 0x1B;//�������
			}
			
			if((UART1_STATE & 0x10))
			{
					UART1_STATE = 0x0F;//��������жϱ�־
					//�ڴ���ӷ�������
//					UART1_BUF = 0xFF;
					g_View.SendingState = SET;
			}
			POP_REG_ADDR_SFR();
	}

#endif
	
#if (UART2_EN == 1)
		#pragma message "����,UART2����"
		/****************************************************************/
		//��������void UART2_Send_NByte(uchar n,uchar *nSendByte)  
		//��  �ܣ�UART2����N BYTES
		//��  ����uchar n:�����ֽ�����uchar *nSendByte����������ָ��
		//����ֵ����
		/****************************************************************/

//		void UART2_Send_NByte(uchar n,uchar *nSendByte)  
//		{
//				uchar i = 0;
//				for(i = 0; i < n; i++)
//				{
//					UART2_Send_Byte(*(nSendByte + i));
//				}		
//		}

	
	//-----------------------------------------------------------------//
	//�������ƣ� void UART2_Init(void)  
	//�������ܣ� UART2��ʼ��
	//��������� ��
	//��������� ��
	//�� �� ֵ�� ��
	//-----------------------------------------------------------------//
	void UART2_Init(void) 
	{ 

			EA = 0;//�����жϣ�
			UART2_IP_SET;//����UART1�ж��ż�Ϊ�ߣ�����ʵ��Ӧ���������ȼ�
			UART2_INT_FLAG_CLR;//���UART2�жϱ�־
			REG_ADDR = 0x51;REG_DATA &= ~0x20;TRISB &= ~0x02;//PB1����Ϊ���
			REG_ADDR = 0x51;REG_DATA &= ~0x10;TRISB |= 0x01; //PB0����Ϊ����
			UART2_BREAK_CHECK_IE_SET(0);//UART2������ж�ʹ��,1Ϊ��������ж�ʹ�ܣ�0Ϊ�ؼ�����ж�ʹ��
			UART2_RXD_EDGE_IE_SET(0);//UART2RXD������ж�ʹ��,1Ϊ��RXD������ж�ʹ�ܣ�0Ϊ��RXD������ж�ʹ��
		
			UART2_MODE_SET(0);//UART2ģʽѡ��,1Ϊѭ��ģʽ����ģʽ��0Ϊ˫��ģʽ
			UART2_STOP_MODE_SET(1);//UART2 STOPλģʽѡ��,1Ϊ2bits��0Ϊ1bit
			UART2_SINGLE_MODE_SET(1);//UART2_MODE_SET(1)����ģʽʱ��1ΪTXD������Ч��0ΪTXD������Ч
			UART2_DATA_MODE_SET(0);//UART2����ģʽѡ��,1Ϊ9λģʽ(�ھ�λλ��żУ��λ)��0Ϊ8λģʽ
			UART2_PARITY_EN_SET(0);//UART2��żУ��λʹ��,1Ϊʹ����żУ��λ��0Ϊ��ʹ����żУ��λ
			UART2_PARITY_SEL(0);//UART2��żУ��λѡ��,1Ϊ��У�飬0ΪżУ��
			UART2_RATE_MATCH_EN(0);//UART2ͬ����(0x55)�������Զ�ƥ��ʹ��,1Ϊ����Ӧ�����ʸ��£�0Ϊ�̶����ò�����
			UART2_CLK_SEL(1);//UART2ģ�鹤��ʱ��ʹ��,1Ϊ�򿪹���ʱ�ӣ�0Ϊ�رղ���λģ��

			UART2_TX_EMPTY_IE_SET(0);	//UART2���ͻ�����ж�ʹ��,1Ϊ�ж�ʹ�ܣ�0Ϊ�жϽ�ֹ
			UART2_TX_FINISH_IE_SET(1);//UART2���ͻ�������ж�ʹ��,1Ϊ�ж�ʹ�ܣ�0Ϊ�жϽ�ֹ	
			UART2_RX_FULL_IE_SET(1);//UART2�������ж�ʹ��,1Ϊ�ж�ʹ�ܣ�0Ϊ�жϽ�ֹ	
			UART2_IDLE_IE_SET(0);//UART2����·���ж�ʹ��,1Ϊ�ж�ʹ�ܣ�0Ϊ�жϽ�ֹ		
			UART2_TRANS_EN_SET(1);//UART2������ʹ��,1Ϊ�򿪣�0Ϊ�رգ���0��д1�����Ŷӷ���һ�������ַ�		
			UART2_RECEIVE_EN_SET(1);//UART2������ʹ��,1Ϊ�򿪣�0Ϊ�ر�		
			UART2_RWU_SET(0);//UART2���������ѿ���,1Ϊ���������ڴ���״̬���ȴ�����������0Ϊ��������������					
			UART2_BREAK_TRANS_SET(0);//UART2����������������һ�������,1Ϊ����һ�������(д1����д0����λ)��0Ϊ������һ�������	


			UART2_SINGLE_DIR_SET(1);//UART2_MODE_SET(1)����ģʽʱ��1ΪTXD�����0ΪTXD����		
			UART2_TXD_INV_SET(0);	//TXD�����ݷ������ã�1ΪTXD�������ݷ��࣬0ΪTXD�������ݲ����� 		
			UART2_RXD_INV_SET(0);//RXD�����ݷ������ã�1ΪRXD�������ݷ��࣬0ΪRXD�������ݲ�����	 		
			UART2_RWU_IDLE_SEL(0);//���ջ������ü�⣬�ڽ��մ���״̬(RWU = 1)�ڼ䣬1Ϊ��⵽�����ַ�ʱ����IDLEλ��0Ϊ��⵽�����ַ�ʱ������IDLEλ	 		
			UART2_IDLE_SEL(0);//������·���ͣ�1Ϊֹͣλ�������ַ�������ʼ��0Ϊ��ʼλ�������ַ�������ʼ������10λʱ��(���data_mode = 1��stop_mode = 1,��ֱ�����1λʱ��)	 		 		
			UART2_WAKE_SEL(0);//���������ѷ�ʽѡ��1Ϊ��ַ��ǻ��ѣ�0Ϊ����·�߻���	 	   		

			UART2_BREAK_TRANS_SIZE(0);//���������λ���ȣ�1Ϊ��13λʱ�䷢�ͳ���(���data_mode = 1��stop_mode = 1,��ֱ�����1λʱ��)��0Ϊ��10λʱ�䷢�ͳ���(���data_mode = 1��stop_mode = 1,��ֱ�����1λʱ��)
			UART2_BREAK_CHECK_EN(0);//����μ��ʹ�ܣ�1Ϊ��11λʱ�䳤�ȼ��(���data_mode = 1��stop_mode = 1,��ֱ�����1λʱ��)��0Ϊ�����	 

			UART2_BDL_SET((uchar)M_HEX_OF_BR(UART2_CFG_BAUD_RATE));//���ò�����=BUSCLK/(16*(UART2_BDH[4:0],UART2_BDL))
			UART2_BDH_SET(((((uint)(M_HEX_OF_BR(UART2_CFG_BAUD_RATE)))>>8)&0x1F));//����UART2_BDH[4:0]��5λ
			UART2_IE_SET;//��UART2�ж�ʹ��				
			EA = 1;//�����ж�
	}
	
//	#pragma disable //���Ͳ����������жϴ��
//	void UART2_Send_Word(uint willSendWord)   
//	{
//			UART2_Send_Byte(willSendWord>>8);
//			UART2_Send_Byte((uchar)willSendWord);
//	}
	
//	#pragma disable //���Ͳ����������жϴ�� 
//	void UART2_Send_Byte(uchar willSendByte)  
//	{
//			UART2_INT_IF_TF_CLR(1);//д1���UART2_TF��־λ
//			UART2_INT_IF_TE_CLR(1);//д1���UART2_TE��־λ
//			UART2_INT_IF_RF_CLR(1);//д1���UART2_RF��־λ
//			UART2_TRANS_ENABLE();//UART2������ʹ��,1Ϊ�򿪣�0Ϊ�رգ���0��д1�����Ŷӷ���һ�������ַ�	
//			UART2_TX_EMPTY_IE_SET(0);	//UART2���ͻ�����ж�ʹ��,1Ϊ�ж�ʹ�ܣ�0Ϊ�жϽ�ֹ
//			if(SCI_C2 & 0x08)
//			{
//				
//				UART2_BUF = willSendByte;
//				while(UART2_TF == 0);
//				
//				UART2_INT_IF_TF_CLR(1);//д1���UART2_TF��־λ
//				UART2_INT_IF_TE_CLR(1);//д1���UART2_TE��־λ
//				UART2_INT_IF_RF_CLR(1);//д1���UART2_RF��־λ
//				
//			}
//			
//	}
	
	
	/* ����2�жϷ����ӳ��� */
	void UART2_ISR() interrupt 15
	{    
			unsigned char temp;	
			static uchar xdata addr_bak = 0;
			PUSH_REG_ADDR_SFR();
			UART2_INT_FLAG_CLR;//���UART2�жϱ�־		
				
			if(SCI_C2 & 0x20)
			{
				if(UART2_RI != 0)
				{
						UART2_INT_IF_RF_CLR(1);//д1���UART2_RF��־λ
						temp = UART2_BUF;
						
				}
			}
			
			if(SCI_C2 & 0x80)//�����˷��ͻ����Ϊ�ж�
			{
				if(UART2_TE != 0)
				{
						UART2_INT_IF_TE_CLR(1);//д1���UART2_TE��־λ
						if(UART2_TE != 0)
						{
								UART2_INT_IF_TE_CLR(1);//д1���UART2_TF��־λ6
								//�ڴ���ӷ�������
						}  
				} 
			}
			
			if(SCI_C2 & 0x40)//�����˷��ͻ����Ϊ�ж�
			{
				if(UART2_TF != 0)
				{
						UART2_INT_IF_TF_CLR(1);//д1���UART2_TF��־λ6
						//�ڴ���ӷ�������
				}   
			}
			POP_REG_ADDR_SFR();
	}

#endif
