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
    static unsigned char clearEeprom;
    unsigned int KeyValue,adc;

   SC12B_Init_Function();
    TMR0_Initialize();
	Motor_Init();
	
    ADC_Init();
    System_Init();
   INTERRUPT_GlobalInterruptEnable();
   INTERRUPT_PeripheralInterruptEnable() ;
  
   run_t.Numbers_counter=0;
   run_t.eepromAddress=0;
   while(1)
   {
 
      #if 1

	  if(run_t.powerOn ==0){
         run_t.powerOn++;
		 run_t.passswordsMatch =1;
		 run_t.passsword_unlock =1;

	  }
      if(run_t.passswordsMatch==0 && run_t.panel_lock==0){
	  if(I2C_Simple_Read_From_Device(SC12B_ADDR,SC_Data,2)==DONE){
		 
	      KeyValue =(unsigned int)(SC_Data[0]<<8) + SC_Data[1];
		  RunCheck_Mode(KeyValue); 
			
	      }
	  }
       
	if(run_t.passswordsMatch ==1 && run_t.adminiId !=1){
		
		  RunCommand_Unlock();
	}
    if(run_t.passsword_unlock==2){ //lock turn on Open 
		if(run_t.getKey ==0x01){ //input password flag.
			run_t.getKey = 0;
			run_t.Confirm =1; //input amdministrator password flag
			run_t.Numbers_counter=0;
			run_t.buzzer_flag =1;
			
	     }
		if(run_t.getKey == 0x81){
			 run_t.getKey = 0;
			clearEeprom=1;
           Buzzer_LongSound();
		}
		if(run_t.Confirm ==1 && run_t.adminiId==1){
            ERR_LED_OFF();
       
			SavePassword_To_EEPROM();
        }
		if(run_t.gTimer_2s ==3 && run_t.unLock_times==1 && run_t.Confirm == 0){
			 run_t.unLock_times ++;
			 Motor_CW_Run();//open passwordlock 
			 __delay_ms(1400);
			 Motor_Stop();

		}
	}
	
       
         BackLight_Fun();
         Buzzer_Sound();
         if(clearEeprom==1){
              run_t.gTimer_8s =0;
              run_t.adminiId=1;
             clearEeprom = 0;
             ClearEEPRO_Data();
			 Buzzer_LongSound();
         }

		    
      if(run_t.gTimer_10s==1){ //5s ->battery be checking 
          run_t.gTimer_10s =0;
         adc= ADC_ReadVoltage();
	     if(adc <  640)BAT_LED_ON() ;//3V ->Vdd = 4.8V
		 else BAT_LED_OFF() ;
      }

	  if(run_t.panel_lock ==1){
          if(run_t.gTimer_1s >8)
		  	ERR_LED_OFF();
          if(run_t.gTimer_60s > 59){
              run_t.panel_lock =0;
			  run_t.error_times = 0;

		  }


	  }



		 #endif 
   }
     
 }
  

