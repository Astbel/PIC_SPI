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
        CLK_LAT=1;   //ACK stop clk working
    }
}
//Timer0 setting  
void Timer0_Init(void)
{
    T0CON1bits.T0CS = 2;        // Fosc/4
    T0CON1bits.T0CKPS =3;      //     /8
    //  32000000/4/8 => 1000000
    T0CON1bits.T0ASYNC = 1;     //TMR0 
    PIR0bits.TMR0IF=0;
    PIE0bits.TMR0IE=1;         //fix timer frequency  
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
unsigned char sentdata(unsigned char slave_address,unsigned int Ram_address,unsigned char Ram_data,unsigned char bit)
{
    unsigned char databuff[40]={0};// Martix for the data user input
    //user data into register
    unsigned char slave_length=3;//command 100 101 110
    //rebulid Ram mapping
    reg=Ram_address;  //
    reg=reg<<4;
    reg=reg|Ram_data; //
    
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



//IO_Iniatl
void IO_inital(void)
{
 //define port RC3 CS
  CS_LAT   =1;
  CS_ANSEL =0;
  CS_TRIS  =0;
  //define port RC4 CLK
  CLK_LAT   =1;   
  CLK_ANSEL =0;
  CLK_TRIS  =0;
  //define port RC5 data
  Data_LAT   =0;
  Data_ANSEL =0;   
  Data_TRIS  =0;  
}
//set LCD BIAS duty
void LCD_BIAS_DUTY_1_2_4COM(void)
{
CS_LAT=0;
sentdata(0x04,0x05,0x00,9); //Bias 1/3 select 4COM
 CS_LAT=1;
__delay_ms(1);
}

//set system clock source
void Clock_Source(void)
{
CS_LAT=0;
sentdata(0x04,0x02,0x08,9);
 CS_LAT=1;
__delay_ms(1);
}

//system enable
void system_enable(void)
{
CS_LAT=0;
sentdata(0x04,0x00,0x02,9);
 CS_LAT=1;
__delay_ms(1);
}

//LCD ON
void LCD_ON(void)
{
CS_LAT=0;
sentdata(0x04,0x00,0x06,9);
CS_LAT=1;
__delay_ms(1);
}

//Clear Ram data
void Clear_Ram_data(void)
{
CS_LAT=0;
sentdata(0x05,0x00,0x00,9);
CS_LAT=1;
__delay_ms(1); 
}

//RC-256K
void RC_256K(void)
{
CS_LAT=0;
sentdata(0x04,0x30,0x00,9);
CS_LAT=1;
__delay_ms(1);  
}

//LCD_OFF
void LCD_OFF(void)
{
CS_LAT=0;
sentdata(0x04,0x00,0x04,9);
CS_LAT=1;
__delay_ms(1);   
}




















