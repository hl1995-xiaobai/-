#include ".\CTK_Library\Config.h"
		
		#if IIC_24C02 

		// ������ʱ��׼����
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
			
			EA = 0;					//�����ж�
			for (i = 0; i < lengthOfData; i++) 
			{
				WDT_CTRL = 7;
				Start();
				
				if (SendByteAndGetNACK(deviceAddr & ~0x01)) 
				{  
					 
					Stop();
					EA = 1;					//�����ж�
					return;
				}
				
				SendByteAndGetNACK(FormNByte);
				
				FormNByte++;
				
				
				SendByteAndGetNACK(dataSource[i]);
				Stop();
				DelayMilliSeconds(1);
			}
			EA = 1;					//�����ж�
		}

		void IICM_ReadDeviceDataTo_24C02(uchar deviceAddr, uchar *target, uchar lengthOfData,uchar FormNByte)
		{
			uchar i;
			
			
			EA = 0;					//�����ж�
			Start();                
			if (SendByteAndGetNACK(deviceAddr & ~0x01)) 
			{
				
				Stop();
				EA = 1;					//�����ж�
				return;
			}
			
			if (SendByteAndGetNACK(FormNByte)) 
			{
				EA = 1;					//�����ж� 
				return;
			}
			
			//	SET_SDA();     
			Start();
			if (SendByteAndGetNACK(deviceAddr | 0x01)) 
			{
				Stop();
				EA = 1;					//�����ж�
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
			EA = 1;					//�����ж�          
		}
		//��ǰ��ַ��
     void IICM_CurrentAddressRead_24C02(uchar deviceAddr,uchar *target, uchar lengthOfData)
		{
			uchar i;
      Start();
			if (SendByteAndGetNACK(deviceAddr | 0x01)) //���Ͷ��豸��ַ
			{
				Stop();
				EA = 1;					
				return;
			}
			for (i = 0; i < lengthOfData; i++) //��ȡ����
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
			EA = 1;					//�����ж�          
		}
		//�����
    void IICM_RandomRead_24C02(uchar deviceAddr, uchar wordAddr,uchar *target, uchar lengthOfData)
		{
			uchar i;
      Start();
      if (SendByteAndGetNACK(deviceAddr & ~0x01)) //�����豸��ַ//
			{  
					Stop();
					EA = 1;					
					return;
			}
      if (SendByteAndGetNACK(wordAddr)) //���Ͷ�Ŀ����ֽڵ�ַ
			{  
					Stop();
					EA = 1;					
					return;
			}  
            
            Start();    //�ٷ���һ�ο�ʼ�ź�     
			if (SendByteAndGetNACK(deviceAddr | 0x01)) //���Ͷ��豸��ַ
			{
				Stop();
				EA = 1;					
				return;
			}
			for (i = 0; i < lengthOfData; i++) //��ȡ����
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
			EA = 1;					//�����ж�          
		}
		//˳���
     void IICM_SequentialRead_24C02(uchar deviceAddr, uchar wordAddr,uchar *target, uchar lengthOfData)
		{
			uchar i;
       Start();
       if (SendByteAndGetNACK(deviceAddr & ~0x01)) //�����豸��ַ//
			{  
					Stop();
					EA = 1;					
					return;
			}
      if (SendByteAndGetNACK(wordAddr)) //���Ͷ�Ŀ����ֽڵ�ַ
			{  
					Stop();
					EA = 1;					
					return;
			}  
            
      Start();    //�ٷ���һ�ο�ʼ�ź�     
			if (SendByteAndGetNACK(deviceAddr | 0x01)) //���Ͷ��豸��ַ
			{
				Stop();
				EA = 1;					
				return;
			}
			for (i = 0; i < lengthOfData; i++) //��ȡ����
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
			EA = 1;					//�����ж�          
		}
		//�ֽ�д
    void IICM_ByteWrite_24C02(uchar deviceAddr,uchar wordAddr, uchar *dataSource, uchar lengthOfData)  
		{   
			uchar i;    
      Start();
      if (SendByteAndGetNACK(deviceAddr & ~0x01)) //�����豸��ַ
			{  
					Stop();
					EA = 1;					
					return;
			}
      if (SendByteAndGetNACK(wordAddr)) //����д�ֽڵ�ַ
			{  
					Stop();
					EA = 1;				
					return;
			}
			for (i = 0; i < lengthOfData; i++)//��������
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
        
    //ҳд//lengthOfData���ȱ���С��һҳ��С��һҳ8���ֽڣ�����EEPROM�ϼ�256���ֽڣ���Ϊ32ҳ��ÿҳ8���ֽ�
    void IICM_PageWrite_24C02(uchar deviceAddr,uchar wordAddr, uchar *dataSource, uchar lengthOfData)  
		{   
			uchar i;    
      Start();
      if (SendByteAndGetNACK(deviceAddr & ~0x01)) //�����豸��ַ
			{  
					Stop();
					EA = 1;					
					return;
			}
			
			if (SendByteAndGetNACK(wordAddr)) //����д�ֽڵ�ַ
			{  
					Stop();
					EA = 1;				
					return;
			}
			for (i = 0; i < lengthOfData; i++)//��������
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
