#include "include.h"

#include ".\BF7615BMXX_XXXX_Library\Config.h"

#include "Key_Function.h"



Key_Struct		KeyData;

//SysDat_Struct xdata SYS_Dat;


unsigned char KEY_NUM(unsigned char SCAN_NUM)
{
	unsigned char	i	= 0;
	unsigned char	j	= 0;
	unsigned long	DatRS = 0;

	if (SCAN_NUM < 32)
		DatRS = keys_flag_l;
	else 
		DatRS = keys_flag_h;

	j					= SCAN_NUM % 32;

	if ((DatRS >> j) & 0x00000001)
		i = 1;
	else 
		i = 0;

	return i;
}


void Get_Key_Code(void) //main 20ms
{

#if(0)

	if((keys_flag_l != 0) || (keys_flag_h != 0))
	{
			if(IsTouch == 0)
			{
				IsTouch = 1;
				//按键处理
				if(keys_flag_l == 0x00000001)
				{
					Key_Data = 0x01;
				}
			}
	}
	else
	{
			if(IsTouch == 1)
			{
				IsTouch = 0;
			}
	}
	
#endif	

	KeyData.Key_CodeRS	= 0;

	if (KEY_NUM(SCAN_00))
		KeyData.Key_CodeRS |= Key_Num1;

	if (KEY_NUM(SCAN_01))
		KeyData.Key_CodeRS |= Key_Num2;

	if (KEY_NUM(SCAN_02))
		KeyData.Key_CodeRS |= Key_Num3;

	if (KEY_NUM(SCAN_03))
		KeyData.Key_CodeRS |= Key_Num4;

	if (KEY_NUM(SCAN_04))
		KeyData.Key_CodeRS |= Key_Num5;

	if (KEY_NUM(SCAN_05))
		KeyData.Key_CodeRS |= Key_Num6;

	if (KEY_NUM(SCAN_06))
		KeyData.Key_CodeRS |= Key_Num7;

	if (KEY_NUM(SCAN_07))
		KeyData.Key_CodeRS |= Key_Num8;

	if (KEY_NUM(SCAN_08))
		KeyData.Key_CodeRS |= Key_Num9;

	if (KEY_NUM(SCAN_09))
		KeyData.Key_CodeRS |= Key_Num10;

	if (KEY_NUM(SCAN_10))
		KeyData.Key_CodeRS |= Key_Num11;

	if (KEY_NUM(SCAN_11))
		KeyData.Key_CodeRS |= Key_Num12;

	if (KEY_NUM(SCAN_12))
		KeyData.Key_CodeRS |= Key_Num13;


#if(0)
	if (Display_Run.UpPowerFlag){
		KeyData.Key_Code = 0;
	}
#endif		
	
}



void Key_Function_Deal(void)
{
	Get_Key_Code();

	if (KeyData.Key_CodeRS == KeyData.Key_Code) {

		if (KeyData.Key_Code == 0) {
			KeyData.key_long = CLE;
			KeyData.Key_StateCnt = 0;
			return;
		}

		if (KeyData.Key_StateCnt < 200)
			KeyData.Key_StateCnt++;


//		if (KeyData.Key_StateCnt == 25) {
		if (KeyData.Key_StateCnt == 50) {
			if (KeyData.Key_CodeRS == Key_Num1) {
				
				KeyData.key_long = SET;
				
			}
			
			
			else if (KeyData.Key_CodeRS == Key_Num10) {	
				
				KeyData.Key_StateCnt = 20;
				KeyData.key_long = SET;
			}

			else if (KeyData.Key_CodeRS == Key_Num11) {	
				
				KeyData.Key_StateCnt = 20;
				KeyData.key_long = SET;
			}
			
		}

	}
	else {

		if((KeyData.Key_Code == 0) && (KeyData.Key_CodeRS != 0)){
			// 按键被按下
			
		}

		else if((KeyData.Key_Code != 0) && (KeyData.Key_CodeRS == 0)){
			// 按键被抬起
			if(KeyData.Key_StateCnt < 5){
				switch (KeyData.Key_CodeRS)
				{
					case Key_Num1:
						KeyData.Key_CodeRS = KeyData.Key_CodeRS;
						break;

					case Key_Num2:
						KeyData.Key_CodeRS = KeyData.Key_CodeRS;
						break;

					case Key_Num3:
						KeyData.Key_CodeRS = KeyData.Key_CodeRS;
						break;

					case Key_Num4:
						KeyData.Key_CodeRS = KeyData.Key_CodeRS;
						break;

					case Key_Num5:
						KeyData.Key_CodeRS = KeyData.Key_CodeRS;
						break;

					case Key_Num6:
						KeyData.Key_CodeRS = KeyData.Key_CodeRS;
						break;

					case Key_Num7:
						KeyData.Key_CodeRS = KeyData.Key_CodeRS;
						break;

					case Key_Num8:
						KeyData.Key_CodeRS = KeyData.Key_CodeRS;
						break;

					case Key_Num9:
						KeyData.Key_CodeRS = KeyData.Key_CodeRS;
						break;

					case Key_Num10:
						KeyData.Key_CodeRS = KeyData.Key_CodeRS;
						break;

					case Key_Num11:
						KeyData.Key_CodeRS = KeyData.Key_CodeRS;
						break;

					case Key_Num12:
						KeyData.Key_CodeRS = KeyData.Key_CodeRS;
						break;

					case Key_Num13:
						KeyData.Key_CodeRS = KeyData.Key_CodeRS;
						break;

					

					default:
						break;
				}
			}
		}

		else if(KeyData.Key_StateCnt > 50){
			// 长按抬起
			
			
		}
	
		

		KeyData.Key_Code		= KeyData.Key_CodeRS;
		KeyData.Key_StateCnt 	= 0;
		KeyData.key_long 		= CLE;
		g_View.FlashOn			= CLE;
	}

}










