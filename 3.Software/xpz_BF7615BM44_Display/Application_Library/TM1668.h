#ifndef __TM1668_H__
#define __TM1668_H__


#define CFG_BRIGHTNESS          7    // 控制亮度
#define CFG_DATA_CMD_SETTING    0x44 // 0x44为固定地址模式，0x40为自动地址增加模式  
#define CFG_DISP_MODE_SETTING   0x03 // 显示命令设置，不需要改变    


extern unsigned char code DEG_TAB_UC[];

extern void TM1668_Init        (void);
extern void TM1668_Switch      (unsigned char flag);
extern void TM1668_SendAddrData (unsigned char addr, unsigned char dat);


#endif