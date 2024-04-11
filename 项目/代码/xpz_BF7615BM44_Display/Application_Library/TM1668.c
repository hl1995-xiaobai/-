#include ".\CTK_Library\Config.h"
#define SET_DIO()   DATAB |=  0x01  
#define CLR_DIO()   DATAB &= ~0x01
#define SET_SCLK()  DATAB |=  0x02
#define CLR_SCLK()  DATAB &= ~0x02
#define SET_STB()   DATAC |=  0x02
#define CLR_STB()   DATAC &= ~0x02
#define INIT_TRIS() TRISC &= ~0x02;TRISB &= ~0x07

// 显示控制，0x88-0x8f 从暗到亮变化
#define M_DISP_CTRL_SETTING(en) ((0x80 + CFG_BRIGHTNESS) | (en << 3))


static void Delay   (unsigned char t);
static void SendData(unsigned char dat);

unsigned char code DEG_TAB_UC[10] = {
    0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F
};
 

void TM1668_Init()
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
  
//		TM1668_SendAddrData(0xC0,0xFF);//COM1,H3
//		TM1668_SendAddrData(0xC2,0xFF);//COM2,H6
//		TM1668_SendAddrData(0xC4,0xFF);//COM3,H5
//		TM1668_SendAddrData(0xC6,0xFF);//COM4,H7
		TM1668_SendAddrData(0xC8,0xFF);//G,W
		TM1668_SendAddrData(0xC9,0xFF);//爆炒
		TM1668_SendAddrData(0xCA,0xFF);//186,220,SL0,SL1,SL3~SL9
		TM1668_SendAddrData(0xCB,0xFF);//开关，煲汤
		TM1668_SendAddrData(0xCC,0xFF);//42,66,100,WIFI,WIFI_LED
		TM1668_SendAddrData(0xCD,0xFF);//定时，火锅

//		TM1668_SendAddrData(0xC0,DEG_TAB_UC[8]);//COM1,H3(bit7)

//		TM1668_SendAddrData(0xC2,DEG_TAB_UC[8]);//COM2,H6(bit7)
//		
//		TM1668_SendAddrData(0xC4,DEG_TAB_UC[8]);//COM3,H5(bit7)
//		
//		TM1668_SendAddrData(0xC6,DEG_TAB_UC[8]);//COM4,H7(bit7)
//		
//		TM1668_SendAddrData(0xC8,0x03);//W(bit1)、G(bit0)
//		
//		TM1668_SendAddrData(0xCA,0x78);//LED3(bit4)、LED4(bit6)、LED5(bit3)、LED7(bit5)
//		
//		TM1668_SendAddrData(0xCC,0x38);//LED1(bit3),LED2(bit4),LED6(bit5)
		
		
} // TM1668_Init()


void TM1668_SendAddrData(unsigned char addr, unsigned char dat)
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


//void TM1668_Switch(unsigned char flag)
//{   
//    CLR_STB();
//    SendData(M_DISP_CTRL_SETTING(flag));
//    SET_STB();
//} // TM1668_Switch(unsigned char)


static void Delay(unsigned char t)  
{
    for(; t > 0; t--);
    return; 
} // Delay(unsigned char)


static void SendData(unsigned char dat)
{
    unsigned char i;

    CLR_SCLK();
    for (i = 0x01; i != 0x00; i <<= 1) 
		{                              
        Delay(1);
        if (dat & i) 
				{
            SET_DIO();
        }
        else
				{
            CLR_DIO();
        }
        SET_SCLK();
        Delay(1);
        CLR_SCLK();
    }
} // SendData(unsigned char)

