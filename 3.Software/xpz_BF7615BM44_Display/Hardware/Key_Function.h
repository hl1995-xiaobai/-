#ifndef _Key_Function_H_
#define _Key_Function_H_


typedef struct
{
	unsigned long Key_Code;
	unsigned long Key_CodeRS;
	unsigned char Key_StateCnt;
	unsigned char key_long;
} Key_Struct;

#if(0)

#define Key_Num1  (0x00000001)
#define Key_Num2  (0x00000002)
#define Key_Num3  (0x00000004)
#define Key_Num4  (0x00000008)
#define Key_Num5  (0x00000010)
#define Key_Num6  (0x00000020)
#define Key_Num7  (0x00000040)
#define Key_Num8  (0x00000080)

#define Key_Num9  (0x00000100)
#define Key_Num10 (0x00000200)
#define Key_Num11 (0x00000400)
#define Key_Num12 (0x00000800)
#define Key_Num13 (0x00001000)
#define Key_Num14 (0x00002000)
#define Key_Num15 (0x00004000)
#define Key_Num16 (0x00008000)
#define Key_Num17 (0x00010000)
#define Key_Num18 (0x00020000)
#define Key_Num19 (0x00040000)
#define Key_Num20 (0x00080000)
#define Key_Num21 (0x00100000)

#endif

#define Key_Num1  (0x00000001)
#define Key_Num2  (0x00000002)
#define Key_Num3  (0x00000004)
#define Key_Num4  (0x00000008)
#define Key_Num5  (0x00000010)
#define Key_Num6  (0x00000020)
#define Key_Num7  (0x00000040)
#define Key_Num8  (0x00000080)

#define Key_Num9  (0x00000100)
#define Key_Num10 (0x00000200)
#define Key_Num11 (0x00000400)
#define Key_Num12 (0x00000800)
#define Key_Num13 (0x00001000)

extern  Key_Struct  KeyData;

void Key_Function_Deal(void);
void Power_SET(unsigned char i);
void Power_clear(void);
void Get_Key_Code(void);

#endif