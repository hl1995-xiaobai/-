#include ".\CTK_Library\Config.h"
#include ".\Application_Library\slider.h"
#if SLIDER_SENSOR_NUMBER
#include "Slider.h"

#include <math.h>
#define LEVEL_INSIDE    ((LEVEL_LENGTH + EDGE_RANGE) * LEVEL_OUTSIDE * 1.000)
#define MULTI_FACTOR    ((LEVEL_INSIDE / (SLIDER_SENSOR_NUMBER - 1) + 0.005) * 100)
#define DIV_FACTOR      (LEVEL_LENGTH + EDGE_RANGE)
#define EDGE_LEFT       (LEVEL_LENGTH + (EDGE_RANGE / 2))
#define EDGE_RIGHT      (EDGE_RANGE / 2)

// 手指离开后返回主函数的等待时间
#define SLIDER_MAX_DEPART_COUNT    50 

// 边界的宽度----只能是偶数!!
#define EDGE_RANGE          0 

// 外部最大级数（从1算起）     
#define LEVEL_OUTSIDE       255

// 每一(外部)级别所占的(内部)点数(不包含间隙) 
#define LEVEL_LENGTH        1 

// Differ值下拉的值
#define SUB_DATA            20 

//按滑条顺序配置通道序号
uchar code SLIDER_SENSOR_ARRAY[SLIDER_SENSOR_NUMBER] = {3, 6, 5, 4, 1, 2};

void Slider_EventLoop()
{   
    uint  lastPoint, thisPoint;
    uchar thisLvl;       
    uchar i, departCnt = 0, changeCnt = 0;  
    bit   isNewTouch = 1;               
    ulong sumOfMulData;
    uint  sumOfData;
    int   tempI;
    uint  pointSum = 0;
    uchar pointSumAddCount = 0;
	uchar j = 0;
    
    while (1) 
	{
        if(aCycleScanDone)
		{
			WDT_CTRL = 7;
			aCycleScanDone = 0;
	        departCnt++;
	        sumOfMulData = 0;
	        sumOfData = 0;
	        for (i = 0; i < SLIDER_SENSOR_NUMBER; i++) 
			{
	            j = SLIDER_SENSOR_ARRAY[i];
				tempI = (baseline[j] - rawData[j]);
	            if (tempI > 50) 
				{
	                departCnt = 0;
	            }
	            if (tempI < SUB_DATA) 
				{
	                tempI = 0;
	            }
	            switch (i) 
				{                
	                case 3:
	                    tempI *= 15;
	                    break;
	                case 4:
	                    tempI *= 10;
	                    break;
	                case 5:
	                    tempI *= 10;
	                    break;
	                case 6:
	                    tempI *= 15;
	                    break;
	                default:
	                    break;
	            }
	            if (tempI != 0) 
				{
	                sumOfData += tempI;
	                sumOfMulData += ((ulong)tempI * i);
	            }
	        }
	        if (departCnt == 0) 
			{           
	            sumOfMulData = sumOfMulData * (ulong)MULTI_FACTOR;
	
	            if(sumOfData != 0) 
				{
	                sumOfData = (((sumOfMulData / sumOfData) + 50) / 100);
	                thisPoint = sumOfData;
	                if (isNewTouch) 
					{
	                    lastPoint = thisPoint;
	                    thisLvl = thisPoint / (uchar)DIV_FACTOR;
	                    isNewTouch = 0;
	                }
	                else 
					{ 
	                    pointSum += thisPoint;
	                    pointSumAddCount++;
	                    if (pointSumAddCount == 8) 
						{
	                        pointSum >>= 3;
	                        lastPoint = pointSum;
	                        pointSumAddCount = 0;
	                        pointSum = 0;   
							thisLvl = (lastPoint / (uchar)DIV_FACTOR);
	                    }
	                }
	            }
	        }
	        else 
			{
	            if ((departCnt > SLIDER_MAX_DEPART_COUNT) ) 
				{
	                    return;
	            }
	        }
		}
    }   
}
#endif