/* 
 * File:   newmain.c
 * Author: YYJ-2
 *
 * Created on May 24, 2022, 1:50 PM
 */

#include "main.h"
__CONFIG(0x01A4);  //__CONFIG(0x01B4);  
//#pragma config CONFIG = 0x01B4 
//#pragma config FOSC = INTRCIO, WDTE = ON, PWRTE = OFF, MCLRE = OFF, BOREN = ON, CP = OFF, CPD = OFF   //PIC16F676 
//PIC16F684 
//#pragma config FOSC = INTOSCIO, WDTE = ON, PWRTE = OFF, MCLRE = OFF, CP = OFF, CPD = OFF, BOREN = ON, IESO = OFF, FCMEN = ON

unsigned char SC_Data[2];
/*
 * 
 */
void main(void) 
{
   
    unsigned char resetKey,k;
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
	

	if(run_t.passswordsMatch==0){
	  if(I2C_Simple_Read_From_Device(SC12B_ADDR,SC_Data,2)==DONE){
		 
	      KeyValue =(unsigned int)(SC_Data[0]<<8) + SC_Data[1];
		   
             
          RunCheck_Mode(KeyValue); 
			
	      	      
          }
	       
	 	 
      }
	if(run_t.passswordsMatch ==1){
		  RunCommand_Unlock();
		   
		    
       
	 }
	  if(run_t.passsword_unlock==2){
	  	
		resetKey = Scan_Key();
		if(resetKey ==0x01){

           ERR_LED_ON()  ;
	       OK_LED_ON()  ;

		}
		SavePassword_To_EEPROM();

	 }

	
	    
		BackLight_Fun();

	    Buzzer_Sound();


   }
    
}

