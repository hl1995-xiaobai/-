#ifndef __TM1668_H__
#define __TM1668_H__


#define CFG_BRIGHTNESS          7    // ��������
#define CFG_DATA_CMD_SETTING    0x44 // 0x44Ϊ�̶���ַģʽ��0x40Ϊ�Զ���ַ����ģʽ  
#define CFG_DISP_MODE_SETTING   0x03 // ��ʾ�������ã�����Ҫ�ı�    


extern unsigned char code DEG_TAB_UC[];

extern void TM1668_Init        (void);
extern void TM1668_Switch      (unsigned char flag);
extern void TM1668_SendAddrData (unsigned char addr, unsigned char dat);


#endif