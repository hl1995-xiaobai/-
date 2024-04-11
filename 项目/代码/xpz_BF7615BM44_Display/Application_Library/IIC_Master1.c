#include ".\CTK_Library\Config.h"
#include ".\Project\Project.h"
#include "intrins.h"
#include "absacc.h"

#if CHIP_BF7615AMXX
		#include ".\CTK_Library\BF7615AMXX\BF7615AMXX.H"
		#include ".\CTK_Library\BF7615AMXX\BF7615AMXX_API.h"
		#include ".\CTK_Library\BF7615AMXX\BF7615AMXX_CTK.H"
		#include ".\CTK_Library\BF7615AMXX\BF7615AMXX_API_Timer.h"
		#include ".\CTK_Library\BF7615AMXX\BF76152AMXX_API_IIC_Master.h"
		#if (TRACEMODE == TRUE)
			#include ".\CTK_Library\BF7615AMXX\BF7615AMXX_TraceMode.h"
		#endif

#if (IICM_PA_EN == 1)

			
			void  Delay(uchar time); // unit: 10us
			void 	IICM_Init(void);
			void  Start();
			void  Stop();
			void  Respond(uchar ACKSignal);
			uchar ReceiveByte();
			bit   SendByteAndGetNACK(uchar dataToSend);
			void IICM_WriteDeviceFromData(uchar deviceAddr, uchar *dataSource, uchar lengthOfData);
			void IICM_ReadDeviceDataTo(uchar deviceAddr, uchar *target, uchar lengthOfData);
			
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
			//函数名称： void IICM_WriteDeviceFromData(uchar deviceAddr, uchar *dataSource, uchar lengthOfData) 
			//函数功能： IIC模拟主机写
			//输入参数： uchar deviceAddr：从机写地址； uchar *dataSource：待写数据指针地址；	uchar lengthOfData：写数据长度
			//输出参数： 无
			//返 回 值： 无
			//-----------------------------------------------------------------------------------------------------------//
			void IICM_WriteDeviceFromData(uchar deviceAddr, uchar *dataSource, uchar lengthOfData)  
			{   
			    uchar i;    
			
					EA_OFF;//关总中断； 
			    Start();
			        
			    if (SendByteAndGetNACK(deviceAddr & ~0x01)) {   
			        Stop();
					EA_ON;//开总中断；
			        return;
			    }
			
			    for (i = 0; i < lengthOfData; i++) {
			        if (SendByteAndGetNACK(dataSource[i])) {
			            Stop();
						EA_ON;//开总中断；
			            return;
			        }
			    }   
			    EA_ON;//开总中断；                     
			    Stop();
			}
			
			//-----------------------------------------------------------------------------------------------------------//
			//函数名称： void IICM_ReadDeviceDataTo(uchar deviceAddr, uchar *target, uchar lengthOfData)
			//函数功能： IIC模拟主机写
			//输入参数： uchar deviceAddr：从机读地址； uchar *dataSource：读取数据指针地址；	uchar lengthOfData：读取数据长度
			//输出参数： 无
			//返 回 值： 无
			//-----------------------------------------------------------------------------------------------------------//
			void IICM_ReadDeviceDataTo(uchar deviceAddr, uchar *target, uchar lengthOfData)
			{
			    uchar i;    
			
				EA_OFF;//关总中断； 
			    Start();                
			    if (SendByteAndGetNACK(deviceAddr | 0x01)) {
			        Stop();
					EA_ON;//开总中断；
			        return;
			    }   
			    
			    for (i = 0; i < lengthOfData; i++) {
			        target[i] = ReceiveByte();
			        if (i == (lengthOfData - 1))
			            break;
			        Respond(ACK);
			    }
			
			    Respond(NACK);
				EA_ON;//开总中断；
			    Stop();           
			}
		#endif
#endif