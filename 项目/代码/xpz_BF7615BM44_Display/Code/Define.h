#ifndef _DEFINE_H_
#define _DEFINE_H_


// ����ͨ�����ͱ���
#define  	uchar 	unsigned char
#define 	uint8	unsigned char
#define 	uint16	unsigned int
#define 	uint32	unsigned long

#define 	int8	signed char
#define 	int16	signed int


// ���峣�ú�
#define SET 		1
#define CLE 		0

#define OPEN 		1
#define CLOSE 		0

#define DOOR_OPEN 	1
#define DOOR_CLOSE 	0


// �����ֽڽṹ��
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


// ����������
#define SET_ERR(x,y) (x) |= (y)
#define GET_ERR(x,y) (x) & (y)
#define CLR_ERR(x,y) (x) &= (~y)

/*����λ������*/
#define SET_BIT(x,y)  x|=(1<<y)											//ָ����ĳһλ����1
#define CLR_BIT(x,y)  x&=~(1<<y)										//ָ����ĳһλ����0
#define REVERSE_BIT(x,y) x^=(1<<y)										//ָ����ĳһλ��ȡ��
#define GET_BIT(x,y) ((x) >> (y)&1)										//��ȡ��ĳһλ��ֵ

/*������ֵ��*/

//�����ֵ����Сֵ
#define  MAX(x,y) (((x)>(y)) ? (x) : (y))
#define  MIN(x,y) (((x) < (y)) ? (x) : (y))

/*����ṹ���Աƫ�����ʹ�С��*/

#define FPOS(type,field) ((uint32)&((type *)0)->field)					//�õ�һ��field�ڽṹ��(struct)�е�ƫ����
#define FSIZ(type,field) sizeof(((type *)0)->field)						//�õ�һ���ṹ����field��ռ�õ��ֽ���

/*����ߵ�λ������*/

//�õ�һ���ֵĸ�λ�͵�λ�ֽ�
#define UINT16_LO(xxx)  ((uint8) ((uint16)(xxx) & 255))
#define UINT16_HI(xxx)  ((uint8) ((uint16)(xxx) >> 8))

/*�����Сдת����*/

#define UPCASE(c) (((c)>='a' && (c) <= 'z') ? ((c) �C 0��20) : (c)) 		//��һ����ĸת��Ϊ��д

/*���������С��*/

#define ARR_SIZE(a)  (sizeof((a))/sizeof((a[0])))						//��������Ԫ�صĸ���


// ��������ʱ���ȡ��
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


