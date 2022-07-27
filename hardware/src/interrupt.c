
#include "../../hardware/inc/interrupt.h"
#include "../../main.h"

void interrupt INT(void)//void __interrupt() INTERRUPT_InterruptManager (void)
{
    // interrupt handler TMR0 
    if(INTCONbits.T0IE==1 && INTCONbits.TMR0IF==1){
    
            TMR0_ISR();
    
    }
    
//   if(PIE1bits.TMR1IE == 1 && PIR1bits.TMR1IF == 1)
//    {
//            TMR0_ISR();
//    } 
//    else
//    {
//            //Unhandled Interrupt
//    }
} 