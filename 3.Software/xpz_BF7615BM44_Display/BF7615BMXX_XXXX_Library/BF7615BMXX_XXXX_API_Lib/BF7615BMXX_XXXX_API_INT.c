#include ".\BF7615BMXX_XXXX_Library\Config.h"

//-----------------------------------------------------------------//
//�������ƣ� void ExtInt0_Init(uchar TriggerMode,uchar int0_sel)
//�������ܣ� �ⲿ�ж�0��ʼ��
//���������
//�ⲿ�ж�0������ʽѡ��uchar TriggerMode
//			 TriggerMode = 0��������ʽΪ˫���ش���
//			 TriggerMode = 1��������ʽΪ�½��ش���
//			 TriggerMode = 2��������ʽΪ�Ͻ��ش���
//			 uchar int0_sel,	��Ӧ��λΪ1ѡ��ΪINT���ܣ�Ϊ0ѡ��ΪIO�ڹ���
//��������� ��
//�� �� ֵ�� ��
//-----------------------------------------------------------------// 
#if ExtInt0_EN
#pragma message "���룬void ExtInt0_Init(uchar TriggerMode,uchar int0_sel)����"
void ExtInt0_Init(uchar TriggerMode,uint int0_sel)
{
	EA = 0;//�����жϣ�
	INT0_IP_SET;//����IN0�ж��ż�Ϊ��	������ʵ��Ӧ���������ȼ�
	INT0_INT_FLAG_CLR;//���INT0�жϱ�־
	EXINT_STAT = 0;//���INT0_0x�жϱ�־
	
	REG_ADDR = 0x35;
	REG_DATA |= int0_sel;//��ӦλΪ0ѡ��ΪIO�ڹ��ܣ�1ѡ��ΪINT�жϹ���
	TRISH |= (uchar)int0_sel;//����Ϊ����
	DATAH |= (uchar)int0_sel;//��������Ϊ��
	INT0_POLO_SET(TriggerMode);//0Ϊ˫�ش�����1Ϊ�½��ش�����2Ϊ�����ش�����
	
	REG_ADDR = 0x34;
	REG_DATA |= (int0_sel>>8)&0x01;//��ӦλΪ0ѡ��ΪIO�ڹ��ܣ�1ѡ��ΪINT�жϹ���
	TRISB |= ((int0_sel >> 8)&0x01);//����Ϊ����
	DATAB |= ((int0_sel >> 8)&0x01);//��������Ϊ��
	
	INT0_08_INT_FLAG_CLR;//���INT0_08�жϱ�־
	INT0_08_POLO_SET(TriggerMode);//0Ϊ˫�ش�����1Ϊ�½��ش�����2Ϊ�����ش�����
	
	REG_ADDR = 0x00;
	INT0_IE_SET;//ʹ���ⲿINT0�ж� 
	EA = 1;//�����ж�	
}
//-----------------------------------------------------------------//
//�������ƣ� void Ext0_ISR() interrupt 0
//�������ܣ� �ⲿ�ж�0�ж��Ӻ���
//��������� ��
//��������� ��
//�� �� ֵ�� ��
//-----------------------------------------------------------------// 
void Ext0_ISR() interrupt 0 
{
	static uchar xdata addr_bak = 0;
	PUSH_REG_ADDR_SFR();
	INT0_INT_FLAG_CLR;//���INT0�жϱ�־
	
	if(GET_INT0_FLAG(0))
	{
		INT0_00_INT_FLAG_CLR;//���INT0_00�жϱ�־
	}
	
	/*********INT0_0x**********/
	if(GET_INT0_FLAG(1))
	{
		INT0_01_INT_FLAG_CLR;
	}

	if(GET_INT0_FLAG(2))
	{
				
		INT0_02_INT_FLAG_CLR;
		
	}
	if(GET_INT0_FLAG(3))
	{
		INT0_03_INT_FLAG_CLR;
		
	}
	if(GET_INT0_FLAG(4))
	{
		INT0_04_INT_FLAG_CLR;
		
	}
	if(GET_INT0_FLAG(5))
	{
		INT0_05_INT_FLAG_CLR;
			
	}
	if(GET_INT0_FLAG(6))
	{
		INT0_06_INT_FLAG_CLR;
		
	}
	if(GET_INT0_FLAG(7))
	{
		INT0_07_INT_FLAG_CLR;
		
	}
	
	
	if(GET_INT0_08_FLAG())
	{
		INT0_08_INT_FLAG_CLR;//���INT0_08�жϱ�־
		
	}			
	POP_REG_ADDR_SFR();
	/*********INT0_0x**********/

} 
#endif

//-----------------------------------------------------------------//
//�������ƣ� void ExtInt1_Init(uchar TriggerMode)
//�������ܣ� �ⲿ�ж�1��ʼ��
//��������� 
//�ⲿ�ж�1������ʽѡ��uchar TriggerMode
//			 TriggerMode = 0��������ʽΪ˫���ش���
//			 TriggerMode = 1��������ʽΪ�½��ش���
//			 TriggerMode = 2��������ʽΪ�Ͻ��ش���

//��������� ��
//�� �� ֵ�� ��
//-----------------------------------------------------------------// 
#if ExtInt1_EN
#pragma message "���룬void ExtInt1_Init(uchar TriggerMode)����"
void ExtInt1_Init(uchar TriggerMode)
{
	EA = 0;//�����жϣ�
	INT1_IP_SET;//����IN1�ж��ż�Ϊ��	������ʵ��Ӧ���������ȼ�
	INT1_INT_FLAG_CLR;//���INT1�жϱ�־
	INT1_FUN_SET(1);//0ѡ��ΪIO�ڹ��ܣ�1ѡ��ΪINT�жϹ���
	INT1_POLO_SET(TriggerMode);//0Ϊ˫�ش�����1Ϊ�½��ش�����2Ϊ�����ش�����
	REG_ADDR = 0x00;
	INT1_IE_SET;//ʹ���ⲿINT1�ж� 
	EA = 1;//�����ж�		
}
//-----------------------------------------------------------------//
//�������ƣ� void Ext1_ISR() interrupt 2
//�������ܣ� �ⲿ�ж�1�ж��Ӻ���
//��������� ��
//��������� ��
//�� �� ֵ�� ��
//-----------------------------------------------------------------// 
void Ext1_ISR() interrupt 2 
{
	static uchar xdata addr_bak = 0;
	PUSH_REG_ADDR_SFR();
	INT1_INT_FLAG_CLR;//���INT1�жϱ�־
	POP_REG_ADDR_SFR();
}
#endif


//-----------------------------------------------------------------//
//�������ƣ� void ExtInt2_Init(uchar TriggerMode)
//�������ܣ� �ⲿ�ж�2��ʼ��
//��������� 
//�ⲿ�ж�1������ʽѡ��uchar TriggerMode
//			 TriggerMode = 0��������ʽΪ�½��ش���
//			 TriggerMode = 1��������ʽΪ�����ش���
//			 TriggerMode = 2��������ʽΪ˫���ش���
//��������� ��
//�� �� ֵ�� ��
//-----------------------------------------------------------------// 
#if ExtInt2_EN
#pragma message "���룬void ExtInt2_Init(uchar TriggerMode)����"
void ExtInt2_Init(uchar TriggerMode)
{
	EA = 0;//�����жϣ�
	INT2_IP_SET;//����IN1�ж��ż�Ϊ��	������ʵ��Ӧ���������ȼ�
	INT2_INT_FLAG_CLR;//���INT1�жϱ�־
	INT2_FUN_SET(1);//0ѡ��ΪIO�ڹ��ܣ�1ѡ��ΪINT�жϹ��� 

	INT2_POLO_SET(TriggerMode);//0Ϊ˫�ش�����1Ϊ�½��ش�����2Ϊ�����ش�����
	INT2_IE_SET;//ʹ���ⲿINT1�ж� 
	EA = 1;//�����ж�			
}
//-----------------------------------------------------------------//
//�������ƣ� void Ext2_ISR() interrupt 9
//�������ܣ� �ⲿ�ж�2�ж��Ӻ���
//��������� ��
//��������� ��
//�� �� ֵ�� ��
//-----------------------------------------------------------------// 
void Ext2_ISR() interrupt 9 
{
	static uchar xdata addr_bak = 0;
	PUSH_REG_ADDR_SFR();
	INT2_INT_FLAG_CLR;//���INT2�жϱ�־
	POP_REG_ADDR_SFR();	
}
#endif

//-----------------------------------------------------------------//
//�������ƣ� void ExtInt3_Init(uchar TriggerMode)
//�������ܣ� �ⲿ�ж�3��ʼ��
//��������� 
//�ⲿ�ж�1������ʽѡ��uchar TriggerMode
//			 TriggerMode = 0��������ʽΪ�½��ش���
//			 TriggerMode = 1��������ʽΪ�����ش���
//			 TriggerMode = 2��������ʽΪ˫���ش���
//��������� ��
//�� �� ֵ�� ��
//-----------------------------------------------------------------// 
#if ExtInt3_EN
#pragma message "���룬void ExtInt3_Init(uchar TriggerMode)����"
void ExtInt3_Init(uchar TriggerMode)
{
	EA = 0;//�����жϣ�
	INT3_IP_SET;//����IN1�ж��ż�Ϊ��	������ʵ��Ӧ���������ȼ�
	INT3_INT_FLAG_CLR;//���INT1�жϱ�־
	INT3_FUN_SET(1);//0ѡ��ΪIO�ڹ��ܣ�1ѡ��ΪINT�жϹ��� 
	INT3_POLO_SET(TriggerMode);//0Ϊ˫�ش�����1Ϊ�½��ش�����2Ϊ�����ش�����
	INT3_IE_SET;//ʹ���ⲿINT1�ж� 
	EA = 1;//�����ж�			
}
//-----------------------------------------------------------------//
//�������ƣ� void Ext3_ISR() interrupt 21
//�������ܣ� �ⲿ�ж�3�ж��Ӻ���
//��������� ��
//��������� ��
//�� �� ֵ�� ��
//-----------------------------------------------------------------// 
void Ext3_ISR() interrupt 21 
{
	static uchar xdata addr_bak = 0;
	PUSH_REG_ADDR_SFR();
	INT3_INT_FLAG_CLR;//���INT2�жϱ�־	
	POP_REG_ADDR_SFR();
}
#endif

//-----------------------------------------------------------------//
//�������ƣ� void ExtInt4_Init(uchar TriggerMode,ulong int4_sel)
//�������ܣ� �ⲿ�ж�4��ʼ��
//��������� 
//�ⲿ�ж�1������ʽѡ��uchar TriggerMode
//			 TriggerMode = 0��������ʽΪ�½��ش���
//			 TriggerMode = 1��������ʽΪ�����ش���
//			 ulong int4_sel:��Ӧ��λΪ1ʱ��ѡ��ΪINT���ܣ�Ϊ0ʱΪIO�ڹ���
//��������� ��
//�� �� ֵ�� ��
//-----------------------------------------------------------------// 
#if ExtInt4_EN
#pragma message "���룬void ExtInt4_Init(uchar TriggerMode,ulong int4_sel)����"
void ExtInt4_Init(uchar TriggerMode,ulong int4_sel)
{
	EA = 0;//�����жϣ�
	INT4_IP_SET;//����IN4�ж��ż�Ϊ��	������ʵ��Ӧ���������ȼ�
	INT4_INT_FLAG_CLR;//���INT4�жϱ�־
	
	REG_ADDR = 0x36;
	REG_DATA = (uchar)int4_sel;//PE4,��ӦλΪ0ѡ��ΪIO�ڹ��ܣ�1ѡ��ΪINT�жϹ���


	REG_ADDR = 0x37;
	REG_DATA = (uchar)(int4_sel>>8);//PE5~PE7,PF4,��ӦλΪ0ѡ��ΪIO�ڹ��ܣ�1ѡ��ΪINT�жϹ���
		
	REG_ADDR = 0x38;
	REG_DATA = (uchar)(int4_sel>>16);//PF5~PF7,PG0~PG3,��ӦλΪ0ѡ��ΪIO�ڹ��ܣ�1ѡ��ΪINT�жϹ���
	
	TRISE |= (0xF0 & ((uchar)(int4_sel >> 3)));//����Ϊ����
	DATAE |= (0xF0 & ((uchar)(int4_sel >> 3)));//��������Ϊ��
	
	TRISF |= (0xF0 & ((uchar)(int4_sel >> 11)));//����Ϊ����
	DATAF |= (0xF0 & ((uchar)(int4_sel >> 11)));//��������Ϊ��
	
	TRISG |= (0x0F & ((uchar)(int4_sel >> 19)));//����Ϊ����
	DATAG |= (0x0F & ((uchar)(int4_sel >> 19)));//��������Ϊ��
	
	INT4_POLO_SET(TriggerMode);//1Ϊ����������0Ϊ�½��ش�����

	INT4_IE_SET;//ʹ���ⲿINT1�ж� 
	EA = 1;//�����ж�			
}
//-----------------------------------------------------------------//
//�������ƣ� void Ext4_ISR() interrupt 22
//�������ܣ� �ⲿ�ж�4�ж��Ӻ���,ͨ����ȡ��ӦIO��DATAX�������ж�INT4XX���ж�������Դ
//��������� ��
//��������� ��
//�� �� ֵ�� ��
//-----------------------------------------------------------------// 
void Ext4_ISR() interrupt 22 
{
	static uchar xdata addr_bak = 0;
	PUSH_REG_ADDR_SFR();
	INT4_INT_FLAG_CLR;//���INT4�жϱ�־
	if((DATAE&0x40) == 0x00)//PE6�½���
	{

	}				
	else//PE6������
	{
		
	}
	
	if((DATAE&0x80)  == 0x00)//PE7�½���
	{

	}				
	else//PE7������
	{

	}
	
	if((DATAF&0x10)  == 0x00)//PF4�½���
	{
	
	}				
	else//PF4������
	{

	}
	if((DATAF&0x20)  == 0x00)//PF5�½���
	{
		
	}				
	else//PF5������
	{

	}
	if((DATAF&0x40)  == 0x00)//PF6�½���
	{
		
	}				
	else//PF6������
	{

	}
	if((DATAF&0x80)  == 0x00)//PF7�½���
	{
		
	}				
	else//PF7������
	{
			
	}
	POP_REG_ADDR_SFR();
}
#endif
