
/*LCM define table for calling in adc reulst switch case*/
/*2020/7/30 array for LCM SEG & COM*/
/*2020/7/31 define seven gate parameter gate2 gate3*/
/*2020/8/3 user updata with adc conver to spi*/

/*User include here*/
#include "config.h"
#include "Dspic_GPIO.h"
#include "libpic30.h"
#include "Restart_GPIO_SPI.h"
#include "ADC_lcm_table.h" 
#include "LCM_TABLE.h"
#include  <math.h>

/*here define for variable for ADC transfer to spi */
//typedef struct ADC_SPI_Vaule{
//    unsigned char vaule1;   // vaule for adc return 
//    unsigned char vaule2;   // vaule for adc return
//}ADC_SPI_READ;
//
//ADC_SPI_READ ADC_transfer;
//SEG
//SEG define from lcm labels using calling icon
unsigned char SEG_Array[28]={0x0,0x1,0x2,0x3,0x4,0x5,0x6,0x7,0x8,0x9,0xA,0xB,0xC,0xD,0xE,0xF,0x10,0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18,0x19,0x1A,0x1B};

//here define for com select of using binary 8 4 2 1 0b0000 for this slotion
//8 is com1
//4 is com2
//2 is com3
//1 is com4
//this hex define here is declare for ones a time using both coms port
//0xC is com1+com2 
//0xA is com1+com3
//0x9 is com1+com4
//0x6 is com2+com3
//0x5 is com2+com4
//0x3 is com3+com4
//0xE is com1+com2+com3 
//0xD is com1+com2+com4
//0xB is com1+com3+com4
//0x7 is com2+com3+com4
//0xF is com1+com2+com3+com4
//COM define array here
unsigned char COM_Array[15]={0x8,0x4,0x2,0x1,0xC,0xA,0x9,0x6,0x5,0x3,0xE,0xD,0xB,0x7,0xF};

ADC_SPI_READ ADC_transfer;
/*2020/8/4 adc vaule transfer to spi function*/
ADC_SPI_READ ADC_Transfer_SPI(void)
{
    unsigned char point_vaule;
    /*result is the adc register here first get this vaule*/
    ADC_transfer.vaule1=ceil(result); //get last vaule from adc
    ADC_transfer.vaule1=(ADC_transfer.vaule1)*10;
    point_vaule=(result)*10;
    ADC_transfer.vaule2=(point_vaule-ADC_transfer.vaule1);
    return(ADC_transfer);
}

/*ADC_vaule read from here*/
ADC_SPI_READ LCM_TABLE(unsigned char select_mode)
{
    switch(select_mode)
    {    /*SEG & COM*/  
       case 0: //parameter
        ADC_transfer.COM_REG_1=COM_Array[13];
        ADC_transfer.COM_REG_2=COM_Array[11];   
        break;
       case 1: //parameter
        ADC_transfer.COM_REG_1=COM_Array[15];/*0*/
        ADC_transfer.COM_REG_2=COM_Array[6];   
        break;
       case 2: //parameter
        ADC_transfer.COM_REG_1=COM_Array[14];
        ADC_transfer.COM_REG_2=COM_Array[5];     
        break;
       case 3: //parameter
        ADC_transfer.COM_REG_1=COM_Array[9];
        ADC_transfer.COM_REG_2=COM_Array[11];     
        break;
       case 4: //parameter
        ADC_transfer.COM_REG_1=COM_Array[5];
        ADC_transfer.COM_REG_2=COM_Array[8];     
        break;
       case 5: //parameter
        ADC_transfer.COM_REG_1=COM_Array[12];
        ADC_transfer.COM_REG_2=COM_Array[6];     
        break;
       case 6: //parameter
        ADC_transfer.COM_REG_1=COM_Array[15];
        ADC_transfer.COM_REG_2=COM_Array[6];     
        break;
       case 7: //parameter
        ADC_transfer.COM_REG_1=COM_Array[1];
        ADC_transfer.COM_REG_2=COM_Array[11];     
        break;
       case 8: //parameter
        ADC_transfer.COM_REG_1=COM_Array[15];
        ADC_transfer.COM_REG_2=COM_Array[11];     
        break;
       case 9: //parameter
        ADC_transfer.COM_REG_1=COM_Array[12];
        ADC_transfer.COM_REG_2=COM_Array[11];     
        break;
       default: //defulat setting
        ADC_transfer.COM_REG_1=COM_Array[13];
        ADC_transfer.COM_REG_2=COM_Array[11];     
        break;
    }
    return(ADC_transfer);
}
//
ADC_SPI_READ LCM_TABLE2(unsigned char select_mode)
{
    switch(select_mode)
    {    /*SEG & COM*/  
       case 0: //parameter
        ADC_transfer.COM_REG_1=COM_Array[13];
        ADC_transfer.COM_REG_2=COM_Array[11];   
        break;
       case 1: //parameter
        ADC_transfer.COM_REG_1=COM_Array[15];/*0*/
        ADC_transfer.COM_REG_2=COM_Array[6];   
        break;
       case 2: //parameter
        ADC_transfer.COM_REG_1=COM_Array[14];
        ADC_transfer.COM_REG_2=COM_Array[5];     
        break;
       case 3: //parameter
        ADC_transfer.COM_REG_1=COM_Array[9];
        ADC_transfer.COM_REG_2=COM_Array[11];     
        break;
       case 4: //parameter
        ADC_transfer.COM_REG_1=COM_Array[5];
        ADC_transfer.COM_REG_2=COM_Array[8];     
        break;
       case 5: //parameter
        ADC_transfer.COM_REG_1=COM_Array[12];
        ADC_transfer.COM_REG_2=COM_Array[6];     
        break;
       case 6: //parameter
        ADC_transfer.COM_REG_1=COM_Array[15];
        ADC_transfer.COM_REG_2=COM_Array[6];     
        break;
       case 7: //parameter
        ADC_transfer.COM_REG_1=COM_Array[1];
        ADC_transfer.COM_REG_2=COM_Array[11];     
        break;
       case 8: //parameter
        ADC_transfer.COM_REG_1=COM_Array[15];
        ADC_transfer.COM_REG_2=COM_Array[11];     
        break;
       case 9: //parameter
        ADC_transfer.COM_REG_1=COM_Array[12];
        ADC_transfer.COM_REG_2=COM_Array[11];     
        break;
       default: //defulat setting
        ADC_transfer.COM_REG_1=COM_Array[13];
        ADC_transfer.COM_REG_2=COM_Array[11];     
        break;
    }
    return(ADC_transfer);
}