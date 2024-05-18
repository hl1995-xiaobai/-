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
uint EndCnt =0;   									//用于延时
uchar Last_key =0;									//最后一次按键值
uchar Timer0_cnt =0;   								//完整码发送后 开始计数
bit First_Reaptcode =0; 							//标示第一个连续码
bit Start_Flag = 0;									//引导码标志
bit Repeat_Flag = 0;								//连续码标志

uchar Key_Value =0;									//按键值


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
//函数名：void Signal_Carrier(uint count)
//功  能：载波38 Period-26us
//参  数：count: 延时计数
//返回值：无
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
//函数名：void delay_ms( BYTE time)
//功  能：延时函数
//参  数：time: 1--1ms
//返回值：无
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
//函数名：void IR_Start()
//功  能：发送引导码
//参  数：无
//返回值：无
/*******************************************************/
void IR_Start()
{
   	SET_IR_TX;        					//发送时候置输出
	SET_IR;

#if (CARRIER_SWITCH == 1)
	Signal_Carrier(CARRIER_DELAY_9MS);	//9ms
#endif

#if (CARRIER_SWITCH == 0)
	delay_ms(9);	 					//发送9ms高
#endif

	CLR_IR;
	EndCnt =2030;
	do{;}while(--EndCnt);	
}

/********************************************************/
//函数名：void IRSend_Byte(uchar dat)
//功  能：发送数据
//参  数：data数据
//返回值：无
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
			EndCnt =783;	    	//数据位为1输出1.68MS LOW
			do{;}while(--EndCnt);
		}
		else
		{
			EndCnt =261;			//数据位是0输出0.56ms HIGH
			do{;}while(--EndCnt);
		}
		Symble <<=1;
	}	
}

/********************************************************/
//函数名：void IRSend_Opposite_Byte(uchar dat)
//功  能：发送数据反码
//参  数：data数据
//返回值：无
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
//函数名：void IRSend_16Byte(uint dat)
//功  能：发送16位数据
//参  数：data数据
//返回值：无
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
//函数名：void IRSend_code(uint custom,uchar dat)
//功  能：发送完整码
//参  数：custom:用户码;data数据
//返回值：无
/*******************************************************/
void IRSend_code(uint custom,uchar dat)
{
	 IRSend_16Byte(custom);
	 IRSend_Byte(dat);
	 IRSend_Opposite_Byte(dat);
}

/********************************************************/
//函数名：void IR_EndPulse(void)
//功  能：结束码
//参  数：无
//返回值：无
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
	SET_IR_RX;	 //结束时候置IR方向口为输入
}

/********************************************************/
//函数名：void IR_SendRepeat_Code(void)
//功  能：发送连续码
//参  数：无
//返回值：无
/*******************************************************/
void IR_SendRepeat_Code()
{
	SET_IR_TX;           					//设置为输出
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
//函数名：void IRSend_KeyValue(uint custom,uchar key_value)
//功  能：IR发送按键值
//参  数：custom:用户码;key_value:按键值
//返回值：无
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
	}//大约70ms左右
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
	}//计时40ms发送首个连续码
	else if(Timer0_cnt > 16)
	{
		EA =0; 
		IR_SendRepeat_Code();
		IR_EndPulse();
		Timer0_cnt =0;
		EA =1;
	}//连续发送连续码
}


///////////////////////////////////////////////////////////////////////////////////////////////////


/****************************非NEC_IR**********************************/

/********************************************************/
//函数名：void IRSend_7bit(uchar dat)
//功  能：发送7bit
//参  数：data数据
//返回值：无
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
			do{;}while(--EndCnt);//数据位为1输出0.42MS LOW
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
			do{;}while(--EndCnt);//数据位是0输出0.42ms*3 HIGH
		}
		Symble <<=1;
	}	
}


/********************************************************/
//函数名：void IRSend_2bit(uchar dat)
//功  能：发送2bit
//参  数：data数据
//返回值：无
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
			do{;}while(--EndCnt);//数据位为1输出0.42MS LOW
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
			do{;}while(--EndCnt);//数据位是0输出0.42ms*3 HIGH
		}
		Symble <<=1;
	}	
}



/********************************************************/
//函数名：void IRSend_3bit_Start(uchar dat)
//功  能：发送3bit
//参  数：data数据
//返回值：无
/*******************************************************/
void IRSend_3bit_Start(uchar dat)
{

	uchar Send_Data =0;
	uchar Symble =0x01;
	uchar i =0;
	SET_IR_TX;        					//发送时候置输出
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
			do{;}while(--EndCnt);//数据位为1输出0.42MS LOW
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
			do{;}while(--EndCnt);//数据位是0输出0.42ms*3 HIGH
		}
		Symble <<=1;
	}	
}

/********************************************************/
//函数名：void IRSend_code_1(uint custom,uchar dat)
//功  能：发送完整码
//参  数：custom:用户码;data数据
//返回值：无
/*******************************************************/
void IRSend_code_1(uchar custom,uchar dat)
{
	 IRSend_2bit(custom);
	 IRSend_7bit(dat);
}


/********************************************************/
//函数名：void IRSend_KeyValue_1(uint custom,uchar key_value)
//功  能：IR发送按键值
//参  数：custom:用户码;key_value:按键值
//返回值：无
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
	}//大约70ms左右
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
//	}//计时40ms发送首个连续码
	else if(Timer0_cnt > 3)
	{
		EA =0; 
		IRSend_3bit_Start(START_3BIT);
		IRSend_code_1(custom,key_value);
		Timer0_cnt =0;
		EA =1;
	}//连续发送连续码
}
/****************************非NEC_IR**********************************/
#endif

//****************************IR_接收*********************************
#if (IR_SEND_OR_REC == 0)
//uint Timer1_IR_ReceiveCount = 0;   					//IR接收计算
//bit ReceiveCount_Flag = 0;   						//开始计数标志
//uchar IR_Receive_Data[4] = {0x00,0x00,0x00,0x00};	//IR接收缓存
//uchar IR_Receive_Data_Cout = 0;						//IR接收计数


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
//函数名：void IR_Receive(void)
//功  能：IR数据接收
//参  数：无
//返回值：无
/********************************/
void IR_Receive(void)
{
	uchar tmp4 = 0;
	uchar tmp5 = 0;
	SET_IR_RX;
	if(++Receive_Count1 < 60000);

	if(Receive_Count1 >= 1)//100us
	{	
		Receive_Count1 = 0;//100us清零
		//低电平判断
		if(GET_IR_DATA == 0)
		{
			if(Low_Flag == 0)
			{
				//低电平标志
				Low_Flag = 1;
			}
			else
			{
				//低电平计数
				Receive_Count3++;
				//接收位标志
				Bit_Flag = 1;
			}
			if(Bit_Flag == 2)
			{
				
				Bit_Flag = 0;

				if(Rec_Start_Flag == 1)
				{
					//判断Repeat码
					if(Receive_Count3 >= 70)//7ms
					{
						//大于1ms并小于3ms的高电平为Repeat码
						if((Receive_Count4 >= 10) && (Receive_Count4 < 30))
						{	
							if(Repeat_Flag == 0)
							{
								//起始位标志
								Repeat_Flag = 1;
								Rec_Start_Flag = 0;

								//清0
								Receive_Count3 = 0;
								Receive_Count4 = 0;
								Receive_Count5 = 0;
							}
						}
					}

					if(Receive_Count4 > 6)//6ms
					{
						if(Receive_Count3 < Receive_Count4)//判断为1
						{
							//计算接收的数据和位
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
					//如果Receive_Count3 >= Receive_Count4)，判断为0
					else
					{
						//计算接收的数据和位
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
							//接收下一位标志
							Add_Flag = 1;
							//接收下一位计数
					   		Receive_Count5++;	
						}
						//大于32位清0
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
								//起始位标志
								Rec_Start_Flag = 1;
								//清0
								Receive_Count3 = 0;
								Receive_Count4 = 0;
								Receive_Count5 = 0;
								
							}
						}
					}	
				}
			}	
		}
		//高电平判断
		else if(GET_IR_DATA != 0)
		{	
			if(Add_Flag == 1)
			{
				//接收下一位标志清0
				Add_Flag = 0;
			}	
			if(Low_Flag == 1)
			{
				//低电平标志清0
				Low_Flag = 0;
			}
			else
			{
				//高电平计数
				Receive_Count4++;
				Bit_Flag = 2;
				if(Rec_Start_Flag == 1)
				{	
					//接收位标志
					if(Receive_Count4 > 800)//80ms
					{	
						//结束位标志，清0
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