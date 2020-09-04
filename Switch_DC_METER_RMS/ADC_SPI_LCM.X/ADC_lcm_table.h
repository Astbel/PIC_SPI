#ifndef ADC_LCM_TABLE_H
#define	ADC_LCM_TABLE_H

//External Interrupt function and Flag
extern void Init_Timer2(void);

extern unsigned char Key;

//AC source variable & Array
extern unsigned int AC_INDEX[100];
extern unsigned char AC_POINT;
extern unsigned char Sample_count;
extern  double AC_sum;

/*user define variable here is ADC using part*/
extern  unsigned int ADCValue;      //adc hex register
extern  float result;        //Register for adc vaule
//SEG COM set for the switch case  

/*function of the ADC*/
extern void ADC_init(void);
extern unsigned int ADC_read(void);
/*function for lcm inital on */

extern void ADC_SPI(void);


#endif	/* PORT_H */