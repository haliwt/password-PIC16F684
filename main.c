/* 
 * File:   newmain.c
 * Author: YYJ-2
 *
 * Created on May 24, 2022, 1:50 PM
 */

#include "main.h"
//__CONFIG(0x01B4);  
//#pragma config CONFIG = 0x01B4 
//#pragma config FOSC = INTRCIO, WDTE = ON, PWRTE = OFF, MCLRE = OFF, BOREN = ON, CP = OFF, CPD = OFF   //PIC16F676 
//PIC16F684 
#pragma config FOSC = INTOSCIO, WDTE = ON, PWRTE = OFF, MCLRE = OFF, CP = OFF, CPD = OFF, BOREN = ON, IESO = OFF, FCMEN = ON

/*
 * 
 */
void main(void) 
{
   
   SC12B_Init_Function();
    TMR1_Initialize();
    ADC_Init();
    System_Init();
   INTERRUPT_GlobalInterruptEnable();
   INTERRUPT_PeripheralInterruptEnable() ;
   while(1)
   {
   
       CProcessCmdRun();
      if(run_t.timer_base ==250){ //5s 
         run_t.timer_base = 0;
         ADC_ReadVoltage();
      }
      //Modify password state 
      if(run_t.OpenPasswrod == 1 ||  run_t.firstInPassword ==2){ //setup new user password for 10 numbers

         if(run_t.timer_led ==1){
			     OK_LED_OFF();
           }
           else{
			     OK_LED_ON();
           }
		}

      if(run_t.eePasswordOver ==1){

         if(run_t.timer_led ==1){
			     ERR_LED_OFF();
           }
           else{
			     ERR_LED_ON();
           }
      }
   }
    
}

