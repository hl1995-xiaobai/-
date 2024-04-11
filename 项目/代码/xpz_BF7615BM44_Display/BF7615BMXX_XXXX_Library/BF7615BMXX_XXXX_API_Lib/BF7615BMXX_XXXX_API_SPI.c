#include ".\BF7615BMXX_XXXX_Library\Config.h"

#if (SPI_EN == 1)

	//-----------------------------------------------------------------//
	//�������ƣ� void SPI_Init(void)  
	//�������ܣ� SPI��ʼ��
	//��������� ��
	//��������� ��
	//�� �� ֵ�� ��
	//-----------------------------------------------------------------//
	void SPI_Init(void) 
	{ 
		EA = 0;//�����жϣ�
		SPI_IP_SET;//����SPI�ж��ż�Ϊ��
		SPI_RE_INT_SET(0);//SPI�����ж�ʹ�ܣ�1Ϊ���ջ������ж�ʹ�ܣ�0Ϊ��ֹ�ж�
		SPI_EN_SET(1);//SPIģ��ʹ�ܣ�1Ϊģ��ʹ�ܣ�0Ϊģ��ر�
		SPI_TE_INT_SET(0);//SPI�����ж�ʹ�ܣ�1Ϊ���ͻ�����ж�ʹ�ܣ�0Ϊ��ֹ�ж�
		SPI_MS_SET(1);//SPI����ģʽѡ��1Ϊ������0Ϊ�ӻ�
		SPI_CPO_SET(1);//SPIʱ�Ӽ���ѡ��1ΪSPIʱ�ӵ���Ч,����ʱ�ߣ�0ΪSPIʱ�Ӹ���Ч,����ʱ��
		SPI_CPH_SET(1);//SPIʱ����λѡ��1Ϊ��һ����Чʱ���ط������ݣ�0Ϊ��һ����Чʱ���ز�������
		SPI_LSB_SET(1);//SPI��λ����ѡ��1Ϊ��������ʼ�ڵ�λ��0Ϊ��������ʼ�ڸ�λ
		SPI_CS_SET();//SPIƬѡ������CS
		
		SPI_FEE_SET(0);//CPHA=0ʱ��SPI���ݷ���ѡ��1Ϊ���ͽ��յ������ݸ�����/�ӻ���0Ϊ����MCUд������ݸ�����/�ӻ�
		SPI_HSPE_START(0);//SPI����ģʽ����(�������Ӳ���Զ�����)��1ΪSPI����ģʽ������0Ϊ����ģʽ�ر�
		SPI_HA_DU_SEL(0);//SPI��/ȫ��ģʽѡ��1Ϊ��˫��ģʽ��0Ϊȫ˫��ģʽ
		SPI_BIDIR_SEL(1);//SPI�빤ģʽ����/���շ���ѡ��1Ϊ���ͣ�0Ϊ����
		SPI_SPR_SET(2);
		//SPI������ϵ��(���2MHz):
		//{0-SYS_CLK/2};{1-SYS_CLK/4};{2-SYS_CLK/6};{3-SYS_CLK/8};{4-SYS_CLK/10};{5-SYS_CLK/12};{6-SYS_CLK/14};{7-SYS_CLK/16};
		SPI_IE_SET;//��SPI�ж�ʹ�� 
		EA = 1;//�����ж�
	}
	
//	void spi_high_speed_comm(uint tx_addr,uint rx_addr,uint comm_num,HIGH_SPEED_MODE_enum high_mode)
//	{
//		uchar tx_addr_buff = (tx_addr >> 4);
//		uchar rx_addr_buff = (rx_addr >> 4);
//		
//		REG_ADDR = SPI_TX_START_ADDR;
//		REG_DATA = tx_addr_buff;

//		REG_ADDR = SPI_RX_START_ADDR;
//		REG_DATA = rx_addr_buff;

//		REG_ADDR = SPI_NUM_L;
//		REG_DATA = (uchar)comm_num;

//		REG_ADDR = SPI_NUM_H;
//		REG_DATA = ((comm_num >> 8) & 0x0f);

//		if(FULL_DUPLEX_MODE==high_mode)
//		{
//			SPI_CFG2 &= ~HALF_DUPLEX;
//		}
//		else if(HALF_DUPLEX_TX==high_mode)
//		{
//			SPI_CFG2 |= HALF_DUPLEX;
//			SPI_CFG2 |= SPI_HALF_DUPLEX_TX;
//		}
//		else if(HALF_DUPLEX_RX==high_mode)
//		{
//			SPI_CFG2 |= HALF_DUPLEX;
//			SPI_CFG2 &= ~SPI_HALF_DUPLEX_TX;
//		}
//		SPI_CFG1 &= ~SPI_CS_N;
//		SPI_CFG2 |= SPI_HIGH_SPEED;

//	}

	/*!
	\brief      wait spi high speed communication complete
	\param[in]  none
	\param[out] none
	\retval     SUCCESS or ERROR 
	*/
//	ErrStatus wait_spi_high_comm_end(void)
//	{	
//		while(SPI_CFG2 & SPI_HIGH_SPEED);
//		while((SPI_STATE & SPI_INT_TX_EMPTY) == 0x00);
//		SPI_CFG1 |= SPI_CS_N;
//		SPI_CFG2 &= ~HALF_DUPLEX;
//		return SUCCESS;
//	}

	/*!
	\brief      spi send and receive a byte
	\param[in]  dat: send data//�������Ƭѡʱ�������ݣ���������������Ƭѡ
	\param[out] none
	\retval     receive data
	*/
	uchar spi_sendbyte(uchar dat)
	{	
		while((SPI_STATE & SPI_INT_TX_EMPTY) == 0x00);
		SPI_SPID = dat;
		while((SPI_STATE & SPI_INT_RX_FULL) == 0x00);
		dat = SPI_SPID;
		SPI_STATE &= ~SPI_INT_RX_FULL;
		return dat;
	}
	
	
	
	/* SPI�жϷ����ӳ��� */
	void SPI_ISR() interrupt 20
	{    
		static uchar xdata addr_bak = 0;
		PUSH_REG_ADDR_SFR();
		SPI_INT_FLAG_CLR;//���SPI�жϱ�־  
		POP_REG_ADDR_SFR();
	}

#endif
