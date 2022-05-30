#include "../inc/ADC.h"


void ADC_Init(void)
{
     CMCON = 0x07;
     ANSELbits.ANS4 = 1 ; //I/O as analog  CHANNEL 4 
     WPU = 0x00;
     TRISCbits.TRISC0 = 1 ; 

     ADCON0 = 0x90;  // analog channel 4,Operiation is not  
}

/**
 * @brief 
 * 
 * @return 
 */
unsigned int ADC_ReadVoltage(void)
{
    unsigned int  adcValue;
    ADCON0bits.ADON = 1;
    __delay_ms(2);
   ADCON0bits.GO_DONE =1;
   while(ADCON0bits.GO_DONE ==1);

   adcValue = ADRESH ;
   adcValue  &= 0x03;
   adcValue += ADRESL;

   return  adcValue;

}