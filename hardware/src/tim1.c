#include "../inc/tim1.h"
#include"../../main.h"


/**
  Section: Global Variables Definitions
*/
//volatile uint16_t timer1ReloadVal;
//void (*TMR1_InterruptHandler)(void);

/******************************************************************************************************
*
*Functin Name: void TIMER1_Init(void)
*Funciton : TIMER0 and TIMER1 is 10ms 
*           prescaler = 4 
*           Timer0 overflow = 256 * prescaler * (__XTAL_FREQ / 4)= 256 * 4 * 1us = 1024us = 1.024ms
*           TIMER0 0f initial value  =(256 - (4MHz/4us)/4 * 0.001s) = (256 - 250)= 6
*
*           TMR1H:TMR1L = [65536-[(__XTAL-FREQ/4)/prescaler] * Timer0 overflow(s)]
*			Tim is need timer ,explame 10000us 10ms -unit us
*           Freq = system clock frequency is = 4MHz 
*           prescale = 1,2,4,8,prscale=8 ->Tim = 10ms
*           TMR1H:TMR1L = 65536-[(Tim*Freq)/(4*precals)] =65536-((10000 * 4)/(4*8))=64286
            prscale = 8 ->Tim =1ms
*           TMR1H:TMR1L = 65536-[(Tim*Freq)/(4*precals)] =65536-((1000 * 4)/(4*8))=65535-125 =65410
*
******************************************************************************************************/

void TMR1_Initialize(void)
{
    //Set the Timer to the options selected in the GUI

    //TMR1H : TMR1L = 64286; 
    TMR1H = 0xFB;

    //TMR1L 48; 
    TMR1L = 0x1E;

    // Clearing IF flag before enabling the interrupt.
    PIR1bits.TMR1IF = 0;

    // Load the TMR value to reload variable
    //timer1ReloadVal=(uint16_t)((TMR1H << 8) | TMR1L);

    // Enabling TMR1 interrupt.
    PIE1bits.TMR1IE = 1;

    // Set Default Interrupt Handler
   

    // T1CKPS 1:8; nT1SYNC synchronize; internal TMR1CS FOSC/4; TMR1ON enabled; 
    T1CON = 0b00110101; //0x04;
}


/**
 * @brief  TMR1 is 10ms
 * 
 */
void TMR1_ISR(void)
{
    static unsigned char t,t1,t2,t3,tm1;
    // Clear the TMR1 interrupt flag
    PIR1bits.TMR1IF = 0;
   
     //TMR1H : TMR1L = 64286;  
    TMR1H = 0xFB;

    //TMR1L 48; 
    TMR1L = 0x1E;

    // ticker function call;
    // ticker is 1 -> Callback function gets called everytime this ISR executes
   t++;
   if(t==2){
   	 t=0;
	 t3++;
	 run_t.timer_20ms=1;
	 if(t3==3){
       t3=0;
	   run_t.timer_60ms=1;

	 }
	 
	 t2++;
	   if(t2==200){
	      t2=0;
	      t1++;
	      if(t1==3){
		  	 t1=0;
			 tm1++;
		     if(tm1==1)
	             run_t.timer_led=1;
	          else{
			  	tm1=0;
	           run_t.timer_led=0;
	         
	          }
	   	}
	      run_t.timer_base ++;
	      run_t.timer_Core ++ ;

	   }
   }
}




