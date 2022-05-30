
#include "../../hardware/inc/interrupt.h"
#include "../../main.h"

void __interrupt() INTERRUPT_InterruptManager (void)
{
    // interrupt handler
    if(INTCONbits.T0IE ==1 && INTCONbits.T0IF ==1){
         TMR0_ISR();

    }
    else if(PIE1bits.TMR1IE == 1 && PIR1bits.TMR1IF == 1)
    {
            TMR1_ISR();
    } 
    else
    {
            //Unhandled Interrupt
    }
} 