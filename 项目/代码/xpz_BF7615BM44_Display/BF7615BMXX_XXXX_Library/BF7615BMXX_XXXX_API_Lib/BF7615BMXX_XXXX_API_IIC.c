#include ".\BF7615BMXX_XXXX_Library\Config.h"
#if IICS_EN
	uint data  IICS_Soft_Cnt = 0;
	uint xdata SCLEN_SoftCnt = 0; 
#endif

	#if IICS_EN
		#if (TRACEMODE==0)
		#pragma message "����,IIC�ӻ�����"
		//-----------------------------------------------------------------//
		//�������ƣ� void IIC_Slave_Init(uchar IICSlaveAddr,uchar iic_port)
		//�������ܣ� IIC�ӻ���ʼ��
		//��������� uchar IICSlaveAddr:IIC�ӻ���ַ;,uchar iic_port://IIC����ӳ��ѡ��0-Ϊѡ��PC4/5Ϊ���ڣ�1ѡ��PE4/5Ϊ����
		//��������� ��
		//�� �� ֵ�� ��
		//-----------------------------------------------------------------//
		void IIC_Slave_Init(uchar IICSlaveAddr,uchar iic_port)
		{
			EA = 0;//�����жϣ��� 
			IIC_IP_SET; //����IIC�ж����ȼ�Ϊ�ߣ�����ʵ��Ӧ���������ȼ�
			IIC_INT_FLAG_CLR;//���IIC�жϱ�־λ 
			REG_ADDR = 0x50;REG_DATA = 0x02;
			//bit0:IICģ���˲�ѡ��1Ϊѡ�������˲���0Ϊ��ѡ�������˲�(Sleepģʽʱ��IIC���ܻ���MCU)
	
			if(iic_port == 1)
			{
//					SET_PE4_PU_ON;//��������
//					SET_PE5_PU_ON;//��������
//				
//				
//					SET_PE4_IO_IN;
//					SET_PE5_IO_IN;
				
						REG_ADDR = 0x1B;REG_DATA |= 0x10;//PE4��������
						REG_ADDR = 0x1B;REG_DATA |= 0x20;//PE5��������
						REG_ADDR = 0x27;REG_DATA &= ~0x01;TRISE |= 0x10;//PE4����RXD0Ϊ����
						REG_ADDR = 0x27;REG_DATA &= ~0x02;TRISE |= 0x20;//PE5����TXD0Ϊ����
				
					IIC_PORT_SET(iic_port);
			}
			else
			{
//					SET_PC4_PU_ON;//��������
//					SET_PC5_PU_ON;//��������
//				
//					SET_PC4_IO_IN;
//					SET_PC5_IO_IN;
				
					REG_ADDR = 0x19;REG_DATA |= 0x10;//PC4��������
					REG_ADDR = 0x19;REG_DATA |= 0x20;//PC5��������
					REG_ADDR = 0x26;REG_DATA &= ~0x40;TRISC |= 0x10;//PC4����RXD0Ϊ����
					REG_ADDR = 0x26;REG_DATA &= ~0x80;TRISC |= 0x20;//PC5����TXD0Ϊ����
				
					IIC_PORT_SET(iic_port);
			}

			IICADD = IICSlaveAddr;//����IIC�ӻ���ַ��
			IICSTAT = 0x00;//���IIC״̬�Ĵ�����
			
			IICCON |= IIC_EN;//IIC����ʹ��
			IICCON |= (IIC_SR);//IICת��������Ӧ100K
			IICCON |= IIC_SCLEN;//SLCʱ����������
			IICCON &= (~IIC_W_SCL_EN);//��ʹ��д����,����IIC������дʱ������
			IICCON |= (IIC_R_SCL_EN);//ʹ�ܶ����ͣ�����IIC������дʱ������
			IIC_IE_SET; //��IIC�ж�ʹ��
			
			EA = 1;//�����жϣ�
		}
		//-----------------------------------------------------------------//
		//�������ƣ� void Master_Read_Data()  
		//�������ܣ� �����͵�����д��IICBUF
		//��������� ��
		//��������� ��
		//�� �� ֵ�� ��
		//-----------------------------------------------------------------//
		void Master_Read_Data()    
		{   
			uchar tmp;
			IICBUF = tmp;
			SCLEN_SET;
	
		}
		//-----------------------------------------------------------------//
		//�������ƣ� void Master_Write_Data()  
		//�������ܣ� ��IICBUF��ȡ����
		//��������� ��
		//��������� ��
		//�� �� ֵ�� ��
		//-----------------------------------------------------------------//
		void Master_Write_Data() 
		{   
			uchar tmp;
			tmp = IICBUF;
			
		} 
		//-----------------------------------------------------------------//
		//�������ƣ� void IIC_ISR_PA() interrupt 10 
		//�������ܣ� PA��IIC�ж��Ӻ���
		//��������� ��
		//��������� ��
		//�� �� ֵ�� ��
		//-----------------------------------------------------------------//
		void IIC_ISR_PA() interrupt 10
		{
				uchar tmp;
				static uchar xdata addr_bak = 0;
				PUSH_REG_ADDR_SFR();
				IIC_INT_FLAG_CLR;//���IIC�жϱ�־λ
 
				if (IICS_WCOL)//д��ͻ��־λ
				{ 
						IICS_WCOL_CLR;
				}
				if (IICS_RECOV)//����ͻ��־λ  
				{
						IICS_RECOV_CLR;
						tmp = IICBUF;
				}
				if (IICS_AD == 0)//�ǵ�ַ
				{	 
				
					
						if (IICS_RW)//������ 
						{
								Master_Read_Data();
								SCLEN_SET; 
						}
						else //����д
						{

								tmp = IICBUF;
								
						}   
					}
					else 
					{
						if (IICS_RW)//������ 
						{
								      
								Master_Read_Data();
								SCLEN_SET;	  
						}
						else//����д  
						{   
					
							if (IICS_BF) 
							{ 
								Master_Write_Data();
							}
						}
				}
				SCLEN_SET;
				POP_REG_ADDR_SFR();
		}
		
		#endif
	#endif//PA_SLAVE