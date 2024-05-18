#ifndef __BF7615BMXX_XXXX_API_IIC_H__
#define __BF7615BMXX_XXXX_API_IIC_H__


#define IICS_EN					0	//IIC �ڴӻ�ʹ�����ã� 			1:ʹ�ܱ��룬0:��ʹ�ܱ���

#define IICS_WCOL (IICSTAT & 0x02)//д��ͻ��־λ
#define IICS_WCOL_CLR (IICSTAT &= ~0x02)//���д��ͻ��־λ

#define IICS_RECOV (IICSTAT & 0x01)//����ͻ��־λ
#define IICS_RECOV_CLR (IICSTAT &= ~0x01)//�������ͻ��־λ

#define IICS_AD (IICSTAT & 0x10)//��ַ�����ݱ�־λ
#define IICS_RW (IICSTAT & 0x20)//��д��־λ

#define SCLEN 		(IICCON & 0x04)//��ʱ��ʹ������״̬
#define SCLEN_CLR (IICCON &= ~0x04)//��ʹ��ʱ������״̬
#define SCLEN_SET (IICCON |= 0x04)//ʹ��ʱ������״̬
#define IICS_RW   (IICSTAT & 0x20)//��д��־λ
#define IICS_BF   (IICSTAT & 0x08)//��IIC_BUF����־λ
#define PSW_P 	  (PSW & 0x01)//PSW��ż��־λ


#define IIC_EN 				0x01       
#define IIC_SR 				0x02      
#define IIC_SCLEN 		0x04    	
#define IIC_W_SCL_EN 	0x08 			
#define IIC_R_SCL_EN 	0x10 			
#define IIC_RST 			0x20

#define IIC_PE 			0x01
#define IIC_PC 			0x00

#define IIC_PORT_SET(x) {REG_ADDR = 0x34;REG_DATA &= ~(0x10);REG_DATA |= (0x10&(x<<4));}//IIC����ӳ��ѡ��0-Ϊѡ��PC4/5Ϊ���ڣ�1ѡ��PE4/5Ϊ����
#define IIC_AFIL_SET(x) {REG_ADDR = 0x50;REG_DATA &= ~(0x02);REG_DATA |= (0x02&(x<<1));}//IICģ���˲�ѡ��1Ϊѡ��ģ���˲���0Ϊ��ѡ��ģ���˲�
#define IIC_DFIL_SET(x) {REG_ADDR = 0x50;REG_DATA &= ~(0x01);REG_DATA |= (0x01&(x<<0));}//IICģ���˲�ѡ��1Ϊѡ�������˲���0Ϊ��ѡ�������˲�

#define IIC_IE_SET IEN1 |= 0x08												//��IIC�ж�ʹ��
#define IIC_IE_CLR IEN1 &= ~0x08											//��IIC�ж�ʹ��
#define IIC_IP_SET IPL1 |= 0x08												//����IIC�ж����ȼ�Ϊ��
#define IIC_IP_CLR IPL1 &= ~0x08											//����IIC�ж����ȼ�Ϊ��
#define IIC_INT_FLAG_CLR IRCON1 &= ~0x08								// ���IIC�жϱ�־λ


#if IICS_EN
extern uint data IICS_Soft_Cnt;
extern uint xdata SCLEN_SoftCnt;
extern void IIC_Slave_Init(uchar IICSlaveAddr,uchar iic_port);
#endif

#if (TRACEMODE==1)
extern unsigned long xdata keys_flag_Tracemode;	
extern unsigned long xdata keys_flag_Tracemode_H;	
#endif
#endif