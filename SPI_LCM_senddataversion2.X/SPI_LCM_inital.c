#include <xc.h>
#include "port.h"
//#include "LCM_setting_system.c"
#include "LCM_sent_double_data.c"
/* Private variables ---------------------------------------------------------*/
#define _XTAL_FREQ 32000000  // defines for the crystal Osc 32Mhz
//start config
#pragma config WDTE = OFF
#pragma config MCLRE = OFF
#pragma config LVP = OFF
#pragma config FEXTOSC = OFF
#pragma config RSTOSC = HFINT32
#pragma config BORV = HIGH    //  Vbor => 2.7V


void CLK(void);
void Timer0_Init(void);
void main(void);
void LCD_BIAS_DUTY_1_3_4COM(void);
void Clock_Source(void);    //32XTL
void system_enable(void);
void LCD_ON(void);
void LCD_OFF(void);
void Clear_Ram_data(void);
void Ram_data_All_high(void);
void RC_256K(void);
unsigned char sentdata(unsigned char slave_address,unsigned int data,unsigned char bit);
//unsigned char sentdata(unsigned char slave_address,unsigned int data1,unsigned int data2,unsigned char bit);


void main(void)
{
   //start inital 
  //define port RC3 CS
  CS_LAT   =1;
  CS_ANSEL =0;
  CS_TRIS  =0;
  //define port RC4 CLK
  CLK_LAT   =0;   
  CLK_ANSEL =0;
  CLK_TRIS  =0;
  //define port RC5 data
  Data_LAT   =0;
  Data_ANSEL =0;   
  Data_TRIS  =0;  
  //call timer & GIE to start up interrupt
  clk_control=0; //clk for interrupt flag
  Timer0_Init();
  INTCONbits.GIE=1;
  
//*inital data send here*/
 //CLEAR_RAM_DATA
  Clear_Ram_data();
  
 //BIAS_DUTY COM SELECTING
  LCD_BIAS_DUTY_1_3_4COM();

  //system enable
  system_enable(); 
                  
  //LCD ON
  LCD_ON();

/***********here start send one bit*******************/
    while(1)
    {       
        CS_LAT=0;
        sentdata(0x05,0x1451,10);
        CS_LAT=1;
        __delay_ms(1);    
    }
}
