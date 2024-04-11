#include "CTK\CTK.h"
#include "TM1629.h"


#define SET_DIO()   DATAA |=  0x04  
#define CLR_DIO()   DATAA &= ~0x04
#define SET_SCLK()  DATAA |=  0x01
#define CLR_SCLK()  DATAA &= ~0x01
#define SET_STB()   DATAC |=  0x04
#define CLR_STB()   DATAC &= ~0x04

#define INIT_TRIS() TRISA &= ~0x05;PC2_Init();PC2_OUT();PC2_OUT_H();

// 显示控制，0x88-0x8f 从暗到亮变化

#define M_DISP_CTRL_SETTING(en) ((0x80 + CFG_BRIGHTNESS) | (en << 3))

static void Delay   (unsigned char t);
static void SendData(unsigned char dat);

//0-9
//unsigned char code DEG_TAB_UC[10] = {
//    0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F
//};

//0-9
unsigned char code DEG_TAB_UC[10] = {0xD7, 0x11, 0xE5, 0x75, 0x33, 0x76, 0xF6, 0x15, 0xF7, 0x77};

void TM1629_Init()
{
	EA = 0;
    INIT_TRIS();
    SET_STB();
    Delay(5);

    // 发送显示模式设置
    CLR_STB();
    SendData(CFG_DISP_MODE_SETTING);
    SET_STB();
    Delay(5);

    // 发送数据命令设置
    CLR_STB();
    SendData(CFG_DATA_CMD_SETTING);
    SET_STB();
    Delay(5);



    // 发送显示控制
    CLR_STB();
    SendData(M_DISP_CTRL_SETTING(1));
    SET_STB();
    Delay(5); 

	EA = 1;
	      
} //TM1629_Init()


void TM1629_SendAddrData(unsigned char addr, unsigned char dat)
{
    SET_STB();
    Delay(1);
    CLR_STB();
    SendData(addr);
    Delay(1);
    SendData(dat);
    SET_STB();
    Delay(5);
} // TM1668_SendAddrData(unsigned char, unsigned char)   

/*
void TM1629_Switch(unsigned char flag)
{   
    CLR_STB();
    SendData(M_DISP_CTRL_SETTING(flag));
    SET_STB();
} // TM1668_Switch(unsigned char)

*/
static void Delay(unsigned char t)  
{
    for(; t > 0; t--);
    return; 
} // Delay(unsigned char)


static void SendData(unsigned char dat)
{
    unsigned char i;

    CLR_SCLK();
    for (i = 0x01; i != 0x00; i <<= 1) {                              
        Delay(1);
        if (dat & i) {
            SET_DIO();
        }
        else {
            CLR_DIO();
        }
        SET_SCLK();
        Delay(1);
        CLR_SCLK();
    }
} // SendData(unsigned char)