#include "IR.h"
#include ".\Application_Library\IR.h"
#include ".\Project\Project.h"

#if CHIP_BF6911AX

	#include ".\CTK_Library\BF6911AX\BF6911AX.H"
	#include ".\CTK_Library\BF6911AX\BF6911AX_CTK.H"
	#include ".\CTK_Library\BF6911AX\BF6911AX_SetTouchFlag.h"
	#include ".\CTK_Library\BF6911AX\BF6911AX_API.h"

	#if (TRACEMODE == TRUE)
		#include ".\CTK_Library\BF6911AX\BF6911AX_TraceMode.h"
	#endif

#endif


#if (IR_SEND_OR_REC == 1)
uint EndCnt =0;   									//������ʱ
uchar Last_key =0;									//���һ�ΰ���ֵ
uchar Timer0_cnt =0;   								//�����뷢�ͺ� ��ʼ����
bit First_Reaptcode =0; 							//��ʾ��һ��������
bit Start_Flag = 0;									//�������־
bit Repeat_Flag = 0;								//�������־

uchar Key_Value =0;									//����ֵ


void IR_Start();
void IRSend_Byte(uchar dat);
void IRSend_Opposite_Byte(uchar dat);
void IRSend_16Byte(uint dat);
void IR_EndPulse();
void IR_SendRepeat_Code();
void IRSend_code(uint custom,uchar dat);
void Signal_Carrier(uint count);

void IRSend_KeyValue(uint custom,uchar key_value);

/********************************************************/
//��������void Signal_Carrier(uint count)
//��  �ܣ��ز�38 Period-26us
//��  ����count: ��ʱ����
//����ֵ����
/*******************************************************/
#if (CARRIER_SWITCH == 1)
void Signal_Carrier(uint count)
{
	uint i;
	i = count; 
	while(i--)
	{ 

		IR = 1;
		_nop_();
		_nop_();
		_nop_();
		_nop_();
		_nop_();
		_nop_();
		_nop_();
		_nop_();
		_nop_();
		_nop_();

		_nop_();
		_nop_();
		_nop_();
		_nop_();
		_nop_();
		_nop_();
		_nop_();
		_nop_();
		_nop_();
		_nop_();

		_nop_();
		_nop_();
		_nop_();
		_nop_();
		_nop_();
		_nop_();
		_nop_();
		_nop_();
		_nop_();
		_nop_();

		_nop_();
		_nop_();
		_nop_();
		_nop_();
		_nop_();
		_nop_();
		_nop_();
		_nop_();
		_nop_();
		_nop_();

		_nop_();
		_nop_();
		_nop_();
		_nop_();
		_nop_();
		_nop_();
		_nop_();
		_nop_();
		_nop_();
		_nop_();//50

		IR = 0;
		_nop_();
		_nop_();
		_nop_();
		_nop_();
		_nop_();
		_nop_();
		_nop_();
		_nop_();
		_nop_();
		_nop_();

		_nop_();
		_nop_();
		_nop_();
		_nop_();
		_nop_();
		_nop_();
		_nop_();
		_nop_();
		_nop_();
		_nop_();

		_nop_();
		_nop_();
		_nop_();
		_nop_();
		_nop_();
		_nop_();
		_nop_();
		_nop_();
		_nop_();
		_nop_();

		_nop_();
		_nop_();
		_nop_();
		_nop_();
		_nop_();
		_nop_();
		_nop_();
		_nop_();
		_nop_();
		_nop_();

		_nop_();
		_nop_();
		_nop_();
		_nop_();
		_nop_();
		_nop_();
		_nop_();
		_nop_();
		_nop_();
		_nop_();

		_nop_();
		_nop_();
		_nop_();
		_nop_();
		_nop_();
		_nop_();
		_nop_();
		_nop_();
		_nop_();
		_nop_();

		_nop_();
		_nop_();
		_nop_();
		_nop_();
		_nop_();
		_nop_();
		_nop_();
		_nop_();
		_nop_();
		_nop_();

		_nop_();
		_nop_();
		_nop_();
		_nop_();
		_nop_();
		_nop_();
		_nop_();
		_nop_();
		_nop_();
		_nop_();

		_nop_();
		_nop_();
		_nop_();
		_nop_();
		_nop_();
		_nop_();
		_nop_();
		_nop_();
		_nop_();
		_nop_();//90
	}
}
#endif

/********************************************************/
//��������void delay_ms( BYTE time)
//��  �ܣ���ʱ����
//��  ����time: 1--1ms
//����ֵ����
/*******************************************************/
#if (CARRIER_SWITCH == 0)
void delay_ms( BYTE time)
{
    unsigned char a,b,c;
    for(c=time;c>0;c--)
      for(b=120;b>0;b--)
            for(a=15;a>0;a--);
}
#endif
/********************************************************/
//��������void IR_Start()
//��  �ܣ�����������
//��  ������
//����ֵ����
/*******************************************************/
void IR_Start()
{
   	SET_IR_TX;        					//����ʱ�������
	SET_IR;

#if (CARRIER_SWITCH == 1)
	Signal_Carrier(CARRIER_DELAY_9MS);	//9ms
#endif

#if (CARRIER_SWITCH == 0)
	delay_ms(9);	 					//����9ms��
#endif

	CLR_IR;
	EndCnt =2030;
	do{;}while(--EndCnt);	
}

/********************************************************/
//��������void IRSend_Byte(uchar dat)
//��  �ܣ���������
//��  ����data����
//����ֵ����
/*******************************************************/
void IRSend_Byte(uchar dat)
{

	uchar Send_Data =0;
	uchar Symble =0x01;
	uchar i =0;
	Send_Data =dat;
	for(i=0;i<8;i++)
	{	
	   	SET_IR;
#if (CARRIER_SWITCH == 1)
		Signal_Carrier(CARRIER_DELAY_560US);//0.56ms
#endif

#if (CARRIER_SWITCH == 0)
		EndCnt =261;
		do{;}while(--EndCnt);
#endif
		CLR_IR;
		if(Send_Data & Symble)
		{
			EndCnt =783;	    	//����λΪ1���1.68MS LOW
			do{;}while(--EndCnt);
		}
		else
		{
			EndCnt =261;			//����λ��0���0.56ms HIGH
			do{;}while(--EndCnt);
		}
		Symble <<=1;
	}	
}

/********************************************************/
//��������void IRSend_Opposite_Byte(uchar dat)
//��  �ܣ��������ݷ���
//��  ����data����
//����ֵ����
/*******************************************************/
void IRSend_Opposite_Byte(uchar dat)
{
	uchar Send_Data =0;
	uchar Symble =0x01;
	uchar i =0;
	Send_Data =dat;
	for(i=0;i<8;i++)
	{
		SET_IR;
#if (CARRIER_SWITCH == 1)
		Signal_Carrier(CARRIER_DELAY_560US);//0.56ms
#endif

#if (CARRIER_SWITCH == 0)
		EndCnt =261;
		do{;}while(--EndCnt);
#endif
		CLR_IR;
		if(Send_Data & Symble)
		{
			EndCnt =261;
			do{;}while(--EndCnt);	
		}
		else
		{
			 EndCnt =783;
			do{;}while(--EndCnt);
		}
		Symble <<=1;
	}
}

/********************************************************/
//��������void IRSend_16Byte(uint dat)
//��  �ܣ�����16λ����
//��  ����data����
//����ֵ����
/*******************************************************/
void IRSend_16Byte(uint dat)
{
	uchar High_data,Low_data;
	High_data =dat>>8;
	IRSend_Byte(High_data);
	Low_data =dat;
	IRSend_Byte(Low_data);
}

/********************************************************/
//��������void IRSend_code(uint custom,uchar dat)
//��  �ܣ�����������
//��  ����custom:�û���;data����
//����ֵ����
/*******************************************************/
void IRSend_code(uint custom,uchar dat)
{
	 IRSend_16Byte(custom);
	 IRSend_Byte(dat);
	 IRSend_Opposite_Byte(dat);
}

/********************************************************/
//��������void IR_EndPulse(void)
//��  �ܣ�������
//��  ������
//����ֵ����
/*******************************************************/
void IR_EndPulse(void)
{
	SET_IR;
#if (CARRIER_SWITCH == 1)
	Signal_Carrier(CARRIER_DELAY_560US);//0.56ms
#endif

#if (CARRIER_SWITCH == 0)
	EndCnt =261;
	do{;}while(--EndCnt);
#endif
	CLR_IR;
	SET_IR_RX;	 //����ʱ����IR�����Ϊ����
}

/********************************************************/
//��������void IR_SendRepeat_Code(void)
//��  �ܣ�����������
//��  ������
//����ֵ����
/*******************************************************/
void IR_SendRepeat_Code()
{
	SET_IR_TX;           					//����Ϊ���
	SET_IR;

#if (CARRIER_SWITCH == 1)
	Signal_Carrier(CARRIER_DELAY_9MS);	//9ms
#endif

#if (CARRIER_SWITCH == 0)
	delay_ms(9);
#endif

	CLR_IR;			 
	EndCnt =975;			 			//2.25MS
	do{;}while(--EndCnt);
}

/********************************************************/
//��������void IRSend_KeyValue(uint custom,uchar key_value)
//��  �ܣ�IR���Ͱ���ֵ
//��  ����custom:�û���;key_value:����ֵ
//����ֵ����
/*******************************************************/
void IRSend_KeyValue(uint custom,uchar key_value)
{
	if(Last_key !=key_value)
	{
		EA =0;
		IR_Start();
		IRSend_code(custom,key_value);
		IR_EndPulse();
		EA =1;
		Last_key = key_value;
		TR0 =1;
		Timer0_cnt =0;
	}//��Լ70ms����
	else if(First_Reaptcode == 0)
	{	 	
		 if(Timer0_cnt >= 8)
		 {	
			EA =0;
			IR_SendRepeat_Code();
			IR_EndPulse();
			First_Reaptcode = 1;
			Timer0_cnt =0;
			EA =1;
		}
	}//��ʱ40ms�����׸�������
	else if(Timer0_cnt > 16)
	{
		EA =0; 
		IR_SendRepeat_Code();
		IR_EndPulse();
		Timer0_cnt =0;
		EA =1;
	}//��������������
}


///////////////////////////////////////////////////////////////////////////////////////////////////


/****************************��NEC_IR**********************************/

/********************************************************/
//��������void IRSend_7bit(uchar dat)
//��  �ܣ�����7bit
//��  ����data����
//����ֵ����
/*******************************************************/
void IRSend_7bit(uchar dat)
{

	uchar Send_Data =0;
	uchar Symble =0x01;
	uchar i =0;
	Send_Data =dat;
	for(i=0;i<7;i++)
	{	
	   	SET_IR;
//#if (CARRIER_SWITCH == 1)
//		Signal_Carrier(CARRIER_DELAY_560US);//0.56ms
//#endif
//
//#if (CARRIER_SWITCH == 0)
//		EndCnt =261;
//		do{;}while(--EndCnt);
//#endif
//		CLR_IR;
		
		if(Send_Data & Symble)
		{
			CLR_IR;
			#if (CARRIER_SWITCH == 1)
				Signal_Carrier(CARRIER_DELAY_420US*3);//0.42*3ms
			#endif


			#if (CARRIER_SWITCH == 0)
				EndCnt =196*3;
				do{;}while(--EndCnt);//0.42*3ms LOW
			#endif

			SET_IR;
			EndCnt =196;	    	
			do{;}while(--EndCnt);//����λΪ1���0.42MS LOW
		}
		else
		{
			CLR_IR;
			#if (CARRIER_SWITCH == 1)
				Signal_Carrier(CARRIER_DELAY_420US);//0.0.42
			#endif

			#if (CARRIER_SWITCH == 0)
				EndCnt =196;
				do{;}while(--EndCnt);//0.42ms LOW
			#endif

			EndCnt =196*3;			
			do{;}while(--EndCnt);//����λ��0���0.42ms*3 HIGH
		}
		Symble <<=1;
	}	
}


/********************************************************/
//��������void IRSend_2bit(uchar dat)
//��  �ܣ�����2bit
//��  ����data����
//����ֵ����
/*******************************************************/
void IRSend_2bit(uchar dat)
{

	uchar Send_Data =0;
	uchar Symble =0x01;
	uchar i =0;
	Send_Data =dat;
	for(i=0;i<2;i++)
	{	
	   	SET_IR;
//#if (CARRIER_SWITCH == 1)
//		Signal_Carrier(CARRIER_DELAY_560US);//0.56ms
//#endif
//
//#if (CARRIER_SWITCH == 0)
//		EndCnt =261;
//		do{;}while(--EndCnt);
//#endif
		
		if(Send_Data & Symble)
		{	
			CLR_IR;
			#if (CARRIER_SWITCH == 1)
				Signal_Carrier(CARRIER_DELAY_420US*3);//0.42*3ms
			#endif


			#if (CARRIER_SWITCH == 0)
				EndCnt =196*3;
				do{;}while(--EndCnt);//0.42*3ms LOW
			#endif

			SET_IR;
			EndCnt =196;	    	
			do{;}while(--EndCnt);//����λΪ1���0.42MS LOW
		}
		else
		{
			CLR_IR;
			#if (CARRIER_SWITCH == 1)
				Signal_Carrier(CARRIER_DELAY_420US);//0.0.42
			#endif

			#if (CARRIER_SWITCH == 0)
				EndCnt =196;
				do{;}while(--EndCnt);//0.42ms LOW
			#endif

			EndCnt =196*3;			
			do{;}while(--EndCnt);//����λ��0���0.42ms*3 HIGH
		}
		Symble <<=1;
	}	
}



/********************************************************/
//��������void IRSend_3bit_Start(uchar dat)
//��  �ܣ�����3bit
//��  ����data����
//����ֵ����
/*******************************************************/
void IRSend_3bit_Start(uchar dat)
{

	uchar Send_Data =0;
	uchar Symble =0x01;
	uchar i =0;
	SET_IR_TX;        					//����ʱ�������
	SET_IR;
	Send_Data =dat;
	for(i=0;i<3;i++)
	{	
	   	SET_IR;
//#if (CARRIER_SWITCH == 1)
//		Signal_Carrier(CARRIER_DELAY_560US);//0.56ms
//#endif
//
//#if (CARRIER_SWITCH == 0)
//		EndCnt =261;
//		do{;}while(--EndCnt);
//#endif
		CLR_IR;
		if(Send_Data & Symble)
		{
			CLR_IR;
			#if (CARRIER_SWITCH == 1)
				Signal_Carrier(CARRIER_DELAY_420US*3);//0.42*3ms
			#endif


			#if (CARRIER_SWITCH == 0)
				EndCnt =196*3;
				do{;}while(--EndCnt);//0.42*3ms LOW
			#endif

			SET_IR;
			EndCnt =196;	    	
			do{;}while(--EndCnt);//����λΪ1���0.42MS LOW
		}
		else
		{
			CLR_IR;
			#if (CARRIER_SWITCH == 1)
				Signal_Carrier(CARRIER_DELAY_420US);//0.0.42
			#endif

			#if (CARRIER_SWITCH == 0)
				EndCnt =196;
				do{;}while(--EndCnt);//0.42ms LOW
			#endif

			EndCnt =196*3;			
			do{;}while(--EndCnt);//����λ��0���0.42ms*3 HIGH
		}
		Symble <<=1;
	}	
}

/********************************************************/
//��������void IRSend_code_1(uint custom,uchar dat)
//��  �ܣ�����������
//��  ����custom:�û���;data����
//����ֵ����
/*******************************************************/
void IRSend_code_1(uchar custom,uchar dat)
{
	 IRSend_2bit(custom);
	 IRSend_7bit(dat);
}


/********************************************************/
//��������void IRSend_KeyValue_1(uint custom,uchar key_value)
//��  �ܣ�IR���Ͱ���ֵ
//��  ����custom:�û���;key_value:����ֵ
//����ֵ����
/*******************************************************/
void IRSend_KeyValue_1(uchar custom,uchar key_value)
{
	if(Last_key != key_value)
	{
		EA =0;
		IRSend_3bit_Start(START_3BIT);
		IRSend_code_1(custom,key_value);
		EA =1;
		Last_key = key_value;
		TR0 =1;
		Timer0_cnt =0;
	}//��Լ70ms����
//	else if(First_Reaptcode == 0)
//	{	 	
//		 if(Timer0_cnt >= 8)
//		 {	
//			EA =0;
//			IR_SendRepeat_Code();
//			IR_EndPulse();
//			First_Reaptcode = 1;
//			Timer0_cnt =0;
//			EA =1;
//		}
//	}//��ʱ40ms�����׸�������
	else if(Timer0_cnt > 3)
	{
		EA =0; 
		IRSend_3bit_Start(START_3BIT);
		IRSend_code_1(custom,key_value);
		Timer0_cnt =0;
		EA =1;
	}//��������������
}
/****************************��NEC_IR**********************************/
#endif

//****************************IR_����*********************************
#if (IR_SEND_OR_REC == 0)
//uint Timer1_IR_ReceiveCount = 0;   					//IR���ռ���
//bit ReceiveCount_Flag = 0;   						//��ʼ������־
//uchar IR_Receive_Data[4] = {0x00,0x00,0x00,0x00};	//IR���ջ���
//uchar IR_Receive_Data_Cout = 0;						//IR���ռ���


uint Send_Count1 = 0;
uint Send_Count2 = 0;
uint Send_Count3 = 0;
uchar Send_Byte1 = 0;
uchar Send_Byte2 = 0;

uint Receive_Count1 = 0;
uint Receive_Count3 = 0;
uint Receive_Count4 = 0;
uchar Receive_Count5 = 0;

bit Rec_Start_Flag = 0;
bit Repeat_Flag = 0;
bit Over_Flag = 0;
bit Low_Flag = 0;
bit Add_Flag = 0;
uchar Bit_Flag = 0;
uchar Receive_Data_Buffer[8] = {0,0,0,0,0,0,0,0};


/********************************/
//��������void IR_Receive(void)
//��  �ܣ�IR���ݽ���
//��  ������
//����ֵ����
/********************************/
void IR_Receive(void)
{
	uchar tmp4 = 0;
	uchar tmp5 = 0;
	SET_IR_RX;
	if(++Receive_Count1 < 60000);

	if(Receive_Count1 >= 1)//100us
	{	
		Receive_Count1 = 0;//100us����
		//�͵�ƽ�ж�
		if(GET_IR_DATA == 0)
		{
			if(Low_Flag == 0)
			{
				//�͵�ƽ��־
				Low_Flag = 1;
			}
			else
			{
				//�͵�ƽ����
				Receive_Count3++;
				//����λ��־
				Bit_Flag = 1;
			}
			if(Bit_Flag == 2)
			{
				
				Bit_Flag = 0;

				if(Rec_Start_Flag == 1)
				{
					//�ж�Repeat��
					if(Receive_Count3 >= 70)//7ms
					{
						//����1ms��С��3ms�ĸߵ�ƽΪRepeat��
						if((Receive_Count4 >= 10) && (Receive_Count4 < 30))
						{	
							if(Repeat_Flag == 0)
							{
								//��ʼλ��־
								Repeat_Flag = 1;
								Rec_Start_Flag = 0;

								//��0
								Receive_Count3 = 0;
								Receive_Count4 = 0;
								Receive_Count5 = 0;
							}
						}
					}

					if(Receive_Count4 > 6)//6ms
					{
						if(Receive_Count3 < Receive_Count4)//�ж�Ϊ1
						{
							//������յ����ݺ�λ
							tmp4 = Receive_Count5 / 8;
							tmp5 = Receive_Count5 % 8;
							switch(tmp4)
							{
								case 0:Receive_Data_Buffer[0] |= (0x01 << tmp5);break;
								case 1:Receive_Data_Buffer[1] |= (0x01 << tmp5);break;
								case 2:Receive_Data_Buffer[2] |= (0x01 << tmp5);break;
								case 3:Receive_Data_Buffer[3] |= (0x01 << tmp5);break;
								case 4:Receive_Data_Buffer[4] |= (0x01 << tmp5);break;
								case 5:Receive_Data_Buffer[5] |= (0x01 << tmp5);break;
								case 6:Receive_Data_Buffer[6] |= (0x01 << tmp5);break;
								case 7:Receive_Data_Buffer[7] |= (0x01 << tmp5);break;	
							}
							Receive_Count3 = 0;
							Receive_Count4 = 0;		 	
						}
					}
					//���Receive_Count3 >= Receive_Count4)���ж�Ϊ0
					else
					{
						//������յ����ݺ�λ
						tmp4 = Receive_Count5 / 8;
						tmp5 = Receive_Count5 % 8;
						switch(tmp4)
						{
							case 0:Receive_Data_Buffer[0] &= ~(0x01 << tmp5);break;
							case 1:Receive_Data_Buffer[1] &= ~(0x01 << tmp5);break;
							case 2:Receive_Data_Buffer[2] &= ~(0x01 << tmp5);break;
							case 3:Receive_Data_Buffer[3] &= ~(0x01 << tmp5);break;
							case 4:Receive_Data_Buffer[4] &= ~(0x01 << tmp5);break;
							case 5:Receive_Data_Buffer[5] &= ~(0x01 << tmp5);break;
							case 6:Receive_Data_Buffer[6] &= ~(0x01 << tmp5);break;
							case 7:Receive_Data_Buffer[7] &= ~(0x01 << tmp5);break;	
						}
						Receive_Count3 = 0;
						Receive_Count4 = 0;
					}
					if(Repeat_Flag == 0)
					{
						if(Add_Flag == 0)
						{
							//������һλ��־
							Add_Flag = 1;
							//������һλ����
					   		Receive_Count5++;	
						}
						//����32λ��0
						if(Receive_Count5 > 32)
						{
							Receive_Count5 = 0;	
//							TRUN_PB1;	
						}
					}
						
				}
				else
				{
					if(Receive_Count3 >= 70)//7ms
					{
						
						if((Receive_Count4 >= 30))//(3~10)ms
						{	
							
							if(Rec_Start_Flag == 0)
							{
								//��ʼλ��־
								Rec_Start_Flag = 1;
								//��0
								Receive_Count3 = 0;
								Receive_Count4 = 0;
								Receive_Count5 = 0;
								
							}
						}
					}	
				}
			}	
		}
		//�ߵ�ƽ�ж�
		else if(GET_IR_DATA != 0)
		{	
			if(Add_Flag == 1)
			{
				//������һλ��־��0
				Add_Flag = 0;
			}	
			if(Low_Flag == 1)
			{
				//�͵�ƽ��־��0
				Low_Flag = 0;
			}
			else
			{
				//�ߵ�ƽ����
				Receive_Count4++;
				Bit_Flag = 2;
				if(Rec_Start_Flag == 1)
				{	
					//����λ��־
					if(Receive_Count4 > 800)//80ms
					{	
						//����λ��־����0
						Receive_Count3 = 0;
						Receive_Count4 = 0;
						Receive_Count5 = 0;
						Bit_Flag = 0;
						Repeat_Flag = 0;
						Rec_Start_Flag = 0;	
					}
				}
			}
		}
	}		
}

#endif