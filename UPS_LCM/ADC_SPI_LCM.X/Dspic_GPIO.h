#ifndef DSPIC_GPIO_H
#define	DSPIC_GPIO_H

/*GPIO setting for dspic*/

/*Port define-------------------------------*/
//set  CS,PWM,Data  
//dspic define as PCB port 28
#define CS_LAT             LATBbits.LATB14     //CS port
//#define CS_ANSEL           ANSELBbit
#define CS_TRIS            TRISBbits.TRISB14

//dspic define as PCB port 8
#define CLK_LAT             LATBbits.LATB13
//#define CLK_ANSEL           ANSELCbits.ANSC1  //PWM port
#define CLK_TRIS            TRISBbits.TRISB13

//dspic define as PCB port 16
#define Data_LAT           LATBbits.LATB15      //DATA port 
//#define Data_ANSEL         ANSELBbits
#define Data_TRIS          TRISBbits.TRISB15

//here goes define ADC detect port
// which is on PCB borad port 27
#define ADCREAD_LAT       LATAbits.LATA1  
#define ADCREAD_ANSEL     ANSELAbits.ANSA1
#define ADCREAD_TRIS      TRISAbits.TRISA1

//external interrupt switching port
#define switch_LAT       LATAbits.LATA4
#define switch_ANSEL     ANSELAbits.ANSA4
#define switch_TRIS      TRISAbits.TRISA4
#define switch_PORT      PORTAbits.RA4

//User debug for external interrupt  RA3 boost relay
#define Excheck_LAT      LATAbits.LATA3
//#define Excheck_ANSEL
#define Excheck_TRIS    TRISAbits.TRISA3
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
extern unsigned char   wait_int1;       //waitting interrupt

#define _ISR_PSV		__attribute__((interrupt,auto_psv))		// Interrupt Auto Store PSV Page
#define _ISR_NPSV	__attribute__((interrupt,no_auto_psv))		// Interrupt No Auto Store PSV Page

#endif	/* PORT_H */