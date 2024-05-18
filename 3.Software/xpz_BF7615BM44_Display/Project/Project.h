#ifndef __PROJECT_H__
#define __PROJECT_H__

/**********************PA口**********************/

#define SET_PA0_IO_IN TRISA |= 0x01
#define SET_PA1_IO_IN TRISA |= 0x02
#define SET_PA2_IO_IN TRISA |= 0x04
#define SET_PA3_IO_IN TRISA |= 0x08

#define SET_PA0_IO_OUT TRISA &= ~0x01
#define SET_PA1_IO_OUT TRISA &= ~0x02
#define SET_PA2_IO_OUT TRISA &= ~0x04
#define SET_PA3_IO_OUT TRISA &= ~0x08

#define SET_PA0_L DATAA &= ~0x01
#define SET_PA1_L DATAA &= ~0x02
#define SET_PA2_L DATAA &= ~0x04
#define SET_PA3_L DATAA &= ~0x08

#define SET_PA0_H DATAA |= 0x01
#define SET_PA1_H DATAA |= 0x02
#define SET_PA2_H DATAA |= 0x04
#define SET_PA3_H DATAA |= 0x08

#define GET_PA0 (DATAA&0x01)
#define GET_PA1 (DATAA&0x02)
#define GET_PA2 (DATAA&0x04)
#define GET_PA3 (DATAA&0x08)

#define SET_PA0_PU_ON REG_ADDR = 0x17;REG_DATA |= 0x01
#define SET_PA1_PU_ON REG_ADDR = 0x17;REG_DATA |= 0x02
#define SET_PA2_PU_ON REG_ADDR = 0x17;REG_DATA |= 0x04
#define SET_PA3_PU_ON REG_ADDR = 0x17;REG_DATA |= 0x08

#define SET_PA0_PU_OFF REG_ADDR = 0x17;REG_DATA &= ~0x01
#define SET_PA1_PU_OFF REG_ADDR = 0x17;REG_DATA &= ~0x02
#define SET_PA2_PU_OFF REG_ADDR = 0x17;REG_DATA &= ~0x04
#define SET_PA3_PU_OFF REG_ADDR = 0x17;REG_DATA &= ~0x08

/**********************PA口**********************/

/**********************PB口**********************/

#define SET_PB0_IO_IN TRISB |= 0x01
#define SET_PB1_IO_IN TRISB |= 0x02
#define SET_PB2_IO_IN TRISB |= 0x04
#define SET_PB3_IO_IN TRISB |= 0x08
#define SET_PB4_IO_IN TRISB |= 0x10
#define SET_PB5_IO_IN TRISB |= 0x20
#define SET_PB6_IO_IN TRISB |= 0x40
#define SET_PB7_IO_IN TRISB |= 0x80

#define SET_PB0_IO_OUT TRISB &= ~0x01
#define SET_PB1_IO_OUT TRISB &= ~0x02
#define SET_PB2_IO_OUT TRISB &= ~0x04
#define SET_PB3_IO_OUT TRISB &= ~0x08
#define SET_PB4_IO_OUT TRISB &= ~0x10
#define SET_PB5_IO_OUT TRISB &= ~0x20
#define SET_PB6_IO_OUT TRISB &= ~0x40
#define SET_PB7_IO_OUT TRISB &= ~0x80

#define SET_PB0_L DATAB &= ~0x01
#define SET_PB1_L DATAB &= ~0x02
#define SET_PB2_L DATAB &= ~0x04
#define SET_PB3_L DATAB &= ~0x08
#define SET_PB4_L DATAB &= ~0x10
#define SET_PB5_L DATAB &= ~0x20
#define SET_PB6_L DATAB &= ~0x40
#define SET_PB7_L DATAB &= ~0x80

#define SET_PB0_H DATAB |= 0x01
#define SET_PB1_H DATAB |= 0x02
#define SET_PB2_H DATAB |= 0x04
#define SET_PB3_H DATAB |= 0x08
#define SET_PB4_H DATAB |= 0x10
#define SET_PB5_H DATAB |= 0x20
#define SET_PB6_H DATAB |= 0x40
#define SET_PB7_H DATAB |= 0x80

#define GET_PB0 (DATAB&0x01)
#define GET_PB1 (DATAB&0x02)
#define GET_PB2 (DATAB&0x04)
#define GET_PB3 (DATAB&0x08)
#define GET_PB4 (DATAB&0x10)
#define GET_PB5 (DATAB&0x20)
#define GET_PB6 (DATAB&0x40)
#define GET_PB7 (DATAB&0x80)

#define SET_PB0_PU_ON REG_ADDR = 0x18;REG_DATA |= 0x01
#define SET_PB1_PU_ON REG_ADDR = 0x18;REG_DATA |= 0x02
#define SET_PB2_PU_ON REG_ADDR = 0x18;REG_DATA |= 0x04
#define SET_PB3_PU_ON REG_ADDR = 0x18;REG_DATA |= 0x08
#define SET_PB4_PU_ON REG_ADDR = 0x18;REG_DATA |= 0x10
#define SET_PB5_PU_ON REG_ADDR = 0x18;REG_DATA |= 0x20
#define SET_PB6_PU_ON REG_ADDR = 0x18;REG_DATA |= 0x40
#define SET_PB7_PU_ON REG_ADDR = 0x18;REG_DATA |= 0x80

#define SET_PB0_PU_OFF REG_ADDR = 0x18;REG_DATA &= ~0x01
#define SET_PB1_PU_OFF REG_ADDR = 0x18;REG_DATA &= ~0x02
#define SET_PB2_PU_OFF REG_ADDR = 0x18;REG_DATA &= ~0x04
#define SET_PB3_PU_OFF REG_ADDR = 0x18;REG_DATA &= ~0x08
#define SET_PB4_PU_OFF REG_ADDR = 0x18;REG_DATA &= ~0x10
#define SET_PB5_PU_OFF REG_ADDR = 0x18;REG_DATA &= ~0x20
#define SET_PB6_PU_OFF REG_ADDR = 0x18;REG_DATA &= ~0x40
#define SET_PB7_PU_OFF REG_ADDR = 0x18;REG_DATA &= ~0x80

/**********************PB口**********************/

/**********************PC口**********************/

#define SET_PC0_IO_IN TRISC |= 0x01
#define SET_PC1_IO_IN TRISC |= 0x02
#define SET_PC2_IO_IN TRISC |= 0x04
#define SET_PC3_IO_IN TRISC |= 0x08
#define SET_PC4_IO_IN TRISC |= 0x10
#define SET_PC5_IO_IN TRISC |= 0x20
#define SET_PC6_IO_IN TRISC |= 0x40
#define SET_PC7_IO_IN TRISC |= 0x80

#define SET_PC0_IO_OUT TRISC &= ~0x01
#define SET_PC1_IO_OUT TRISC &= ~0x02
#define SET_PC2_IO_OUT TRISC &= ~0x04
#define SET_PC3_IO_OUT TRISC &= ~0x08
#define SET_PC4_IO_OUT TRISC &= ~0x10
#define SET_PC5_IO_OUT TRISC &= ~0x20
#define SET_PC6_IO_OUT TRISC &= ~0x40
#define SET_PC7_IO_OUT TRISC &= ~0x80

#define SET_PC0_L DATAC &= ~0x01
#define SET_PC1_L DATAC &= ~0x02
#define SET_PC2_L DATAC &= ~0x04
#define SET_PC3_L DATAC &= ~0x08
#define SET_PC4_L DATAC &= ~0x10
#define SET_PC5_L DATAC &= ~0x20
#define SET_PC6_L DATAC &= ~0x40
#define SET_PC7_L DATAC &= ~0x80

#define SET_PC0_H DATAC |= 0x01
#define SET_PC1_H DATAC |= 0x02
#define SET_PC2_H DATAC |= 0x04
#define SET_PC3_H DATAC |= 0x08
#define SET_PC4_H DATAC |= 0x10
#define SET_PC5_H DATAC |= 0x20
#define SET_PC6_H DATAC |= 0x40
#define SET_PC7_H DATAC |= 0x80

#define GET_PC0 (DATAC&0x01)
#define GET_PC1 (DATAC&0x02)
#define GET_PC2 (DATAC&0x04)
#define GET_PC3 (DATAC&0x08)
#define GET_PC4 (DATAC&0x10)
#define GET_PC5 (DATAC&0x20)
#define GET_PC6 (DATAC&0x40)
#define GET_PC7 (DATAC&0x80)

#define SET_PC0_PU_ON REG_ADDR = 0x19;REG_DATA |= 0x01
#define SET_PC1_PU_ON REG_ADDR = 0x19;REG_DATA |= 0x02
#define SET_PC2_PU_ON REG_ADDR = 0x19;REG_DATA |= 0x04
#define SET_PC3_PU_ON REG_ADDR = 0x19;REG_DATA |= 0x08
#define SET_PC4_PU_ON REG_ADDR = 0x19;REG_DATA |= 0x10
#define SET_PC5_PU_ON REG_ADDR = 0x19;REG_DATA |= 0x20
#define SET_PC6_PU_ON REG_ADDR = 0x19;REG_DATA |= 0x40
#define SET_PC7_PU_ON REG_ADDR = 0x19;REG_DATA |= 0x80

#define SET_PC0_PU_OFF REG_ADDR = 0x19;REG_DATA &= ~0x01
#define SET_PC1_PU_OFF REG_ADDR = 0x19;REG_DATA &= ~0x02
#define SET_PC2_PU_OFF REG_ADDR = 0x19;REG_DATA &= ~0x04
#define SET_PC3_PU_OFF REG_ADDR = 0x19;REG_DATA &= ~0x08
#define SET_PC4_PU_OFF REG_ADDR = 0x19;REG_DATA &= ~0x10
#define SET_PC5_PU_OFF REG_ADDR = 0x19;REG_DATA &= ~0x20
#define SET_PC6_PU_OFF REG_ADDR = 0x19;REG_DATA &= ~0x40
#define SET_PC7_PU_OFF REG_ADDR = 0x19;REG_DATA &= ~0x80


#define SET_PC4_OD_ON REG_ADDR = 0x25;REG_DATA |= 0x01
#define SET_PC5_OD_ON REG_ADDR = 0x25;REG_DATA |= 0x02

#define SET_PC4_OD_OFF REG_ADDR = 0x25;REG_DATA &= ~0x01
#define SET_PC5_OD_OFF REG_ADDR = 0x25;REG_DATA &= ~0x02

/**********************PC口**********************/

/**********************PE口*********************/

#define SET_PE0_IO_IN TRISE |= 0x01
#define SET_PE1_IO_IN TRISE |= 0x02
#define SET_PE2_IO_IN TRISE |= 0x04
#define SET_PE3_IO_IN TRISE |= 0x08
#define SET_PE4_IO_IN TRISE |= 0x10
#define SET_PE5_IO_IN TRISE |= 0x20
#define SET_PE6_IO_IN TRISE |= 0x40
#define SET_PE7_IO_IN TRISE |= 0x80

#define SET_PE0_IO_OUT TRISE &= ~0x01
#define SET_PE1_IO_OUT TRISE &= ~0x02
#define SET_PE2_IO_OUT TRISE &= ~0x04
#define SET_PE3_IO_OUT TRISE &= ~0x08
#define SET_PE4_IO_OUT TRISE &= ~0x10
#define SET_PE5_IO_OUT TRISE &= ~0x20
#define SET_PE6_IO_OUT TRISE &= ~0x40
#define SET_PE7_IO_OUT TRISE &= ~0x80

#define SET_PE0_L DATAE &= ~0x01
#define SET_PE1_L DATAE &= ~0x02
#define SET_PE2_L DATAE &= ~0x04
#define SET_PE3_L DATAE &= ~0x08
#define SET_PE4_L DATAE &= ~0x10
#define SET_PE5_L DATAE &= ~0x20
#define SET_PE6_L DATAE &= ~0x40
#define SET_PE7_L DATAE &= ~0x80

#define SET_PE0_H DATAE |= 0x01
#define SET_PE1_H DATAE |= 0x02
#define SET_PE2_H DATAE |= 0x04
#define SET_PE3_H DATAE |= 0x08
#define SET_PE4_H DATAE |= 0x10
#define SET_PE5_H DATAE |= 0x20
#define SET_PE6_H DATAE |= 0x40
#define SET_PE7_H DATAE |= 0x80

#define GET_PE0 (DATAE&0x01)
#define GET_PE1 (DATAE&0x02)
#define GET_PE2 (DATAE&0x04)
#define GET_PE3 (DATAE&0x08)
#define GET_PE4 (DATAE&0x10)
#define GET_PE5 (DATAE&0x20)
#define GET_PE6 (DATAE&0x40)
#define GET_PE7 (DATAE&0x80)

#define SET_PE0_PU_ON REG_ADDR = 0x1B;REG_DATA |= 0x01
#define SET_PE1_PU_ON REG_ADDR = 0x1B;REG_DATA |= 0x02
#define SET_PE2_PU_ON REG_ADDR = 0x1B;REG_DATA |= 0x04
#define SET_PE3_PU_ON REG_ADDR = 0x1B;REG_DATA |= 0x08
#define SET_PE4_PU_ON REG_ADDR = 0x1B;REG_DATA |= 0x10
#define SET_PE5_PU_ON REG_ADDR = 0x1B;REG_DATA |= 0x20
#define SET_PE6_PU_ON REG_ADDR = 0x1B;REG_DATA |= 0x40
#define SET_PE7_PU_ON REG_ADDR = 0x1B;REG_DATA |= 0x80

#define SET_PE0_PU_OFF REG_ADDR = 0x1B;REG_DATA &= ~0x01
#define SET_PE1_PU_OFF REG_ADDR = 0x1B;REG_DATA &= ~0x02
#define SET_PE2_PU_OFF REG_ADDR = 0x1B;REG_DATA &= ~0x04
#define SET_PE3_PU_OFF REG_ADDR = 0x1B;REG_DATA &= ~0x08
#define SET_PE4_PU_OFF REG_ADDR = 0x1B;REG_DATA &= ~0x10
#define SET_PE5_PU_OFF REG_ADDR = 0x1B;REG_DATA &= ~0x20
#define SET_PE6_PU_OFF REG_ADDR = 0x1B;REG_DATA &= ~0x40
#define SET_PE7_PU_OFF REG_ADDR = 0x1B;REG_DATA &= ~0x80

#define SET_PE4_OD_ON REG_ADDR  = 0x25;REG_DATA |= 0x04
#define SET_PE5_OD_ON REG_ADDR  = 0x25;REG_DATA |= 0x08

#define SET_PE4_OD_OFF REG_ADDR = 0x25;REG_DATA &= ~0x04
#define SET_PE5_OD_OFF REG_ADDR = 0x25;REG_DATA &= ~0x08

/**********************PE口**********************/

/**********************PF口*********************/

#define SET_PF0_IO_IN TRISF |= 0x01
#define SET_PF1_IO_IN TRISF |= 0x02
#define SET_PF2_IO_IN TRISF |= 0x04
#define SET_PF3_IO_IN TRISF |= 0x08
#define SET_PF4_IO_IN TRISF |= 0x10
#define SET_PF5_IO_IN TRISF |= 0x20
#define SET_PF6_IO_IN TRISF |= 0x40
#define SET_PF7_IO_IN TRISF |= 0x80

#define SET_PF0_IO_OUT TRISF &= ~0x01
#define SET_PF1_IO_OUT TRISF &= ~0x02
#define SET_PF2_IO_OUT TRISF &= ~0x04
#define SET_PF3_IO_OUT TRISF &= ~0x08
#define SET_PF4_IO_OUT TRISF &= ~0x10
#define SET_PF5_IO_OUT TRISF &= ~0x20
#define SET_PF6_IO_OUT TRISF &= ~0x40
#define SET_PF7_IO_OUT TRISF &= ~0x80

#define SET_PF0_L DATAF &= ~0x01
#define SET_PF1_L DATAF &= ~0x02
#define SET_PF2_L DATAF &= ~0x04
#define SET_PF3_L DATAF &= ~0x08
#define SET_PF4_L DATAF &= ~0x10
#define SET_PF5_L DATAF &= ~0x20
#define SET_PF6_L DATAF &= ~0x40
#define SET_PF7_L DATAF &= ~0x80

#define SET_PF0_H DATAF |= 0x01
#define SET_PF1_H DATAF |= 0x02
#define SET_PF2_H DATAF |= 0x04
#define SET_PF3_H DATAF |= 0x08
#define SET_PF4_H DATAF |= 0x10
#define SET_PF5_H DATAF |= 0x20
#define SET_PF6_H DATAF |= 0x40
#define SET_PF7_H DATAF |= 0x80

#define GET_PF0 (DATAF&0x01)
#define GET_PF1 (DATAF&0x02)
#define GET_PF2 (DATAF&0x04)
#define GET_PF3 (DATAF&0x08)
#define GET_PF4 (DATAF&0x10)
#define GET_PF5 (DATAF&0x20)
#define GET_PF6 (DATAF&0x40)
#define GET_PF7 (DATAF&0x80)

#define SET_PF0_PU_ON REG_ADDR = 0x1C;REG_DATA |= 0x01
#define SET_PF1_PU_ON REG_ADDR = 0x1C;REG_DATA |= 0x02
#define SET_PF2_PU_ON REG_ADDR = 0x1C;REG_DATA |= 0x04
#define SET_PF3_PU_ON REG_ADDR = 0x1C;REG_DATA |= 0x08
#define SET_PF4_PU_ON REG_ADDR = 0x1C;REG_DATA |= 0x10
#define SET_PF5_PU_ON REG_ADDR = 0x1C;REG_DATA |= 0x20
#define SET_PF6_PU_ON REG_ADDR = 0x1C;REG_DATA |= 0x40
#define SET_PF7_PU_ON REG_ADDR = 0x1C;REG_DATA |= 0x80

#define SET_PF0_PU_OFF REG_ADDR = 0x1C;REG_DATA &= ~0x01
#define SET_PF1_PU_OFF REG_ADDR = 0x1C;REG_DATA &= ~0x02
#define SET_PF2_PU_OFF REG_ADDR = 0x1C;REG_DATA &= ~0x04
#define SET_PF3_PU_OFF REG_ADDR = 0x1C;REG_DATA &= ~0x08
#define SET_PF4_PU_OFF REG_ADDR = 0x1C;REG_DATA &= ~0x10
#define SET_PF5_PU_OFF REG_ADDR = 0x1C;REG_DATA &= ~0x20
#define SET_PF6_PU_OFF REG_ADDR = 0x1C;REG_DATA &= ~0x40
#define SET_PF7_PU_OFF REG_ADDR = 0x1C;REG_DATA &= ~0x80

/**********************PF口**********************/

/**********************PG口*********************/

#define SET_PG0_IO_IN TRISG |= 0x01
#define SET_PG1_IO_IN TRISG |= 0x02
#define SET_PG2_IO_IN TRISG |= 0x04
#define SET_PG3_IO_IN TRISG |= 0x08

#define SET_PG0_IO_OUT TRISG &= ~0x01
#define SET_PG1_IO_OUT TRISG &= ~0x02
#define SET_PG2_IO_OUT TRISG &= ~0x04
#define SET_PG3_IO_OUT TRISG &= ~0x08


#define SET_PG0_L DATAG &= ~0x01
#define SET_PG1_L DATAG &= ~0x02
#define SET_PG2_L DATAG &= ~0x04
#define SET_PG3_L DATAG &= ~0x08


#define SET_PG0_H DATAG |= 0x01
#define SET_PG1_H DATAG |= 0x02
#define SET_PG2_H DATAG |= 0x04
#define SET_PG3_H DATAG |= 0x08


#define GET_PG0 (DATAG&0x01)
#define GET_PG1 (DATAG&0x02)
#define GET_PG2 (DATAG&0x04)
#define GET_PG3 (DATAG&0x08)


#define SET_PG0_PU_ON REG_ADDR = 0x1D;REG_DATA |= 0x01
#define SET_PG1_PU_ON REG_ADDR = 0x1D;REG_DATA |= 0x02
#define SET_PG2_PU_ON REG_ADDR = 0x1D;REG_DATA |= 0x04
#define SET_PG3_PU_ON REG_ADDR = 0x1D;REG_DATA |= 0x08


#define SET_PG0_PU_OFF REG_ADDR = 0x1D;REG_DATA &= ~0x01
#define SET_PG1_PU_OFF REG_ADDR = 0x1D;REG_DATA &= ~0x02
#define SET_PG2_PU_OFF REG_ADDR = 0x1D;REG_DATA &= ~0x04
#define SET_PG3_PU_OFF REG_ADDR = 0x1D;REG_DATA &= ~0x08


/**********************PG口**********************/

/**********************PH口*********************/

#define SET_PH0_IO_IN TRISH |= 0x01
#define SET_PH1_IO_IN TRISH |= 0x02
#define SET_PH2_IO_IN TRISH |= 0x04
#define SET_PH3_IO_IN TRISH |= 0x08
#define SET_PH4_IO_IN TRISH |= 0x10
#define SET_PH5_IO_IN TRISH |= 0x20
#define SET_PH6_IO_IN TRISH |= 0x40
#define SET_PH7_IO_IN TRISH |= 0x80


#define SET_PH0_IO_OUT TRISH &= ~0x01
#define SET_PH1_IO_OUT TRISH &= ~0x02
#define SET_PH2_IO_OUT TRISH &= ~0x04
#define SET_PH3_IO_OUT TRISH &= ~0x08
#define SET_PH4_IO_OUT TRISH &= ~0x10
#define SET_PH5_IO_OUT TRISH &= ~0x20
#define SET_PH6_IO_OUT TRISH &= ~0x40
#define SET_PH7_IO_OUT TRISH &= ~0x80

#define SET_PH0_L DATAH &= ~0x01
#define SET_PH1_L DATAH &= ~0x02
#define SET_PH2_L DATAH &= ~0x04
#define SET_PH3_L DATAH &= ~0x08
#define SET_PH4_L DATAH &= ~0x10
#define SET_PH5_L DATAH &= ~0x20
#define SET_PH6_L DATAH &= ~0x40
#define SET_PH7_L DATAH &= ~0x80

#define SET_PH0_H DATAH |= 0x01
#define SET_PH1_H DATAH |= 0x02
#define SET_PH2_H DATAH |= 0x04
#define SET_PH3_H DATAH |= 0x08
#define SET_PH4_H DATAH |= 0x10
#define SET_PH5_H DATAH |= 0x20
#define SET_PH6_H DATAH |= 0x40
#define SET_PH7_H DATAH |= 0x80

#define GET_PH0 (DATAH&0x01)
#define GET_PH1 (DATAH&0x02)
#define GET_PH2 (DATAH&0x04)
#define GET_PH3 (DATAH&0x08)
#define GET_PH4 (DATAH&0x10)
#define GET_PH5 (DATAH&0x20)
#define GET_PH6 (DATAH&0x40)
#define GET_PH7 (DATAH&0x80)

#define SET_PH0_PU_ON REG_ADDR = 0x1E;REG_DATA |= 0x01
#define SET_PH1_PU_ON REG_ADDR = 0x1E;REG_DATA |= 0x02
#define SET_PH2_PU_ON REG_ADDR = 0x1E;REG_DATA |= 0x04
#define SET_PH3_PU_ON REG_ADDR = 0x1E;REG_DATA |= 0x08
#define SET_PH4_PU_ON REG_ADDR = 0x1E;REG_DATA |= 0x10
#define SET_PH5_PU_ON REG_ADDR = 0x1E;REG_DATA |= 0x20
#define SET_PH6_PU_ON REG_ADDR = 0x1E;REG_DATA |= 0x40
#define SET_PH7_PU_ON REG_ADDR = 0x1E;REG_DATA |= 0x80

#define SET_PH0_PU_OFF REG_ADDR = 0x1E;REG_DATA &= ~0x01
#define SET_PH1_PU_OFF REG_ADDR = 0x1E;REG_DATA &= ~0x02
#define SET_PH2_PU_OFF REG_ADDR = 0x1E;REG_DATA &= ~0x04
#define SET_PH3_PU_OFF REG_ADDR = 0x1E;REG_DATA &= ~0x08
#define SET_PH4_PU_OFF REG_ADDR = 0x1E;REG_DATA &= ~0x10
#define SET_PH5_PU_OFF REG_ADDR = 0x1E;REG_DATA &= ~0x20
#define SET_PH6_PU_OFF REG_ADDR = 0x1E;REG_DATA &= ~0x40
#define SET_PH7_PU_OFF REG_ADDR = 0x1E;REG_DATA &= ~0x80

/**********************PH口**********************/


//IO口翻转
#define TRUN_PA0 PA0 = ~PA0
#define TRUN_PA1 PA1 = ~PA1
#define TRUN_PA2 PA2 = ~PA2
#define TRUN_PA3 PA3 = ~PA3

#define TRUN_PB0 PB0 = ~PB0
#define TRUN_PB1 PB1 = ~PB1
#define TRUN_PB2 PB2 = ~PB2
#define TRUN_PB3 PB3 = ~PB3
#define TRUN_PB4 PB4 = ~PB4
#define TRUN_PB5 PB5 = ~PB5
#define TRUN_PB6 PB6 = ~PB6
#define TRUN_PB7 PB7 = ~PB7

#define TRUN_PC0 PC0 = ~PC0
#define TRUN_PC1 PC1 = ~PC1
#define TRUN_PC2 PC2 = ~PC2
#define TRUN_PC3 PC3 = ~PC3
#define TRUN_PC4 PC4 = ~PC4
#define TRUN_PC5 PC5 = ~PC5
#define TRUN_PC6 PC6 = ~PC6
#define TRUN_PC7 PC7 = ~PC7


#define TRUN_PE0 PE0 = ~PE0
#define TRUN_PE1 PE1 = ~PE1
#define TRUN_PE2 PE2 = ~PE2
#define TRUN_PE3 PE3 = ~PE3
#define TRUN_PE4 PE4 = ~PE4
#define TRUN_PE5 PE5 = ~PE5
#define TRUN_PE6 PE6 = ~PE6
#define TRUN_PE7 PE7 = ~PE7


#define TRUN_PF4 PF4 = ~PF4
#define TRUN_PF5 PF5 = ~PF5
#define TRUN_PF6 PF6 = ~PF6
#define TRUN_PF7 PF7 = ~PF7

#define TRUN_PG0 PG0 = ~PG0
#define TRUN_PG1 PG1 = ~PG1
#define TRUN_PG2 PG2 = ~PG2
#define TRUN_PG3 PG3 = ~PG3


#define TRUN_PH0 PH0 = ~PH0
#define TRUN_PH1 PH1 = ~PH1
#define TRUN_PH2 PH2 = ~PH2
#define TRUN_PH3 PH3 = ~PH3
#define TRUN_PH4 PH4 = ~PH4
#define TRUN_PH5 PH5 = ~PH5
#define TRUN_PH6 PH6 = ~PH6
#define TRUN_PH7 PH7 = ~PH7

	extern bit IsTouch;
	extern uchar xdata Key_Data;
	extern void Project(void);
#endif