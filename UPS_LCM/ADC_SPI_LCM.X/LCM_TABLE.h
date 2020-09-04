#ifndef LCM_TABLE_H
#define LCM_TABLE_H
#include <math.h>
/*User variable*/
extern unsigned char mode_count;

//2020/9/4 user updata with AC meter struct vaule3,4,5

// seven gate register
extern unsigned char COM_REG_1;
extern unsigned char COM_REG_2;
//8/5 extern struct struct
 typedef struct ADC_SPI_READ   //define a type names as ASV , and name this struct as ADC_SPI_READ
 {
    //input side
    unsigned int vaule0;   //Register for saving adc smaple  tens
    unsigned int vaule1;   // Register for saving adc sample interger 
    unsigned int vaule2;   // Register for saving adc sample floating
    //output side
    unsigned int vaule3;   //Register for saving adc smaple  tens
    unsigned int vaule4;   // Register for saving adc sample interger 
    unsigned int vaule5;   // Register for saving adc sample floating

    unsigned char COM_REG_1;//COM1_REG
    unsigned char COM_REG_2;//COM2_REG
    unsigned char select_mode; //select mode
 
}ASV;

extern ASV ADC_Vaules;//this is for struct to return



// extern ADC_SPI_READ ADC_transfer;

 extern ASV ADC_Transfer_SPI(void);
//8/4 updata function with struct and lcm table


//User define for LCD seven gate part
extern void LCM_TABLE0(unsigned char select_mode);
extern void LCM_TABLE1(unsigned char select_mode);
extern void LCM_TABLE2(unsigned char select_mode);

//User define for LCD seven gate output
extern void LCM_TABLE3(unsigned char select_mode);
extern void LCM_TABLE4(unsigned char select_mode);
extern void LCM_TABLE5(unsigned char select_mode);

#endif