/*2020/8/12 change data type for ADCValue and result*/
/*2020/8/27 user update external interrupt*/



/*here include file */
#include "config.h"
#include "Dspic_GPIO.h"
#include <libpic30.h>
#include <xc.h>
#include "ADC_lcm_table.h"
#include "Restart_GPIO_SPI.h"
#include "LCM_TABLE.h"
#include  <math.h>
#include  <stdlib.h>

/*user define variable*/
unsigned int    ADCValue=0;  //16bit type
float           result=0;    //16bit type
//Numbers of AC points
unsigned char   AC_POINT=100;
unsigned int    AC_INDEX[100]={};
unsigned char   Sample_count;
double          AC_sum =0;
/*here ADC setting as Auto sample conversion*/
/*here start adc inital user define port*/
void ADC_init(void)
{
    //IO for analog AN1,Dspic dont have PCFG 
    ANSELAbits.ANSA1=1;//set RA1 as analog
    TRISAbits.TRISA1=1;//set RA1 as analog    
    /*AD1CON1 REG select*/   
    AD1CON1bits.ADON    =0; //disable for setting ADC
    AD1CON1bits.ADSIDL  =0; //continue operate when system idel
    AD1CON1bits.ASAM    =1; //Sampling begins when SAMP bit is set
    AD1CON1bits.AD12B   =0; //10bit but only use channel 0 to test now
    AD1CON1bits.FORM    =0; //output adc vaule is interger
    AD1CON1bits.ADDMABM =0;// DMA buffers written in order of conversion
    AD1CON1bits.SSRCG   =0;  //Sample Clock Source Group bit
    AD1CON1bits.SSRC    =7;   //Sample Clock Source Select bits  (Manual mode)
     //AD1CON2 register setting
    AD1CON2bits.BUFM    =0;   //only use sinagl buff
    AD1CON2bits.CSCNA   =0;   //dont scan input
    AD1CON2bits.SMPI    =0;	 // ISR after N Sample/Convert
    AD1CON2bits.ALTS    =0;   //only use MUXA
    AD1CON2bits.CHPS    =0;   // only using channel 0 for now 
    AD1CON2bits.VCFG    =0;  //Select for the adc voltage ref for Avdd & Avss
     //auto adc smplie if AD1 SRCG=7 SSRCG=0 then enable to use 
    AD1CON3bits.ADRC    =1;       //clock from system clock
    AD1CON3bits.ADCS    =5;      //ADC conversion time
    AD1CON3bits.SAMC    =31;     //at manual sample this dont count
    //analog channel select
    AD1CHS0bits.CH0NA   =0; //Channel 0 negative input is VREFL
    AD1CHS0bits.CH0SA   =1; //select RA1 for analog 
    //scan AN1 
    AD1CSSL    = 0x0000;            // dont scan
    AD1CON1bits.ADON    = 1;  //now enable analog bit  
}
/*ADC_Vaule read transfrom here*/

/*ADC read need an IO port to transfar the adc vaule*/
unsigned int ADC_read(void)
{
    /*here is sample the adc manual mode */
    while(!AD1CON1bits.DONE);  //waitting for convert
     //hex conversion goes to register  in dspic ADBUF is unsigned short need to convert otherwise the value is wrong
    ADCValue=ADC1BUF0;         
   //result = (float)((60*(float) ADCValue) / 1023.0 );
//2020/8/27 updata AC source
    result = (float)(((60*(float) ADCValue) / 1023.0));
    //16bit dspic convert want to cost the data lost last switch the data to 32bit
    //set 5000 is the Vref Vsource the SIC is mV so 5V*1000
    return (result);
}
/*adc to spi function*/
void DC_Meter(void)
{  
    ADC_read();  //transfer adc hex vaule to number
    //loading adc vaule
    ADC_Transfer_SPI();
    //here go with switch case select how to light up lcm 7 gate 
    
    LCM_TABLE0(ADC_Vaules.vaule0);  //Interger type  vaule0 tens showing
    
    LCM_TABLE1(ADC_Vaules.vaule1);  //Interger type  vaule1 interger showing
    
    LCM_TABLE2(ADC_Vaules.vaule2); //floating type   vaule2 floating showing
    __delay_us(10000000);          //this delay time  is for the fast floating number
   
}


//2020/8/27 AC Meter

//Saving up for reticfer of the ac power
void AC_Meter_Index(void)
{
    for ( Sample_count = 0; Sample_count < AC_POINT; Sample_count++)
    {
        AC_INDEX[Sample_count]=result;
    }
}


//2020/8/27 rms calculus for ac power
unsigned int RMS_calculus(void)
{
    for (Sample_count = 0; Sample_count < AC_POINT; Sample_count++)
    {
        AC_sum +=pow( AC_INDEX[Sample_count],2);
    }
        return sqrt(AC_sum / AC_POINT);
}

//2020/9/4 AC output for lcd
void AC_Meter(void)
{
    LCM_TABLE3(ADC_Vaules.vaule3);  //Interger type  vaule0 tens showing
    
    LCM_TABLE4(ADC_Vaules.vaule4);  //Interger type  vaule1 interger showing
    
    LCM_TABLE5(ADC_Vaules.vaule5); //floating type   vaule2 floating showing
}