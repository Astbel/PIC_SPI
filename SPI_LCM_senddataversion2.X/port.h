#ifndef PORT_H
#define	PORT_H


/*Port define-------------------------------*/
//set  CS,PWM,Data  
#define CS_LAT             LATCbits.LATC3       //CS port
#define CS_ANSEL           ANSELCbits.ANSC3
#define CS_TRIS            TRISCbits.TRISC3

#define CLK_LAT             LATCbits.LATC4
#define CLK_ANSEL           ANSELCbits.ANSC4   //PWM port
#define CLK_TRIS            TRISCbits.TRISC4

#define Data_LAT           LATCbits.LATC5      //DATA port
#define Data_ANSEL         ANSELCbits.ANSC5
#define Data_TRIS          TRISCbits.TRISC5

/*Private variables ---------------------------------------------------------*/
#define _XTAL_FREQ 32000000  // defines for the crystal Osc 32Mhz

//vaule user define
 unsigned int   reg=0;            //reg   for  user send data 
//int8_t        reg=0;  
unsigned char   n=0;             //inital for the n vaule FOR LOOP use
unsigned char   i=0;
unsigned char   endsend=0;       //lastbit flag
unsigned char   clk_control=0;   //clk crontol flag
unsigned char   CLKOK=0;           //send data start flag 1sent 0end           
unsigned char   CLK_count=0;        // For Clk step count 
unsigned char   sendbit=0;          //
//unsigned char   bit=0;

//7_1updata auto count for data


#endif	/* PORT_H */