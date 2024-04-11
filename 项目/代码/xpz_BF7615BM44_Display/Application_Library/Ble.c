#include ".\CTK_Library\Config.h"
#if BLE_TRACE 
uchar xdata sns_index[3] = 0;
uchar xdata sns_index_count = 0;
uchar xdata ble_sns_num = 0;
bit receive_flag = 0;
bit receive_start = 0;

/****************************************************************/
//��������void UART0_Send_SNS_Frame(uchar sns_num)  
//��  �ܣ�UART0����SNSһ֡����
//��  ����uchar sns_num:SNSͨ��
//����ֵ����
/****************************************************************/
void UART0_Send_SNS_Frame(uchar sns_num) 
{
//		UART0_Send_Byte('[');
//		UART0_Send_Byte('S');
//		UART0_Send_Byte('N');
//		UART0_Send_Byte('S');
		UART0_Send_Byte('0'+ sns_num%100/10);
		UART0_Send_Byte('0'+ sns_num%10);
//		UART0_Send_Byte(']');
		UART0_Send_Byte(':');
		UART0_Send_SNS_Baseline(sns_num);
	
		UART0_Send_SNS_Rawdata(sns_num);

		UART0_Send_SNS_Differ(sns_num);
	
//		UART0_Send_Byte('-');
//		UART0_Send_Byte('-');
//		UART0_Send_Byte('\n');
//		UART0_Send_Byte('\n');
//		UART0_Send_Byte('\n');
//		UART0_Send_Byte('\n');
}
/****************************************************************/
//��������void UART0_Send_SNS_Baseline(uchar sns_num)  
//��  �ܣ�UART0����SNS baseline����
//��  ����uchar sns_num:SNSͨ��
//����ֵ����
/****************************************************************/
void UART0_Send_SNS_Baseline(uchar sns_num)  
{
		UART0_Send_Byte('[');
		UART0_Send_Byte('0'+ base_line[sns_num]%100000/10000);
		UART0_Send_Byte('0'+ base_line[sns_num]%10000/1000);
		UART0_Send_Byte('0'+ base_line[sns_num]%1000/100);
		UART0_Send_Byte('0'+ base_line[sns_num]%100/10);
		UART0_Send_Byte('0'+ base_line[sns_num]%10);
		UART0_Send_Byte(']');
}
/****************************************************************/
//��������void UART0_Send_SNS_Rawdata(uchar sns_num)  
//��  �ܣ�UART0����SNS rawdata����
//��  ����uchar sns_num:SNSͨ��
//����ֵ����
/****************************************************************/
void UART0_Send_SNS_Rawdata(uchar sns_num)  
{
		UART0_Send_Byte('[');
		UART0_Send_Byte('0'+ raw_data[sns_num]%100000/10000);
		UART0_Send_Byte('0'+ raw_data[sns_num]%10000/1000);
		UART0_Send_Byte('0'+ raw_data[sns_num]%1000/100);
		UART0_Send_Byte('0'+ raw_data[sns_num]%100/10);
		UART0_Send_Byte('0'+ raw_data[sns_num]%10);
		UART0_Send_Byte(']');
	

}
/****************************************************************/
//��������void UART0_Send_SNS_Differ(uchar sns_num)  
//��  �ܣ�UART0����SNS differ����
//��  ����uchar sns_num:SNSͨ��
//����ֵ����
/****************************************************************/
void UART0_Send_SNS_Differ(uchar sns_num)  
{
		int differ = 0;
		differ = base_line[sns_num] - raw_data[sns_num];
		UART0_Send_Byte('[');
		if(differ >= 0)
		{
//				UART0_Send_Byte('P');
		}
		else
		{
//				UART0_Send_Byte('N');
				differ *= -1;
		}
		UART0_Send_Byte('0'+ differ%10000/1000);
		UART0_Send_Byte('0'+ differ%1000/100);
		UART0_Send_Byte('0'+ differ%100/10);
		UART0_Send_Byte('0'+ differ%10);
		UART0_Send_Byte(']');
		
}
#endif