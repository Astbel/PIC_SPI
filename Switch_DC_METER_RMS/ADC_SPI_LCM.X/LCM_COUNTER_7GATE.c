/*2020/7/31   this type recode for adc the variable for switch case is unable to set */
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

//unsigned char LCM_7GATE_PLUS=0;
unsigned char GATE2=0;
unsigned char MODE2_COUNT=0;
/*switch case for  seven gate counter function*/
