#include ".\BF7615BMXX_XXXX_Library\Config.h"
		
	#if (EEPROM_EN == 1)
		#pragma message "����,EEPROM����"
		uchar xdata Eeprom_Write_Buffer[10] = {0};
		uint rom_offset = 0;
		void Eeprom_Init(void);
		void Eeprom_Erase_Page(void);
		bit Eeprom_Write_Byte(uchar page,uint addr,uchar write_byte);
		bit Eeprom_Write_NBytes(uchar page,uint addr,uchar *write_data,uint length);
		uchar Eeprom_Read_Byte(uchar page,uint Byte_N);
		void NVR_Erase_Page(uchar nvr);
		
		/****************************************************************/
		//��������uint Read_ROM_Offset(void)
		//��  �ܣ���ȡCODEƫ�Ƶ�ַ
		//��  ������
		//����ֵ��uint,CFG_BOOT_SEL = 0ʱ,����0x800;CFG_BOOT_SEL = 1ʱ,����0x1000;
		//CFG_BOOT_SEL = 2ʱ,����0x2000;CFG_BOOT_SEL = 3ʱ,����0x0000;
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
		//�������ƣ� void Eeprom_Init(void)
		//�������ܣ� Eeprom_Init��дʱ���ʼ��
		//��������� ��
		//��������� ��
		//�� �� ֵ�� ��
		//-----------------------------------------------------------------//
		void Eeprom_Init(void)
		{
			EEP_SEL(0);//ѡ��EEP
			EEPROM_ERASE_TIMER_SET(4);//EEP_SELECT=0ʱ������ʱ��ѡ��(0~9):1ms~10ms(����1ms)+0.13ms,>9:9.13ms��EEP_SELECT=1ʱ������ʱ��ѡ��(0~9):0.5ms~5ms(����1ms)+0.0652ms,>9:4.5652ms���Ƽ�5ms
			EEPROM_WRITE_TIMER_SET();//�ֽ�дʱ��ѡ��(23.5)us
			rom_offset = Read_ROM_Offset();
		}
		
		//-----------------------------------------------------------------//
		//�������ƣ� void Eeprom_Erase_Page(void)
		//�������ܣ� Eepromҳ����
		//��������� ��
		//��������� ��
		//�� �� ֵ�� ��
		//-----------------------------------------------------------------//
		void Eeprom_Erase_Page(void)
		{
			#ifdef IICS_EN
				#if IICS_EN
					IICCON &= ~0x01;//IIC����ʹ�ܹر�
				#endif
			#endif
			
			#ifdef TRACEMODE
				#if TRACEMODE
					IICCON &= ~0x01;//IIC����ʹ�ܹر�
				#endif
			#endif
			EA = 0;//�����жϣ�
			EEP_SEL(0);//ѡ��EEP
			SPROG_ADDR_L = 0x00;
			SPROG_ADDR_H = 0x00;
			SPROG_ADDR_H &= ~(0x7C);//ѡ��Ҫд��ҳ
			SPROG_CMD = 0x96;
			_nop_();
			_nop_();
			_nop_();
			_nop_();
			SPROG_ADDR_L = 0x00;
			SPROG_ADDR_H = 0x00;
			#ifdef IICS_EN
				#if IICS_EN
					IICCON |= 0x01;//IIC����ʹ�ܹر�
				#endif
			#endif
			
			#ifdef TRACEMODE
				#if TRACEMODE
					IICCON |= 0x01;//IIC����ʹ�ܹر�
				#endif
			#endif
			EA = 1;//�����ж�
		}
		
		//-----------------------------------------------------------------//
		//�������ƣ� void NVR_Erase_Page(uchar nvr)
		//�������ܣ� NVR_Erase_Page����,uchar nvr:3/4ѡ��Ҫ������NVR:3/4��ӦNVR3/4
		//��������� ��
		//��������� ��
		//�� �� ֵ�� ��
		//-----------------------------------------------------------------//
		void NVR_Erase_Page(uchar nvr)
		{
			#ifdef IICS_EN
				#if IICS_EN
					IICCON &= ~0x01;//IIC����ʹ�ܹر�
				#endif
			#endif
			
			#ifdef TRACEMODE
				#if TRACEMODE
					IICCON &= ~0x01;//IIC����ʹ�ܹر�
				#endif
			#endif
			EA = 0;//�����жϣ�
			EEP_SEL(1);//ѡ��NVR
			EEPROM_ERASE_TIMER_SET(9);//EEP_SELECT=0ʱ������ʱ��ѡ��(0~9):1ms~10ms(����1ms)+0.13ms,>9:9.13ms��EEP_SELECT=1ʱ������ʱ��ѡ��(0~9):0.5ms~5ms(����1ms)+0.0652ms,>9:4.5652ms���Ƽ�5ms
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
					IICCON |= 0x01;//IIC����ʹ�ܹر�
				#endif
			#endif
			
			#ifdef TRACEMODE
				#if TRACEMODE
					IICCON |= 0x01;//IIC����ʹ�ܹر�
				#endif
			#endif
			EA = 1;//�����ж�
		}
		
	//-----------------------------------------------------------------//
	//�������ƣ� bit NVR_Write_Byte(uchar nvr,uint addr,uchar write_byte)
	//�������ܣ� NVRд����
	//��������� uchar nvr��ѡ��Ҫд���nvrҳ��uint addr:��ǰҳ��Ӧ�ĵ�ַ(0~511)��uchar write_byte����Ҫд�������;uchar write_time:д����ʱ��ѡ�񣺽���̶�Ϊ�̶�Ϊ23.5us
	//��������� ��
	//�� �� ֵ�� 0:д�ɹ���1��дʧ�ܣ�
	//-----------------------------------------------------------------//
	
		
		bit NVR_Write_Byte(uchar nvr,uint addr,uchar write_byte)
		{	
			uint i = 0;
			bit Write_OK = 0;
			#ifdef IICS_EN
				#if IICS_EN
					IICCON &= ~0x01;//IIC����ʹ�ܹر�
				#endif
			#endif
			
			#ifdef TRACEMODE
				#if TRACEMODE
					IICCON &= ~0x01;//IIC����ʹ�ܹر�
				#endif
			#endif
			EA = 0;//�����жϣ�
			EEP_SEL(1);//ѡ��NVR
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
			SPROG_ADDR_H |= (addr>>8)&0x03;//ѡ��Ҫ���ַ
			SPROG_DATA = write_byte;//׼��д�������
			SPROG_CMD = 0x69;
			_nop_();
			_nop_();
			_nop_();
			_nop_();
			SPROG_ADDR_L = 0x00;
			SPROG_ADDR_H = 0x00;
			#ifdef IICS_EN
				#if IICS_EN
					IICCON |= 0x01;//IIC����ʹ�ܹر�
				#endif
			#endif
			
			#ifdef TRACEMODE
				#if TRACEMODE
					IICCON |= 0x01;//IIC����ʹ�ܹر�
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
			
			EA = 1;//�����ж�
			return Write_OK;
				
		}

	//-----------------------------------------------------------------//
	//�������ƣ� bit Eeprom_Write_Byte(uchar page,uint addr,uchar write_byte)
	//�������ܣ� Eepromд����
	//��������� uchar page��ѡ��Ҫд���ҳ��uint addr:��ǰҳ��Ӧ�ĵ�ַ(0~1023)��uchar write_byte����Ҫд�������;uchar write_time:д����ʱ��ѡ�񣺽���̶�Ϊ23.5us
	//��������� ��
	//�� �� ֵ�� 0:д�ɹ���1��дʧ�ܣ�
	//-----------------------------------------------------------------//
	
		
		bit Eeprom_Write_Byte(uchar page,uint addr,uchar write_byte)
		{	
			uint i = 0;
			bit Write_OK = 0;
			#ifdef IICS_EN
				#if IICS_EN
					IICCON &= ~0x01;//IIC����ʹ�ܹر�
				#endif
			#endif
			
			#ifdef TRACEMODE
				#if TRACEMODE
					IICCON &= ~0x01;//IIC����ʹ�ܹر�
				#endif
			#endif
			EA = 0;//�����жϣ�
			SPROG_ADDR_L = 0x00;
			SPROG_ADDR_H = 0x00;
			SPROG_ADDR_H &= ~(0x7C);//ѡ��Ҫд��ҳ
			SPROG_ADDR_L = addr;
			SPROG_ADDR_H |= (addr>>8)&0x03;//ѡ��Ҫ���ַ
			SPROG_DATA = write_byte;//׼��д�������
			SPROG_CMD = 0x69;
			_nop_();
			_nop_();
			_nop_();
			_nop_();
			SPROG_ADDR_L = 0x00;
			SPROG_ADDR_H = 0x00;
			#ifdef IICS_EN
				#if IICS_EN
					IICCON |= 0x01;//IIC����ʹ�ܹر�
				#endif
			#endif
			
			#ifdef TRACEMODE
				#if TRACEMODE
					IICCON |= 0x01;//IIC����ʹ�ܹر�
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
			
			EA = 1;//�����ж�
			return Write_OK;
				
		}
		
		//-----------------------------------------------------------------//
		//�������ƣ� bit Eeprom_Write_NBytes(uchar page,uint addr,uchar *write_data,uint length)
		//�������ܣ� Eepromдlength Bytes����
		//��������� uchar rank��ѡ��Ҫд���ҳ��uint addr:��ǰҳ��Ӧ�ĵ�ַ(0~1023)��uchar *write_data��
		//��Ҫд�������;uint length(1~1024):�ӵ�ǰҳ��addr�ֽڿ�ʼд��length���ֽ�(length<= (1024-addr))��
		//��������� uchar nvr��ѡ��Ҫд���nvrҳ��uint addr:��ǰҳ��Ӧ�ĵ�ַ(0~511)��uchar write_byte����Ҫд�������;uchar write_time:д����ʱ��ѡ�񣺽���̶�Ϊ�̶�Ϊ23.5us
		//��������� ��
		//�� �� ֵ�� 0:д�ɹ���1��дʧ�ܣ�
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
		//�������ƣ� uchar Eeprom_Read_Byte(uchar page,uint Byte_N)
		//�������ܣ� Eeprom������
		//��������� uchar page��ѡ��Ҫ��ȡ��ҳ��uint Byte_N����ȡҳ�ĵ�Byte_N�ֽ�;
		//��������� ��
		//�� �� ֵ�� ���ض�ҳ�ĵ�Byte_N�ֽڵ����ݣ�
		//CFG_BOOT_SEL = 0 ʱ��ROM_OFFSETH/L = 0x0800�� 
		//CFG_BOOT_SEL = 1 ʱ��ROM_OFFSETH/L = 0x1000�� 
		//CFG_BOOT_SEL = 2 ʱ��ROM_OFFSETH/L = 0x2000,
		//CFG_BOOT_SEL = 3 ʱ��ROM_OFFSETH/L = 0x0000//��BOOT �������ܡ�
		//Ӧ��BOOT ����ʱ����������CODE ���Ծ��Ե�ַ�ķ��ʣ���Ҫ��ȥROM_OFFSET_H/L ��ƫ�Ƶ�ַ
		//��PC - ROM_OFFSET��,�ٶ�CODE �����Ե�ַ���з��ʡ�
		//-----------------------------------------------------------------//
		uchar Eeprom_Read_Byte(uchar page,uint Byte_N)
		{	
			uchar code *P_Rank;
			P_Rank = 0xFC00 - page*1024 - rom_offset; 
			return (*(P_Rank + Byte_N));	
		}
		
		//-----------------------------------------------------------------//
		//�������ƣ� uchar NVR_Read_Byte(uchar nvr,uint Byte_N)
		//�������ܣ� ��NVR����
		//��������� uchar nvr��3/4ѡ��Ҫ��ȡ��ҳ:NVR3/NVR4��uint Byte_N:0~511����ȡNVRҳ�ĵ�Byte_N�ֽ�;
		//��������� ��
		//�� �� ֵ�� ���ض�NVRҳ�ĵ�Byte_N�ֽڵ����ݣ�
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
