/* 
 * File:   newmain.c
 * Author: YYJ-2
 *
 * Created on May 24, 2022, 1:50 PM
 */

#include "main.h"
//__CONFIG(0x01B4);  
//#pragma config CONFIG = 0x01B4 
#pragma config FOSC = INTRCIO, WDTE = ON, PWRTE = OFF, MCLRE = OFF, BOREN = ON, CP = OFF, CPD = OFF


/*
 * 
 */
void main(void) 
{
   
   SC12B_Init_Function();
    TMR1_Initialize();
   INTERRUPT_GlobalInterruptEnable();
   INTERRUPT_PeripheralInterruptEnable() ;
   while(1)
   {
      Password_Modify();
       
   }
    
}

