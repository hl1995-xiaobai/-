#ifndef __TM1628_H__
#define __TM1628_H__


#define CFG_BRIGHTNESS          6    // ��������
#define CFG_DATA_CMD_SETTING    0x44 // 0x44Ϊ�̶���ַģʽ��0x40Ϊ�Զ���ַ����ģʽ  
#define CFG_DISP_MODE_SETTING   0x03 // ��ʾ�������ã�����Ҫ�ı�    


extern unsigned char code DEG_TAB_UC[];

extern void TM1628_Init        (void);
extern void TM1628_Switch      (unsigned char flag);
extern void TM1628_SendAddrData (unsigned char addr, unsigned char dat);


#endif