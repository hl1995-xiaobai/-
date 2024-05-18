#include ".\CTK_Library\Config.h"
		
	#if (EEPROM_EN == 1)
		#pragma message "����,EEPROM����"
		
		#if EEPROM_FRAME_RW
			bit Eep_Erase_Flag = 0;
			bit Eep_Erase_EN = 1;
			bit Eep_First_Check = 0;
			uchar xdata Eeprom_Fram_Write_Buffer[EEPROM_DATA_LEN] = {0};
			uchar xdata Eeprom_Fram_Read_Buffer[EEPROM_FRAM_LEN] = {0};
			bit Eeprom_Erase_Page_Chcek(void);
			bit Eeprom_Frame_Write(uchar page,uchar *p_eep_data);
			bit Eeprom_Frame_Read(uchar page,uchar *p_read_eep_data);
		#endif
			
		
		
		#if EEPROM_FRAME_RW
		//-----------------------------------------------------------------//
		//�������ƣ� bit Eeprom_Erase_Page_Chcek(void)
		//�������ܣ� Eepromҳ����,��Eep_Erase_EN == 1ʱ�����������
		//��������� ��
		//��������� ��
		//�� �� ֵ�� 1:��ʾ�����ɹ�; 0����ʾ�������ɹ�
		//-----------------------------------------------------------------//
		bit Eeprom_Erase_Page_Chcek(void)
		{
				uint i = 0;
				if(Eep_First_Check == 0)
				{
					Eep_First_Check = 1;
					if(Eeprom_Frame_Read(0,Eeprom_Fram_Read_Buffer) == 0)//��һ���ϵ�У������
					{
							Eep_Erase_EN = 0;
							Eep_Erase_Flag = 1;
					}
				}
				if(Eep_Erase_EN == 1)
				{
										
					Eeprom_Erase_Page();
					
					Eep_Erase_Flag = 1;
					Eep_Erase_EN = 0;
					
					EA = 0;//�����жϣ�
					for (i= 0; i < 1024;i++)
					{
							if(Eeprom_Read_Byte(0,i)!= 0xFF)
							{
								Eep_Erase_Flag = 0;

								break;
							}
					}
					EA = 1;//�����ж�
				
				}

				return Eep_Erase_Flag;
		}
		
		//-----------------------------------------------------------------//
		//�������ƣ� bit Eeprom_Frame_Write(uchar page,uchar *p_eep_data)
		//�������ܣ� Eeprom֡д����
		//��������� uchar rank��ѡ��Ҫд���ҳ��uchar *p_eep_data:֡д�������ָ��;
		//��������� ��
		//�� �� ֵ�� 0:д�ɹ���1��дʧ�ܣ�
		//-----------------------------------------------------------------//
		
		bit Eeprom_Frame_Write(uchar page,uchar *p_eep_data)
		{	
				uint i = 0;
				uint j = 0;
				uchar check_sum = 0;
				uchar check1 = 0;
				uchar check2 = 0;
				uchar end = 0;
				
				for (i = 0; i < (1024/EEPROM_FRAM_LEN); i++)
				{
					check1 = Eeprom_Read_Byte(page,((i+1)*EEPROM_FRAM_LEN - 3));
					check2 = Eeprom_Read_Byte(page,((i+1)*EEPROM_FRAM_LEN - 2));
					end = Eeprom_Read_Byte(page,((i+1)*EEPROM_FRAM_LEN - 1));
					
					if((check1 != ~check2) && (end != 0XAE))//����δд��֡��ַ������֡д��
					{
							check_sum = 0;
							for(j = (i*EEPROM_FRAM_LEN);j < ((i+1)*EEPROM_FRAM_LEN-3);j++)
							{
									check_sum += *(p_eep_data + (j-(i*EEPROM_FRAM_LEN)));
									Eeprom_Write_Byte(page,j,*(p_eep_data + (j-(i*EEPROM_FRAM_LEN))));
							}
							
							Eeprom_Write_Byte(page,((i+1)*EEPROM_FRAM_LEN-3),check_sum);
							Eeprom_Write_Byte(page,((i+1)*EEPROM_FRAM_LEN-2),~check_sum);
							Eeprom_Write_Byte(page,((i+1)*EEPROM_FRAM_LEN-1),0xAE);
							
							for(j = (i*EEPROM_FRAM_LEN);j < ((i+1)*EEPROM_FRAM_LEN-3);j++)//��У��
							{
									check_sum += Eeprom_Read_Byte(page,j);
							}
							check1 = Eeprom_Read_Byte(page,((i+1)*EEPROM_FRAM_LEN - 3));
							check2 = Eeprom_Read_Byte(page,((i+1)*EEPROM_FRAM_LEN - 2));
							end = Eeprom_Read_Byte(page,((i+1)*EEPROM_FRAM_LEN - 1));
							if((check1 == ~check2) && (end == 0XAE))
							{
									return 0;//��У��OK
							}
							else
							{
									return 1;//��У��Fail
							}
					}
					if(i == ((1024/EEPROM_FRAM_LEN-1)))
					{
						Eep_Erase_EN = 1;
						Eeprom_Erase_Page();
						check_sum = 0;
						for(j = (0*EEPROM_FRAM_LEN);j < ((0+1)*EEPROM_FRAM_LEN-3);j++)
						{
								check_sum += *(p_eep_data + (j-(0*EEPROM_FRAM_LEN)));
								Eeprom_Write_Byte(page,j,*(p_eep_data + (j-(0*EEPROM_FRAM_LEN))));
						}
						
						Eeprom_Write_Byte(page,((0+1)*EEPROM_FRAM_LEN-3),check_sum);
						Eeprom_Write_Byte(page,((0+1)*EEPROM_FRAM_LEN-2),~check_sum);
						Eeprom_Write_Byte(page,((0+1)*EEPROM_FRAM_LEN-1),0xAE);
					}
				}
				return 0;
		}
		
		//-----------------------------------------------------------------//
		//�������ƣ� bit Eeprom_Frame_Read(uchar page,uchar *p_read_eep_data)
		//�������ܣ� Eeprom֡������,�������д���֡����
		//��������� uchar rank��ѡ��Ҫ����ҳ��uchar *p_read_eep_data:֡��������ָ�룻
		//��������� ��
		//�� �� ֵ�� 0:֡������У��OK��1��֡������У��Fail��
		//-----------------------------------------------------------------//
		
		bit Eeprom_Frame_Read(uchar page,uchar *p_read_eep_data)
		{	
				uint i = 0;
				uint j = 0;
				uchar check_sum = 0;
				uchar check1 = 0;
				uchar check2 = 0;
				uchar end = 0;
				for (i = 0; i < (1024/EEPROM_FRAM_LEN); i++)
				{
					check1 = Eeprom_Read_Byte(page,((i+1)*EEPROM_FRAM_LEN - 3));
					check2 = Eeprom_Read_Byte(page,((i+1)*EEPROM_FRAM_LEN - 2));
					end = Eeprom_Read_Byte(page,((i+1)*EEPROM_FRAM_LEN - 1));
					
					if((check1 != ~check2) && (end != 0XAE))
					{
							check_sum = 0;
							if(i != 0)
							{
								for(j = ((i-1)*EEPROM_FRAM_LEN);j < ((i)*EEPROM_FRAM_LEN);j++)
								{
										*(p_read_eep_data + (j-((i-1)*EEPROM_FRAM_LEN))) = Eeprom_Read_Byte(page,j);
										check_sum += *(p_read_eep_data + (j-((i-1)*EEPROM_FRAM_LEN)));
								}
								if(((*(p_read_eep_data + (EEPROM_FRAM_LEN-3))) == ~(*(p_read_eep_data + (EEPROM_FRAM_LEN-2)))) && ((*(p_read_eep_data + (EEPROM_FRAM_LEN-1))) == 0XAE))
								{
										return 0;//��У��OK
								}
								else
								{
										return 1;//��У��Fail
								}
							}
							else
							{
								for(j = 0;j < (EEPROM_FRAM_LEN);j++)
								{
										*(p_read_eep_data + j) = Eeprom_Read_Byte(page,j);
										check_sum += *(p_read_eep_data + j);
								}
								if(((*(p_read_eep_data + (EEPROM_FRAM_LEN-3))) = ~(*(p_read_eep_data + (EEPROM_FRAM_LEN-2)))) && ((*(p_read_eep_data + (EEPROM_FRAM_LEN-1))) != 0XAE))
								{
										return 0;//��У��OK
								}
								else
								{
										
										return 1;//��У��Fail
								}
							}
					}
					
					if(i == ((1024/EEPROM_FRAM_LEN-1)))
					{
							Eep_Erase_EN = 1;
						
							for(j = ((i-1)*EEPROM_FRAM_LEN);j < ((i)*EEPROM_FRAM_LEN);j++)
							{
									*(p_read_eep_data + (j-((i-1)*EEPROM_FRAM_LEN))) = Eeprom_Read_Byte(page,j);
									check_sum += *(p_read_eep_data + (j-((i-1)*EEPROM_FRAM_LEN)));
							}
							if(((*(p_read_eep_data + (EEPROM_FRAM_LEN-3))) == ~(*(p_read_eep_data + (EEPROM_FRAM_LEN-2)))) && ((*(p_read_eep_data + (EEPROM_FRAM_LEN-1))) == 0XAE))
							{
								
									return 0;//��У��OK
							}
							else
							{
									return 1;//��У��Fail
							}
					}
				}
				
				return 0;
		}
		#endif
		
#endif
