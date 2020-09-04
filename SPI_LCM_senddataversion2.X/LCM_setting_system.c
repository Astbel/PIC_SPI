#include "port.h"

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
        CLK_LAT=1;   
    }
}
//Timer0 setting
void Timer0_Init(void)
{
    T0CON1bits.T0CS = 2;        // Fosc/4
    T0CON1bits.T0CKPS = 3;      //     /8
    //  32000000/4/8 => 1000000
    T0CON1bits.T0ASYNC = 1;     //
    PIR0bits.TMR0IF=0;
    PIE0bits.TMR0IE=1;
    TMR0H=100;                   // 1s / 1000000 => 1us => 100*1us => 100us
    T0CON0bits.T0EN=1;
}
//Interrupt
void __interrupt() ISR()
{
   if(TMR0IF==1)     // flag equl to 1  
   { 
        CLK();           //calling for pwm function to start the system         
        TMR0IF=0;        //clear the flag    
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
    for (n = 0; n< slave_length-1; n++)
    {
        databuff[n] = (slave_address>>(slave_length-n-1) & 0x01);
    }

    //user data logic and && into martixa
    for ( n = 0; n < bit-1; n++) //data match bit and logic and & 0x01 output RC5  
    {
        databuff[n+slave_address]=((reg>>(bit-n-1))&0x01); 
    //  DataBuf[n+SlaveLength-1] = (REG2>>(Length-n)) & 0x01
    }
    //end of data in martix

    clk_control=1;
    endsend=0;
    while (sendbit!=0) // lock data for waitting send done
    {
        while((CLK_LAT==1)&&(CLK_count))
        {
            for(i=0; i<= sendbit; i++)//output part need count slave_address
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
}

//set LCD BIAS duty
void LCD_BIAS_DUTY(void)
{
CS_LAT=0;
sentdata(0x04,0x40,9);
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
