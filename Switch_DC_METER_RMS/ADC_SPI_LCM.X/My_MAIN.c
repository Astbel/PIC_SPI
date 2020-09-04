/*
 * File:   newmainXC16.c
 * Author: zackchen1110
 *
 * Created on 2020?7?23?, ?? 9:29
 */
/*2020/7/24 updata with mupliti send data,updata with adc read and also interrupt level for spi and adc
 * LEVEL for ADC and SPI shows here
 * ADC level 7 
 * SPI level 6
 */
/*2020/7/28 redine the output port for the LCM test 
 * LATA -RA1     -DATA
 * LATB -RB10    -CLK
 * LATC -RC1     -CS
 */
/*7/30 updata with clr sram mapping for inital
button using
switch_LAT     RA4
switch_ANSEL
switch_TRIS
 */

/*2020/9/2 code for switch button
*/
#include "config.h"
#include "Dspic_GPIO.h"
#include "libpic30.h"  //here is for using delay function
/*this file is set for the SPI _IO for dspic*/
#include "xc.h"
/*include user function here*/
#include "Restart_GPIO_SPI.h"
#include "ADC_lcm_table.h" 
#include "LCM_TABLE.h"
#include "LCM_COUNTER_7GATE.h"

//2020/9/1 user updata for button error check vaule
unsigned char button_check;

void IO_Initial(void);
 /*Test for LCM_light a cycle  to show all image using variable*/
 /*function of user define in main*/ 
int main(void)
{
    /*calling osc funcition to change init*/
    OSC_Init();
    IO_Initial(); //inital IO & ADC & external 
    /*inital spi port*/
    /*CS*/
     ADC_init();
     //CALLING TIMER1 AND GIE
     /*test io port for adc function at RA9 */
     TRISCbits.TRISC1=0;/*set as output loading data check probe for adc*/
     /*Timer inital*/
     Init_Timer1();
     /*calling external inital*/
     INTCON2bits.GIE=1; //GOBAL FLAG
     /*INITAL DATA SEND HERE*/
     LCM_Init();  /*LCM inital*/ 
     //inital user key
     Key=0;
     /*here test with close bit by bit*/


          while(1)
     {   
              
         /*User test SPI & 7 gate*/
//        CS_LAT=0;
//        sentdata(0x5,0x2,0x1,10);
//        CS_LAT=1;
//        __delay_ms(1);
//              
//        CS_LAT=0;
//        sentdata(0x5,0x3,0x1,10);
//        CS_LAT=1;
//        __delay_ms(1);
            
     if (!switch_PORT)  //check if button if it was close
     {
     ADC_SPI();      
     }
     else
     {
       CLR_RAM_DATA(); //clear up the meter,disable the meter
       switch_PORT=0;  //reset switch flag
     }
   }
}
 
//IO initail for system progress
void IO_Initial(void)
{
//Chip select inital
      CS_LAT   =1;
//     CS_ANSEL =0;
     CS_TRIS  =0;
     
 /*SPI CLK inital*/
    CLK_LAT   =0;   
//    CLK_ANSEL =0;
    CLK_TRIS  =0;
    
/*SPI DATA inital*/
     Data_LAT   =0;
//     Data_ANSEL =0;   
     Data_TRIS  =0;  
     
     /*ADC IO & inital setting*/
     //IO port is RA1
     ADCREAD_LAT    =0;
     ADCREAD_ANSEL  =1; 
     ADCREAD_TRIS   =1; 
     
     //switch button inital
     switch_LAT     =0;
     switch_ANSEL   =0;
     switch_TRIS    =1;
     switch_PORT    =0;
     //external obserase point inital
     Excheck_LAT    =0;
     Excheck_TRIS   =0;  //set as output
     
}

