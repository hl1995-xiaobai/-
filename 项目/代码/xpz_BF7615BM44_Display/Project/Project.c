#include ".\BF7615BMXX_XXXX_Library\Config.h"
/****************************************************************/
//�ο�������Project.c��Project.h
/****************************************************************/
bit IsTouch = 0;
uchar xdata Key_Data = 0x00;


	
/****************************************************************/
//��������void Project(void)
//��  �ܣ���Ŀ��Ŀ���ܺ���
//��  ������
//����ֵ����
/****************************************************************/
void Project(void)//����
{
#if(0)
    if((keys_flag_l != 0) || (keys_flag_h != 0))
	{
			if(IsTouch == 0)
			{
				IsTouch = 1;
				//��������
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