#include "include.h"    
#include "View.h"       

volatile SYS_HARDWARE_T g_SysHardware;   	// 全局变量，存储系统硬件信息，易变的，可能会被中断或其他线程修改
volatile SYS_TIME_CNT_T g_sysTimeCnt;    	// 全局变量，存储系统时间计数器信息，易变的，可能会被中断或其他线程修改
volatile VIEW_T g_View;                  	// 全局变量，存储视图信息，易变的，可能会被中断或其他线程修改
xdata const PSM16106_T pSM16106 = (PSM16106_T)(&r_SM16106);
volatile DISPLAY_LED_T  		g_DisplayLed;
volatile CONFIG_T g_config;               	// 全局变量，存储配置信息，易变的，可能会被中断或其他线程修改


// 函数 htons: 将16位整数的字节序从主机字节序转换为网络字节序（大端字节序）
// 参数 v: 待转换的16位整数
// 返回值: 转换后的16位整数
uint16 htons(uint16 v){
    return ((v>>8) | (v<<8));    											// 高8位和低8位交换位置
}


// 函数 htonl: 将32位整数的字节序从主机字节序转换为网络字节序（大端字节序）
// 参数 v: 待转换的32位整数
// 返回值: 转换后的32位整数
uint32 htonl(uint32 v){
    return ((((v) & 0xff000000u) >> 24) | (((v) & 0x00ff0000u) >>  8) | 
            (((v) & 0x0000ff00u) <<  8) | (((v) & 0x000000ffu) << 24));   // 字节位置互换
}


// 函数 Checkout: 计算字节数组的校验和
// 参数 in: 待计算校验和的字节数组
// 参数 size: 字节数组的大小
// 返回值: 字节数组的校验和
uint8 Checkout(uint8* in, uint8 size){
    uint8 ret = 0;    														// 初始化校验和为0

    // 遍历字节数组，累加每个字节的值到校验和
    while(size--){
        ret += in[size];    												// 累加每个字节的值到校验和
    }
    
    return ret;   	 														// 返回计算得到的校验和
}
