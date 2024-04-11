#if (IICM_PA_EN == 1)
			#pragma message "���룬void IICM_Init(void)"
			#define SET_SDA()   DATAA |= 0x10
			#define CLR_SDA()   DATAA &= ~0x10
			#define OUT_SDA()   TRISA &= ~0x10
			#define IN_SDA()    TRISA |= 0x10
			#define SDA()       DATAA & 0x10
			
			#define SET_SCL()   DATAA |= 0x08
			#define CLR_SCL()   DATAA &= ~0x08
			#define OUT_SCL()   TRISA &= ~0x08
			#define IN_SCL()    TRISA |= 0x08
			
			#define NACK    1
			#define ACK     0
			
			void  Delay(uchar time); // unit: 10us
			void  Start();
			void  Stop();
			void  Respond(uchar ACKSignal);
			uchar ReceiveByte();
			bit   SendByteAndGetNACK(uchar dataToSend);
			
			
			static void Delay(uchar time)
			{
			    unsigned char a, b;
			    for(b = time; b>0; b--) {   
			        for(a = 17; a>0; a--);
			    }
			}
			
			
			void IICM_Init(void)
			{
			    OUT_SDA();
			    OUT_SCL();
			    SET_SDA();
			    SET_SCL();
			}
			
			
			static void Start()
			{
			    OUT_SDA();
			    SET_SDA();  
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
			
			//-----------------------------------------------------------------------------------------------------------//
			//�������ƣ� void IICM_WriteDeviceFromData(uchar deviceAddr, uchar *dataSource, uchar lengthOfData) 
			//�������ܣ� IICģ������д
			//��������� uchar deviceAddr���ӻ�д��ַ�� uchar *dataSource����д����ָ���ַ��	uchar lengthOfData��д���ݳ���
			//��������� ��
			//�� �� ֵ�� ��
			//-----------------------------------------------------------------------------------------------------------//
			void IICM_WriteDeviceFromData(uchar deviceAddr, uchar *dataSource, uchar lengthOfData)  
			{   
			    uchar i;    
			
				EA = 0;
			    Start();
			        
			    if (SendByteAndGetNACK(deviceAddr & ~0x01)) {   
			        Stop();
					EA = 1;
			        return;
			    }
			
			    for (i = 0; i < lengthOfData; i++) {
			        if (SendByteAndGetNACK(dataSource[i])) {
			            Stop();
						EA = 1;
			            return;
			        }
			    }   
			    EA = 1;                        
			    Stop();
			}
			
			//-----------------------------------------------------------------------------------------------------------//
			//�������ƣ� void IICM_ReadDeviceDataTo(uchar deviceAddr, uchar *target, uchar lengthOfData)
			//�������ܣ� IICģ������д
			//��������� uchar deviceAddr���ӻ�����ַ�� uchar *dataSource����ȡ����ָ���ַ��	uchar lengthOfData����ȡ���ݳ���
			//��������� ��
			//�� �� ֵ�� ��
			//-----------------------------------------------------------------------------------------------------------//
			void IICM_ReadDeviceDataTo(uchar deviceAddr, uchar *target, uchar lengthOfData)
			{
			    uchar i;    
			
				EA = 0;
			    Start();                
			    if (SendByteAndGetNACK(deviceAddr | 0x01)) {
			        Stop();
					EA = 1; 
			        return;
			    }   
			    
			    for (i = 0; i < lengthOfData; i++) {
			        target[i] = ReceiveByte();
			        if (i == (lengthOfData - 1))
			            break;
			        Respond(ACK);
			    }
			
			    Respond(NACK);
				EA = 1;
			    Stop();           
			}
		#endif