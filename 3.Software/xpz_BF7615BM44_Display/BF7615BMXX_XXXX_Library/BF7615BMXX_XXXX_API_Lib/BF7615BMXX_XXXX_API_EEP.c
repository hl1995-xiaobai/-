#include ".\BF7615BMXX_XXXX_Library\Config.h"
		
	#if (EEPROM_EN == 1)
		#pragma message "编译,EEPROM功能"
		uchar xdata Eeprom_Write_Buffer[10] = {0};
		uint rom_offset = 0;
		void Eeprom_Init(void);
		void Eeprom_Erase_Page(void);
		bit Eeprom_Write_Byte(uchar page,uint addr,uchar write_byte);
		bit Eeprom_Write_NBytes(uchar page,uint addr,uchar *write_data,uint length);
		uchar Eeprom_Read_Byte(uchar page,uint Byte_N);
		void NVR_Erase_Page(uchar nvr);
		
		/****************************************************************/
		//函数名：uint Read_ROM_Offset(void)
		//功  能：读取CODE偏移地址
		//参  数：无
		//返回值：uint,CFG_BOOT_SEL = 0时,返回0x800;CFG_BOOT_SEL = 1时,返回0x1000;
		//CFG_BOOT_SEL = 2时,返回0x2000;CFG_BOOT_SEL = 3时,返回0x0000;
		/****************************************************************/
		uint Read_ROM_Offset(void)
		{
			uint rom_offset_tem = 0;
			EA = 0;
			REG_ADDR = 0x6C;
			rom_offset_tem = (((uint)REG_DATA) << 8);
			REG_ADDR = 0x6B;
			rom_offset_tem |= REG_DATA;
			EA = 1;
			return rom_offset_tem;
		}
		//-----------------------------------------------------------------//
		//函数名称： void Eeprom_Init(void)
		//函数功能： Eeprom_Init擦写时间初始化
		//输入参数： 无
		//输出参数： 无
		//返 回 值： 无
		//-----------------------------------------------------------------//
		void Eeprom_Init(void)
		{
			EEP_SEL(0);//选择EEP
			EEPROM_ERASE_TIMER_SET(4);//EEP_SELECT=0时，擦出时间选择(0~9):1ms~10ms(步进1ms)+0.13ms,>9:9.13ms，EEP_SELECT=1时，擦出时间选择(0~9):0.5ms~5ms(步进1ms)+0.0652ms,>9:4.5652ms，推荐5ms
			EEPROM_WRITE_TIMER_SET();//字节写时间选择(23.5)us
			rom_offset = Read_ROM_Offset();
		}
		
		//-----------------------------------------------------------------//
		//函数名称： void Eeprom_Erase_Page(void)
		//函数功能： Eeprom页擦除
		//输入参数： 无
		//输出参数： 无
		//返 回 值： 无
		//-----------------------------------------------------------------//
		void Eeprom_Erase_Page(void)
		{
			#ifdef IICS_EN
				#if IICS_EN
					IICCON &= ~0x01;//IIC工作使能关闭
				#endif
			#endif
			
			#ifdef TRACEMODE
				#if TRACEMODE
					IICCON &= ~0x01;//IIC工作使能关闭
				#endif
			#endif
			EA = 0;//关总中断；
			EEP_SEL(0);//选择EEP
			SPROG_ADDR_L = 0x00;
			SPROG_ADDR_H = 0x00;
			SPROG_ADDR_H &= ~(0x7C);//选择要写的页
			SPROG_CMD = 0x96;
			_nop_();
			_nop_();
			_nop_();
			_nop_();
			SPROG_ADDR_L = 0x00;
			SPROG_ADDR_H = 0x00;
			#ifdef IICS_EN
				#if IICS_EN
					IICCON |= 0x01;//IIC工作使能关闭
				#endif
			#endif
			
			#ifdef TRACEMODE
				#if TRACEMODE
					IICCON |= 0x01;//IIC工作使能关闭
				#endif
			#endif
			EA = 1;//开总中断
		}
		
		//-----------------------------------------------------------------//
		//函数名称： void NVR_Erase_Page(uchar nvr)
		//函数功能： NVR_Erase_Page擦除,uchar nvr:3/4选择要擦除的NVR:3/4对应NVR3/4
		//输入参数： 无
		//输出参数： 无
		//返 回 值： 无
		//-----------------------------------------------------------------//
		void NVR_Erase_Page(uchar nvr)
		{
			#ifdef IICS_EN
				#if IICS_EN
					IICCON &= ~0x01;//IIC工作使能关闭
				#endif
			#endif
			
			#ifdef TRACEMODE
				#if TRACEMODE
					IICCON &= ~0x01;//IIC工作使能关闭
				#endif
			#endif
			EA = 0;//关总中断；
			EEP_SEL(1);//选择NVR
			EEPROM_ERASE_TIMER_SET(9);//EEP_SELECT=0时，擦出时间选择(0~9):1ms~10ms(步进1ms)+0.13ms,>9:9.13ms，EEP_SELECT=1时，擦出时间选择(0~9):0.5ms~5ms(步进1ms)+0.0652ms,>9:4.5652ms，推荐5ms
			SPROG_ADDR_L = 0x00;
			if(nvr == 3)
			{
				SPROG_ADDR_H = 0x00;//NVR3
			}
			else
			{
				SPROG_ADDR_H = 0x04;//NVR4
			}

			SPROG_CMD = 0x96;
			_nop_();
			_nop_();
			_nop_();
			_nop_();
			SPROG_ADDR_L = 0x00;
			SPROG_ADDR_H = 0x00;
			#ifdef IICS_EN
				#if IICS_EN
					IICCON |= 0x01;//IIC工作使能关闭
				#endif
			#endif
			
			#ifdef TRACEMODE
				#if TRACEMODE
					IICCON |= 0x01;//IIC工作使能关闭
				#endif
			#endif
			EA = 1;//开总中断
		}
		
	//-----------------------------------------------------------------//
	//函数名称： bit NVR_Write_Byte(uchar nvr,uint addr,uchar write_byte)
	//函数功能： NVR写数据
	//输入参数： uchar nvr：选择将要写入的nvr页；uint addr:当前页对应的地址(0~511)；uchar write_byte：将要写入的数据;uchar write_time:写操作时间选择：建议固定为固定为23.5us
	//输出参数： 无
	//返 回 值： 0:写成功；1：写失败；
	//-----------------------------------------------------------------//
	
		
		bit NVR_Write_Byte(uchar nvr,uint addr,uchar write_byte)
		{	
			uint i = 0;
			bit Write_OK = 0;
			#ifdef IICS_EN
				#if IICS_EN
					IICCON &= ~0x01;//IIC工作使能关闭
				#endif
			#endif
			
			#ifdef TRACEMODE
				#if TRACEMODE
					IICCON &= ~0x01;//IIC工作使能关闭
				#endif
			#endif
			EA = 0;//关总中断；
			EEP_SEL(1);//选择NVR
			SPROG_ADDR_L = 0x00;
			SPROG_ADDR_H = 0x00;
			
			if(nvr == 3)
			{
				SPROG_ADDR_H = 0x00;//NVR3
			}
			else
			{
				SPROG_ADDR_H = 0x04;//NVR4
			}
			SPROG_ADDR_L = addr;
			SPROG_ADDR_H |= (addr>>8)&0x03;//选择要入地址
			SPROG_DATA = write_byte;//准备写入的数据
			SPROG_CMD = 0x69;
			_nop_();
			_nop_();
			_nop_();
			_nop_();
			SPROG_ADDR_L = 0x00;
			SPROG_ADDR_H = 0x00;
			#ifdef IICS_EN
				#if IICS_EN
					IICCON |= 0x01;//IIC工作使能关闭
				#endif
			#endif
			
			#ifdef TRACEMODE
				#if TRACEMODE
					IICCON |= 0x01;//IIC工作使能关闭
				#endif
			#endif
			if(NVR_Read_Byte(nvr,addr)== write_byte)
			{
					Write_OK = 0;
			}
			else
			{
					Write_OK = 1;
			}
			
			EA = 1;//开总中断
			return Write_OK;
				
		}

	//-----------------------------------------------------------------//
	//函数名称： bit Eeprom_Write_Byte(uchar page,uint addr,uchar write_byte)
	//函数功能： Eeprom写数据
	//输入参数： uchar page：选择将要写入的页；uint addr:当前页对应的地址(0~1023)；uchar write_byte：将要写入的数据;uchar write_time:写操作时间选择：建议固定为23.5us
	//输出参数： 无
	//返 回 值： 0:写成功；1：写失败；
	//-----------------------------------------------------------------//
	
		
		bit Eeprom_Write_Byte(uchar page,uint addr,uchar write_byte)
		{	
			uint i = 0;
			bit Write_OK = 0;
			#ifdef IICS_EN
				#if IICS_EN
					IICCON &= ~0x01;//IIC工作使能关闭
				#endif
			#endif
			
			#ifdef TRACEMODE
				#if TRACEMODE
					IICCON &= ~0x01;//IIC工作使能关闭
				#endif
			#endif
			EA = 0;//关总中断；
			SPROG_ADDR_L = 0x00;
			SPROG_ADDR_H = 0x00;
			SPROG_ADDR_H &= ~(0x7C);//选择要写的页
			SPROG_ADDR_L = addr;
			SPROG_ADDR_H |= (addr>>8)&0x03;//选择要入地址
			SPROG_DATA = write_byte;//准备写入的数据
			SPROG_CMD = 0x69;
			_nop_();
			_nop_();
			_nop_();
			_nop_();
			SPROG_ADDR_L = 0x00;
			SPROG_ADDR_H = 0x00;
			#ifdef IICS_EN
				#if IICS_EN
					IICCON |= 0x01;//IIC工作使能关闭
				#endif
			#endif
			
			#ifdef TRACEMODE
				#if TRACEMODE
					IICCON |= 0x01;//IIC工作使能关闭
				#endif
			#endif
			if(Eeprom_Read_Byte(page,addr)== write_byte)
			{
					Write_OK = 0;
			}
			else
			{
					Write_OK = 1;
			}
			
			EA = 1;//开总中断
			return Write_OK;
				
		}
		
		//-----------------------------------------------------------------//
		//函数名称： bit Eeprom_Write_NBytes(uchar page,uint addr,uchar *write_data,uint length)
		//函数功能： Eeprom写length Bytes数据
		//输入参数： uchar rank：选择将要写入的页；uint addr:当前页对应的地址(0~1023)；uchar *write_data：
		//将要写入的数据;uint length(1~1024):从当前页第addr字节开始写入length个字节(length<= (1024-addr))；
		//输入参数： uchar nvr：选择将要写入的nvr页；uint addr:当前页对应的地址(0~511)；uchar write_byte：将要写入的数据;uchar write_time:写操作时间选择：建议固定为固定为23.5us
		//输出参数： 无
		//返 回 值： 0:写成功；1：写失败；
		//-----------------------------------------------------------------//
	
		bit Eeprom_Write_NBytes(uchar page,uint addr,uchar *write_data,uint length)
		{	
			uint i = 0;
			bit Write_OK = 0;
			for(i = 0;i < length;i++)
			{
					if(Eeprom_Write_Byte(page,addr+i,*(write_data+i))!= 0)
					{
							Write_OK = 1;
					}
			}
			return Write_OK;
				
		}
		
		//-----------------------------------------------------------------//
		//函数名称： uchar Eeprom_Read_Byte(uchar page,uint Byte_N)
		//函数功能： Eeprom读数据
		//输入参数： uchar page：选择将要读取的页；uint Byte_N：读取页的第Byte_N字节;
		//输出参数： 无
		//返 回 值： 返回读页的第Byte_N字节的内容；
		//CFG_BOOT_SEL = 0 时，ROM_OFFSETH/L = 0x0800， 
		//CFG_BOOT_SEL = 1 时，ROM_OFFSETH/L = 0x1000， 
		//CFG_BOOT_SEL = 2 时，ROM_OFFSETH/L = 0x2000,
		//CFG_BOOT_SEL = 3 时，ROM_OFFSETH/L = 0x0000//无BOOT 升级功能。
		//应用BOOT 功能时，程序所有CODE 区对绝对地址的访问，需要减去ROM_OFFSET_H/L 的偏移地址
		//（PC - ROM_OFFSET）,再对CODE 区绝对地址进行访问。
		//-----------------------------------------------------------------//
		uchar Eeprom_Read_Byte(uchar page,uint Byte_N)
		{	
			uchar code *P_Rank;
			P_Rank = 0xFC00 - page*1024 - rom_offset; 
			return (*(P_Rank + Byte_N));	
		}
		
		//-----------------------------------------------------------------//
		//函数名称： uchar NVR_Read_Byte(uchar nvr,uint Byte_N)
		//函数功能： 读NVR数据
		//输入参数： uchar nvr：3/4选择将要读取的页:NVR3/NVR4；uint Byte_N:0~511：读取NVR页的第Byte_N字节;
		//输出参数： 无
		//返 回 值： 返回读NVR页的第Byte_N字节的内容；
		//-----------------------------------------------------------------//
		uchar NVR_Read_Byte(uchar nvr,uint Byte_N)
		{	
			
			uchar read_tem = 0;
			EA = 0;
			SPROG_CMD = 0x88;

			if(nvr == 3)
			{
				SPROG_ADDR_H = (0x4400+Byte_N)>>8;
				SPROG_ADDR_L = (uchar)(0x4400+Byte_N);
			}
			else if(nvr == 4)
			{
				SPROG_ADDR_H = (0x4600+Byte_N)>>8;
				SPROG_ADDR_L = (uchar)(0x4600+Byte_N);
			}
			read_tem = SPROG_RDATA;
			SPROG_CMD = 0x00;
			SPROG_ADDR_H = 0x00;
			SPROG_ADDR_L = 0x00;
			EA = 1;
			return read_tem;	
		}
#endif
