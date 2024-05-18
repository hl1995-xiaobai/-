#ifndef _VIEW_H_
#define _VIEW_H_

//#include "SteamOvenView.h"
//#include "RangeHoodView.h"

#define HOST_FIRMWARE_VERSION_NUMBER		0x10	/*����λ���̼��汾�ţ�V1.0*/

#define NUM_AREAS 16  // ������16������


#define SET_MODE_AUTO_END_TIME   			5  		/*����ģʽ�Զ�����ʱ�䣨�룩*/
#define BRIGHT_AUTO_END_TIME     			180  	/*�����Զ�����ʱ�䣨�룩*/
#define AUTO_DOOR_LOCK_CNT					3     	/*�����Զ���������ʱ(��)*/
#define AUTO_WORK_END_CNT					180     /*��������״̬��ʾʱ��*/
#define AUTO_OFF_TIME    		 			180  	/*�Զ��ػ�ʱ��180���룩*/
#define AUTO_STANDBY_TIME    		 		120  	/*�Զ�����ʱ�䣨�룩*/
#define HEART_BEAT_TIME    		 			10  	/*��������10���룩*/
#define IOT_REPORT_TIME    		 			8  		/*�ϱ�����10���룩*/
#define MODULE_STATUS_QUERY_TIME    		8  		/*ģ��״̬��ѯ10���룩*/
#define IOT_CMD_TIME    		 			25  	/*ָ��������250�����룩*/
#define WINDSPEED_MAX_DELAY_OFF_TIME    	120  	/*���3����ʱ�ر�120���룩*/
#define WINDSPEED_MAX_DELAY_OFF_TEN_MINUTES 600  	/*���3����ʱ�ر�600���룩*/
#define CLEANOUT_AUTO_ENTER_TIME    		5  		/*3S�Զ�������ϴģʽ���룩*/
#define SUBSCRIBE_TIME    					300  	/*ԤԼ3�����޲�����������ƣ��룩*/


// ��������������ܵ�Ԥ��ʱ�䣨�룩
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



#define AREA_POWER							0     /*��Դ����*/
#define AREA_DOOR							1     /*��������*/
#define AREA_A								2     /*A ����*/
#define AREA_B								3     /*B ����*/
#define AREA_C								4     /*C ����*/
#define AREA_D								5     /*D ����*/
#define AREA_E								6     /*E ����*/
#define AREA_DRAIN							7     /*��ˮ ����*/
#define AREA_MENU							8     /*�˵����� ����*/
#define AREA_NUM1							9     /*����1 ����*/
#define AREA_NUM2							10     /*����2 ����*/
#define AREA_UP								11     /*�� ����*/
#define AREA_DOWN							12     /*�� ����*/
#define AREA_HEAT							13     /*���� ����*/
#define AREA_PLAY							14     /*���� ����*/
#define AREA_HAND							15     /*���� ����*/




#define LED_QL								2     /*ȫ��*/
#define LED_BL								1     /*����*/
#define LED_NULL							0     /*����*/



#define LED_NORMAL_BRIGHT					10     /*LED��������*/
#define LED_STANDBY_BRIGHT					2      /*LED��������*/


#define STEAM_OVEN_POWER_OFF 		0  /**/
#define STEAM_OVEN_POWER_ON 		1  /**/

#define WORK_SET_MODE_OFF			 				0  
#define WORK_SET_MODE_SYSTIME_H						1 	/*����ϵͳʱ��Сʱ*/
#define WORK_SET_MODE_SYSTIME_M						2 	/*����ϵͳʱ�����*/
#define WORK_SET_MODE_STEAMOVEN_TIME				3 	/*���������乤��ʱ��*/
#define WORK_SET_MODE_STEAMOVEN_TEMPER				4 	/*���������乤���¶�*/
#define WORK_SET_MODE_STEAMOVEN_SUBSCRIBE_HOUR		5 	/*����ԤԼʱ��Сʱ*/
#define WORK_SET_MODE_STEAMOVEN_SUBSCRIBE_MINUTE	6 	/*����ԤԼʱ�����*/
#define WORK_SET_MODE_LEFT_CLOCK	   				7 	/*������ʱ*/
#define WORK_SET_MODE_RIGHT_CLOCK	   				8 	/*�����Ҷ�ʱ*/
#define WORK_SET_MODE_SPEED			   				9 	/*��ʾ����*/
#define WORK_SET_MODE_GESTURE		   				10 	/*������ֿ*/
#define WORK_SET_MODE_FIREWALL		   				11 	/*���ÿ����رշ��𱨾�*/
#define WORK_SET_MODE_GAS		   					12 	/*���ÿ����رշ��𱨾�*/
#define WORK_SHOW_BOT_TEMPER 						13  /*��ʾ�����¶�*/
#define WORK_SHOW_PROBE_TEMPER 						14  /*��ʾ̽ͷ�¶�*/
#define WORK_SET_CLEANOUT 							15  /*��ϴ*/
#define WORK_SET_HEAD_HEAT							16	/*����ͷ�����¹���*/








#define ERROR_CODE_NO_ERROR				0
#define ERROR_CODE_INTER_NTC			1	/*ǻ��NTC����*/
#define ERROR_CODE_BOT_NTC				2	/*�����̵�NTC�쳣*/
#define ERROR_CODE_NO_ARRIVE			3	/*�����¶��쳣*/
#define ERROR_CODE_COMMUNICATE			4	/*ͨѶ����*/
#define ERROR_CODE_DOOR_OPEN			5	/*�ſع���*/
#define ERROR_CODE_WATER_LACK			6	/*ȱˮ����*/

#define ACK_NULL						0	/**/
#define STATUS_ILLUMINATIONCTRL_ACK		1	/*����*/
#define STATUS_HOODSPEEDCTRL_ACK		2	/*����*/
#define STATUS_WASHCTRL_ACK				3	/*��ϴ*/
#define STATUS_PAUSE					4	/*��ͣ*/
#define STATUS_STOP						5	/*ֹͣ*/
#define STATUS_PLAY						6	/*����*/
#define STATUS_ERROR_EVENT				7	/*�����¼�*/
#define STATUS_ALERT_EVENT				8	/*�����¼�*/
#define STATUS_COOK_EVENT				9	/*����¼�*/
#define STATUS_ERROR					10	/*����*/


#define SYSMODE_NORMAL 	0	/*��������ģʽ*/
#define SYSMODE_TEST 	1	/*����ģʽ*/
#define SYSMODE_PLANT 	2	/*����ģʽ*/


// ����ϵͳӲ����Ϣ�ṹ��
typedef struct{
	uint8 sysInit 		:1;		// ϵͳ��ʼ����־λ
	uint8 SysMode 		:2;		// ϵͳģʽ
	
	uint8 SysTime100us	:1;		//
	
	uint8 SysTime1ms	:1;		// 1����ϵͳʱ���־λ
	uint8 SysTime10ms	:1;		// 10����ϵͳʱ���־λ
	uint8 SysTime20ms 	:1;		// 20����ϵͳʱ���־λ
	uint8 SysTime100ms 	:1;		// 100����ϵͳʱ���־λ
	
	uint8 SysTime500ms 	:1;		// 500����ϵͳʱ���־λ
	uint8 SysTime1S 	:1;		// 1��ϵͳʱ���־λ
	uint8 				:6;		//

	uint8 VersionYear	:8;		// �����汾��
	uint8 VersionMonth	:8;		// �����汾��
	uint8 VersionDay	:8;		// �����汾��
	uint8 SysCnt		:8;		// ϵͳ������
	uint8 SysTimeHour;			// ϵͳʱ��Сʱ
	uint8 SysTimeMinute;		// ϵͳʱ�����
	uint8 SysTimeSecond;		// ϵͳʱ����

	uint8 TestCnt;				// ���Լ�����
	uint8 TestType;				// ��������

	uint8 Time_4ms_cnt;
	uint8 Time_20ms_cnt;
	uint8 Time_100ms_cnt;
	uint16 Time_500ms_cnt;
	uint16 Time_1000ms_cnt;
}xdata SYS_HARDWARE_T;

// ����ϵͳʱ��������ṹ��
typedef struct{
	uint8 Time0TL0;				// ��ʱ��0��8λ
	uint8 Time0TH0;				// ��ʱ��0��8λ
	uint8 sysTime100usCnt;
	uint8 sysTime10msCnt;		// 10����ϵͳʱ�������
	uint8 sysTime20msCnt;		// 20����ϵͳʱ�������
	uint8 sysTime100msCnt	:4;	// 100����ϵͳʱ�������
	uint8 sysTime500msCnt	:4;	// 500����ϵͳʱ�������
	uint8 sysTime1sCnt		:4;	// 1��ϵͳʱ�������
	uint8 Timecnt			:5;	// ��ʱ��������
	uint8 cnt;					// ������
}xdata SYS_TIME_CNT_T;




// ������ͼ��Ϣ�ṹ��
typedef struct{
	uint8 VersionYearP;						// �����汾��
	uint8 VersionMonthP;					// �����汾��
	uint8 VersionDayP;						// �����汾��
	uint8 VersionNumber;					// ��λ���̼��汾��
	uint8 TemperShowCnt;					// �¶���ʾ������

	uint8 PowerOn			:1;				// ��Դ
	uint8 KidLock			:1;				// ͯ��
	uint8 FlashOn			:1;				// ��˸
	uint8 Flash				:1;				// ��˸
	uint8 FashFlash			:1;				// ����
	uint8 Flash_1000ms		:1;				// ��˸
	uint8 wifi_icon 		:1;				// Wifi ͼ����ʾ��ʽ ����
	uint8 wifi_icon_flash 	:1;				// Wifi ͼ����ʾ��ʽ ��˸

	uint8 oil_spill_alarm_icon 			:1;	// ���ͱ��� ͼ����ʾ��ʽ ����
	uint8 oil_spill_alarm_icon_flash 	:1;	// ���ͱ��� ͼ����ʾ��ʽ ��˸
	uint8 					:2;				//
	uint8 buzzer			:4;				// ������

	uint8 SetMode;							// ����ģʽ
	uint8 LedBright;						// LED ����

	uint8 AutoOffCnt;						// �Զ��ػ��������룩
	uint8 AutoStandbyCnt;					// �Զ������������룩

	uint8 SetModeOffCnt;					// ����ģʽ�����������룩

	uint8 AutoOffStandbyCnt;				// �ػ��Զ������������룩

	uint8 Cnt;								//

	uint8 SendingState;						// ����״̬

	uint8 CurrentArea;  					// ��ǰLED�������

	uint8 BrightnessTime[NUM_AREAS];

	uint8 packet_id_query_device_status;

	uint8 CommandIntervalPeriod;

	uint8 QueryDeviceStatusSendFlag							: 1;	/*��ѯ�豸״̬*/
	uint8 SendWashDataSendFlag								: 1;	/*��׼ϴ��*/
	uint8 SendFunctionTestSendFlag							: 1;	/*ά�����ܲ���*/	
	uint8 ErrorInformationReportingSendFlag					: 1;	/*������Ϣ�ϱ�*/
	
	uint8 SendFunctionSettingSendFlag						: 1;	/*�����趨*/
	uint8 SendParameterCalibrationSendFlag					: 1;	/*����У׼*/
	uint8 SendDryingDataSendFlag							: 1;	/*���*/
	uint8 													: 1;

	// STEAM_OVEN_VIEW_T SteamOven;
	// RANGE_HOOD_VIEW_T RangeHood;
	// RANGE_HOOD_RECV_T RangeHoodRead;
}xdata VIEW_T,*PVIEW_T;


typedef struct{	
	
	uint16 LED_OUT0 		:1;
	uint16 LED_OUT1			:1;
	uint16 LED_OUT2			:1;
	uint16 LED_OUT3			:1;
	uint16 LED_OUT4			:1;
	uint16 LED_OUT5			:1;
	uint16 LED_OUT6			:1;
	uint16 LED_OUT7			:1;

	uint16 LED_OUT8			:1;
	uint16 LED_OUT9			:1;
	uint16 LED_OUT10		:1;
	uint16 LED_OUT11		:1;

	uint16 					:4;
	
}xdata SM16106_T,*PSM16106_T;


typedef union{
//	uint8 BrightnessTime[NUM_AREAS];
//    uint8 CurrentArea;  // ��ǰLED�������

	uint8 v[5];
	struct{
		uint8 	key_power_led 		:1;
		uint8 	key_door_led 		:1;
		uint8 	key_A_led 			:1;
		uint8 	key_B_led 			:1;
		uint8 	key_C_led 			:1;
		uint8 	key_D_led 			:1;
		uint8 	key_E_led 			:1;
		uint8 	key_drain_led 		:1;

		uint8 	key_menu_led 		:1;
		uint8 	key_up_led 			:1;
		uint8  	key_down_led		:1;
		uint8 	key_heat_led		:1;
		uint8 	key_play_led 		:1;
		uint8 	hand_left_led 		:1;
		uint8 	hand_right_led 		:1;
		uint8 		 				:1;

		uint8 	process_led 		:1;
		uint8  	time_led			:1;		
		uint8 		 				:6;

		uint8 	num1_A_led 			:1;
		uint8 	num1_F_led 			:1;
		uint8 	num1_B_led 			:1;
		uint8 	num1_G_led 			:1;
		uint8 	num1_E_led 			:1;
		uint8 	num1_C_led 			:1;
		uint8 	num1_D_led 			:1;
		uint8 	point_led			:1;

		uint8 	num2_A_led 			:1;
		uint8 	num2_F_led 			:1;
		uint8 	num2_B_led 			:1;
		uint8 	num2_G_led 			:1;
		uint8 	num2_E_led 			:1;
		uint8 	num2_C_led 			:1;
		uint8 	num2_D_led 			:1;
		uint8 	temper_led			:1;
	
	}v_f;
	
}xdata DISPLAY_LED_T;


// ����������Ϣ�ṹ��
typedef struct{
	uint8  magic; 							// ħ��
	uint32 oilBoxCnt; 						// �ͺм���
	union{
		uint8 vlue;
		struct{
			uint8 firewall	:1;				// ����ǽ��������
			uint8 gas		:1;				// ������������
			uint8 gears		:1;				// ��ʾת��
			uint8 Gesture	:1;				// ������ֿ����
			uint8 oilBox	:1;				// �����ͺб�������
			uint8 			:3;				//
		}b;
	}sw;
	uint8  DegugCount;						// ���Լ���
	uint8  checkout;						// У��λ
}xdata CONFIG_T;






#define BUZZER_KEY_EVENT() 		g_View.buzzer  = 1				// ��������������¼��꣬���÷�����״̬Ϊ1
#define BUZZER_POWER_ON() 		g_View.buzzer  = 2				// ��������������¼��꣬���÷�����״̬Ϊ2
#define BUZZER_POWER_OFF() 		g_View.buzzer  = 3				// ����������ػ��¼��꣬���÷�����״̬Ϊ3
#define BUZZER_ERRPR() 			g_View.buzzer  = 4				// ��������������¼��꣬���÷�����״̬Ϊ4
#define BELL_END() 				g_View.buzzer = 5				// ��������������¼��꣬���÷�����״̬Ϊ5		
#define BELL_TEMPER_ARRIVE() 	g_View.buzzer = 6				// ����������¶ȵ����¼��꣬���÷�����״̬Ϊ6
#define BUZZER_ERRPR3() 		g_View.buzzer = 7				// ��������������¼�3�꣬���÷�����״̬Ϊ7
#define BUZZER_ERRPR5() 		g_View.buzzer = 8				// ��������������¼�5�꣬���÷�����״̬Ϊ8


// ����ȫ�ֱ���
extern volatile SYS_HARDWARE_T 		g_SysHardware;
extern volatile SYS_TIME_CNT_T 		g_sysTimeCnt;
extern volatile VIEW_T g_View;
extern xdata const PSM16106_T pSM16106;
extern volatile DISPLAY_LED_T  		g_DisplayLed;
extern volatile CONFIG_T 			g_config;


// ��������

uint8 Checkout(uint8* in, uint8 size);
uint16 htons(uint16 v);
uint32 htonl(uint32 v);


#endif



















































