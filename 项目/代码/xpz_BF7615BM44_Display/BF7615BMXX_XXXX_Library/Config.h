#ifndef __CONFIG_H__
#define __CONFIG_H__

typedef unsigned char uchar;
typedef unsigned int  uint;
typedef unsigned long ulong;
typedef unsigned char BYTE;

#define TRUE  1
#define FALSE 0


#define OPEN  1
#define CLOSE 0

#define TRACEMODE_UART	0
#define TRACEMODE_IIC		1
/*******************************配置部分*******************************************/
/********芯片选择：TRUE表示该系列芯片，FALSE表示未选择系列该芯片***/	    	  
#define BF7615BMXX_XXXX TRUE	 

#define CHIPTYPE   TRUE

#define CHIP_BF7615BMXX_XXXX (CHIPTYPE == BF7615BMXX_XXXX)
		 

/*
芯片系列：CHIP_BF7615BMXX_XXXX。 
芯片选型：只能选择一种芯片型号定义为"TURE",其于的芯片型号定义为"FALSE"。
调试模式：将"TRACEMODE"定义为"TRUE"时为调试模式，定义为"FALSE"时为工作模式。
通道开启：将"OPENSNS"对应的位设置为1表示开启该触摸通道。
*/
 
/******************TRUE: 调试模式*********
*******************FALSE: 工作模式********/
#define TRACEMODE  FALSE

#define CH_MAX 				22//1~44：配置最大按键扫描数
#define SNS_NUM 	 		4//SNS_NUM<=CH_MAX//1~44：配置最大按键扫描数
#define CTK_RESO			4//0~7 CTK电容扫描分辨率，计数器位数：(CFG_CTK_RESOLUTION+9)位。
#define CTK_DS				1//检测速度0:24MHz,1:12MHz,2:6MHz,3:4MHz
#define CTK_PRS				62
//63/62-1~1.5~3MHz,61-400K,40-1MHz,16-2MHz,24-1.5MHz,22-1.6MHz,8-3MHz,4-4MHz,0-6MHz
//PRS(充放电频率) = 96/2/(x+8)；x = 61时，PRS(充放电频率) = 400K；x = 62/63，PRS(充放电频率) = (1~1.5~3)MHz。
#define CTK_RB 				2		//选择RB电阻大小0:20K,1:40K,2:60K,3:80K,4:150K,5:200K,6:250K,7:300K。推荐RB = 60K
#define CTK_REF 			5		//0~7 参考电压(0:1.79V),(1:2.14V),(2:2.47V),(3:2.81V),(4:3.18V),(5:3.48V),(6:3.86V),(7:4.19V);
//注：VCC-CTK_REF>0.5V

#define ADJUST_STE 		0	//自适应步进
#define ADJUST_LINE      (((((ulong)0x0001<<(CTK_RESO + 9)))*70)/100)//自适应目标线-分辨率最大计数的70%
#define ADJUST_PARA_LINE (((((ulong)0x0001<<(CTK_PARA_RESO + 9)))*70)/100)//自适应目标线-分辨率最大计数的70%

#define FTH_PARA 				300//并联模式手指阈值
#define CTK_PARA_RESO		CTK_RESO	//0~7 CTK电容扫描分辨率，计数器位数：(CFG_CTK_RESOLUTION+9)位。
#define CTK_PARA_PRS		62//63/62-1~1.5~3MHz,61-400K,40-1MHz,16-2MHz,24-1.5MHz,22-1.6MHz,8-3MHz,4-4MHz,0-6MHz
//PRS(充放电频率) = 96/2/(x+8)；x = 61时，PRS(充放电频率) = 400K；x = 62/63，PRS(充放电频率) = (1~1.5~3)MHz。
#define CTK_PARA_RB 		2	//选择RB电阻大小0:20K,1:40K,2:60K,3:80K,4:150K,5:200K,6:250K,7:300K。推荐RB = 60K
#define CTK_PARA_REF 		5//并联模式参考电压(0:1.81V),(1:2.14V),(2:2.49V),(3:2.83V),(4:3.18V),(5:3.51V),(6:3.86V),(7:4.10V);注：VCC-VTH>0.5V
#define PAR_NnoiseRenMaxCnt 20		//并联模式负噪声更新判断次数
#define PAR_PnoiseRenMaxCnt 20		//并联模式正噪声更新判断次数

#define CS_SW								0	//CS开关1为开；0为关，使用"MCU04_CS_DataDeal_V1.0"库时CS_SW = 1;开启后按键响应速度有所下降。
#define CS_NOISE 						500//CS噪声判断值
#define CS_FTH_RATE					15//当Data_Deal()返回值>CS_NOISE时,手指阈值比例;例：CS_FTH_RATE=10时，FingerThreshold = CS_FTH_RATE*FingerThreshold/10
#define FTHD_HY_RATE  			10//CS_SW = 1时，FTH迟滞比例，当手指按下时，FHT按照 FingerThreshold = FTHD_HY*FTH/10

/*************电流源手动设置********/
#define PUIV00 300
#define PUIV01 300
#define PUIV02 300
#define PUIV03 300
#define PUIV04 300
#define PUIV05 300
#define PUIV06 300
#define PUIV07 300
#define PUIV08 300
#define PUIV09 300
#define PUIV10 300
#define PUIV11 300
#define PUIV12 300
#define PUIV13 300
#define PUIV14 300
#define PUIV15 300
#define PUIV16 300
#define PUIV17 300
#define PUIV18 300
#define PUIV19 300
#define PUIV20 300
#define PUIV21 300
#define PUIV22 300
#define PUIV23 300
#define PUIV24 300
#define PUIV25 300
#define PUIV26 300
#define PUIV27 300
#define PUIV28 300
#define PUIV29 300
#define PUIV30 300
#define PUIV31 300

#define PUIV32 300
#define PUIV33 300
#define PUIV34 300
#define PUIV35 300
#define PUIV36 300
#define PUIV37 300
#define PUIV38 300
#define PUIV39 300

#define PUIV40 300
#define PUIV41 300
#define PUIV42 300
#define PUIV43 300
#define PUIV44 300
#define PUIV45 300
#define PUIV46 300
#define PUIV47 300



/*******************************配置部分*******************************************/

/***通道开启： SCAN_XX:0~11,16~47,SCAN_00~SCAN_SNS_NUM有效，SCAN_00不能为255***/

#define SCAN_00 16
#define SCAN_01 10
#define SCAN_02 17
#define SCAN_03 11
                
#define SCAN_04 4
#define SCAN_05 5
#define SCAN_06 6
#define SCAN_07 7

#define SCAN_08 10//8
#define SCAN_09 10//9
#define SCAN_10 10
#define SCAN_11 11

#define SCAN_12 16
#define SCAN_13 17
#define SCAN_14 18
#define SCAN_15 19
#define SCAN_16 20
#define SCAN_17 21
#define SCAN_18 22
#define SCAN_19 23

#define SCAN_20 24
#define SCAN_21 25
#define SCAN_22 26
#define SCAN_23 27

#define SCAN_24 28
#define SCAN_25 29
#define SCAN_26 30
#define SCAN_27 31

#define SCAN_28 32
#define SCAN_29 33
#define SCAN_30 34
#define SCAN_31 35

#define SCAN_32 36
#define SCAN_33 37
#define SCAN_34 38
#define SCAN_35 39
#define SCAN_36 40
#define SCAN_37 41
#define SCAN_38 42
#define SCAN_39 43

#define SCAN_40 44
#define SCAN_41 45
#define SCAN_42 46
#define SCAN_43 47

/***通道开启： SCAN_XX:0~31,SCAN_00~SCAN_SNS_NUM有效***/

/*******************手指阈值设置与芯片引脚SNSXX对应********/

#define FTH00 400
#define FTH01 400
#define FTH02 400
#define FTH03 400
#define FTH04 400
#define FTH05 400
#define FTH06 400
#define FTH07 400
#define FTH08 400
#define FTH09 400
#define FTH10 400
#define FTH11 400
#define FTH12 400
#define FTH13 400
#define FTH14 400
#define FTH15 400
#define FTH16 400
#define FTH17	400
#define FTH18 400
#define FTH19 400
#define FTH20 400
#define FTH21 400
#define FTH22 400
#define FTH23 400
#define FTH24 400
#define FTH25 400
#define FTH26 400
#define FTH27 400
#define FTH28 400
#define FTH29 400
#define FTH30 400
#define FTH31 400

#define FTH32 400
#define FTH33 400
#define FTH34 400
#define FTH35 400
#define FTH36 400
#define FTH37 400
#define FTH38 400
#define FTH39 400
           
#define FTH40 400
#define FTH41 400
#define FTH42 400
#define FTH43 400
#define FTH44 400
#define FTH45 400
#define FTH46 400
#define FTH47 400






#define TK_LEFT_COUNT 			2						//手指离开判断次数；

#define	LONG_KEY_COUNT  		5000				//定时器0开启1ms定时，长按键清除判断次数,1000为1S,0为取消长按键判断功能

#define TK_EOT 							0						//超过eot*fht消顶,0时取消消顶

#define	TK_COMFIRM_COUNT  	6					//手指触摸确认次数；

#define RENOVATE_MODE 			0							//基线更新模式：0:常规模式；1：防水模式
#define KEYS_RENOVATE_FLAG_L 	0xFFFFFFFF//0xFFFFFDCC		//0xFFFFFFFF;//0xFFFFFFFF//0x00000000;//按键基线更新屏蔽标志1：开启基线更新；0：关闭基线更新		
#define KEYS_RENOVATE_FLAG_H 	0xFFFFFFFF//0xFFFFFDCC		//0xFFFFFFFF;//0xFFFFFFFF//0x00000000;//按键基线更新屏蔽标志1：开启基线更新；0：关闭基线更新		

#define RENOVATE_FTH_RATE 	6							//按键手指阈值= fht*RENOVATE_FTH_RATE/10		
#define RENOVATE_NTH_RATE		2							//按键基线更新噪声阈值= fht*RENOVATE_NTH_RATE/10	
#define TK_RATE_HY  				8							//有按键按下时手指阈值FingerThreshold = FingerThreshold*TK_RATE_HY/10;


#define OVER_P_NOISE_MAX_COUNT			30				//按键基线更新differ>=正噪声计数,更新基线，值越小，基线更新越快

#define UNDER_P_NOISE_MAX_COUNT			10					//按键基线更新differ<=正噪声计数,更新基线，值越小，基线更新越快
#define OVER_N_NOISE_MAX_COUNT			10					//按键基线更新differ>=负噪声计数,更新基线，值越小，基线更新越快	

#define	UNDER_N_NOISE_MAX_COUNT			5				//按键基线更新differ<=负噪声计数,更新基线，值越小，基线更新越快
#define	UNDER_2N_NOISE_MAX_COUNT		10				//按键基线更新differ<=负噪声计数,更新基线，值越小，基线更新越快
#define UNDER_N											3					//按键基线更新differ<=-(differ*UNDER_N)倍数

#define MULTI_KEY_MAX_COUNT					0						//多按键消除判断个数，等于0时无多按键判断
#define MULTI_KEY_RST_COUNT					3					//多按键计数判断基线复位;	


#if (RENOVATE_MODE == 1)
#define RENOVATE_MODE1_FTH_RATE 			4						//RENOVATE_MODE = 1时,mode_flag_l对应的按键置位时，手指阈值= fht*renovate_mode1_fth_rate/10
#define WATER_OVER_P_NOISE_MAX_COUNT	20					//RENOVATE_MODE = 1时,按键基线更新differ>=正噪声计数,更新基线，值越小，基线更新越快
#define WATER_FLOW_LEFT_MAX_COUNT			3					//RENOVATE_MODE = 1时,溢水离开判断次数;
#define WATER_FLOW_MAX_COUNT					2						//RENOVATE_MODE = 1时,溢水判断个数;	
#define WATER_FLOW_RST_COUNT					30					//RENOVATE_MODE = 1时,溢水计数判断基线复位;
#define WATER_FLOW_RATE								5						//RENOVATE_MODE = 1时,溢水判断比例,(((long)n_base_line[i] - (long)base_line[i])) > (renovate_water_flow_rate*FingerThreshold/10)的个数大于2时为溢水。
#define N_BASE_LINE_RENO_MAX_COUNT		50						//RENOVATE_MODE = 1时,n_base_line基线更新判断次数；
#endif

#define UN_NORMAL_CHECK 						0 			//Rawdata 导常判断 1为开，0为关
#if UN_NORMAL_CHECK
#define UN_NORMAL_MAX_COUNT					3				//Rawdata>=分辨率最大计数的80%时异常判断次数
#define UN_NORMAL_RECOVER_MAX_COUNT	3				//判断Rawdata异常时允许适应次数
#endif

#if SNS_NUM
extern unsigned int   code 	FTH[];
extern unsigned char  code 	SNS[];
extern unsigned int   code 	PUIV[]; 
extern unsigned char  xdata sensor_open[];
extern unsigned int   xdata pull_i_value[];
extern unsigned char  xdata touch_left_count[];
extern unsigned char  xdata over_p_noise_count[];
extern unsigned char  xdata under_p_noise_count[];
extern unsigned char  xdata over_n_noise_count[];
extern unsigned char  xdata under_n_noise_count[];
extern unsigned char xdata under_2n_noise_count[];
extern unsigned char  xdata n_base_line_reno_count[];

extern unsigned int   xdata n_base_line[];
extern unsigned char  xdata touch_confirm_count[];
#endif

#if CHIP_BF7615BMXX_XXXX
	#include "absacc.h"
	#include "intrins.h"
	#include ".\BF7615BMXX_XXXX_Library\BF7615BMXX_XXXX.H"
	#include ".\BF7615BMXX_XXXX_Library\Touch_MCU_Init.h"
	#include ".\BF7615BMXX_XXXX_Library\BF7615BMXX_XXXX_CTK_Lib\BF7615BMXX_XXXX_CTK.H"
	#include ".\BF7615BMXX_XXXX_Library\BF7615BMXX_XXXX_CTK_Lib\BF7615BMXX_XXXX_CTK_Idle.h"
	#include ".\BF7615BMXX_XXXX_Library\BF7615BMXX_XXXX_CTK_Lib\BF7615BMXX_XXXX_CTK_Touch.H"
	#include ".\BF7615BMXX_XXXX_Library\BF7615BMXX_XXXX_CTK_Lib\BF7615BMXX_XXXX_CTK_Trace.h"
	#include ".\BF7615BMXX_XXXX_Library\BF7615BMXX_XXXX_API_Lib\BF7615BMXX_XXXX_API_Timer.h"
	
//	#include ".\BF7615BMXX_XXXX_Library\BF7615BMXX_XXXX_API_Lib\BF7615BMXX_XXXX_API_ADC.h"
//	#include ".\BF7615BMXX_XXXX_Library\BF7615BMXX_XXXX_API_Lib\BF7615BMXX_XXXX_API_UART.h"
//	#include ".\BF7615BMXX_XXXX_Library\BF7615BMXX_XXXX_API_Lib\BF7615BMXX_XXXX_API_IIC.h"	
//	#include ".\BF7615BMXX_XXXX_Library\BF7615BMXX_XXXX_API_Lib\BF7615BMXX_XXXX_API_EEP.h"
//	#include ".\BF7615BMXX_XXXX_Library\BF7615BMXX_XXXX_API_Lib\BF7615BMXX_XXXX_API_LED.h"	
	#include ".\BF7615BMXX_XXXX_Library\BF7615BMXX_XXXX_API_Lib\BF7615BMXX_XXXX_API_LVDT.h"
//	#include ".\BF7615BMXX_XXXX_Library\BF7615BMXX_XXXX_API_Lib\BF7615BMXX_XXXX_API_INT.h"
//	#include ".\BF7615BMXX_XXXX_Library\BF7615BMXX_XXXX_API_Lib\BF7615BMXX_XXXX_API_PWM.h"
//	#include ".\BF7615BMXX_XXXX_Library\BF7615BMXX_XXXX_API_Lib\BF7615BMXX_XXXX_API_LCD.h"
//	#include ".\BF7615BMXX_XXXX_Library\BF7615BMXX_XXXX_API_Lib\BF7615BMXX_XXXX_API_SPI.h"
	#include ".\Project\Project.h"
	#if (CS_SW == 1)
		#include ".\BF7615BMXX_XXXX_Library\BF7615BMXX_XXXX_CTK_Lib\DataDeal.h"
	#endif

#endif

#endif  
