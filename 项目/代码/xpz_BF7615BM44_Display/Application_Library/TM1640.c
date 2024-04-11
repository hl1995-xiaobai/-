#include "CTK01.h"
#include "TM1640.h"
    

#define SET_DIN()   DATAC |=  0x20
#define CLR_DIN()   DATAC &= ~0x20
#define SET_SCLK()  DATAC |=  0x10
#define CLR_SCLK()  DATAC &= ~0x10
#define INIT_TRIS() TRISC &= ~0x30

#define M_DISP_CTRL_SETTING(en) ((0x80 + CFG_BRIGHTNESS) | (en << 3))


static void SendDat(unsigned char dat);
static void Start  (void);
static void End    (void);


void TM1640_Init()
{
    INIT_TRIS();
    // 数据命令设置（固定地址）
    Start();
    SendDat(CFG_DATA_CMD_SETTING);
    End();

    TM1640_SendAddrDat(0xC0, 0x00);
    TM1640_SendAddrDat(0xC1, 0x00);
    TM1640_SendAddrDat(0xC2, 0x00);
    TM1640_SendAddrDat(0xC3, 0x00);
    TM1640_SendAddrDat(0xC4, 0x00);
    TM1640_SendAddrDat(0xC5, 0x00);
    // 显示控制设置
    Start();
    SendDat(M_DISP_CTRL_SETTING(1));
    End();
}


void TM1640_Switch(unsigned char flag)
{
    Start();
    SendDat(M_DISP_CTRL_SETTING(flag));
    End();
}


void TM1640_SendAddrDat(unsigned char addr,unsigned char dat)
{
    Start();
    SendDat(addr);
    SendDat(dat);
    End();
}


static void SendDat(unsigned char dat)
{
    unsigned char i;
    
    for (i = 0x01; i != 0x00; i <<= 1) {
        if (dat & i) {  
            SET_DIN();
        }
        else {
            CLR_DIN();
        }
        SET_SCLK();
        CLR_SCLK();
    }
}


static void Start()
{
    SET_DIN(); 
    SET_SCLK(); 
    CLR_DIN();
    CLR_SCLK();
}


static void End()
{
    CLR_SCLK();
    CLR_DIN();
    SET_SCLK();
    SET_DIN();
}   

