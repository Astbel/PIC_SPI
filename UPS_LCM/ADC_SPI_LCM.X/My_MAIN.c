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
#include "libpic30.h"  
#include "xc.h"
#include "Restart_GPIO_SPI.h"
#include "ADC_lcm_table.h" 
#include "LCM_TABLE.h"
#include "UPS_STATUS.h"

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
//    ups_variable_status(); //inital variable status


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
     /*here test with close bit by bit*/

     //2020/9/3 point for using at ups status
     ups_point=5;

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
     
     DC_Meter();   // reading the status of the ups
     AC_Meter();   //display AC meter


     UPS_calcute();//calcute the average of the ups status
     UPS_STATUS(UPS_MOVING_AVG); //selecting showing mode for ups
      //Mode for Battery Bar select
     Ups_Bat_Mode();            
     ups_Bat_Bar_Left(Ups_Bat_Status);
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
//   CS_ANSEL =0;
     CS_TRIS  =0;
     
 /*SPI CLK inital*/
    CLK_LAT   =0;   
//  CLK_ANSEL =0;
    CLK_TRIS  =0;
    
/*SPI DATA inital*/
     Data_LAT   =0;
//   Data_ANSEL =0;   
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

//inital status for error work
void ups_variable_status(void)
{
//STEP1_Restart_GPIO_SPI_Variable inital
unsigned  int   reg=0;            //reg   for  user send data 
unsigned  char   n=0;             //inital for the n vaule FOR LOOP use
unsigned  char   i=0;
unsigned  char   endsend=0;       //lastbit flag
unsigned  char   clk_control=0;   //clk crontol flag
unsigned  char  CLKOK=0;           //send data start flag 1sent 0end      
unsigned  char   testpoint=0;      
unsigned  char   CLK_count=0;        // For Clk step count 
unsigned  char   sendbit=0;          //

//STEP2 ADC_LCM_TABLE inital
unsigned char AC_POINT=0;
unsigned char Sample_count=0;
double AC_sum=0;
unsigned int ADCValue=0;      //adc hex register
float result=0;        //Register for adc vaule

//STEP3 LCM_TABLE inital
unsigned char COM_REG_1=0;
unsigned char COM_REG_2=0;

//STEP4 UPS_STATUS
unsigned char ups_mode=0;
unsigned char UPS_MOVING_AVG=0; //variable using in switch case to select mode
unsigned char ups_point=0;
unsigned char Ups_Bat_Status=0;

}