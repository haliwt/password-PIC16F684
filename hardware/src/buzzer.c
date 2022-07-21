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
	
     for(m=0;m<30;m++){
          BEEP=!BEEP;
          __delay_us(500);//delayUS(99);
         // __delay_ms(1);
     }

//     m=200;
//     while(--m){
//         BEEP=!BEEP;
//         __delay_us(60);// delayUS(199);
//     }

}

void Buzzer_LongSound(void)
{
    unsigned int m;
	
     for(m=0;m<50;m++){
          BEEP=!BEEP;
          __delay_us(800);//delayUS(99);
         // __delay_ms(1);
     }



}


