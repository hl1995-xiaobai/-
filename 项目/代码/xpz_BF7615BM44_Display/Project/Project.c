#include ".\BF7615BMXX_XXXX_Library\Config.h"
/****************************************************************/
//参考范例：Project.c和Project.h
/****************************************************************/
bit IsTouch = 0;
uchar xdata Key_Data = 0x00;


	
/****************************************************************/
//函数名：void Project(void)
//功  能：项目项目功能函数
//参  数：无
//返回值：无
/****************************************************************/
void Project(void)//范例
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
	if(Test){
		SET_PB6_H;
	}else{
		SET_PB6_L;
	}	
}