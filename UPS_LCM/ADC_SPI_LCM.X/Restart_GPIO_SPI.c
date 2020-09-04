/*2020/7/27 inital data run to display check all the inital is work*/
/**/

/*include config here*/
#include "config.h"
/*include GPIO header here*/
#include "Dspic_GPIO.h"
/*User define Header include here*/
#include <libpic30.h>
/*User spi file define here*/
#include "Restart_GPIO_SPI.h"
#include "ADC_lcm_table.h"
#include "LCM_TABLE.h"
/*User variable dalcare here*/
 unsigned int   reg=0;            //reg   for  user send data 
 unsigned char   n=0;             //inital for the n vaule FOR LOOP use
 unsigned char   i=0;
 unsigned char   endsend=0;       //lastbit flag
 unsigned char   clk_control=0;   //clk crontol flag
 unsigned char   CLKOK=0;           //send data start flag 1sent 0end      
 unsigned char   testpoint=0;      
 unsigned char   CLK_count=0;        // For Clk step count 
 unsigned char   sendbit=0;          //
 unsigned char    Clear_RAM_MAP=0x00;
 /*array for inital clear ram */
 unsigned char CLR_RAMAY[28]={0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27};
/*dspic create Osc PLL here*/
/*calcaute system osc*/
void OSC_Init(void){
    // FRC => 7.37M
    // Fosc = Fpllo = FRC*(PLLFBD+2)/(PLLPRE+2)/(2(PLLPOST+1))
    //      = 7.37M * 65 / 2 / 2
    //      = 7.37M * 65 / 4
    //      = 119.7625M
    
    // Fcy  = Fp    = Fsys
    //      = Fosc/2
    //      = 59.88125M
    
    PLLFBD = 63;            //  PLLFBD = N + 2 = 63 + 2 = 65
    CLKDIVbits.PLLPOST = 0; //  2
    CLKDIVbits.PLLPRE = 0;  //  2
    __builtin_write_OSCCONH(0x01);
    __builtin_write_OSCCONL(0x01);
    while(OSCCONbits.COSC != 0b001);// Wait for clock switch to occur
    while(OSCCONbits.LOCK != 1){};// Wait for PLL to lock
    
    //  Faclk = FRC * 16 => 7.37*16 = 117.92M
    OSCTUNbits.TUN = 0 ;		// Set Center F ~= 7.37 MHz
}
/*SPI_CLK_function*/
void CLK(void)
{
    if(clk_control==1)   //enable CLK    
    {        
        CLK_LAT =! CLK_LAT;
        if(!CLK_LAT)
        {
            CLKOK=1;   
            CLK_count++;        
        }
    }
    else              
    {
        CLK_count=0;
        CLK_LAT=1;   //ACK stop clk working
    }
}

/*Dspic setting Timer for IO type SPI Interrupt*/
void Init_Timer1(void)
{
    T1CONbits.TON = 1;    //Activate the timer module
    T1CONbits.TCKPS = 0;  //Select input clock prescaler as 1:1
//                            11 = 1:256 
//                            10 = 1:64
//                            01 = 1:8 
//                            00 = 1:1 
    T1CONbits.TGATE = 0;  //Disable Gate Time Accumulation Mode
    T1CONbits.TCS   = 0;    //Select internal clock as the timer clock source
    T1CONbits.TSYNC = 0;  //External clock source is left unsynchronized
    IPC0bits.T1IP   = 5;     //Assigning ADC ISR priority
    IFS0bits.T1IF   = 1;   
    IEC0bits.T1IE   = 1;   //Timer 1 enable 
    TMR1=0x00;        //clear timer register
    PR1 = 200;      //calculation of the Tcy divde prescale  
    
    //2020/8/26  upload PR1 to 200 test over after oscilloscope of spi is 153kHz
}
/*timer interrupt*/
 void _ISR_PSV _T1Interrupt( void )               
{
   if(IFS0bits.T1IF==1)     // flag equl to 1  
   { 
        CLK();           //calling for pwm function to start the system         
        IFS0bits.T1IF=0;        //clear the flag    
   }
}
 /*2020 / 7/24 define as sending singal data*/
 // if the function test can use paste here
 /*Here go with send data function*/
 //sentdata function
unsigned char sentdata(unsigned char slave_address,unsigned int SEG,unsigned char COM,unsigned char bit)
{
    unsigned char databuff[16]={0};// Martix for the data user input
    //user data into register
    unsigned char slave_length=3;//command 100 101 110
    //switch case for inital and sending for case0 and case1 using for sentdata
    //case 0 is orginal 
    reg=SEG;  //
    reg=reg<<4;
    reg=reg|COM; //
    
    sendbit=bit+slave_length; 
    //slave_address into databuf
    for (n = 0; n< slave_length; n++)
    {
        databuff[n] = ((slave_address >> (slave_length-n-1)) & 0x01);
    }
    //user data logic and && into martixa
    for ( n = slave_length; n < slave_length+bit; n++) //data match bit and logic and & 0x01 output RC5  
    {
        databuff[n] = ((reg >> (bit-(n-slave_length)-1)) & 0x01); //mask and 
    }
    //end of data in martix
    clk_control=1;
    endsend=0;
    while (sendbit!=0) // define user data send bits if not done while loop never ends
    {
        while((CLK_LAT==0)&&(CLK_count)) //low start users data standby
        {
            for(i=0; i<= bit+slave_length; i++)//output part need count slave_address
            {                
                Data_LAT=databuff[i];  //test
                sendbit--;
                endsend++;
                CLKOK=0;        //send end
                while(!CLKOK)
                {
                
                }
                if(endsend==bit+slave_length)//check if data endsend counter start at 1 and counter to bit+1
                {
                    Data_LAT=0;
                    clk_control=0;
                    return(sendbit);//if sendbir not equal to zero => error
                }
            } 
        }
    }
    return(endsend);
}
/*2020/7/24 define new function as sending mupliti sending data*/
 
 
 
/*inital function for lcm to call*/
/*LCD bias duty 1/2*/ 
void LCD_BIAS_DUTY_1_2_4COM(void)
{
CS_LAT=0;
sentdata(0x4,0x5,0x0,9); //Bias 1/3 select 4COM
CS_LAT=1;
__delay_ms(1);
}

//set LCD BIAS duty
void LCD_BIAS_DUTY_1_3_4COM(void)
{
CS_LAT=0;
sentdata(0x4,0x5,0x2,9); //Bias 1/3 select 4COM
 CS_LAT=1;
__delay_ms(1);
}
//XTAL Freq
void RC_Source(void)
{
CS_LAT=0;
sentdata(0x4,0x3,0x0,9);
 CS_LAT=1;
__delay_ms(1);
}

//set system clock source
void Clock_Source(void)
{
CS_LAT=0;
sentdata(0x4,0x2,0x8,9);
 CS_LAT=1;
__delay_ms(1);
}

//system enable
void system_enable(void)
{
CS_LAT=0;
sentdata(0x4,0x0,0x2,9);
 CS_LAT=1;
__delay_ms(1);
}

//LCD ON
void LCD_ON(void)
{
CS_LAT=0;
sentdata(0x4,0x0,0x06,9);
CS_LAT=1;
__delay_ms(1);
}

//Clear Ram data
void Clear_Ram_data(void)
{
CS_LAT=0;
sentdata(0x4,0x0,0x0,9);
CS_LAT=1;
__delay_ms(1); 
}

//RC-256K
void RC_256K(void)
{
CS_LAT=0;
sentdata(0x4,0x30,0x0,9);
CS_LAT=1;
__delay_ms(1);  
}

//LCD_OFF
void LCD_OFF(void)
{
CS_LAT=0;
sentdata(0x4,0x0,0x4,9);
CS_LAT=1;
__delay_ms(1);   
}

/*normal mode*/
void TEST_mode(void)
{
CS_LAT=0;
sentdata(0x4,0x01,0x0,9);
CS_LAT=1;
__delay_ms(1);    
}

/*CLR_TIMER*/
void CLR_TIMER(void)
{
CS_LAT=0;
sentdata(0x4,0x10,0x8,9);
CS_LAT=1;
__delay_ms(1); 
}
/*CLR_WDR*/
void CLR_WDT(void)
{
CS_LAT=0;
sentdata(0x4,0x1,0xC,9);
CS_LAT=1;
__delay_ms(1); 
}

/*clean SRAM for lcm*/
void CLR_RAM(void)
{
CS_LAT=0;
sentdata(0x5,0x0,0x0,10);
CS_LAT=1;
__delay_ms(1);  
}

/* Clear_RAM_MAP using in the auto clr ram map*/
void CLR_RAM_DATA(void){
for( Clear_RAM_MAP=0; Clear_RAM_MAP<31; Clear_RAM_MAP++)
{
    /*maybe too fast that wont write in */
    CS_LAT=0;
    sentdata(0x5, Clear_RAM_MAP,0x0,10);// COM SET AS 0x0 with one turn close one column of LCM
    CS_LAT=1;
    __delay_ms(1); 
}
}


/*2020/8/12 updata system inital function*/
void LCM_Init(void)
{
  Clear_Ram_data();
  LCD_BIAS_DUTY_1_2_4COM();
  system_enable();
   LCD_ON();  //START HT1621 LCM MODULA
   CLR_RAM(); //RESET THE LCD RAM MAP
  CLR_RAM_DATA(); //This function start when lcd on and close light one by one 
}


