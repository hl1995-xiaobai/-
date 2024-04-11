#ifndef __BF7615BMXX_XXXX_CTK_H__
#define __BF7615BMXX_XXXX_CTK_H__

#define CTK_START 				{CSD_START &= ~0X01;CSD_START |= 0X01;}//CTKģ�鿪��
#define CTK_STOP 					(CSD_START &= ~0X01)//CTKģ��ֹͣ
#define CTK_PULL_I_SET(x) {PULL_I_SEL = x;SNS_SCAN_CFG2 &= (~0x80);SNS_SCAN_CFG2 |= ((0x100&x)>>1);}//��������Դ����//2020-07-20
#define CTK_PRS_SW_SET(x) {SNS_SCAN_CFG1 &= ~(0x40);SNS_SCAN_CFG1 |= (0x40&(((unsigned char)x)<<6));}//ǰ�˳�ŵ翪��,1Ϊ�أ�0Ϊ��
#define CTK_LP_EN_SET(x)		{SYS_CLK_CFG &= ~(0x20);SYS_CLK_CFG |= (0x20&(((unsigned char)x)<<5));}//1��CTKģ���Ƶ��;0��CTKģ������ģʽ
#define CTK_PRS_SET(x) 			{SNS_SCAN_CFG1 &= ~(0x3F);SNS_SCAN_CFG1 |= (0x3F&(x<<0));}
//CSD_LP_EN = 0�PRS(��ŵ�Ƶ��) = 96/2/(x+8)��x = 61ʱ��PRS(��ŵ�Ƶ��) = 400K��x =  62/63��PRS(��ŵ�Ƶ��) = (1~1.5~3)MHz��
//CSD_LP_EN = 1�PRS(��ŵ�Ƶ��) = 24/2/(x+2);
#define CTK_PAR_SET(x) 				{SNS_SCAN_CFG2 &= ~(0x40);SNS_SCAN_CFG2 |= (0x40&(x<<6));}//1:Ϊ��ͨ������ģʽ��0��Ϊ��ͨ��ģʽ//2020-07-20
#define CTK_ADDR_SET(x) 			{SNS_SCAN_CFG2 &= ~(0x3F);SNS_SCAN_CFG2 |= (0x3F&(x<<0));}//����ͨ����ַ0~11,16~47//2020-07-20
#define CTK_RESO_SET(x) 			{SNS_SCAN_CFG3 &= ~(0x70);SNS_SCAN_CFG3 |= (0x70&(x<<4));}//0~7 CTK����ɨ��ֱ��ʣ�������λ����(CFG_CTK_RESOLUTION+9)λ��
#define CTK_DS_SET(x) 				{SNS_SCAN_CFG3 &= ~(0x0C);SNS_SCAN_CFG3 |= (0x0C&(x<<2));}//����ٶ�0:24MHz,1:12MHz,2:6MHz,3:4MHz
#define CTK_PRE_CH_SET(x) 		{SNS_SCAN_CFG3 &= ~(0x02);SNS_SCAN_CFG3 |= (0x02&(x<<1));}//Ԥ���ʱ�䣺0Ϊ20us,1Ϊ40us
#define CTK_PRE_DISCH_SET(x) 	{SNS_SCAN_CFG3 &= ~(0x01);SNS_SCAN_CFG3 |= (0x01&(x<<0));}//Ԥ�ŵ�ʱ�䣺0Ϊ2us,1Ϊ10us

#define CTK_PD_SET(x) 				{REG_ADDR = 0x2D;REG_DATA &= ~0x02;REG_DATA |= (0x02&(x<<1));}//0ΪCTK����1ΪCTK��
#define CTK_RB_SET(x) 				{REG_ADDR = 0x2B;REG_DATA &= (~0x38);REG_DATA |= (0x38&(x<<3));}//ѡ��RB�����С0:20K,1:40K,2:60K,3:80K,4:150K,5:200K,6:250K,7:300K��
#define CTK_VTH_SET(x) 				{REG_ADDR = 0x2B;REG_DATA &= (~0x07);REG_DATA |= (0x07&(x<<0));}//0~7 �ο���ѹ(0:1.9V),(1:2.1V),(2:2.5V),(3:2.8V),(4:3.2V),(5:3.5V),(6:3.9V),(7:4.2V);
#define CTK_INT_FLAG_CLR IRCON1 &= ~0X20//���CTK�жϱ�־λ

#define CTK_IE_SET IEN1 |= 0X20//��CTK�ж�ʹ��
#define CTK_IE_CLR IEN1 &= ~0X20//��CTK�ж�ʹ

#define CTK_IP_SET IPL1 |= 0X20//����CTK�ж��ż�Ϊ��
#define CTK_IP_CLR IPL1 &= ~0X20//����CTK�ж��ż�Ϊ��


extern unsigned int  xdata raw_data[];
extern unsigned int  xdata base_line[];

#if SNS_NUM

extern unsigned char xdata sensor_open[];				//0~31	
extern unsigned char xdata Mode;								//0Ϊ��ͨ��ģʽ��1Ϊ��ͨ������ģʽ
extern unsigned int  xdata pull_i_value[];//����Դ����;

#if (CS_SW == 1)
extern	uint cs_noise;
#endif

extern bit adjust_done_flag;
extern bit ctk_circle_done;//0Ϊctkɨ���У�1Ϊɨ��һ�����
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
extern unsigned char  xdata water_flow_key_count;//��ˮ����
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
//�������ƣ� void Base_Line_Init()
//�������ܣ� ���߳�ʼ��
//��������� ��
//��������� ��
//�� �� ֵ�� ��
//-----------------------------------------------------------------//
extern void Base_Line_Init();


//-----------------------------------------------------------------//
//�������ƣ� void CTK_BF7615BMXX_XXXX_Get_KEYS_Touch(unsigned char sns)
//�������ܣ� ��ȡ������־��������ʱ���
//��������� unsigned char sns:��Ӧ��Sensorͨ��
//��������� ��
//�� �� ֵ�� ��
//-----------------------------------------------------------------//
extern void CTK_BF7615BMXX_XXXX_Get_KEYS_Touch(unsigned char sns);

//-----------------------------------------------------------------//
//�������ƣ� void CTK_SNS_Renovate(unsigned char addr,unsigned int fth)
//�������ܣ� SNS���߸���
//��������� unsigned char addr��SNSͨ��;unsigned int fth:��ָ��ֵ
//��������� ��
//�� �� ֵ�� ��
//-----------------------------------------------------------------//
extern void CTK_SNS_Renovate(unsigned char addr,unsigned int fth);

//-----------------------------------------------------------------//
//�������ƣ� void CTK_BF7615BMXX_XXXX_Set_Para(int i_rank)
//�������ܣ� ��������ͨ������
//��������� 
//unsigned int i_rank:����Դ����;
//��������� ��
//�� �� ֵ�� ��
//-----------------------------------------------------------------//   
extern void CTK_BF7615BMXX_XXXX_Set_Para(unsigned int i_rank);



//-----------------------------------------------------------------//
//�������ƣ� void CTK_Set_Para(void)
//�������ܣ� ����CTKɨ����������߸��²���
//��������� ��
//��������� ��
//�� �� ֵ�� ��
//-----------------------------------------------------------------//
extern void CTK_Set_Para(void);

#endif

#endif