#include "../inc/run.h"
#include "../../main.h"


KEY_T key_t;

static void CProcessDispatchRun(unsigned char sig);
/**
 * @brief 
 * 
 * @param pt 
 
 * @param sig 
 */
static void CProcessDispatchRun(unsigned char sig)
{
   static unsigned char eepromData;
   switch (run_t.state_) {

   case is_Start: //state 
      switch (sig) { //signal

      case KEY_0 : //KEY_0 

      break;

      case KEY_1:
	  	 switch(run_t.cmdCtr_){

		 case 1:
		 	run_t.eeprom_buf[0] = EEPROM_Read_Byte(0x00); //address :0x00 ~0x7F (128bytes)
			
			
			if(run_t.eeprom_buf[0]==0){

                  run_t.password_low_bits = 0x02;   // 9876543210 = 
             }
			else{

				run_t.eeprom_buf[1] = EEPROM_Read_Byte(0x01); //address :0x00 ~0x7F (128bytes)
				
			    if(run_t.eeprom_buf[1] == 0x01){

					 run_t.password_low_bits = 0x02;   // 9876543210 = 	
				}
				else{
                    return ;

				}


			}

		 break;

		 case 2:


		        run_t.eeprom_buf[2] = EEPROM_Read_Byte(0x02); //address :0x00 ~0x7F (128bytes)
				
			    if(run_t.eeprom_buf[2] == 0x01){

					 run_t.password_low_bits = 0x02;   // 9876543210 = 	
				}
				else{
                    return ;

				}
		 break;
				
		 case 3:
			  run_t.eeprom_buf[2] = EEPROM_Read_Byte(0x02); //address :0x00 ~0x7F (128bytes)
				
			    if(run_t.eeprom_buf[2] == 0x01){

					 run_t.password_low_bits = 0x02;   // 9876543210 = 	
				}
				else{
                    return ;

				}
		 break;

		 case 4:

		 break;

		 case 5:

		 break;

		 case 6:

		 break;
	  	
	  	}

    

	  //"KEY_2"

	  case KEY_2:

		switch (run_t.cmdCtr_){
		
	  	case 1:
		 	
			  run_t.eeprom_buf[1] = EEPROM_Read_Byte(0x01); //address :0x00 ~0x7F (128bytes)
				
			    if(run_t.eeprom_buf[1] == 0x02){

					 run_t.password_low_bits = 0x04;   // 98->76543210 = 	
				}
				else{
                    return ;

				}


		

		 break;

		 case 2:

		           run_t.eeprom_buf[0] = EEPROM_Read_Byte(0x00); //address :0x00 ~0x7F (128bytes)
					 
					 
					 if(run_t.eeprom_buf[0]==0){
		 
						   run_t.password_low_bits = 0x04;	 // 9876543210 = 
					  }
					 else{
		 
						 run_t.eeprom_buf[2] = EEPROM_Read_Byte(0x02); //address :0x00 ~0x7F (128bytes)
						 
						 if(run_t.eeprom_buf[2] == 0x02){
		 
							  run_t.password_low_bits = 0x04;	// 9876543210 =  
						 }
						 else{
							 return ;
		 
						 }
		 
		 
					 }
		 break;
				
		 case 3:
			  run_t.eeprom_buf[2] = EEPROM_Read_Byte(0x02); //address :0x00 ~0x7F (128bytes)
				
			    if(run_t.eeprom_buf[2] == 0x02){

					 run_t.password_low_bits = 0x04;   // 98 -> 76543210 = 	
				}
				else{
                    return ;

				}
		 break;

		 case 4:

		 break;

		 case 5:

		 break;

		 case 6:

		 break;
		}

      break;

	  //"KEY_3"

	  case KEY_3:

      break;

	  case KEY_4:

      break;

	  
	  case KEY_5:
	  
		break;
	  
	  case KEY_6:
	  
		break;
	  
	  case KEY_7:
	  
		break;
	  
	  case KEY_8:
	  
		break;
	  
	  case KEY_9:
	  
		break;
	  
	  case KEY_10: //"*"  -> 1. administrator password first sysbol . 2-> cancel 
	      
		if(run_t.cmdCtr_ ==1){ //the first input key of number 
 			run_t.cmdCtr_ ++;
		   run_t.eeprom_buf[0] = EEPROM_Read_Byte(0x00); //address :0x00 ~0x7F (128bytes)
		   if(run_t.eeprom_buf[0]==0){
		         run_t.head = 0;
		   	}
		   else{

			 run_t.head = run_t.eeprom_buf[0] ;
		   }
				   
		
		}
		else{

            run_t.password_low_bits = 0x00; 
			run_t.cmdCtr_ = 0;

		}
	  
     break;
	  
	  case KEY_11: //"#"
	  
		break;
	  
			
	 
      }
      break;

   case is_Idle: //state
      switch (sig) { //siginal
      case KEY_0:
        // pt->commentCtr_ += 2;         /* SLASH-STAR count as comment */
        // CParser1Tran(me, COMMENT);     /* transition to "comment" */
         break;
       }
     break;

  
      
   
    }
}


void CProcessCmdRun(void)
{
    uint8_t  sig;

   run_t.state_= is_Idle;
   I2C_Simple_Read_Device(OUTPUT0_REG,&key_t.KeyValue);
   while ( key_t.KeyValue != 0) {
        BACKLIGHT_ON(); //LED ON 8s
       run_t.state_= is_Start;
       run_t.cmdCtr_ ++ ;
       switch (key_t.KeyValue ){
       case 0x01: //KEY6 =6
        sig = KEY_6;     
        break; 
       case 0x02: //KEY0 = *
        sig = KEY_10;    
        break; 
       case 0x04: //KEY7 =7
        sig = KEY_7;     
        break; 
       case 0x08: 
        sig = KEY_1;     
        break; //KEY1 =1
       case 0x10: 
        sig = KEY_8;     
        break; // KEY8=8
       case 0x20: 
        sig = KEY_2;     
        break; //KEY2 = 2
       case 0x40: 
        sig = KEY_9;     
        break; //KEY9 = 9
       case 0x80: 
        sig = KEY_3;     
        break; //KEY =3
       case 0x100: 
        sig = KEY_0;    
        break;  //KEY= 0
       case 0x200: 
        sig = KEY_4;    
        break;  //KEY4= 4
       case 0x400: //KEY11 = #
        sig = KEY_11;   
        break;  
       case 0x800: //KEY5 =5
        sig = KEY_5;    
        break;  

       default: 
         break;
       }
       CProcessDispatchRun(sig); 
      
   }



}


