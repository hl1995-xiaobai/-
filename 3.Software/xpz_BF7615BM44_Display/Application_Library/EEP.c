#include ".\CTK_Library\Config.h"
		
	#if (EEPROM_EN == 1)
		#pragma message "编译,EEPROM功能"
		
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
		//函数名称： bit Eeprom_Erase_Page_Chcek(void)
		//函数功能： Eeprom页擦除,当Eep_Erase_EN == 1时，才允许擦除
		//输入参数： 无
		//输出参数： 无
		//返 回 值： 1:表示擦除成功; 0：表示擦除不成功
		//-----------------------------------------------------------------//
		bit Eeprom_Erase_Page_Chcek(void)
		{
				uint i = 0;
				if(Eep_First_Check == 0)
				{
					Eep_First_Check = 1;
					if(Eeprom_Frame_Read(0,Eeprom_Fram_Read_Buffer) == 0)//第一次上电校验数据
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
					
					EA = 0;//关总中断；
					for (i= 0; i < 1024;i++)
					{
							if(Eeprom_Read_Byte(0,i)!= 0xFF)
							{
								Eep_Erase_Flag = 0;

								break;
							}
					}
					EA = 1;//开总中断
				
				}

				return Eep_Erase_Flag;
		}
		
		//-----------------------------------------------------------------//
		//函数名称： bit Eeprom_Frame_Write(uchar page,uchar *p_eep_data)
		//函数功能： Eeprom帧写数据
		//输入参数： uchar rank：选择将要写入的页；uchar *p_eep_data:帧写入的数据指针;
		//输出参数： 无
		//返 回 值： 0:写成功；1：写失败；
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
					
					if((check1 != ~check2) && (end != 0XAE))//查找未写的帧地址，按照帧写入
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
							
							for(j = (i*EEPROM_FRAM_LEN);j < ((i+1)*EEPROM_FRAM_LEN-3);j++)//读校验
							{
									check_sum += Eeprom_Read_Byte(page,j);
							}
							check1 = Eeprom_Read_Byte(page,((i+1)*EEPROM_FRAM_LEN - 3));
							check2 = Eeprom_Read_Byte(page,((i+1)*EEPROM_FRAM_LEN - 2));
							end = Eeprom_Read_Byte(page,((i+1)*EEPROM_FRAM_LEN - 1));
							if((check1 == ~check2) && (end == 0XAE))
							{
									return 0;//读校验OK
							}
							else
							{
									return 1;//读校验Fail
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
		//函数名称： bit Eeprom_Frame_Read(uchar page,uchar *p_read_eep_data)
		//函数功能： Eeprom帧读数据,查找最后写入的帧数据
		//输入参数： uchar rank：选择将要读的页；uchar *p_read_eep_data:帧读的数据指针；
		//输出参数： 无
		//返 回 值： 0:帧读数据校验OK；1：帧读数据校验Fail；
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
										return 0;//读校验OK
								}
								else
								{
										return 1;//读校验Fail
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
										return 0;//读校验OK
								}
								else
								{
										
										return 1;//读校验Fail
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
								
									return 0;//读校验OK
							}
							else
							{
									return 1;//读校验Fail
							}
					}
				}
				
				return 0;
		}
		#endif
		
#endif
