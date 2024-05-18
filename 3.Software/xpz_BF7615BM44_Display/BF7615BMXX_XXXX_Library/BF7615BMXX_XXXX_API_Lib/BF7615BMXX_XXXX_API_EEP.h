#ifndef __BF7615BMXX_XXXX_API_EEP_H__
#define __BF7615BMXX_XXXX_API_EEP_H__


#define EEPROM_EN									0	// 1:使能编译，0:不使能编译


//0x5b地址的REG_DATA[0]:EEP_SELECT写1为选择NVR3和NVR4作为EEP功能,写0为选择mainblock最后1K作为EEP功能
#define EEP_SEL(reg_data) Write_REG(0x5b,reg_data)

#define EEPROM_ERASE_TIMER_SET(x)  		{SPROG_TIM &= (~0x1F);SPROG_TIM |= (0x1F&x);}//擦出时间选择(0~9):1ms~10ms(步进1ms)+0.13ms,>9:9.13ms
#define EEPROM_WRITE_TIMER_SET()  		{SPROG_TIM &= (~0xE0);SPROG_TIM |= (0xE0);}//字节写时间选择(23.5)us

#if EEPROM_EN
	extern uchar xdata Eeprom_Write_Buffer[];
	extern uint rom_offset;
	extern uint Read_ROM_Offset(void);
	extern void Eeprom_Init(void);
	extern void Eeprom_Erase_Page(void);
	extern void NVR_Erase_Page(uchar nvr);	
	extern bit Eeprom_Write_Byte(uchar page,uint addr,uchar write_byte);
	extern bit Eeprom_Write_NBytes(uchar page,uint addr,uchar *write_data,uint length);
	extern uchar Eeprom_Read_Byte(uchar page,uint Byte_N);
	extern uchar NVR_Read_Byte(uchar nvr,uint Byte_N);
	extern bit NVR_Write_Byte(uchar nvr,uint addr,uchar write_byte);
#endif
	
#endif