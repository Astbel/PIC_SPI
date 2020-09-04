//2020/9/3 LCM status for UPS updata with STATUS SELECT online mode & battery mode
//2020/9/4 


#include "config.h"
#include "Dspic_GPIO.h"
#include "libpic30.h"  
#include "xc.h"
#include "Restart_GPIO_SPI.h"
#include "ADC_lcm_table.h" 
#include "LCM_TABLE.h"
#include "UPS_STATUS.h"
//UPS define for battery bar at the lcd SEG and COM
/*
                SEG     COM     SEG     COM
100%   60V      0x1B    0xF     0x1A    0x8
 
75%    45V      0x1B    0xF     0x1A    0x0

50%    30V      0x1B    0xB     0x1A    0x0

25%    15V      0x1B    0x9     0x1A    0x0

0%      0V      0x1B    0x8     0x1A    0x0

*/

//variable from ups mode to select
//unsigned char ups_mode;
float  ups[5]={};   //Index for adc result saving in 
float  sum;         //sum the Moving Average for the adc result
unsigned char ups_array;    //for loop variable using in saving data to array
unsigned char ups_sum;      //sum all the array 
unsigned char ups_point;    //ups point for divde for the array vaule
unsigned char UPS_MOVING_AVG; //variable using in switch case to select mode
float   Ups_Bat_Bar;          //using at ups battery bar showing
unsigned char Ups_Bat_Status; //Battery Bar select mode variable     
//2020/9/3 unable refrash adc vaule status stop here


//UPS status caulcate form ADC result
unsigned int UPS_calcute(void)
{
     
    //lcd display status
   for ( ups_array = 0; ups_array < ups_point; ups_array++)
   {
       ups[ups_array]=result;   //updata array adc vaule to array
   }

   //2020/9/4 user updata divide 50 from the adc vaule of the reult is mutiple 10 so divde have to did the same thing
   //the result is form LCM_TABLE function result=result*10;
   sum=(ups[0]+ups[1]+ups[2]+ups[3]+ups[4])/50;// divde all the ad vaule and anayslis for the status
   
    //consider sum the vaule of the status of the ups
    if (sum >= 60)
    {
      UPS_MOVING_AVG    =1;   //define to switch case ONline mode
    }
    else
    {
       UPS_MOVING_AVG   =2;  //define to switch case battery mode
    }
    return(UPS_MOVING_AVG); //updata for UPS status 
}




//UPS STATUS ICON SHOW 
//Online Mode
void ups_online_mode(void)
{
    //right side of square
    CS_LAT=0;
    sentdata(0x5,0x14,0xF,10);
    CS_LAT=1;
    __delay_ms(1);

    //VAC show
    CS_LAT=0;
    sentdata(0x5,0x13,0x1,10);
    CS_LAT=1;
    __delay_ms(1);

    //icon AND 100% Battery bar
    CS_LAT=0;
    sentdata(0x5,0x15,0x5,10);
    CS_LAT=1;
    __delay_ms(1);


    //OTP & P1 & 
    CS_LAT=0;
    sentdata(0x5,0x16,0xF,10);
    CS_LAT=1;
    __delay_ms(1);

    //line group1
    CS_LAT=0;
    sentdata(0x5,0x17,0xc,10);
    CS_LAT=1;
    __delay_ms(1);

    //status below1: battery & line grounp2
    CS_LAT=0;
    sentdata(0x5,0x18,0xE,10);
    CS_LAT=1;
    __delay_ms(1);

    //status below2:input & sinwave & line group3
    CS_LAT=0;
    sentdata(0x5,0x19,0xD,10);
    CS_LAT=1;
    __delay_ms(1);

    //left side square and battery
    CS_LAT=0;
    sentdata(0x5,0x1A,0xA,10);
    CS_LAT=1;
    __delay_ms(1);

    //left side of square
    CS_LAT=0;
    sentdata(0x5,0x1B,0xF,10);
    CS_LAT=1;
    __delay_ms(1);
}

//Battery Mode
void ups_Battery_Mode(void)
{
    //Vac right icon show 
    CS_LAT=0;
    sentdata(0x5,0x13,0x1,10);
    CS_LAT=1;
    __delay_ms(1);

    //right square
    CS_LAT=0;
    sentdata(0x5,0x14,0xF,10);
    CS_LAT=1;
    __delay_ms(1);

    //icon & right top square
    CS_LAT=0;
    sentdata(0x5,0x15,0x5,10);
    CS_LAT=1;
    __delay_ms(1);

    //ups down status 1
    CS_LAT=0;
    sentdata(0x5,0x16,0xB,10);
    CS_LAT=1;
    __delay_ms(1);

    //ups down status 2  
    CS_LAT=0;
    sentdata(0x5,0x17,0xC,10);
    CS_LAT=1;
    __delay_ms(1);

    //ups down status 3
    CS_LAT=0;
    sentdata(0x5,0x18,0xA,10);
    CS_LAT=1;
    __delay_ms(1);

    //input incon show
    CS_LAT=0;
    sentdata(0x5,0x19,0x1,10);
    CS_LAT=1;
    __delay_ms(1);

    //left top square
    CS_LAT=0;
    sentdata(0x5,0x1A,0xA,10);
    CS_LAT=1;
    __delay_ms(1);

    //left square
    CS_LAT=0;
    sentdata(0x5,0x1B,0xF,10);
    CS_LAT=1;
    __delay_ms(1);

    //top seven gate square
    CS_LAT=0;
    sentdata(0x5,0xC,0x1,10);
    CS_LAT=1;
    __delay_ms(1);

    //clock icon and square show
    CS_LAT=0;
    sentdata(0x5,0x7,0xB,10);
    CS_LAT=1;
    __delay_ms(1);

}

    //UPS switch case 
void UPS_STATUS(unsigned char ups_mode)
{
    switch (ups_mode)
    {
    case 1:
        ups_online_mode();
        break;
    case 2:
        ups_Battery_Mode();        
        break;
    default:   //default mode still have to light up seven gate
        

        break;
    }
}

//function for define at ups battery bar 
//Range define by the Battery Bar
unsigned int Ups_Bat_Mode(void)
{
    Ups_Bat_Bar=result/10;  //ref check divde to get battery bar showing
    //next consider for the bat_bar to  going to ups_Bat_Bar 
    if (Ups_Bat_Bar>=60)        
    {
        Ups_Bat_Status=0;
    }
    else if (Ups_Bat_Bar>=45)
    {
        Ups_Bat_Status=1;
    }
    else if (Ups_Bat_Bar>=30)
    {
        Ups_Bat_Status=2;
    }
    else if (Ups_Bat_Bar>=15)
    {
        Ups_Bat_Status=3;
    }
    else
    {
       Ups_Bat_Status=4;
    }
    
    return(Ups_Bat_Status);
}



//UPS Battery bar tune in  only for left side
void ups_Bat_Bar_Left(unsigned ups_mode)
{
    switch (ups_mode)
    {
    //100% UPS 
    case 0:
    CS_LAT=0;
    sentdata(0x5,0x1B,0xF,10);
    CS_LAT=1;
    __delay_ms(1);

    CS_LAT=0;
    sentdata(0x5,0x1A,0x8,10);
    CS_LAT=1;
    __delay_ms(1);
    break;

    //still need to disable 100% ups status part
    //75% UPS    
     case 1:
    CS_LAT=0;
    sentdata(0x5,0x1B,0xF,10);
    CS_LAT=1;
    __delay_ms(1);       
    //disable part
    CS_LAT=0;
    sentdata(0x5,0x1A,0x0,10);
    CS_LAT=1;
    __delay_ms(1);
    break;

    //50% UPS
     case 2:
    CS_LAT=0;
    sentdata(0x5,0x1B,0xB,10);
    CS_LAT=1;
    __delay_ms(1);        
    //disable part
    CS_LAT=0;
    sentdata(0x5,0x1A,0x0,10);
    CS_LAT=1;
    __delay_ms(1);
    break;

    //25% UPS
     case 3:
    CS_LAT=0;
    sentdata(0x5,0x1B,0x9,10);
    CS_LAT=1;
    __delay_ms(1);      
    //disable part
    CS_LAT=0;
    sentdata(0x5,0x1A,0x0,10);
    CS_LAT=1;
    __delay_ms(1);
    break;

    //0% UPS
     case 4:
    CS_LAT=0;
    sentdata(0x5,0x1B,0x8,10);
    CS_LAT=1;
    __delay_ms(1);    
    //disable part
    CS_LAT=0;
    sentdata(0x5,0x1A,0x0,10);
    CS_LAT=1;
    __delay_ms(1);
    break;

    //default setting for ups 0%
    default:
    CS_LAT=0;
    sentdata(0x5,0x1B,0x8,10);
    CS_LAT=1;
    __delay_ms(1);     
    //disable part
    CS_LAT=0;
    sentdata(0x5,0x1A,0x0,10);
    CS_LAT=1;
    __delay_ms(1);
    break;

    }
}

//AC side LCD BAR showing
void ups_Bat_Bar_Right(unsigned ups_mode)
{
    switch (ups_mode)
    {
    //100% UPS 
    case 0:
    CS_LAT=0;
    sentdata(0x5,0x14,0xF,10);
    CS_LAT=1;
    __delay_ms(1);

    CS_LAT=0;
    sentdata(0x5,0x15,0x1,10);
    CS_LAT=1;
    __delay_ms(1);
    break;

    //still need to disable 100% ups status part
    //75% UPS    
     case 1:
    CS_LAT=0;
    sentdata(0x5,0x14,0xF,10);
    CS_LAT=1;
    __delay_ms(1);       
    //disable part
    CS_LAT=0;
    sentdata(0x5,0x15,0x0,10);
    CS_LAT=1;
    __delay_ms(1);
    break;

    //50% UPS
     case 2:
    CS_LAT=0;
    sentdata(0x5,0x14,0xD,10);
    CS_LAT=1;
    __delay_ms(1);        
    //disable part
    CS_LAT=0;
    sentdata(0x5,0x15,0x0,10);
    CS_LAT=1;
    __delay_ms(1);
    break;

    //25% UPS
     case 3:
    CS_LAT=0;
    sentdata(0x5,0x14,0x5,10);
    CS_LAT=1;
    __delay_ms(1);      
    //disable part
    CS_LAT=0;
    sentdata(0x5,0x15,0x0,10);
    CS_LAT=1;
    __delay_ms(1);
    break;

    //0% UPS
     case 4:
    CS_LAT=0;
    sentdata(0x5,0x14,0x1,10);
    CS_LAT=1;
    __delay_ms(1);    
    //disable part
    CS_LAT=0;
    sentdata(0x5,0x15,0x0,10);
    CS_LAT=1;
    __delay_ms(1);
    break;

    //default setting for ups 0%
    default:
    CS_LAT=0;
    sentdata(0x5,0x14,0x1,10);
    CS_LAT=1;
    __delay_ms(1);     
    //disable part
    CS_LAT=0;
    sentdata(0x5,0x15,0x0,10);
    CS_LAT=1;
    __delay_ms(1);
    break;

    }
}