#include "../inc/buzzer.h"

void BUZZER_Init(void)
{
     TRISCbits.TRISC5 =0 ; //I/O as output 
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

      BUZZER_PIN_ON();
	  __delay_us(250);
	  BUZZER_PIN_OFF();
	  __delay_us(250);

}

