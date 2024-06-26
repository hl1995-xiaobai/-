#include "include.h"

#include "SysTime.h"



void SysTimeInit(void){

	memset((void*)&g_sysTimeCnt,0, sizeof(SYS_TIME_CNT_T));

	g_SysHardware.SysTimeHour = 12;
	
	 
}

void Time_Basic(void) //Interrupt-0-250us
{
	if(g_SysHardware.Time_4ms_cnt)	g_SysHardware.Time_4ms_cnt--;
	if(g_SysHardware.Time_20ms_cnt) 	g_SysHardware.Time_20ms_cnt--;
	if(g_SysHardware.Time_100ms_cnt) 	g_SysHardware.Time_100ms_cnt--;
	if(g_SysHardware.Time_500ms_cnt) 	g_SysHardware.Time_500ms_cnt--;
	if(g_SysHardware.Time_1000ms_cnt) g_SysHardware.Time_1000ms_cnt--;
}



void SysTime100us(void){

	
	g_sysTimeCnt.sysTime100usCnt++;

	if(g_sysTimeCnt.sysTime100usCnt >= 10){
		g_SysHardware.SysTime1ms = SET;
		g_sysTimeCnt.sysTime100usCnt = 0;
		g_SysHardware.SysTime1ms = SET;
	}
}


void SysTime1ms(void){

//	g_SysHardware.SysTime1ms = SET;

	g_sysTimeCnt.sysTime10msCnt++;
	if(g_sysTimeCnt.sysTime10msCnt >= 10 ){
		g_sysTimeCnt.sysTime10msCnt = 0;
		g_SysHardware.SysTime10ms = SET;
	}
	
}

void SysTime10msPool(){
	g_sysTimeCnt.sysTime20msCnt++;
	if(g_sysTimeCnt.sysTime20msCnt >= 2 ){
		g_sysTimeCnt.sysTime20msCnt = 0;
		g_SysHardware.SysTime20ms = SET;
	}
}


void SysTime20msPool(){
	g_sysTimeCnt.sysTime100msCnt++;
	if(g_sysTimeCnt.sysTime100msCnt >= 5 ){
		g_sysTimeCnt.sysTime100msCnt = 0;
		g_SysHardware.SysTime100ms = SET;
	}
}

void SysTime100msPool(){
	g_sysTimeCnt.sysTime500msCnt++;
	if(g_sysTimeCnt.sysTime500msCnt >= 5 ){
		g_sysTimeCnt.sysTime500msCnt = 0;
		g_SysHardware.SysTime500ms = SET;
	}
}

void SysTime500msPool(){
	g_sysTimeCnt.sysTime1sCnt++;
	if(g_sysTimeCnt.sysTime1sCnt >= 2 ){
		g_sysTimeCnt.sysTime1sCnt = 0;
		g_SysHardware.SysTime1S = SET;
	}
}

