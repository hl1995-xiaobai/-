#include "CTK01.h"
#include "TM1628.h"

#define SET_DIO()   DATAA |=  0x02  
#define CLR_DIO()   DATAA &= ~0x02
#define SET_SCLK()  DATAA |= 0x01
#define CLR_SCLK()  DATAA &= ~0x01
#define SET_STB()   PC4=1
#define CLR_STB()   PC4 =0
#define INIT_TRIS() TRISA &= ~0x03;TC4=0

// 显示控制，0x88-0x8f 从暗到亮变化
#define M_DISP_CTRL_SETTING(en) ((0x80 + CFG_BRIGHTNESS) | (en << 3))


static void Delay   (unsigned char t);
static void SendData(unsigned char dat);



void TM1628_Init()
{
    INIT_TRIS();
    SET_STB();
    Delay(1);

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

	//1628位段初始化。
	TM1628_SendAddrData(0xC0,0x00);
	TM1628_SendAddrData(0xC2,0x00);
	TM1628_SendAddrData(0xC4,0x00);
	TM1628_SendAddrData(0xC6,0x00);
      
} // TM1668_Init()


void TM1628_SendAddrData(unsigned char addr, unsigned char dat)
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
void TM1628_Switch(unsigned char flag)
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


}