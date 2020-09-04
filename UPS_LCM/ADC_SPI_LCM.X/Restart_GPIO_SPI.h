#ifndef __RESTART_GPIO_SPI_H
#define __RESTART_GPIO_SPI_H
/*2020/7/29 updata clear ram run */
/*User variable*/
extern unsigned  int   reg;            //reg   for  user send data 
extern  unsigned  char   n;             //inital for the n vaule FOR LOOP use
extern unsigned  char   i;
 extern unsigned char   endsend;       //lastbit flag
extern unsigned char   clk_control;   //clk crontol flag
extern unsigned   char  CLKOK;           //send data start flag 1sent 0end      
extern  unsigned char   testpoint;      
extern unsigned char   CLK_count;        // For Clk step count 
extern unsigned char   sendbit;          //
//here go with clear ram variable
extern unsigned char  Clear_RAM_MAP; //for loop variable using in auto run the  lcm inital
/*user void function*/
//Osc PLL function 
void OSC_Init(void);
//SPI_CLK_function
void CLK(void);
//Timer1
void Init_Timer1(void);
//Here go with send data function
unsigned char sentdata(unsigned char slave_address,unsigned int Ram_address,unsigned char Ram_data,unsigned char bit);

//LCM inital 2020 8/12 updata
extern void LCM_Init(void);


//set LCD BIAS duty
void LCD_BIAS_DUTY_1_3_4COM(void);
//set system clock source
void Clock_Source(void);
//system enable
void system_enable(void);
//LCD ON
void LCD_ON(void);


//Clear Ram data
void Clear_Ram_data(void);

void RC_Source(void);

void test_send(void);

void LCD_OFF(void);

void TEST_mode(void);

void CLR_TIMER(void);

void CLR_WDT(void);

void LCD_BIAS_DUTY_1_2_4COM(void);

void CLR_RAM(void);

void CLR_RAM_DATA(void);
#endif
