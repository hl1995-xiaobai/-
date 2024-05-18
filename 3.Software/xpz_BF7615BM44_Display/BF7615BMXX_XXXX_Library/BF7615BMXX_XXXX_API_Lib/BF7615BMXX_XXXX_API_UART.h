#ifndef __BF7615BMXX_XXXX_API_UART_H__
#define __BF7615BMXX_XXXX_API_UART_H__



#define UART0_EN							1	// 1:ʹ�ܱ��룬0:��ʹ�ܱ���
#define UART0_PORT 						UART0_PE//ѡ��UART0ӳ�䵽UART0A_PE4/5(RXD,TXD),UART0B_PF4/5(RXD,TXD),UART0C_PC4/5(RXD,TXD)
#define UART0_CFG_BAUD_RATE   9600 // ������ѡ��2400/4800/9600/14400/19200/38400/57600/115200

#define UART1_EN							1	// 1:ʹ�ܱ��룬0:��ʹ�ܱ���
#define UART1_PORT 						UART1_PC//ѡ��UART1ӳ�䵽UART1A_PH4/5(RXD,TXD),UART1B_PC6/7(RXD,TXD)
#define UART1_CFG_BAUD_RATE   9600 // ������ѡ��2400/4800/9600/14400/19200/38400/57600/115200

#define UART2_EN							0	// 1:ʹ�ܱ��룬0:��ʹ�ܱ���
#define UART2_CFG_BAUD_RATE   9600 // ������ѡ��2400/4800/9600/14400/19200/38400/57600/115200


#define UART0_MUDULE_EN 	0x40//ʹ��UAERT0ģ��
#define UART0_MULTI 			0x10//ʹ�ܶദ����ͨ��
#define UART0_RE_EN 			0x20//��������ʹ��
#define UART0_STOP_BIT 		0x08//ֹͣλ;1:2λ��0��1λ
#define UART0_SEND_MODE 	0x04//��������ģʽbit[3]��0����λģʽ��1��9λģʽģʽ
#define UART0_ODD_EVEN_EN 0x02//��żУ��ʹ��1��������żУ�飻0:�ر���żУ��
#define UART0_ODD_EVEN_SE 0x01//��żУ��ѡ��1����У�飻0:żУ��

#define UART1_MUDULE_EN 	0x40//ʹ��UAERT1ģ��
#define UART1_MULTI 			0x10//ʹ�ܶദ����ͨ��
#define UART1_RE_EN 			0x20//��������ʹ��
#define UART1_STOP_BIT 		0x08//ֹͣλ;1:2λ��0��1λ
#define UART1_SEND_MODE 	0x04//��������ģʽbit[3]��0����λģʽ��1��9λģʽģʽ
#define UART1_ODD_EVEN_EN 0x02//��żУ��ʹ��1��������żУ�飻0:�ر���żУ��
#define UART1_ODD_EVEN_SE 0x01//��żУ��ѡ��1����У�飻0:żУ��



#define UART0_RX_EN 	0x04
#define UART0_TX_EN 	0x08
#define UART0_RI 			0x08
#define UART0_TI 			0x10
#define UART0_PE 			0x01
#define UART0_PF 			0x02
#define UART0_PC 			0x00


#define UART1_RX_EN 	0x04
#define UART1_TX_EN 	0x08
#define UART1_RI 			0x08
#define UART1_TI 			0x10
#define UART1_PH 			0x01
#define UART1_PC 			0x00

#define CFG_BUSCLK    24   // BUSCLKƵ��

#define _CFG_BUSCLK (CFG_BUSCLK * 1e6)

#define M_HEX_OF_BR(br)     (_CFG_BUSCLK/(16.0*br))


#define UART0_PORT_SET(x) {REG_ADDR = 0x34;REG_DATA &= ~(0x60);REG_DATA |= (0x60&(x<<5));}//���ڹ���ӳ��ѡ��0-Ϊѡ��PC4/5Ϊ���ڣ�1ѡ��PE4/5Ϊ���ڣ�2/3ѡ��PF4/5Ϊ����
#define UART0_ON_OFF(x) {UART0_CON1 &= ~(0x40);UART0_CON1 |= (0x40&(x<<6));}//UAERTģ�鿪��,1Ϊ����0Ϊ��
#define UART0_IE_SET IEN2 |= 0x04													//��UART�ж�ʹ��
#define UART0_IE_CLR IEN2 &= ~0x04												//��UART�ж�ʹ��
#define UART0_IP_SET IPL2 |= 0x04													//����UART�ж����ȼ�Ϊ��
#define UART0_IP_CLR IPL2 &= ~0x04												//����UART�ж����ȼ�Ϊ��
#define UART0_INT_FLAG_CLR IRCON2 &= ~0x04								// ���UART�жϱ�־λ

#define UART1_PORT_SET(x) {REG_ADDR = 0x34;REG_DATA &= ~(0x80);REG_DATA |= (0x80&(x<<7));}//���ڹ���ӳ��ѡ��0-Ϊѡ��PC6/7Ϊ���ڣ�1ѡ��PH4/5Ϊ����
#define UART1_ON_OFF(x) 	{UART1_CON1 &= ~(0x40);UART1_CON1 |= (0x40&(x<<6));}//UAERTģ�鿪��,1Ϊ����0Ϊ��
#define UART1_IE_SET IEN2 |= 0x08													//��UART�ж�ʹ��
#define UART1_IE_CLR IEN2 &= ~0x08												//��UART�ж�ʹ��
#define UART1_IP_SET IPL2 |= 0x08													//����UART�ж����ȼ�Ϊ��
#define UART1_IP_CLR IPL2 &= ~0x08												//����UART�ж����ȼ�Ϊ��
#define UART1_INT_FLAG_CLR IRCON2 &= ~0x08								// ���UART�жϱ�־λ


#define UART2_BREAK_CHECK_IE_SET(x) 	{SCI_S2 &= ~(0x08);SCI_S2 |= (0x08&(x<<3));}//UART2������ж�ʹ��,1Ϊ��������ж�ʹ�ܣ�0Ϊ�ؼ�����ж�ʹ��
#define UART2_RXD_EDGE_IE_SET(x) 			{SCI_S2 &= ~(0x04);SCI_S2 |= (0x04&(x<<2));}//UART2RXD������ж�ʹ��,1Ϊ��RXD������ж�ʹ�ܣ�0Ϊ��RXD������ж�ʹ��

#define UART2_MODE_SET(x) 						{SCI_C1 &= ~(0x80);SCI_C1 |= (0x80&(x<<7));}//UART2ģʽѡ��,1Ϊѭ��ģʽ����ģʽ��0Ϊ˫��ģʽ
#define UART2_STOP_MODE_SET(x) 				{SCI_C1 &= ~(0x40);SCI_C1 |= (0x40&(x<<6));}//UART2STOPλģʽѡ��,1Ϊ2bits��0Ϊ1bit
#define UART2_SINGLE_MODE_SET(x)			{SCI_C1 &= ~(0x20);SCI_C1 |= (0x20&(x<<5));}//UART2_MODE_SET(1)����ģʽʱ��1ΪTXD������Ч��0ΪTXD������Ч,�����ڲ�
#define UART2_DATA_MODE_SET(x) 				{SCI_C1 &= ~(0x10);SCI_C1 |= (0x10&(x<<4));}//UART2����ģʽѡ��,1Ϊ9λģʽ(�ھ�λλ��żУ��λ)��0Ϊ8λģʽ
#define UART2_PARITY_EN_SET(x) 				{SCI_C1 &= ~(0x08);SCI_C1 |= (0x08&(x<<3));}//UART2��żУ��λʹ��,1Ϊʹ����żУ��λ��0Ϊ��ʹ����żУ��λ
#define UART2_PARITY_SEL(x) 	 				{SCI_C1 &= ~(0x04);SCI_C1 |= (0x04&(x<<2));}//UART2��żУ��λѡ��,1Ϊ��У�飬0ΪżУ��
#define UART2_RATE_MATCH_EN(x) 				{SCI_C1 &= ~(0x02);SCI_C1 |= (0x02&(x<<1));}//UART2ͬ����(0x55)�������Զ�ƥ��ʹ��,1Ϊ����Ӧ�����ʸ��£�0Ϊ�̶����ò�����
#define UART2_CLK_SEL(x) 	 						{SCI_C1 &= ~(0x01);SCI_C1 |= (0x01&(x<<0));}//UART2ģ�鹤��ʱ��ʹ��,1Ϊ�򿪹���ʱ�ӣ�0Ϊ�رղ���λģ��


#define UART2_TX_EMPTY_IE_SET(x)			{SCI_C2 &= ~(0x80);SCI_C2 |= (0x80&(x<<7));}//UART2���ͻ�����ж�ʹ��,1Ϊ�ж�ʹ�ܣ�0Ϊ�жϽ�ֹ
#define UART2_TX_FINISH_IE_SET(x)			{SCI_C2 &= ~(0x40);SCI_C2 |= (0x40&(x<<6));}//UART2���ͻ�������ж�ʹ��,1Ϊ�ж�ʹ�ܣ�0Ϊ�жϽ�ֹ
#define UART2_RX_FULL_IE_SET(x)				{SCI_C2 &= ~(0x20);SCI_C2 |= (0x20&(x<<5));}//UART2�������ж�ʹ��,1Ϊ�ж�ʹ�ܣ�0Ϊ�жϽ�ֹ
#define UART2_IDLE_IE_SET(x)					{SCI_C2 &= ~(0x10);SCI_C2 |= (0x10&(x<<4));}//UART2����·���ж�ʹ��,1Ϊ�ж�ʹ�ܣ�0Ϊ�жϽ�ֹ
#define UART2_TRANS_EN_SET(x)					{SCI_C2 &= ~(0x08);SCI_C2 |= (0x08&(x<<3));}//UART2������ʹ��,1Ϊ�򿪣�0Ϊ�رգ���0��д1�����Ŷӷ���һ�������ַ�
#define UART2_TRANS_DISABLE()					{SCI_C2 &= ~(0x08);}//UART2�رշ�����ʹ��
#define UART2_TRANS_ENABLE()					{SCI_C2 |= (0x08);}//UART2�򿪷�����ʹ��
#define UART2_RECEIVE_EN_SET(x)				{SCI_C2 &= ~(0x04);SCI_C2 |= (0x04&(x<<2));}//UART2������ʹ��,1Ϊ�򿪣�0Ϊ�ر�
#define UART2_RWU_SET(x)							{SCI_C2 &= ~(0x02);SCI_C2 |= (0x02&(x<<1));}//UART2���������ѿ���,1Ϊ���������ڴ���״̬���ȴ�����������0Ϊ��������������
#define UART2_BREAK_TRANS_SET(x)			{if(x == 1){SCI_C2 |= (0x01);SCI_C2  &= ~(0x01&(x<<0));}}//UART1����������������һ�������,1Ϊ����һ�������(д1��0����λ)��0Ϊ������һ�������


#define UART2_SINGLE_DIR_SET(x)				{SCI_C3 &= ~(0x20);SCI_C3 |= (0x20&(x<<5));}//UART2_MODE_SET(1)����ģʽʱ��1ΪTXD�����0ΪTXD����
#define UART2_TXD_INV_SET(x)	 				{SCI_C3 &= ~(0x10);SCI_C3 |= (0x10&(x<<4));}//TXD�����ݷ������ã�1ΪTXD�������ݷ��࣬0ΪTXD�������ݲ�����
#define UART2_RXD_INV_SET(x)	 				{SCI_C3 &= ~(0x08);SCI_C3 |= (0x08&(x<<3));}//RXD�����ݷ������ã�1ΪRXD�������ݷ��࣬0ΪRXD�������ݲ�����
#define UART2_RWU_IDLE_SEL(x)	 				{SCI_C3 &= ~(0x04);SCI_C3 |= (0x04&(x<<2));}//���ջ������ü�⣬�ڽ��մ���״̬(RWU = 1)�ڼ䣬1Ϊ��⵽�����ַ�ʱ����IDLEλ��0Ϊ��⵽�����ַ�ʱ������IDLEλ
#define UART2_IDLE_SEL(x)	 		 				{SCI_C3 &= ~(0x02);SCI_C3 |= (0x02&(x<<1));}//������·���ͣ�1Ϊֹͣλ�������ַ�������ʼ��0Ϊ��ʼλ�������ַ�������ʼ������10λʱ��(���data_mode = 1��stop_mode = 1,��ֱ�����1λʱ��)
#define UART2_WAKE_SEL(x)	 	   				{SCI_C3 &= ~(0x01);SCI_C3 |= (0x01&(x<<0));}//���������ѷ�ʽѡ��1Ϊ��ַ��ǻ��ѣ�0Ϊ����·�߻���

#define UART2_BREAK_TRANS_SIZE(x)	 	  {SCI_S2 &= ~(0x02);SCI_S2 |= (0x02&(x<<1));}//���������λ���ȣ�1Ϊ��13λʱ�䷢�ͳ���(���data_mode = 1��stop_mode = 1,��ֱ�����1λʱ��)��0Ϊ��10λʱ�䷢�ͳ���(���data_mode = 1��stop_mode = 1,��ֱ�����1λʱ��)
#define UART2_BREAK_CHECK_EN(x)	 	   	{SCI_S2 &= ~(0x01);SCI_S2 |= (0x01&(x<<0));}//����μ��ʹ�ܣ�1Ϊ��11λʱ�䳤�ȼ��(���data_mode = 1��stop_mode = 1,��ֱ�����1λʱ��)��0Ϊ�����
#define UART2_BDL_SET(x) 							{REG_ADDR = 0x61;REG_DATA &= ~(0xFF);REG_DATA |= (0xFF&(x<<0));}//���ò�����=BUSCLK/(16*(UART2_BDH[4:0],UART2_BDL))
#define UART2_BDH_SET(x) 							{REG_ADDR = 0x60;REG_DATA &= ~(0x1F);REG_DATA |= (0x1F&(x<<0));}//����UART2_BDH[4:0]��5λ

#define UART2_INT_IF_TE_CLR(x)				{SCI_INT_CLR |= (0x80&(x<<7));}//д1���UART2_TE��־λ
#define UART2_INT_IF_TF_CLR(x)				{SCI_INT_CLR |= (0x40&(x<<6));}//д1���UART2_TF��־λ
#define UART2_INT_IF_RF_CLR(x)				{SCI_INT_CLR |= (0x20&(x<<5));}//д1���UART2_RF��־λ
#define UART2_INT_IF_ID_CLR(x)				{SCI_INT_CLR |= (0x10&(x<<4));}//д1���UART2_������·�жϱ�־λ
#define UART2_INT_IF_RO_CLR(x)				{SCI_INT_CLR |= (0x08&(x<<3));}//д1���UART2_RO���������־λ
#define UART2_INT_IF_NE_CLR(x)				{SCI_INT_CLR |= (0x04&(x<<2));}//д1���UART2_������־λ
#define UART2_INT_IF_FE_CLR(x)				{SCI_INT_CLR |= (0x02&(x<<1));}//д1���UART2_֡���־λ
#define UART2_INT_IF_PE_CLR(x)				{SCI_INT_CLR |= (0x01&(x<<0));}//д1���UART2_��żУ������־λ

#define UART2_BDL SCI_BDL
#define UART2_BDH SCI_BDH

#define UART2_BUF SCI_D
#define UART2_TF SCI_TF
#define UART2_TE SCI_TE
#define UART2_RI SCI_RI

#define UART2_IE_SET IEN2 |= 0x01													//��UART2�ж�ʹ��
#define UART2_IE_CLR IEN2 &= ~0x01												//��UART2�ж�ʹ��
#define UART2_IP_SET IPL2  |= 0x01												//����UART2�ж����ȼ�Ϊ��
#define UART2_IP_CLR IPL2 &= ~0x01												//����UART2�ж����ȼ�Ϊ��
#define UART2_INT_FLAG_CLR IRCON2 &= ~0x01								// ���UART2�жϱ�־λ


#if(UART0_EN == 1)
// ���ú궨��
extern void UART0_Init(void);
extern void UART0_Send_Word (unsigned int willSendWord);
extern void UART0_Send_Byte (unsigned char willSendByte);
extern void UART0_Send_NByte(uchar n,uchar *nSendByte);  
#endif


#if(UART1_EN == 1)
// ���ú궨��
extern void UART1_Init(void);
extern void UART1_Send_Word (unsigned int willSendWord);
extern void UART1_Send_Byte (unsigned char willSendByte);
extern void UART1_Send_NByte(uchar n,uchar *nSendByte);  
#endif

#if ((UART0_EN == 1)||(UART1_EN == 1)||(UART2_EN == 1))	

extern uchar UART_Rece_Check(uchar n,uchar *nCheckByte1,uchar *nCheckByte2);  

#endif

#if(UART2_EN == 1)
extern void UART2_Init(void);
extern void UART2_Send_Word (unsigned int willSendWord);
extern void UART2_Send_Byte (unsigned char willSendByte);
extern void UART2_Send_NByte(uchar n,uchar *nSendByte);  
#endif

#endif