#ifndef __BF7615BMXX_XXXX_API_SPI_H__
#define __BF7615BMXX_XXXX_API_SPI_H__

#define SPI_EN				  0	// 1:ʹ�ܱ��룬0:��ʹ�ܱ���

#define SPI_IE_SET  IEN2 |= 0x20//��SPI�ж�ʹ�� 
#define SPI_IE_CLR  IEN2 &= ~0x20//��SPI�ж�ʹ��
#define SPI_IP_SET  IPL2 |= 0x20//����SPI�ж��ż�Ϊ��
#define SPI_IP_CLR  IPL2 &= ~0x20//����SPI�ж��ż�Ϊ��
#define SPI_INT_FLAG_CLR IRCON2 &= ~0X20//���SPI�жϱ�־

#define SPI_RE_INT_SET(x) 	{SPI_CFG1 &= ~0x80;SPI_CFG1 |= (0x80&(x<<7));}//SPI�����ж�ʹ�ܣ�1Ϊ���ջ������ж�ʹ�ܣ�0Ϊ��ֹ�ж�
#define SPI_EN_SET(x) 		{SPI_CFG1 &= ~0x40;SPI_CFG1 |= (0x40&(x<<6));}//SPIģ��ʹ�ܣ�1Ϊģ��ʹ�ܣ�0Ϊģ��ر�
#define SPI_TE_INT_SET(x) 	{SPI_CFG1 &= ~0x20;SPI_CFG1 |= (0x20&(x<<5));}//SPI�����ж�ʹ�ܣ�1Ϊ���ͻ�����ж�ʹ�ܣ�0Ϊ��ֹ�ж�
#define SPI_MS_SET(x) 		{SPI_CFG1 &= ~0x10;SPI_CFG1 |= (0x10&(x<<4));}//SPI����ģʽѡ��1Ϊ������0Ϊ�ӻ�
#define SPI_CPO_SET(x) 		{SPI_CFG1 &= ~0x08;SPI_CFG1 |= (0x08&(x<<3));}//SPIʱ�Ӽ���ѡ��1ΪSPIʱ�ӵ���Ч,����ʱ�ߣ�0ΪSPIʱ�Ӹ���Ч,����ʱ��
#define SPI_CPH_SET(x) 		{SPI_CFG1 &= ~0x04;SPI_CFG1 |= (0x04&(x<<2));}//SPIʱ����λѡ��1Ϊ��һ����Чʱ���ط������ݣ�0Ϊ��һ����Чʱ���ز�������
#define SPI_LSB_SET(x) 		{SPI_CFG1 &= ~0x02;SPI_CFG1 |= (0x02&(x<<1));}//SPI��λ����ѡ��1Ϊ��������ʼ�ڵ�λ��0Ϊ��������ʼ�ڸ�λ
#define SPI_CS_SET() 		  {SPI_CFG1 |= 0x01;}//SPIƬѡ������CS
#define SPI_CS_CLR() 		  {SPI_CFG1 &= ~0x01;}//SPIƬѡ������CS


#define SPI_FEE_SET(x) 		{SPI_CFG2 &= ~0x40;SPI_CFG2 |= (0x40&(x<<6));}//CPHA=0ʱ��SPI���ݷ���ѡ��1Ϊ���ͽ��յ������ݸ�����/�ӻ���0Ϊ����MCUд������ݸ�����/�ӻ�
#define SPI_HSPE_START(x) 	{SPI_CFG2 &= ~0x20;SPI_CFG2 |= (0x20&(x<<5));}//SPI����ģʽ����(�������Ӳ���Զ�����)��1ΪSPI����ģʽ������0Ϊ����ģʽ�ر�
#define SPI_HA_DU_SEL(x) 	{SPI_CFG2 &= ~0x10;SPI_CFG2 |= (0x10&(x<<4));}//SPI��/ȫ��ģʽѡ��1Ϊ��˫��ģʽ��0Ϊȫ˫��ģʽ
#define SPI_BIDIR_SEL(x) 	{SPI_CFG2 &= ~0x08;SPI_CFG2 |= (0x08&(x<<3));}//SPI�빤ģʽ����/���շ���ѡ��1Ϊ���ͣ�0Ϊ����
#define SPI_SPR_SET(x) 		{SPI_CFG2 &= ~0x07;SPI_CFG2 |= (0x07&(x<<0));}//SPI������ϵ��(���2MHz):
//{0-SYS_CLK/2};{1-SYS_CLK/4};{2-SYS_CLK/6};{3-SYS_CLK/8};{4-SYS_CLK/10};{5-SYS_CLK/12};{6-SYS_CLK/14};{7-SYS_CLK/16};

#define SPI_READ_F(x) 		{SPI_STATE &= ~0x04;SPI_STATE |= (0x04&(x<<2));}//SPI������������ǣ����д0��0
#define SPI_ROV(x) 			{SPI_STATE &= ~0x02;SPI_STATE |= (0x02&(x<<1));}//1ΪSPI��ͨͨѶģʽ�£�������ʱ��������źŲ������жϣ�
//����ģʽ�£���Ч(���������ݸ�������{SPI_NUM_H,SPI_NUM_L}ʱ�����������SPRF��λ���������ж�)
#define SPI_TXE_F(x) 		{SPI_STATE &= ~0x01;SPI_STATE |= (0x01&(x<<0));}//SPI���ͻ������ձ�ǣ�д��SPIDӲ���Զ���0
#define SPI_TX_BUF_ADD(x) 	{REG_ADDR = 0x3E;REG_DATA = x;}//SPI����ģʽ�£��������ݻ����׵�ַ
#define SPI_RX_BUF_ADD(x) 	{REG_ADDR = 0x3F;REG_DATA = x;}//SPI����ģʽ�£��������ݻ����׵�ַ
#define SPI_NUM(x) 			{REG_ADDR = 0x40;REG_DATA &= ~0x0F;REG_DATA |= (0x0F&(x>>8));REG_ADDR = 0x41;REG_DATA = x;}//SPI���ݻ����ַ����
//ע1������ģʽ�£�����������CPOL��CPHA,������Ƭѡ������SCLK_OUT��ë�̣�
//ע2���ӻ�ģʽ�£�Ƭѡ���ͺ󣬲��ܹر�SPI_EN���������´�SPI_ENʱ��Ƭ���ٴα�ɵ�ʱ���ڲ�������SCLK��ë�̣�
//ע3��SPI_FEE_SET(1)�����������͵�ǰһ������(��һ�ʷ�������Ϊ0xFF���ڶ��ʷ��͵��ǽ��յ���������һ�����ݣ�����ķ������ݶ����������͵�ǰһ�����ݣ��ù�������CPHA=0��ģʽ)


#define	SPI_TX_START_ADDR  	0x3E
#define	SPI_RX_START_ADDR  	0x3F
#define	SPI_NUM_L          	0x40
#define	SPI_NUM_H           	0x41
#define	ADC_CFG_SEL1			0x42

/* spi device mode define */
#define	SPI_MASTER		(0x01 << 4)
#define	SPI_SLAVE		(0x00)
/* spi clock define */
#define	SYS_CLK_DIVIDE_2	0x00
#define	SYS_CLK_DIVIDE_4	0x01
#define	SYS_CLK_DIVIDE_6	0x02
#define	SYS_CLK_DIVIDE_8	0x03
#define	SYS_CLK_DIVIDE_10	0x04
#define	SYS_CLK_DIVIDE_12	0x05
#define	SYS_CLK_DIVIDE_14	0x06
#define	SYS_CLK_DIVIDE_16	0x07

/* spi duplex define */
#define	FULL_DUPLEX			(0x00)
#define	HALF_DUPLEX			(0x01 << 4)
/* spi endian define */
#define	LSB_FIRST			(0x01 << 1)
#define	MSB_FIRST			(0x00)
/* spi clock polarity define */
#define	CPOL_HIGH			(0x01 << 3)
#define	CPOL_LOW			(0x00)
/* spi clock phase define */
#define	SPI_CPHA_2Edge		(0x01 << 2)
#define SPI_CPHA_1Edge		(0x00)
/* spi communication mode define */
#define	SPI_HIGH_SPEED		(0x01 << 5)	
/* spi interrupt enable define */
#define	SPI_RX_INT_EN		(0x01 << 7)
#define	SPI_TX_INT_EN 		(0x01 << 5)

/* spi interrupt flag define */
#define	SPI_INT_TX_EMPTY	(0x01)
#define	SPI_RX_OVERFLOW		(0x01 << 1)
#define	SPI_INT_RX_FULL		(0x01 << 2)
/* spi half_duplex direct define */
#define	SPI_HALF_DUPLEX_TX	(0x01 << 3)
#define	SPI_HALF_DUPLEX_RX	(0x00)

/* spi cs define */
#define SPI_CS_N			(0x01)


#define SPI_DEVICE_MODE(x)   SPI_CFG1 &= ~0x10;SPI_CFG1 |= (x)
#define SPI_PRESCALE_SET(x)  SPI_CFG2 &= ~0x07;SPI_CFG2 |= (x)
#define SPI_DUPLEX_SET(x)    SPI_CFG2 &= ~0x10;SPI_CFG2 |= (x)
#define SPI_ENDIAN_SET(x)    SPI_CFG1 &= ~0x02;SPI_CFG1 |= (x)
#define SPI_CPOL_SET(x)      SPI_CFG1 &= ~0x08;SPI_CFG1 |= (x)
#define SPI_CPHA_SET(x)      SPI_CFG1 &= ~0x04;SPI_CFG1 |= (x)

#define SPI_TRANSFER_SET(x)  SPI_CFG2 &= ~0x08;SPI_CFG2 |= (x)/* x=SPI_HALF_DUPLEX_TX or SPI_HALF_DUPLEX_RX*/


#define SPI_TX_INT_ENABLE()   SPI_CFG1 |= SPI_TX_INT_EN
#define SPI_TX_INT_DISABLE()  SPI_CFG1 &= ~SPI_TX_INT_EN

#define SPI_RX_INT_ENABLE()   SPI_CFG1 |= SPI_RX_INT_EN
#define SPI_RX_INT_DISABLE()  SPI_CFG1 &= ~SPI_RX_INT_EN

#define SPI_INT_ENABLE()	 IEN2 |= 0x20   /* enable interrupt */
#define SPI_INT_DISABLE()	 IEN2 &= ~0x20  /* disable interrupt */
#define SPI_IPL_SET(x)       IPL2 &= ~0x20;IPL2 |= (x<<5)  /* set interrupt priority */

#define SPI_ENABLE()	 	 SPI_CFG1 |= 0x40   /* enable spi */
#define SPI_DISABLE()	 	 SPI_CFG1 &= ~0x40  /* disable spi */
#define INT_SPI_CLR()        IRCON2 &= ~(0x01 << 5)

/* enum definitions */
typedef enum {DISABLE = 0, ENABLE = !DISABLE} EventStatus, ControlStatus;
typedef enum {RESET = 0, SET = !RESET} FlagStatus;
typedef enum {ERROR = 0, SUCCESS = !ERROR} ErrStatus;
typedef enum {LOW = 0, HIGH = !LOW} IntPrioStatus;

/* high speed mode enum */
typedef enum
{
	FULL_DUPLEX_MODE,	/* full duplex mode */
	HALF_DUPLEX_TX,		/* half duplex tx mode , not receive */
	HALF_DUPLEX_RX		/* half duplex rx mode , not transmit */
}HIGH_SPEED_MODE_enum;

/* function declarations */

/* spi send and receive a byte */
extern uchar spi_sendbyte(uchar dat);
//extern void spi_init(void);
/* spi high speed communication */
extern void spi_high_speed_comm(uint tx_addr,uint rx_addr,uint comm_num,HIGH_SPEED_MODE_enum high_mode);
/* wait for spi high speed communication complete */
extern ErrStatus wait_spi_high_comm_end(void);


extern void SPI_Init(void);
#endif