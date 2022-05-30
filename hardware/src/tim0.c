#include "../inc/tim0.h"
#include "../../main.h"


/******************************************************************************************************
*
*Functin Name: void TMR0_Initialize(void)
*Funciton : TIMER0 is 8bit maxmium =256  for Watchdog
*           Times is 32ms , T= 100ms=100000us  prescaler = 128 ,freq = 4MHz, Period = 0.25us.
*           Timervalue TMR0L : 256 -(T*freq /(4*Prescale)) = 
*           Timer0 maximum overflow = 256 * prescaler * (__XTAL_FREQ / 4)= 256 * 128  = 32768us = 32.768ms
*           TIMER0 0f initial value  =(256 - (4MHz/4us)/4 * 0.001s) = (256 - 250)= 6
*
*
*****************************************************************************************************/

void TMR0_Initialize(void)
{
    //Set the Timer to the options selected in the GUI

    //TMR0=0, maximum = 32.768ms
    TMR0 = 0;

   // Clearing IF flag before enabling the interrupt.
     INTCONbits.T0IF = 0;

    // Enabling TMR0 interrupt.
     INTCONbits.T0IE= 1;

    // TIMER0 watchdog set
      OPTION_REG=0B00001111;        //TMER0 WDT ---128分频


}

void TMR0_ISR(void)
{
    INTCONbits.T0IF = 0;
    TMR0 = 0;
    asm("CLRWDT");

}

