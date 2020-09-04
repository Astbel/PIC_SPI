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
void LCD_BIAS_DUTY_1_2_4COM(void);
void Clock_Source(void);    //32XTL
void system_enable(void);
void LCD_ON(void);
void LCD_OFF(void);
void Clear_Ram_data(void);
void Ram_data_All_high(void);
void RC_256K(void);
void IO_inital(void);
void LCM_init(void);
unsigned char sentdata(unsigned char slave_address,unsigned int Ram_address,unsigned char Ram_data,unsigned char bit);

unsigned char count;
unsigned char data;



void LCM_init(void)
{
    //*inital data send here*/

//CLOCK SOURCE
//  RC_256K();  //call function ht1621 clock source 256k
// Clock_Source(); //32k XTAL
  
//system enable
  system_enable(); 
  
  //BIAS_DUTY COM SELECTING
  LCD_BIAS_DUTY_1_2_4COM();
  
  //clear Ram_Map
  Clear_Ram_data(); 
  
  //LCD_OFF
  //LCD_OFF();
  
  //LCD ON
  LCD_ON();
  
}


void main(void)
{
   //start inital 
  IO_inital();
  //call timer & GIE to start up interrupt
  clk_control=0; //clk for interrupt flag
  Timer0_Init();
  INTCONbits.GIE=1;
  
  LCM_init();

/***********here start send one bit*******************/
 while(1){
     CS_LAT=0;
     sentdata(0x05,0x00,0x0,10);
     CS_LAT=1;
     __delay_ms(1);
 } 
}