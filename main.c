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

unsigned char SC_Data[2];
/*
 * 
 */
void main(void) 
{
   
   unsigned int keyValue;
 

   SC12B_Init_Function();
    TMR1_Initialize();
	
    ADC_Init();
    System_Init();
   INTERRUPT_GlobalInterruptEnable();
   INTERRUPT_PeripheralInterruptEnable() ;
   while(1)
   {
      BUZZER_KeySound();

    // BUZZER_KeySound();
     // if(run_t.timer_20ms==1){
	  	//  run_t.timer_20ms=0;

          if(I2C_Simple_Read_From_Device(SC12B_ADDR,SC_Data,2) == DONE)
           {
                  keyValue =(SC_Data[0]<<8) + SC_Data[1];
			    // keyValue = SC_Data[0];

				  RunCheck_Mode(keyValue);
           }
	
//	      if(I2C_Read_From_Device(SC12B_ADDR,0x08,SC_Data,2)==DONE){
//		 
//	     // keyValue =(SC_Data[0]<<8) + SC_Data[1];
//	     keyValue = SC_Data[0];
//
//		  RunCheck_Mode(keyValue);
//          }
//     /// }

	//  RunCommand_Unlock();
	   
//      if(run_t.timer_base ==250){ //5s ->battery be checking 
//         run_t.timer_base = 0;
//         ADC_ReadVoltage();
//	     run_t.passsword_unlock =0;
//      }
//     // Modify password state 
//     if(run_t.timer_60ms==1){
//	   run_t.timer_60ms=0;
//       Modidy_NewPassword_Function();
//
//    }
//
//	 if(run_t.passsword_unlock ==0 || run_t.passsword_error==1){
//
//	       if(run_t.timer_led==1){
//			        ERR_LED_ON()  ;	
//				}
//				else{
//                    ERR_LED_OFF();
//				}
//
//		if(run_t.passsword_error==1)run_t.changePassword =0;
//
//     }
   }
    
}

