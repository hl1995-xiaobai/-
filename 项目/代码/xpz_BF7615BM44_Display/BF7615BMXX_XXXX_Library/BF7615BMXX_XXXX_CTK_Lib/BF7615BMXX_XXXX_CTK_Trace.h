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
//函数名称： void BF7615BMXX_XXXX_Trace_Mode_Init(unsigned char IICSlaveAddr,unsigned char iic_port)
//函数功能： BF7615BMXX_XXXX_Trace_Mode_Init初始化
//输入参数： unsigned char IICSlaveAddr:IIC从机地址;,unsigned char iic_port://IIC功能映射选择0-为选择PC4/5为串口，1选择PE4/5为串口
//输出参数： 无
//返 回 值： 无
//-----------------------------------------------------------------//
extern void BF7615BMXX_XXXX_Trace_Mode_Init(unsigned char IICSlaveAddr,unsigned char iic_port);
//-----------------------------------------------------------------//
//函数名称： void TraceMode_Master_Read_Data(unsigned char   ch_max,unsigned int xdata *p_rawData,unsigned int xdata *p_baseline,ulong t_keysFlagSN,unsigned long  t_keysFlagSN_H)   
//函数功能： 将发送的数据写入IICBUF
//输入参数： 无
//输出参数： 无
//返 回 值： 无
//-----------------------------------------------------------------//
extern void TraceMode_Master_Read_Data(unsigned int xdata *p_rawData,unsigned int xdata *p_baseline,unsigned long t_keysFlagSN,unsigned long  t_keysFlagSN_H);    
//-----------------------------------------------------------------//
//函数名称： void TraceMode_Master_Write_Data(void)  
//函数功能： 从IICBUF读取数据
//输入参数： 无
//输出参数： 无
//返 回 值： 无
//-----------------------------------------------------------------//
extern void TraceMode_Master_Write_Data(void);

#endif
#endif
