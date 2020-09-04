#ifndef __UPS_STATUS_H
#define __UPS_STATUS_H

//variable define here to use
extern unsigned char ups_mode;
//extern float  ups[5]={};   //Index for adc result saving in 
//extern float  sum;         //sum the Moving Average for the adc result
//extern unsigned char i;    //for loop variable using in saving data to array
extern unsigned char UPS_MOVING_AVG; //variable using in switch case to select mode
extern unsigned char ups_point;
extern unsigned char Ups_Bat_Status;


//function for calling 
extern unsigned int UPS_calcute(void);

 void UPS_STATUS(unsigned char ups_mode);

//UPS Status & UPS Battery Bar
 void ups_online_mode(void);

 void ups_Battery_Mode(void);

void ups_Bat_Bar_Left(unsigned ups_mode);
void ups_Bat_Bar_Right(unsigned ups_mode);

unsigned int Ups_Bat_Mode(void);




















#endif