#ifndef __BF7615BMXX_XXXX_CTK_H__
#define __BF7615BMXX_XXXX_CTK_H__

#define CTK_START 				{CSD_START &= ~0X01;CSD_START |= 0X01;}//CTK模块开启
#define CTK_STOP 					(CSD_START &= ~0X01)//CTK模块停止
#define CTK_PULL_I_SET(x) {PULL_I_SEL = x;SNS_SCAN_CFG2 &= (~0x80);SNS_SCAN_CFG2 |= ((0x100&x)>>1);}//上拉电流源设置//2020-07-20
#define CTK_PRS_SW_SET(x) {SNS_SCAN_CFG1 &= ~(0x40);SNS_SCAN_CFG1 |= (0x40&(((unsigned char)x)<<6));}//前端充放电开关,1为关，0为开
#define CTK_LP_EN_SET(x)		{SYS_CLK_CFG &= ~(0x20);SYS_CLK_CFG |= (0x20&(((unsigned char)x)<<5));}//1：CTK模块低频率;0：CTK模块正常模式
#define CTK_PRS_SET(x) 			{SNS_SCAN_CFG1 &= ~(0x3F);SNS_SCAN_CFG1 |= (0x3F&(x<<0));}
//CSD_LP_EN = 0RS(充放电频率) = 96/2/(x+8)；x = 61时，PRS(充放电频率) = 400K；x =  62/63，PRS(充放电频率) = (1~1.5~3)MHz。
//CSD_LP_EN = 1RS(充放电频率) = 24/2/(x+2);
#define CTK_PAR_SET(x) 				{SNS_SCAN_CFG2 &= ~(0x40);SNS_SCAN_CFG2 |= (0x40&(x<<6));}//1:为多通道并联模式；0：为单通道模式//2020-07-20
#define CTK_ADDR_SET(x) 			{SNS_SCAN_CFG2 &= ~(0x3F);SNS_SCAN_CFG2 |= (0x3F&(x<<0));}//设置通道地址0~11,16~47//2020-07-20
#define CTK_RESO_SET(x) 			{SNS_SCAN_CFG3 &= ~(0x70);SNS_SCAN_CFG3 |= (0x70&(x<<4));}//0~7 CTK电容扫描分辨率，计数器位数：(CFG_CTK_RESOLUTION+9)位。
#define CTK_DS_SET(x) 				{SNS_SCAN_CFG3 &= ~(0x0C);SNS_SCAN_CFG3 |= (0x0C&(x<<2));}//检测速度0:24MHz,1:12MHz,2:6MHz,3:4MHz
#define CTK_PRE_CH_SET(x) 		{SNS_SCAN_CFG3 &= ~(0x02);SNS_SCAN_CFG3 |= (0x02&(x<<1));}//预充电时间：0为20us,1为40us
#define CTK_PRE_DISCH_SET(x) 	{SNS_SCAN_CFG3 &= ~(0x01);SNS_SCAN_CFG3 |= (0x01&(x<<0));}//预放电时间：0为2us,1为10us

#define CTK_PD_SET(x) 				{REG_ADDR = 0x2D;REG_DATA &= ~0x02;REG_DATA |= (0x02&(x<<1));}//0为CTK开，1为CTK关
#define CTK_RB_SET(x) 				{REG_ADDR = 0x2B;REG_DATA &= (~0x38);REG_DATA |= (0x38&(x<<3));}//选择RB电阻大小0:20K,1:40K,2:60K,3:80K,4:150K,5:200K,6:250K,7:300K。
#define CTK_VTH_SET(x) 				{REG_ADDR = 0x2B;REG_DATA &= (~0x07);REG_DATA |= (0x07&(x<<0));}//0~7 参考电压(0:1.9V),(1:2.1V),(2:2.5V),(3:2.8V),(4:3.2V),(5:3.5V),(6:3.9V),(7:4.2V);
#define CTK_INT_FLAG_CLR IRCON1 &= ~0X20//清除CTK中断标志位

#define CTK_IE_SET IEN1 |= 0X20//开CTK中断使能
#define CTK_IE_CLR IEN1 &= ~0X20//关CTK中断使

#define CTK_IP_SET IPL1 |= 0X20//设置CTK中断优级为高
#define CTK_IP_CLR IPL1 &= ~0X20//设置CTK中断优级为低


extern unsigned int  xdata raw_data[];
extern unsigned int  xdata base_line[];

#if SNS_NUM

extern unsigned char xdata sensor_open[];				//0~31	
extern unsigned char xdata Mode;								//0为单通道模式，1为多通道并联模式
extern unsigned int  xdata pull_i_value[];//电流源级数;

#if (CS_SW == 1)
extern	uint cs_noise;
#endif

extern bit adjust_done_flag;
extern bit ctk_circle_done;//0为ctk扫描中，1为扫描一轮完成
extern bit ctk_start_flag;

extern unsigned int xdata pull_i_value_parallel;

extern unsigned long xdata open_sns_l;
extern unsigned long xdata open_sns_h;
extern unsigned long xdata adjust_flag;
extern unsigned char xdata parallel_mode;
extern bit parallel_init_flag;
extern bit ctk_para_done;
extern unsigned int  xdata ctk_soft_reset_count;



extern unsigned int  xdata n_base_line[];
extern unsigned char xdata n_base_line_reno_count[];
extern unsigned char xdata touch_confirm_count[];
	
extern unsigned long xdata keys_flag_l;	
extern unsigned long xdata keys_flag_h;	
extern unsigned long xdata mode_flag_l;
extern unsigned long xdata mode_flag_h;
extern unsigned long xdata sensor_flag_l;
extern unsigned long xdata sensor_flag_h;
extern unsigned long xdata muli_key_flag_l;
extern unsigned long xdata muli_key_flag_h;

extern unsigned char xdata touch_left_count[];	
extern unsigned int  xdata long_key_clear_count;

extern unsigned char  xdata over_p_noise_count[];
extern unsigned char  xdata under_p_noise_count[];
extern unsigned char  xdata over_n_noise_count[];
extern unsigned char  xdata under_n_noise_count[];

#if (RENOVATE_MODE == 1)
extern bit water_flow_flag;	
extern unsigned int 	xdata water_flow_left_count;	
extern unsigned char  xdata water_flow_key_count;//溢水计数
extern unsigned char  xdata water_flow_key_reset_cnt;
#endif
extern unsigned char 	xdata multi_key_count;
extern unsigned char  xdata multi_key_reset_cnt;

#if UN_NORMAL_CHECK
extern unsigned char xdata un_normal_count;
extern unsigned char xdata un_normal_recover_count;
extern bit un_normal_flag;
extern unsigned long xdata adjust_flag;
#endif

//-----------------------------------------------------------------//
//函数名称： void Base_Line_Init()
//函数功能： 基线初始化
//输入参数： 无
//输出参数： 无
//返 回 值： 无
//-----------------------------------------------------------------//
extern void Base_Line_Init();


//-----------------------------------------------------------------//
//函数名称： void CTK_BF7615BMXX_XXXX_Get_KEYS_Touch(unsigned char sns)
//函数功能： 获取按键标志，长按超时清除
//输入参数： unsigned char sns:对应的Sensor通道
//输出参数： 无
//返 回 值： 无
//-----------------------------------------------------------------//
extern void CTK_BF7615BMXX_XXXX_Get_KEYS_Touch(unsigned char sns);

//-----------------------------------------------------------------//
//函数名称： void CTK_SNS_Renovate(unsigned char addr,unsigned int fth)
//函数功能： SNS基线更新
//输入参数： unsigned char addr：SNS通道;unsigned int fth:手指阈值
//输出参数： 无
//返 回 值： 无
//-----------------------------------------------------------------//
extern void CTK_SNS_Renovate(unsigned char addr,unsigned int fth);

//-----------------------------------------------------------------//
//函数名称： void CTK_BF7615BMXX_XXXX_Set_Para(int i_rank)
//函数功能： 配置所有通道参数
//输入参数： 
//unsigned int i_rank:电流源级数;
//输出参数： 无
//返 回 值： 无
//-----------------------------------------------------------------//   
extern void CTK_BF7615BMXX_XXXX_Set_Para(unsigned int i_rank);



//-----------------------------------------------------------------//
//函数名称： void CTK_Set_Para(void)
//函数功能： 设置CTK扫描参数及基线更新参数
//输入参数： 无
//输出参数： 无
//返 回 值： 无
//-----------------------------------------------------------------//
extern void CTK_Set_Para(void);

#endif

#endif