#ifndef _DEFINE_H_
#define _DEFINE_H_


// 定义通用类型别名
#define  	uchar 	unsigned char
#define 	uint8	unsigned char
#define 	uint16	unsigned int
#define 	uint32	unsigned long

#define 	int8	signed char
#define 	int16	signed int


// 定义常用宏
#define SET 		1
#define CLE 		0

#define OPEN 		1
#define CLOSE 		0

#define DOOR_OPEN 	1
#define DOOR_CLOSE 	0


// 定义字节结构体
typedef union
{
	uint8 byte;
	struct
	{	uint8	BIT0	: 1;
		uint8	BIT1	: 1;
		uint8	BIT2	: 1;
		uint8	BIT3	: 1;
		uint8	BIT4	: 1;
		uint8	BIT5	: 1;
		uint8	BIT6	: 1;
		uint8	BIT7	: 1;
	}BITS;
}Byte;

//typedef enum{ TRUE = 1, FALSE = 0 }BOOL;


// 定义错误处理宏
#define SET_ERR(x,y) (x) |= (y)
#define GET_ERR(x,y) (x) & (y)
#define CLR_ERR(x,y) (x) &= (~y)

/*定义位操作宏*/
#define SET_BIT(x,y)  x|=(1<<y)											//指定的某一位数置1
#define CLR_BIT(x,y)  x&=~(1<<y)										//指定的某一位数置0
#define REVERSE_BIT(x,y) x^=(1<<y)										//指定的某一位数取反
#define GET_BIT(x,y) ((x) >> (y)&1)										//获取的某一位的值

/*定义最值宏*/

//求最大值和最小值
#define  MAX(x,y) (((x)>(y)) ? (x) : (y))
#define  MIN(x,y) (((x) < (y)) ? (x) : (y))

/*定义结构体成员偏移量和大小宏*/

#define FPOS(type,field) ((uint32)&((type *)0)->field)					//得到一个field在结构体(struct)中的偏移量
#define FSIZ(type,field) sizeof(((type *)0)->field)						//得到一个结构体中field所占用的字节数

/*定义高低位操作宏*/

//得到一个字的高位和低位字节
#define UINT16_LO(xxx)  ((uint8) ((uint16)(xxx) & 255))
#define UINT16_HI(xxx)  ((uint8) ((uint16)(xxx) >> 8))

/*定义大小写转换宏*/

#define UPCASE(c) (((c)>='a' && (c) <= 'z') ? ((c) – 0×20) : (c)) 		//将一个字母转换为大写

/*定义数组大小宏*/

#define ARR_SIZE(a)  (sizeof((a))/sizeof((a[0])))						//返回数组元素的个数


// 定义日期时间获取宏
#define YEAR ((((__DATE__ [7] - '0') * 10 + (__DATE__ [8] - '0')) * 10 + (__DATE__ [9] - '0')) * 10 + (__DATE__ [10] - '0'))

#define MONTH (__DATE__ [2] == 'n' ? (__DATE__ [1] == 'a' ? 1 : 6) \
    : __DATE__ [2] == 'b' ? 2 \
    : __DATE__ [2] == 'r' ? (__DATE__ [0] == 'M' ? 3 : 4) \
    : __DATE__ [2] == 'y' ? 5 \
    : __DATE__ [2] == 'l' ? 7 \
    : __DATE__ [2] == 'g' ? 8 \
    : __DATE__ [2] == 'p' ? 9 \
    : __DATE__ [2] == 't' ? 10 \
    : __DATE__ [2] == 'v' ? 11 : 12)

#define DAY ((__DATE__ [4] == ' ' ? 0 : __DATE__ [4] - '0') * 10 + (__DATE__ [5] - '0'))

#endif


