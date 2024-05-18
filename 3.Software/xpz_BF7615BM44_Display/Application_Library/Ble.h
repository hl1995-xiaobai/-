#ifndef __BLE_H__
#define __BLE_H__
#define BLE_TRACE 0

	#if BLE_TRACE 
	extern uchar xdata sns_index[];
	extern uchar xdata sns_index_count;
	extern uchar xdata ble_sns_num;
	extern bit receive_flag;
	extern bit receive_start;
	extern void UART0_Send_SNS_Differ(uchar sns_num);
	extern void UART0_Send_SNS_Baseline(uchar sns_num);
	extern void UART0_Send_SNS_Rawdata(uchar sns_num);
	extern void UART0_Send_SNS_Frame(uchar sns_num);
	#endif
#endif