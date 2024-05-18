#include ".\CTK_Library\Config.h"
		
		#if IIC_24C02 

		// 豪秒延时标准程序
		void DelayMilliSeconds(uint _milliSec)
		{
		    unsigned char a,b,c;
		
		    for (; _milliSec > 0; _milliSec--)
		        for (c = 1; c > 0; c--)
		            for (b = 222; b > 0; b--)
		                for (a = 12; a > 0; a--)WDT_CTRL = 7;   
		}

		static void Delay(uchar time)
		{
		    unsigned char a, b;
		    for(b = time; b>0; b--) {   
		        for(a = 17; a>0; a--);
		    }
		}
		
		
		void IICM_Init()
		{
		    OUT_SDA();
		    OUT_SCL();
		    SET_SDA();
		    SET_SCL();
		}
		static void Start()
		{	
			SET_SDA();
		    OUT_SDA();
		    SET_SCL();
		    Delay(1);
		    CLR_SDA();
		    Delay(1);
		    CLR_SCL();
		    Delay(1);
		}
		
		
		static void Stop()
		{   
		    CLR_SCL();
		    OUT_SDA();  
		    CLR_SDA();
		    Delay(1);
		    SET_SCL();
		    Delay(1);
		    SET_SDA();
		}
		
		
		static uchar ReceiveByte()
		{
		    uchar i;
		    uchar buffer;
		    buffer = 0; 
		    IN_SDA();
		        
		    for (i = 0; i < 8; i++) {   
		        CLR_SCL();
		        Delay(2);
		        SET_SCL();
		        Delay(2);           
		        if (SDA()) {        
		            buffer |= 0x01;
		        }
		        if (i < 7) {
		            buffer <<= 1;
		        }
		    }
		    
		    CLR_SCL();
		    OUT_SDA();
		    CLR_SDA();
		
		    return (buffer);
		}
		
		
		static bit SendByteAndGetNACK(uchar dataToSend)
		{
		    uchar i;
		    bit ack;
			
		    for (i = 0; i < 8; i++) {   
		        CLR_SCL();
		        Delay(1);
		        if (dataToSend & 0x80) {
		            SET_SDA();
		        }
		        else {
		            CLR_SDA();
		        }
		        Delay(1);
		        SET_SCL();
		        Delay(1);
		
		        dataToSend <<= 1;
		    }
		    
		    CLR_SCL();
		    Delay(1);
		    
		    IN_SDA();
		    Delay(1);
		    SET_SCL();
		    Delay(2);
		
		    ack = SDA();
		
		    CLR_SCL();
		    Delay(1);                    
		    OUT_SDA();
		    CLR_SDA();
		    Delay(1); 
		    
		
		    return (ack);
		}
		
		
		static void Respond(uchar ACKSignal)
		{
		    OUT_SDA();
		    CLR_SDA();
		    CLR_SCL();
		    if (ACKSignal) {
		        SET_SDA();
		    }
		    else {
		        CLR_SDA();
		    }
				Delay(1);
		    SET_SCL();
		    Delay(1);
		    CLR_SCL();
		}
		void IICM_WriteDeviceFromData_24C02(uchar deviceAddr, uchar *dataSource, uchar lengthOfData,uchar FormNByte)  
		{   
			uchar i;    
			
			EA = 0;					//关总中断
			for (i = 0; i < lengthOfData; i++) 
			{
				WDT_CTRL = 7;
				Start();
				
				if (SendByteAndGetNACK(deviceAddr & ~0x01)) 
				{  
					 
					Stop();
					EA = 1;					//开总中断
					return;
				}
				
				SendByteAndGetNACK(FormNByte);
				
				FormNByte++;
				
				
				SendByteAndGetNACK(dataSource[i]);
				Stop();
				DelayMilliSeconds(1);
			}
			EA = 1;					//开总中断
		}

		void IICM_ReadDeviceDataTo_24C02(uchar deviceAddr, uchar *target, uchar lengthOfData,uchar FormNByte)
		{
			uchar i;
			
			
			EA = 0;					//关总中断
			Start();                
			if (SendByteAndGetNACK(deviceAddr & ~0x01)) 
			{
				
				Stop();
				EA = 1;					//开总中断
				return;
			}
			
			if (SendByteAndGetNACK(FormNByte)) 
			{
				EA = 1;					//开总中断 
				return;
			}
			
			//	SET_SDA();     
			Start();
			if (SendByteAndGetNACK(deviceAddr | 0x01)) 
			{
				Stop();
				EA = 1;					//开总中断
				return;
			}
			
			for (i = 0; i < lengthOfData; i++) {
			target[i] = ReceiveByte();
			
			if (i == (lengthOfData - 1))
			{
			    break;
			}
			else
			{
				Respond(ACK);
			}
			}
			
			Stop();
			EA = 1;					//开总中断          
		}
		//当前地址读
     void IICM_CurrentAddressRead_24C02(uchar deviceAddr,uchar *target, uchar lengthOfData)
		{
			uchar i;
      Start();
			if (SendByteAndGetNACK(deviceAddr | 0x01)) //发送读设备地址
			{
				Stop();
				EA = 1;					
				return;
			}
			for (i = 0; i < lengthOfData; i++) //读取数据
			{
					target[i] = ReceiveByte();
					
					if (i == (lengthOfData - 1))
					{
							break;
					}
					else
					{
							Respond(ACK);
					}
			}
			Respond(NACK);
			Stop();
			EA = 1;					//开总中断          
		}
		//随机读
    void IICM_RandomRead_24C02(uchar deviceAddr, uchar wordAddr,uchar *target, uchar lengthOfData)
		{
			uchar i;
      Start();
      if (SendByteAndGetNACK(deviceAddr & ~0x01)) //发送设备地址//
			{  
					Stop();
					EA = 1;					
					return;
			}
      if (SendByteAndGetNACK(wordAddr)) //发送读目标的字节地址
			{  
					Stop();
					EA = 1;					
					return;
			}  
            
            Start();    //再发送一次开始信号     
			if (SendByteAndGetNACK(deviceAddr | 0x01)) //发送读设备地址
			{
				Stop();
				EA = 1;					
				return;
			}
			for (i = 0; i < lengthOfData; i++) //读取数据
			{
					target[i] = ReceiveByte();
					
					if (i == (lengthOfData - 1))
					{
							break;
					}
					else
					{
							Respond(ACK);
					}
			}
			Respond(NACK);
			Stop();
			EA = 1;					//开总中断          
		}
		//顺序读
     void IICM_SequentialRead_24C02(uchar deviceAddr, uchar wordAddr,uchar *target, uchar lengthOfData)
		{
			uchar i;
       Start();
       if (SendByteAndGetNACK(deviceAddr & ~0x01)) //发送设备地址//
			{  
					Stop();
					EA = 1;					
					return;
			}
      if (SendByteAndGetNACK(wordAddr)) //发送读目标的字节地址
			{  
					Stop();
					EA = 1;					
					return;
			}  
            
      Start();    //再发送一次开始信号     
			if (SendByteAndGetNACK(deviceAddr | 0x01)) //发送读设备地址
			{
				Stop();
				EA = 1;					
				return;
			}
			for (i = 0; i < lengthOfData; i++) //读取数据
			{
					target[i] = ReceiveByte();
					
					if (i == (lengthOfData - 1))
					{
							break;
					}
					else
					{
							Respond(ACK);
					}
			}
			Respond(NACK);
			Stop();
			EA = 1;					//开总中断          
		}
		//字节写
    void IICM_ByteWrite_24C02(uchar deviceAddr,uchar wordAddr, uchar *dataSource, uchar lengthOfData)  
		{   
			uchar i;    
      Start();
      if (SendByteAndGetNACK(deviceAddr & ~0x01)) //发送设备地址
			{  
					Stop();
					EA = 1;					
					return;
			}
      if (SendByteAndGetNACK(wordAddr)) //发送写字节地址
			{  
					Stop();
					EA = 1;				
					return;
			}
			for (i = 0; i < lengthOfData; i++)//发送数据
			{
				WDT_CTRL = 7;
	
				if(SendByteAndGetNACK(dataSource[i]))
				{
						Stop();
						EA = 1;					
						return;
				}
				//DelayMilliSeconds(1);
			}
            //DelayMilliSeconds(1);
      Stop();
			EA = 1;					
		}
        
    //页写//lengthOfData长度必须小于一页大小，一页8个字节，整个EEPROM合计256个字节，分为32页，每页8个字节
    void IICM_PageWrite_24C02(uchar deviceAddr,uchar wordAddr, uchar *dataSource, uchar lengthOfData)  
		{   
			uchar i;    
      Start();
      if (SendByteAndGetNACK(deviceAddr & ~0x01)) //发送设备地址
			{  
					Stop();
					EA = 1;					
					return;
			}
			
			if (SendByteAndGetNACK(wordAddr)) //发送写字节地址
			{  
					Stop();
					EA = 1;				
					return;
			}
			for (i = 0; i < lengthOfData; i++)//发送数据
			{
				WDT_CTRL = 7;
	
				if(SendByteAndGetNACK(dataSource[i]))
				{
					Stop();
          EA = 1;					
          return;
        }
			}
      Stop();
			EA = 1;					
		}
	#endif
