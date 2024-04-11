#if EEPROM_EN 

#define SET_SDA()   DATAA |= 0x04
#define CLR_SDA()   DATAA &= ~0x04
#define OUT_SDA()   TRISA &= ~0x04
#define IN_SDA()    TRISA |= 0x04
#define SDA()       DATAA & 0x04

#define SET_SCL()   DATAA |= 0x08
#define CLR_SCL()   DATAA &= ~0x08
#define OUT_SCL()   TRISA &= ~0x08
#define IN_SCL()    TRISA |= 0x08

#define NACK    1
#define ACK     0

extern void IICM_Init();
extern void DelayMilliSeconds(uint _milliSec);
extern void  Delay(uchar time);
extern void  Start();
extern void  Stop();
extern void  Respond(uchar ACKSignal);
extern uchar ReceiveByte();
extern bit   SendByteAndGetNACK(uchar dataToSend);

extern void IICM_WriteDeviceFromData_24C02(uchar deviceAddr, uchar *dataSource, uchar lengthOfData,uchar FormNByte);
extern void IICM_ReadDeviceDataTo_24C02(uchar deviceAddr, uchar *target, uchar lengthOfData,uchar FormNByte);
#endif
// 豪秒延时标准程序
			void DelayMilliSeconds(uint _milliSec)
			{
			    unsigned char a,b,c;
			
			    for (; _milliSec > 0; _milliSec--)
			        for (c = 1; c > 0; c--)
			            for (b = 222; b > 0; b--)
			                for (a = 12; a > 0; a--)WDT_CTRL = 7;   
			}
	
			void Delay(uchar time)
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
				
				EA_OFF;//关总中断；
				for (i = 0; i < lengthOfData; i++) 
				{
					WDT_CTRL = 7;
					Start();
					
					if (SendByteAndGetNACK(deviceAddr & ~0x01)) 
					{  
						 
						Stop();
						EA_ON;//开总中断
						return;
					}
					
					SendByteAndGetNACK(FormNByte);
					
					FormNByte++;
					
					
					SendByteAndGetNACK(dataSource[i]);
					Stop();
					DelayMilliSeconds(1);
				}
				EA_ON;//开总中断
			}
	
			void IICM_ReadDeviceDataTo_24C02(uchar deviceAddr, uchar *target, uchar lengthOfData,uchar FormNByte)
			{
				uchar i;
				
				
				EA_OFF;//关总中断；
				Start();                
				if (SendByteAndGetNACK(deviceAddr & ~0x01)) 
				{
					
					Stop();
					EA_ON;//开总中断 
					return;
				}
				
				if (SendByteAndGetNACK(FormNByte)) 
				{
					EA_ON;//开总中断 
					return;
				}
				   
				Start();
				if (SendByteAndGetNACK(deviceAddr | 0x01)) 
				{
					Stop();
					EA_ON;//开总中断 
					return;
				}
				
				for (i = 0; i < lengthOfData; i++) 
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
				
				Stop();
				EA_ON;//开总中断           
			}