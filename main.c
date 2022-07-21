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
   
    unsigned char resetKey,k,i=1;
    unsigned int KeyValue,adc;

   SC12B_Init_Function();
    //TMR1_Initialize();
	Motor_Init();
	
    ADC_Init();
    System_Init();
  // INTERRUPT_GlobalInterruptEnable();
  // INTERRUPT_PeripheralInterruptEnable() ;
   run_t.changePassword=0;
   run_t.Numbers_counter=0;
   run_t.eepromAddress=0;
   while(1)
   {


        


	 #if 1
	   k++;


	
	
	  
      if(run_t.passswordsMatch==0){
	  if(I2C_Read_From_Device(SC12B_ADDR,0x08,SC_Data,2)==DONE){
		 
	      KeyValue =(SC_Data[0]<<8) + SC_Data[1];
		  
	         //keyValue = SC_Data[0];
             RunCheck_Mode(KeyValue);
	      	
          }
	      
	 	 
      }
		 if(run_t.passswordsMatch ==1){
		   
		     resetKey = Scan_Key();
			 {
		        if(resetKey ==0x01){

		           ERR_LED_ON()  ;
			       OK_LED_ON()  ;

				}

			 }
		    
		 }

	    // RunCommand_Unlock();
	    
		 if(run_t.BackLight ==1){

			 // run_t.BackLight =0;
		       BACKLIGHT_ON() ;
			  // if(pwd1[1]==1)  ERR_LED_ON()  ;
			  

		 }
		 else{

              BACKLIGHT_OFF() ;
			  ERR_LED_OFF();
		      OK_LED_OFF();
			  BAT_LED_OFF();
		 }

	    Buzzer_Sound();

#if 0
	resetKey = Scan_Key();
	 {
        if(resetKey ==0x01){

           ERR_LED_ON()  ;
	       OK_LED_ON()  ;

		}

	 }
	   
      if(k >2){ //5s ->battery be checking 
         k = 0;
         adc= ADC_ReadVoltage();
	     if(adc > 675)BAT_LED_ON() ;
		 else BAT_LED_OFF() ;
		 	 
	     run_t.passsword_unlock =0;
      }
#endif 
	 
//     // Modify password state 
//     if(run_t.timer_60ms==1){
//	   run_t.timer_60ms=0;
//       Modidy_NewPassword_Function();
//
//    }

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
	 #endif 
   }
    
}

