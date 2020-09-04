#ifndef LCM_TABLE_H
#define LCM_TABLE_H
#include <math.h>
/*User variable*/
extern unsigned char mode_count;

// seven gate register
extern unsigned char COM_REG_1;
extern unsigned char COM_REG_2;
//8/5 extern struct struct
 typedef struct ADC_SPI_READ   //define a type names as ASV , and name this struct as ADC_SPI_READ
 {
    unsigned int vaule0;   //Register for saving adc smaple  tens
    unsigned int vaule1;   // Register for saving adc sample interger 
    unsigned int vaule2;   // Register for saving adc sample floating
    unsigned char COM_REG_1;//COM1_REG
    unsigned char COM_REG_2;//COM2_REG
    unsigned char select_mode; //select mode
 
}ASV;

extern ASV ADC_Vaules;//this is for struct to return



// extern ADC_SPI_READ ADC_transfer;

 extern ASV ADC_Transfer_SPI(void);
//8/4 updata function with struct and lcm table


//first 7 gate
 extern void LCM_TABLE0(unsigned char select_mode);
//second 7gate
  extern void LCM_TABLE1(unsigned char select_mode);
 //third 7gate
 extern void LCM_TABLE2(unsigned char select_mode);

 
#endif