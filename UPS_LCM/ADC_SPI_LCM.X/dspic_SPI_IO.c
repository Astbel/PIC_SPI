/*define Fosc and FCY and libpic30 to use delay function*/
#define FOSC  (7370000ULL)
#define FCY   (FOSC/2)
/**/
#include <xc.h>
#include "config.h"
#include "dspic_SPI_IO.h"
#include <libpic30.h>
#include "GPIO_SETTING.h"

//vaule user define
 unsigned int   reg=0;            //reg   for  user send data 
//int8_t        reg=0;  
 unsigned char   n=0;             //inital for the n vaule FOR LOOP use
 unsigned char   i=0;
 unsigned char   endsend=0;       //lastbit flag
 unsigned char   clk_control=0;   //clk crontol flag
 unsigned char   CLKOK=0;           //send data start flag 1sent 0end      
 unsigned char   testpoint=0;      
 unsigned char   CLK_count=0;        // For Clk step count 
 unsigned char   sendbit=0;          //

/*Dspic OSC type */
/*user define PLL osc to user gain Freq*/
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

//CLK function into interrupt
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
//Timer0 setting
void initTimer1(void)
{
    T1CONbits.TON = 1;    //Activate the timer module
    T1CONbits.TCKPS = 3;  //Select input clock prescaler as 1:1
//                            11 = 1:256 
//                            10 = 1:64
//                            01 = 1:8 
//                            00 = 1:1 
    T1CONbits.TGATE = 0;  //Disable Gate Time Accumulation Mode
    T1CONbits.TCS = 0;    //Select internal clock as the timer clock source
    T1CONbits.TSYNC = 0;  //External clock source is left unsynchronized
    IFS0bits.T1IF = 1; 
    IEC0bits.T1IE = 1;
    IPC0bits.T1IP = 6;
    TMR1=0x00;     //clear timer register
    PR1 = 3906;      //calculation of the Tcy divde prescale
}
//Interrupt
void __attribute__((interrupt,no_auto_psv)) _T1Interrupt( void )               
{
   if(IFS0bits.T1IF==1)     // flag equl to 1  
   { 
        CLK();           //calling for pwm function to start the system         
        IFS0bits.T1IF=0;        //clear the flag    
   }
}



//sentdata function
unsigned char sentdata(unsigned char slave_address,unsigned int data,unsigned char bit)
{
    unsigned char databuff[40]={0};// Martix for the data user input
    //user data into register
    unsigned char slave_length=3;//command 100 101 110
    reg=data;
    sendbit=bit+slave_length;

    //slave_address into databuf
    for (n = 0; n< slave_length; n++)
    {
        databuff[n] = ((slave_address >> (slave_length-n-1)) & 0x01);
    }

    //user data logic and & into martix
    for ( n = slave_length; n < slave_length+bit; n++) //data match bit and logic and & 0x01 output RC5  
    {
        databuff[n] = ((reg >> (bit-(n-slave_length)-1)) & 0x01); 
    }
    //end of data in martix

    clk_control=1;
    endsend=0;
    while (sendbit!=0) // lock data for waitting send done
    {
        while((CLK_LAT==1)&&(CLK_count))
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





//set LCD BIAS duty
void LCD_BIAS_DUTY(void)
{
CS_LAT=0;
sentdata(0x04,0x52,9);
 CS_LAT=1;
__delay_ms(1);
}

//set system clock source
void Clock_Source(void)
{
CS_LAT=0;
sentdata(0x04,0x28,9);
 CS_LAT=1;
__delay_ms(1);
}

//system enable
void system_enable(void)
{
CS_LAT=0;
sentdata(0x04,0x02,9);
 CS_LAT=1;
__delay_ms(1);
}

//LCD ON
void LCD_ON(void)
{
CS_LAT=0;
sentdata(0x04,0x06,9);
CS_LAT=1;
__delay_ms(1);
}






















