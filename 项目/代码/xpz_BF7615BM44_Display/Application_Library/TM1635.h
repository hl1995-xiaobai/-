#ifndef __TM1635_H__
#define __TM1635_H__


#define CFG_BRIGHTNESS          7    // 控制亮度
#define CFG_DATA_CMD_SETTING    0x44 // 0x44为固定地址模式，0x40为自动地址增加模式  
#define CFG_DISP_MODE_SETTING   0x03 // 显示命令设置，不需要改变    


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