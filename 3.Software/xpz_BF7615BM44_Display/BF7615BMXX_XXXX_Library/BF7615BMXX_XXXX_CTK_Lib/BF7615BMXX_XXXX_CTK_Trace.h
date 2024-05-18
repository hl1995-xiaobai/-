#ifndef __BF7615BMXX_XXXX_CTK_TRACE_H__ 
#define __BF7615BMXX_XXXX_CTK_TRACE_H__ 

#if (TRACEMODE == TRUE)

extern unsigned long xdata keys_flag_l_Tracemode;	
extern unsigned long xdata keys_flag_h_Tracemode;	

#if SNS_NUM

extern unsigned char xdata ReadCnt;
extern unsigned char xdata ReceData;
extern unsigned char xdata DataNum;
extern bit OddCheck;
extern bit NeedCheckOdd;
extern unsigned int xdata raw;
extern unsigned int xdata bas;
#endif

//-----------------------------------------------------------------//
//�������ƣ� void BF7615BMXX_XXXX_Trace_Mode_Init(unsigned char IICSlaveAddr,unsigned char iic_port)
//�������ܣ� BF7615BMXX_XXXX_Trace_Mode_Init��ʼ��
//��������� unsigned char IICSlaveAddr:IIC�ӻ���ַ;,unsigned char iic_port://IIC����ӳ��ѡ��0-Ϊѡ��PC4/5Ϊ���ڣ�1ѡ��PE4/5Ϊ����
//��������� ��
//�� �� ֵ�� ��
//-----------------------------------------------------------------//
extern void BF7615BMXX_XXXX_Trace_Mode_Init(unsigned char IICSlaveAddr,unsigned char iic_port);
//-----------------------------------------------------------------//
//�������ƣ� void TraceMode_Master_Read_Data(unsigned char   ch_max,unsigned int xdata *p_rawData,unsigned int xdata *p_baseline,ulong t_keysFlagSN,unsigned long  t_keysFlagSN_H)   
//�������ܣ� �����͵�����д��IICBUF
//��������� ��
//��������� ��
//�� �� ֵ�� ��
//-----------------------------------------------------------------//
extern void TraceMode_Master_Read_Data(unsigned int xdata *p_rawData,unsigned int xdata *p_baseline,unsigned long t_keysFlagSN,unsigned long  t_keysFlagSN_H);    
//-----------------------------------------------------------------//
//�������ƣ� void TraceMode_Master_Write_Data(void)  
//�������ܣ� ��IICBUF��ȡ����
//��������� ��
//��������� ��
//�� �� ֵ�� ��
//-----------------------------------------------------------------//
extern void TraceMode_Master_Write_Data(void);

#endif
#endif
