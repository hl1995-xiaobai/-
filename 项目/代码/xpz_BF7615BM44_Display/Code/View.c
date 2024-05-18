#include "include.h"    
#include "View.h"       

volatile SYS_HARDWARE_T g_SysHardware;   	// ȫ�ֱ������洢ϵͳӲ����Ϣ���ױ�ģ����ܻᱻ�жϻ������߳��޸�
volatile SYS_TIME_CNT_T g_sysTimeCnt;    	// ȫ�ֱ������洢ϵͳʱ���������Ϣ���ױ�ģ����ܻᱻ�жϻ������߳��޸�
volatile VIEW_T g_View;                  	// ȫ�ֱ������洢��ͼ��Ϣ���ױ�ģ����ܻᱻ�жϻ������߳��޸�
xdata const PSM16106_T pSM16106 = (PSM16106_T)(&r_SM16106);
volatile DISPLAY_LED_T  		g_DisplayLed;
volatile CONFIG_T g_config;               	// ȫ�ֱ������洢������Ϣ���ױ�ģ����ܻᱻ�жϻ������߳��޸�


// ���� htons: ��16λ�������ֽ���������ֽ���ת��Ϊ�����ֽ��򣨴���ֽ���
// ���� v: ��ת����16λ����
// ����ֵ: ת�����16λ����
uint16 htons(uint16 v){
    return ((v>>8) | (v<<8));    											// ��8λ�͵�8λ����λ��
}


// ���� htonl: ��32λ�������ֽ���������ֽ���ת��Ϊ�����ֽ��򣨴���ֽ���
// ���� v: ��ת����32λ����
// ����ֵ: ת�����32λ����
uint32 htonl(uint32 v){
    return ((((v) & 0xff000000u) >> 24) | (((v) & 0x00ff0000u) >>  8) | 
            (((v) & 0x0000ff00u) <<  8) | (((v) & 0x000000ffu) << 24));   // �ֽ�λ�û���
}


// ���� Checkout: �����ֽ������У���
// ���� in: ������У��͵��ֽ�����
// ���� size: �ֽ�����Ĵ�С
// ����ֵ: �ֽ������У���
uint8 Checkout(uint8* in, uint8 size){
    uint8 ret = 0;    														// ��ʼ��У���Ϊ0

    // �����ֽ����飬�ۼ�ÿ���ֽڵ�ֵ��У���
    while(size--){
        ret += in[size];    												// �ۼ�ÿ���ֽڵ�ֵ��У���
    }
    
    return ret;   	 														// ���ؼ���õ���У���
}
