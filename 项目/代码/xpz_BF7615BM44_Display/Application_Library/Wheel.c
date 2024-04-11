#include ".\CTK_Library\Config.h"
#include ".\CTK_Library\BF6961AX\BF6961AX.H"
#include ".\CTK_Library\BF6961AX\BF6961AX_CTK.H"
#include ".\Application_Library\wheel.h"
#if WHEEL_SENSOR_NUMBER
#include "Wheel.h"
#include <math.h>

// 手指离开后返回主函数的等待时间
#define WHEEL_MAX_DEPART_COUNT 50
//按滚轮顺序配置通道序号
uchar code WHEEL_SENSOR_ARRAY[WHEEL_SENSOR_NUMBER] = {10, 12, 14, 13};

uint code TAN_RESULT_UI[90] = {
    0, 17, 35, 52, 70, 87, 105, 123, 141, 158,
    176, 194, 213, 231, 249, 268, 287, 306, 325, 344,  
    364, 384, 404, 424, 445, 466, 488, 510, 532, 554, 
    577, 601, 625, 649, 675, 700, 727, 754, 781, 810,
    839, 869, 900, 933, 966, 1000, 1036, 1072, 1111, 1150,
    1192, 1235, 1280, 1327, 1376, 1428, 1483, 1540, 1600, 1664,
    1732, 1804, 1881, 1963, 2050, 2145, 2246, 2356, 2475, 2605,
    2747, 2904, 3078, 3271, 3487, 3732, 4011, 4331, 4705, 5145,
    5671, 6314, 7115, 8144, 9514, 11430, 14301, 19081, 28636, 57290,
};

#define NULL    0
#define PHASE_1 1
#define PHASE_2 2
#define PHASE_3 3
#define PHASE_4 4
char code COS_C[4] = {-1, -1, 1,  1};
char code SIN_C[4] = {-1,  1, 1, -1};


void Wheel_EventLoop()
{           
           uchar i,phase,j;
           uchar departCnt = 0, changeCnt = 0;
           bit   isNewTouch = 1;
           int   x, y;
         ulong   result;
           int   thisAngle; 
    static int   lastAngle;
           int   tempI;

    
    while(1) 
	{
        WDT_CTRL = 7;
        // detect whether there is a touch on the wheel
        x = 0;
        y = 0;
        departCnt++;        
        for (i = 0; i < WHEEL_SENSOR_NUMBER; i++) 
		{
            j = WHEEL_SENSOR_ARRAY[i];
			tempI = (baseline[j] - rawData[j]);
            if (tempI > 40) 
			{
                departCnt = 0;
            }
            if (tempI < 0) 
			{
                tempI = 0;
            }
            x += tempI * COS_C[i];
            y += tempI * SIN_C[i];
        }

        if (departCnt == 0) 
		{           
            phase = NULL;
            if (x > 0) 
			{
                if (y < 0) 
				{
                    phase = PHASE_4;                    
                    y *= -1;
                }
                else if (y > 0) 
				{
                    phase = PHASE_1;
                }
            }
            else if (x < 0) 
			{
                if (y < 0) 
				{
                    phase = PHASE_3;
                    x *= -1;
                    y *= -1;
                }
                else if (y > 0) 
				{
                    phase = PHASE_2;
                    x *= -1;
                }
            }
            else 
			{
                if (y < 0) 
				{
                    thisAngle = 270;
                }
                else if (y > 0) 
				{
                    thisAngle = 90;
                }
            }   

            if (phase) 
			{
                result = (ulong)y * 1000 / x;           
                for (i = 0; i < 89; i++) 
				{
                    if (TAN_RESULT_UI[i+1] > result) 
					{
                        break;
                    }
                }           

                if (phase == PHASE_1) 
				{
                    thisAngle = (int)i;
                }
                else if (phase == PHASE_2) 
				{
                    thisAngle = 180 - (int)i;
                }
                else if (phase == PHASE_3) 
				{  
                    thisAngle = 180 + (int)i;
                }
                else if (phase == PHASE_4) 
				{
                    thisAngle = 360 - (int)i;
                }                    
            }

             
            if (isNewTouch) 
			{ // if a new touch
                lastAngle = thisAngle;
                isNewTouch = 0;
            }
            else 
			{
                i = abs(lastAngle - thisAngle);
                if ((i < 3) || (i > 350)) 
				{
                    changeCnt++;
                    if (changeCnt > 5) 
					{
                        changeCnt = 0;
                        lastAngle = thisAngle;
                    }   
                }
                else 
				{
                    changeCnt = 0;
                }
            }    
        }       
        else 
		{
            if (departCnt > WHEEL_MAX_DEPART_COUNT) 
			{     //如果超出指定值
                    return;                 
            }
        }
    }
}
#endif                     