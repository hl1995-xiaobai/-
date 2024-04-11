#ifndef __TM1635_H__
#define __TM1635_H__


#define CFG_BRIGHTNESS          7    // ��������
#define CFG_DATA_CMD_SETTING    0x44 // 0x44Ϊ�̶���ַģʽ��0x40Ϊ�Զ���ַ����ģʽ  
#define CFG_DISP_MODE_SETTING   0x03 // ��ʾ�������ã�����Ҫ�ı�    


extern unsigned char code SEG_TAB_UC[];
extern unsigned char xdata DIS_TAB[];

extern void TM1635_Delay_us(uint us);
extern void TM1635_I2CStart(void);
extern void TM1635_I2Cask(void);
extern void TM1635_I2CStop(void);
extern void TM1635_I2CWrByte(unsigned char oneByte);
extern unsigned char TM1635_ScanKey(void); 
extern void TM1635_SmgDisplay(bit on_off,uchar *dis_tab,uchar light);
extern void TM1635_Init();


#endif