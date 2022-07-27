/* 
 * File:   newmain.c
 * Author: YYJ-2
 *
 * Created on May 24, 2022, 1:50 PM
 */

#include "main.h"
__CONFIG(0x01D4);  //__CONFIG(0x01B4);  
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
    static unsigned char i;
    unsigned char resetKey;
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


   resetKey = Scan_Key();
		   if(resetKey ==0x01){
               KeyValue ++;
               if(KeyValue==1) BAT_LED_ON();
               else {
                    KeyValue=0;
                   BAT_LED_OFF();
               }
			   run_t.Confirm =1; //input amdministrator password flag
			   run_t.Numbers_counter=0;
			   run_t.buzzer_flag =1;
		       BUZZER_KeySound();
               
		   }
		   if(resetKey == 0x81){
               
               adc ++;
               if(adc==1)
			        OK_LED_ON();
               else{
                   OK_LED_OFF();
                   adc = 0;
               }
			  run_t.BackLight =2;
                Buzzer_LongSound();
			  //ClearEEPRO_Data();
                i=1;
			
              
		   }
   if(i==1){
       i=0;
     ClearEEPRO_Data();
   
     
   }
//   if(resetKey==0){
//   BackLight_Fun();
//    Buzzer_Sound();
//   }
	#if 0

	if(run_t.passswordsMatch==0){
	  if(I2C_Simple_Read_From_Device(SC12B_ADDR,SC_Data,2)==DONE){
		 
	      KeyValue =(unsigned int)(SC_Data[0]<<8) + SC_Data[1];
		  RunCheck_Mode(KeyValue); 
			
	      }
	   }

	if(run_t.passswordsMatch ==1 && run_t.adminiId !=1){
		
		  RunCommand_Unlock();
	}
	
	if(run_t.passsword_unlock==2){ //lock turn on Open 
	  	
		resetKey = Scan_Key();
		if(resetKey ==0x01){
			run_t.Confirm =1; //input amdministrator password flag
			run_t.Numbers_counter=0;
			run_t.buzzer_flag =1;
		

		}
		if(resetKey == 0x81){
			
		   run_t.BackLight =2;
		   ClearEEPRO_Data();
           Buzzer_LongSound();
		}
		if(run_t.Confirm ==1 && run_t.adminiId==1){
            ERR_LED_OFF();
       
			SavePassword_To_EEPROM();
        }
	}
	
    BackLight_Fun();
    Buzzer_Sound();

     #endif 
   }
    
}

