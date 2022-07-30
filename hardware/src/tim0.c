#include "../inc/tim0.h"
#include "../../main.h"


/******************************************************************************************************
*
*Functin Name: void TMR0_Initialize(void)
*Funciton : TIMER0 is 8bit maxmium =256  for Watchdog Prescale = 1,2,4,16,32,64,128
*           Formula : TMR0 initial value =256- (Timer(us)* Freq)/(4*Prescle)=
*           Times is 32ms , T= 100ms=100000us  prescaler = 128 ,freq = 4MHz, Period = 0.25us.
*           Timervalue TMR0L : initValue = 256 -(T*freq /(4*Prescale)) = 256-(32768 *4/(4*128))=256-256=0
*           Timer0 maximum overflow =  256 * prescale * (freq/4) =256 *128 * 1us = 32768us ~32ms 
*           TIMER0 0f initial value  =(256 - (10000us * 4)/(4 * 64) = (256 - 39)= 217
*
*
*****************************************************************************************************/

void TMR0_Initialize(void)
{
    //Set the Timer to the options selected in the GUI

    //TMR0=0, timer times = 10ms
    TMR0 = 217;

   // Clearing IF flag before enabling the interrupt.
     INTCONbits.T0IF = 0;

    // Enabling TMR0 interrupt.
     INTCONbits.T0IE= 1;

    // TIMER0 watchdog set 256
      OPTION_REG=0B00000111;        //TMER0 WDT  DISABLE


}
/***************************************************
 * 
 * Function Name:void TMR0_ISR(void)
 * Function : timer0 is 10ms
 * 
 ***************************************************/
void TMR0_ISR(void)
{
    static unsigned char t0,tm1;
    INTCONbits.T0IF = 0;
    TMR0 = 217;
	

    t0++;
    if(t0>99){ //10*100 =1000ms "1s"
       t0=0;
	   tm1++;
	   run_t.gTimer_2s ++;
	   run_t.gTimer_1s ++;
	   run_t.gTimer_60s++;
	   run_t.gTimer_8s++;
	
	   if(tm1>9){ //10s
		 tm1=0;
		 run_t.gTimer_10s ++;
	    

	   }
	
    }
  

}

