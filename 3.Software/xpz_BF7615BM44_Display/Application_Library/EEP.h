
#define EEPROM_FRAME_RW 							1//EEP֡��д�� 1:ʹ�ܱ��룬0:��ʹ�ܱ���
#define EEPROM_DATA_LEN								61//1��5��13��29��61��125�����ֽڳ��ȣ�֡����Ϊ EEPROM_DATA_LEN + 3(У����1��У����2��������)
#define EEPROM_FRAM_LEN (EEPROM_DATA_LEN+3)

#define EEPROM_ERASE_TIMER_SET(x)  		{SPROG_TIM &= (~0x1F);SPROG_TIM |= (0x1F&x);}//����ʱ��ѡ��
#define EEPROM_WRITE_TIMER_SET()  		{SPROG_TIM &= (~0xE0);SPROG_TIM |= (0xE0);}//�ֽ�дʱ��ѡ��

#if EEPROM_FRAME_RW
	extern bit Eep_Erase_Flag;
	extern bit Eep_Erase_EN;
	extern bit Eep_First_Check;
	extern bit Eeprom_Erase_Page_Chcek(void);
	extern bit Eeprom_Frame_Write(uchar page,uchar *p_eep_data);
	extern bit Eeprom_Frame_Read(uchar page,uchar *p_read_eep_data);
#endif

extern uchar xdata Eeprom_Fram_Write_Buffer[];
extern uchar xdata Eeprom_Fram_Read_Buffer[];


	
