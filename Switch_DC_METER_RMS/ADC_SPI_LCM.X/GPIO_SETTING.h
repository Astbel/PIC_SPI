#ifndef PORT_H
#define	PORT_H

/*GPIO setting for dspic*/

/*Port define-------------------------------*/
//set  CS,PWM,Data  
//dspic define as PCB port 28
#define CS_LAT             LATAbits.LATA1     //CS port
//#define CS_ANSEL           ANSELCbits
#define CS_TRIS            TRISCbits.TRISC1

//dspic define as PCB port 8
#define CLK_LAT             LATAbits.LATA9
//#define CLK_ANSEL           ANSELAbits.  //PWM port
#define CLK_TRIS            TRISAbits.TRISA9

//dspic define as PCB port 16
#define Data_LAT           LATAbits.LATA4      //DATA port 
#define Data_ANSEL         ANSELAbits.ANSA4
#define Data_TRIS          TRISAbits.TRISA4

/*Private variables ---------------------------------------------------------*/
/*define Fosc and FCY and libpic30 to use delay function*/
#define FOSC  (7370000ULL)
#define FCY   (FOSC/2)
//vaule user define
extern unsigned int   reg;            //reg   for  user send data 
extern unsigned char   n;             //inital for the n vaule FOR LOOP use
extern unsigned char   i;
extern unsigned char   endsend;       //lastbit flag
extern unsigned char   clk_control;   //clk crontol flag
extern unsigned char   CLKOK;           //send data start flag 1sent 0end      
extern unsigned char   testpoint;      
extern unsigned char   CLK_count;        // For Clk step count 
extern unsigned char   sendbit;          //




#endif	/* PORT_H */