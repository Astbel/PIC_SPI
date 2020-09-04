
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
#include "LCM_COUNTER_7GATE.h"
#include  <math.h>
#include  <stdlib.h>

/*here define for variable for ADC transfer to spi */
//ADC_SPI_READ ADC_transfer;
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

ASV ADC_Vaules;//this is for struct to return
/*2020/8/4 adc vaule transfer to spi function*/
ASV ADC_Transfer_SPI(void)
{
    result=result*10;
    /*result is the adc register here first get this vaule*/
    ADC_Vaules.vaule0=(result/100);                      //value1 saving ADC Integer part
    ADC_Vaules.vaule1=(result-(100*ADC_Vaules.vaule0))/10;     //value2 saving  ADC Floating part 
    ADC_Vaules.vaule2=(result-((10*ADC_Vaules.vaule1)+(100*ADC_Vaules.vaule0)));
    return (ADC_Vaules);                                //return all the struct vaule1 vaule2
}
/*LCM interger shows here Tens Interger float */

//Tens of the function
void LCM_TABLE0(unsigned char select_mode)
{
    switch(select_mode)
    {    /*SEG & COM*/  
       case 0: //parameter
        ADC_Vaules.COM_REG_1=COM_Array[12];
        ADC_Vaules.COM_REG_2=COM_Array[10];   
        break;
       case 1: //parameter
        ADC_Vaules.COM_REG_1=0x0;/*0*/
        ADC_Vaules.COM_REG_2=COM_Array[7];   
        break;
       case 2: //parameter
        ADC_Vaules.COM_REG_1=COM_Array[13];
        ADC_Vaules.COM_REG_2=COM_Array[4];     
        break;
       case 3: //parameter
        ADC_Vaules.COM_REG_1=COM_Array[8];
        ADC_Vaules.COM_REG_2=COM_Array[10];     
        break;
       case 4: //parameter
        ADC_Vaules.COM_REG_1=COM_Array[4];
        ADC_Vaules.COM_REG_2=COM_Array[7];     
        break;
       case 5: //parameter
        ADC_Vaules.COM_REG_1=COM_Array[11];
        ADC_Vaules.COM_REG_2=COM_Array[5];     
        break;
       case 6: //parameter
        ADC_Vaules.COM_REG_1=COM_Array[14];
        ADC_Vaules.COM_REG_2=COM_Array[5];     
        break;
       case 7: //parameter
        ADC_Vaules.COM_REG_1=COM_Array[0];
        ADC_Vaules.COM_REG_2=COM_Array[10];     
        break;
       case 8: //parameter
        ADC_Vaules.COM_REG_1=COM_Array[14];
        ADC_Vaules.COM_REG_2=COM_Array[10];     
        break;
       case 9: //parameter
        ADC_Vaules.COM_REG_1=COM_Array[4];
        ADC_Vaules.COM_REG_2=COM_Array[10];     
        break;
       default: //defulat setting
        ADC_Vaules.COM_REG_1=0x0;
        ADC_Vaules.COM_REG_2=0x0;   
        break;
    }
    CS_LAT=0;
    sentdata(0x5,0x0,ADC_Vaules.COM_REG_1,10);       
    CS_LAT=1;
    __delay_ms(1);
    
    CS_LAT=0;
    sentdata(0x5,0x1,ADC_Vaules.COM_REG_2,10);       
    CS_LAT=1;
    __delay_ms(1);   
}
//Interger showing
void LCM_TABLE1(unsigned char select_mode)
{
    switch(select_mode)
    {    /*SEG & COM*/  
       case 0: //parameter
        ADC_Vaules.COM_REG_1=COM_Array[12];
        ADC_Vaules.COM_REG_2=COM_Array[14];   
        break;
       case 1: //parameter
        ADC_Vaules.COM_REG_1=0x0;/*0*/
        ADC_Vaules.COM_REG_2=COM_Array[13];   
        break;
       case 2: //parameter
        ADC_Vaules.COM_REG_1=COM_Array[13];
        ADC_Vaules.COM_REG_2=COM_Array[11];     
        break;
       case 3: //parameter
        ADC_Vaules.COM_REG_1=COM_Array[8];
        ADC_Vaules.COM_REG_2=COM_Array[14];     
        break;
       case 4: //parameter
        ADC_Vaules.COM_REG_1=COM_Array[4];
        ADC_Vaules.COM_REG_2=COM_Array[13];     
        break;
       case 5: //parameter
        ADC_Vaules.COM_REG_1=COM_Array[11];
        ADC_Vaules.COM_REG_2=COM_Array[12];     
        break;
       case 6: //parameter
        ADC_Vaules.COM_REG_1=COM_Array[14];
        ADC_Vaules.COM_REG_2=COM_Array[12];     
        break;
       case 7: //parameter
        ADC_Vaules.COM_REG_1=COM_Array[0];
        ADC_Vaules.COM_REG_2=COM_Array[14];     
        break;
       case 8: //parameter
        ADC_Vaules.COM_REG_1=COM_Array[14];
        ADC_Vaules.COM_REG_2=COM_Array[14];     
        break;
       case 9: //parameter
        ADC_Vaules.COM_REG_1=COM_Array[11];
        ADC_Vaules.COM_REG_2=COM_Array[14];     
        break;
       default: //defulat setting
        ADC_Vaules.COM_REG_1=0x0;
        ADC_Vaules.COM_REG_2=0x0;   
        break;
    }
    CS_LAT=0;
    sentdata(0x5,0x2,ADC_Vaules.COM_REG_1,10);       
    CS_LAT=1;
    __delay_ms(1);
    
    CS_LAT=0;
    sentdata(0x5,0x3,ADC_Vaules.COM_REG_2,10);       
    CS_LAT=1;
    __delay_ms(1);   
}

//Floating showing here
void LCM_TABLE2(unsigned char select_mode)
{
    switch(select_mode)
    {    /*SEG & COM*/  
       case 0: //parameter
        ADC_Vaules.COM_REG_1=COM_Array[12];
        ADC_Vaules.COM_REG_2=COM_Array[10];   
        break;
       case 1: //parameter
        ADC_Vaules.COM_REG_1=0x0;/*0*/
        ADC_Vaules.COM_REG_2=COM_Array[7];   
        break;
       case 2: //parameter
        ADC_Vaules.COM_REG_1=COM_Array[13];
        ADC_Vaules.COM_REG_2=COM_Array[4];     
        break;
       case 3: //parameter
        ADC_Vaules.COM_REG_1=COM_Array[8];
        ADC_Vaules.COM_REG_2=COM_Array[10];     
        break;
       case 4: //parameter
        ADC_Vaules.COM_REG_1=COM_Array[4];
        ADC_Vaules.COM_REG_2=COM_Array[7];     
        break;
       case 5: //parameter
        ADC_Vaules.COM_REG_1=COM_Array[11];
        ADC_Vaules.COM_REG_2=COM_Array[5];     
        break;
       case 6: //parameter
        ADC_Vaules.COM_REG_1=COM_Array[14];
        ADC_Vaules.COM_REG_2=COM_Array[5];     
        break;
       case 7: //parameter
        ADC_Vaules.COM_REG_1=COM_Array[0];
        ADC_Vaules.COM_REG_2=COM_Array[10];     
        break;
       case 8: //parameter
        ADC_Vaules.COM_REG_1=COM_Array[14];
        ADC_Vaules.COM_REG_2=COM_Array[10];     
        break;
       case 9: //parameter
        ADC_Vaules.COM_REG_1=COM_Array[11];
        ADC_Vaules.COM_REG_2=COM_Array[10];     
        break;
       default: //defulat setting
        ADC_Vaules.COM_REG_1=0x0;
        ADC_Vaules.COM_REG_2=0x0;     
        break;
    }
     CS_LAT=0;
    sentdata(0x5,0x4,ADC_Vaules.COM_REG_1,10);       
    CS_LAT=1;
    __delay_ms(1);
    
    CS_LAT=0;
    sentdata(0x5,0x5,ADC_Vaules.COM_REG_2,10);       
    CS_LAT=1;
    __delay_ms(1);
}