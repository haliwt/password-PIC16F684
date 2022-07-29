#include "../inc/buzzer.h"

#define uchar  unsigned	char
#define uint   unsigned int




void BUZZER_Init(void)
{
     TRISCbits.TRISC5 =0 ; //I/O as output 

	 PORTCbits.RC5=0;
}
/*******************************************
*
*Function Name: void BUZZER_KeySound(void)
*Function: Key be pressed carry out sound
*
*
*******************************************/
void BUZZER_KeySound(void)
{
      unsigned int m;
	
     for(m=0;m<40;m++){
          BEEP=!BEEP;
          __delay_us(600);//delayUS(99);
        
     }


}

void Buzzer_LongSound(void)
{
    unsigned int m;
	
     for(m=0;m<200;m++){//m<50
          BEEP=!BEEP;
          __delay_us(400);//delayUS(99);
     }



}

void Buzzer_ResetSond(void)
{
     unsigned int m;
	
     for(m=0;m<40;m++){//m<50
          BEEP=!BEEP;
          __delay_us(2);//delayUS(99);
     }

}



