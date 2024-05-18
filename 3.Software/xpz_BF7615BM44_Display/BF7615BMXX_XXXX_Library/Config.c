#include ".\BF7615BMXX_XXXX_Library\Config.h"

#if SNS_NUM

unsigned char code 	SNS[44] ={SCAN_00,SCAN_01,SCAN_02,SCAN_03,SCAN_04,SCAN_05,SCAN_06,SCAN_07,SCAN_08,SCAN_09,SCAN_10,SCAN_11,SCAN_12,SCAN_13,SCAN_14,SCAN_15,\
														  SCAN_16,SCAN_17,SCAN_18,SCAN_19,SCAN_20,SCAN_21,SCAN_22,SCAN_23,SCAN_24,SCAN_25,SCAN_26,SCAN_27,SCAN_28,SCAN_29,SCAN_30,SCAN_31,\
															SCAN_32,SCAN_33,SCAN_34,SCAN_35,SCAN_36,SCAN_37,SCAN_38,SCAN_39,SCAN_40,SCAN_41,SCAN_42,SCAN_43};


unsigned int code 	FTH[48] ={FTH00,FTH01,FTH02,FTH03,FTH04,FTH05,FTH06,FTH07,FTH08,FTH09,FTH10,FTH11,FTH12,FTH13,FTH14,FTH15,\
														  FTH16,FTH17,FTH18,FTH19,FTH20,FTH21,FTH22,FTH23,FTH24,FTH25,FTH26,FTH27,FTH28,FTH29,FTH30,FTH31,\
															FTH32,FTH33,FTH34,FTH35,FTH36,FTH37,FTH38,FTH39,FTH40,FTH41,FTH42,FTH43,FTH44,FTH45,FTH46,FTH47};

unsigned int code 	PUIV[48]={PUIV00,PUIV01,PUIV02,PUIV03,PUIV04,PUIV05,PUIV06,PUIV07,PUIV08,PUIV09,PUIV10,PUIV11,PUIV12,PUIV13,PUIV14,PUIV15,\
															PUIV16,PUIV17,PUIV18,PUIV19,PUIV20,PUIV21,PUIV22,PUIV23,PUIV24,PUIV25,PUIV26,PUIV27,PUIV28,PUIV29,PUIV30,PUIV31,\
															PUIV32,PUIV33,PUIV34,PUIV35,PUIV36,PUIV37,PUIV38,PUIV39,PUIV40,PUIV41,PUIV42,PUIV43,PUIV44,PUIV45,PUIV46,PUIV47};
												
unsigned int   xdata pull_i_value[SNS_NUM] = {255};
unsigned char  xdata sensor_open[SNS_NUM] = {0};
unsigned char  xdata touch_left_count[SNS_NUM] = {0};
unsigned char  xdata over_p_noise_count[SNS_NUM] = {0};
unsigned char  xdata under_p_noise_count[SNS_NUM] = {0};
unsigned char  xdata over_n_noise_count[SNS_NUM] = 	{0};
unsigned char  xdata under_n_noise_count[SNS_NUM] = {0};
unsigned char  xdata under_2n_noise_count[SNS_NUM] = {0};
unsigned char  xdata n_base_line_reno_count[SNS_NUM] = {0};
unsigned int   xdata n_base_line[SNS_NUM] = {0};
unsigned char  xdata touch_confirm_count[SNS_NUM] = {0};

#endif