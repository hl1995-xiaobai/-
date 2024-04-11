#ifndef _VIEW_H_
#define _VIEW_H_

//#include "SteamOvenView.h"
//#include "RangeHoodView.h"

#define SET_MODE_AUTO_END_TIME   			5  		/*设置模式自动结束时间（秒）*/
#define BRIGHT_AUTO_END_TIME     			180  	/*照明自动结束时间（秒）*/
#define AUTO_DOOR_LOCK_CNT					3     	/*门锁自动上锁倒计时(秒)*/
#define AUTO_WORK_END_CNT					180     /*工作结束状态显示时间*/
#define AUTO_OFF_TIME    		 			180  	/*自动关机时间180（秒）*/
#define AUTO_STANDBY_TIME    		 		120  	/*自动待机时间（秒）*/
#define HEART_BEAT_TIME    		 			10  	/*心跳周期10（秒）*/
#define IOT_REPORT_TIME    		 			8  		/*上报周期10（秒）*/
#define MODULE_STATUS_QUERY_TIME    		8  		/*模组状态查询10（秒）*/
#define IOT_CMD_TIME    		 			25  	/*指令间隔周期250（毫秒）*/
#define WINDSPEED_MAX_DELAY_OFF_TIME    	120  	/*风机3档延时关闭120（秒）*/
#define WINDSPEED_MAX_DELAY_OFF_TEN_MINUTES 600  	/*风机3档延时关闭600（秒）*/
#define CLEANOUT_AUTO_ENTER_TIME    		5  		/*3S自动进入清洗模式（秒）*/
#define SUBSCRIBE_TIME    					300  	/*预约3分钟无操作进入呼吸灯（秒）*/


// 定义蒸烤箱各功能的预热时间（秒）
#define STEAM_OVEN_FUNCTION_NORMAL_PREHEATTIME           1200      
#define STEAM_OVEN_FUNCTION_HIGH_TEMPER_PREHEATTIME      1200
#define STEAM_OVEN_FUNCTION_GRILL_PREHEATTIME            1200
#define STEAM_OVEN_FUNCTION_HUMIDFIER_PREHEATTIME        1200
#define STEAM_OVEN_FUNCTION_BAKE_PREHEATTIME             1200

#define STEAM_OVEN_FUNCTION_CIRCLE_AIR_PREHEATTIME       1200
#define STEAM_OVEN_FUNCTION_FERMENT_PREHEATTIME          1200
#define STEAM_OVEN_FUNCTION_UNFREEZE_PREHEATTIME         1200
#define STEAM_OVEN_FUNCTION_DISINFECT_PREHEATTIME        1200
#define STEAM_OVEN_FUNCTION_DRY_PREHEATTIME              1200



#define LED_NORMAL_BRIGHT					10     /*LED开机量度*/
#define LED_STANDBY_BRIGHT					2      /*LED待机量度*/


#define STEAM_OVEN_POWER_OFF 		0  /**/
#define STEAM_OVEN_POWER_ON 		1  /**/

#define WORK_SET_MODE_OFF			 				0  
#define WORK_SET_MODE_SYSTIME_H						1 	/*设置系统时间小时*/
#define WORK_SET_MODE_SYSTIME_M						2 	/*设置系统时间分钟*/
#define WORK_SET_MODE_STEAMOVEN_TIME				3 	/*设置蒸烤箱工作时间*/
#define WORK_SET_MODE_STEAMOVEN_TEMPER				4 	/*设置蒸烤箱工作温度*/
#define WORK_SET_MODE_STEAMOVEN_SUBSCRIBE_HOUR		5 	/*设置预约时间小时*/
#define WORK_SET_MODE_STEAMOVEN_SUBSCRIBE_MINUTE	6 	/*设置预约时间分钟*/
#define WORK_SET_MODE_LEFT_CLOCK	   				7 	/*设置左定时*/
#define WORK_SET_MODE_RIGHT_CLOCK	   				8 	/*设置右定时*/
#define WORK_SET_MODE_SPEED			   				9 	/*显示风速*/
#define WORK_SET_MODE_GESTURE		   				10 	/*开关手挚*/
#define WORK_SET_MODE_FIREWALL		   				11 	/*设置开户关闭防火报警*/
#define WORK_SET_MODE_GAS		   					12 	/*设置开户关闭防火报警*/
#define WORK_SHOW_BOT_TEMPER 						13  /*显示底盘温度*/
#define WORK_SHOW_PROBE_TEMPER 						14  /*显示探头温度*/
#define WORK_SET_CLEANOUT 							15  /*清洗*/
#define WORK_SET_HEAD_HEAT							16	/*设置头部保温功能*/








#define ERROR_CODE_NO_ERROR				0
#define ERROR_CODE_INTER_NTC			1	/*腔体NTC错误*/
#define ERROR_CODE_BOT_NTC				2	/*发热盘底NTC异常*/
#define ERROR_CODE_NO_ARRIVE			3	/*箱体温度异常*/
#define ERROR_CODE_COMMUNICATE			4	/*通讯故障*/
#define ERROR_CODE_DOOR_OPEN			5	/*门控故障*/
#define ERROR_CODE_WATER_LACK			6	/*缺水错误*/

#define ACK_NULL						0	/**/
#define STATUS_ILLUMINATIONCTRL_ACK		1	/*照明*/
#define STATUS_HOODSPEEDCTRL_ACK		2	/*风速*/
#define STATUS_WASHCTRL_ACK				3	/*清洗*/
#define STATUS_PAUSE					4	/*暂停*/
#define STATUS_STOP						5	/*停止*/
#define STATUS_PLAY						6	/*运行*/
#define STATUS_ERROR_EVENT				7	/*错误事件*/
#define STATUS_ALERT_EVENT				8	/*警告事件*/
#define STATUS_COOK_EVENT				9	/*烹饪事件*/
#define STATUS_ERROR					10	/*错误*/


#define SYSMODE_NORMAL 	0	/*正常工作模式*/
#define SYSMODE_TEST 	1	/*测试模式*/
#define SYSMODE_PLANT 	2	/*工厂模式*/


// 定义系统硬件信息结构体
typedef struct{
	uint8 sysInit 		:1;		// 系统初始化标志位
	uint8 SysMode 		:2;		// 系统模式
	uint8 SysTime1ms	:1;		// 1毫秒系统时间标志位
	uint8 SysTime10ms	:1;		// 10毫秒系统时间标志位
	uint8 SysTime20ms 	:1;		// 20毫秒系统时间标志位
	uint8 SysTime100ms 	:1;		// 100毫秒系统时间标志位
	uint8 SysTime500ms 	:1;		// 500毫秒系统时间标志位
	uint8 SysTime1S 	:1;		// 1秒系统时间标志位

	uint8 VersionYear	:8;		// 软件版本年
	uint8 VersionMonth	:8;		// 软件版本月
	uint8 VersionDay	:8;		// 软件版本日
	uint8 SysCnt		:8;		// 系统计数器
	uint8 SysTimeHour;			// 系统时间小时
	uint8 SysTimeMinute;		// 系统时间分钟
	uint8 SysTimeSecond;		// 系统时间秒

	uint8 TestCnt;				// 测试计数器
	uint8 TestType;				// 测试类型
}xdata SYS_HARDWARE_T;

// 定义系统时间计数器结构体
typedef struct{
	uint8 Time0TL0;				// 定时器0低8位
	uint8 Time0TH0;				// 定时器0高8位
	uint8 sysTime10msCnt;		// 10毫秒系统时间计数器
	uint8 sysTime20msCnt;		// 20毫秒系统时间计数器
	uint8 sysTime100msCnt	:4;	// 100毫秒系统时间计数器
	uint8 sysTime500msCnt	:4;	// 500毫秒系统时间计数器
	uint8 sysTime1sCnt		:4;	// 1秒系统时间计数器
	uint8 Timecnt			:5;	// 定时器计数器
	uint8 cnt;					// 计数器
}xdata SYS_TIME_CNT_T;




// 定义视图信息结构体
typedef struct{
	uint8 VersionYearP;						// 软件版本年
	uint8 VersionMonthP;					// 软件版本月
	uint8 VersionDayP;						// 软件版本日
	uint8 TemperShowCnt;					// 温度显示区计数

	uint8 PowerOn			:1;				// 电源
	uint8 KidLock			:1;				// 童锁
	uint8 FlashOn			:1;				// 闪烁
	uint8 Flash				:1;				// 闪烁
	uint8 FashFlash			:1;				// 快闪
	uint8 Flash_1000ms		:1;				// 闪烁
	uint8 wifi_icon 		:1;				// Wifi 图标显示方式 常亮
	uint8 wifi_icon_flash 	:1;				// Wifi 图标显示方式 闪烁

	uint8 oil_spill_alarm_icon 			:1;	// 溢油报警 图标显示方式 常亮
	uint8 oil_spill_alarm_icon_flash 	:1;	// 溢油报警 图标显示方式 闪烁
	uint8 					:2;				//
	uint8 buzzer			:4;				// 蜂鸣器

	uint8 SetMode;							// 设置模式
	uint8 LedBright;						// LED 亮度

	uint8 AutoOffCnt;						// 自动关机计数（秒）
	uint8 AutoStandbyCnt;					// 自动待机计数（秒）

	uint8 SetModeOffCnt;					// 设置模式结束计数（秒）

	uint8 AutoOffStandbyCnt;				// 关机自动待机计数（秒）

	uint8 Cnt;								//

	uint8 SendingState;						// 发送状态

	// STEAM_OVEN_VIEW_T SteamOven;
	// RANGE_HOOD_VIEW_T RangeHood;
	// RANGE_HOOD_RECV_T RangeHoodRead;
}xdata VIEW_T,*PVIEW_T;

// 定义配置信息结构体
typedef struct{
	uint8  magic; 							// 魔数
	uint32 oilBoxCnt; 						// 油盒计数
	union{
		uint8 vlue;
		struct{
			uint8 firewall	:1;				// 防火墙报警开关
			uint8 gas		:1;				// 气敏报警开关
			uint8 gears		:1;				// 显示转速
			uint8 Gesture	:1;				// 开关手挚功能
			uint8 oilBox	:1;				// 开关油盒报警功能
			uint8 			:3;				//
		}b;
	}sw;
	uint8  DegugCount;						// 调试计数
	uint8  checkout;						// 校验位
}xdata CONFIG_T;






#define BUZZER_KEY_EVENT() 		g_View.buzzer  = 1				// 定义蜂鸣器按键事件宏，设置蜂鸣器状态为1
#define BUZZER_POWER_ON() 		g_View.buzzer  = 2				// 定义蜂鸣器开机事件宏，设置蜂鸣器状态为2
#define BUZZER_POWER_OFF() 		g_View.buzzer  = 3				// 定义蜂鸣器关机事件宏，设置蜂鸣器状态为3
#define BUZZER_ERRPR() 			g_View.buzzer  = 4				// 定义蜂鸣器错误事件宏，设置蜂鸣器状态为4
#define BELL_END() 				g_View.buzzer = 5				// 定义蜂鸣器结束事件宏，设置蜂鸣器状态为5		
#define BELL_TEMPER_ARRIVE() 	g_View.buzzer = 6				// 定义蜂鸣器温度到达事件宏，设置蜂鸣器状态为6
#define BUZZER_ERRPR3() 		g_View.buzzer = 7				// 定义蜂鸣器错误事件3宏，设置蜂鸣器状态为7
#define BUZZER_ERRPR5() 		g_View.buzzer = 8				// 定义蜂鸣器错误事件5宏，设置蜂鸣器状态为8


// 声明全局变量
extern volatile SYS_HARDWARE_T 		g_SysHardware;
extern volatile SYS_TIME_CNT_T 		g_sysTimeCnt;
extern volatile VIEW_T g_View;
extern volatile CONFIG_T 			g_config;


// 声明函数

uint8 Checkout(uint8* in, uint8 size);
uint16 htons(uint16 v);
uint32 htonl(uint32 v);


#endif




















































