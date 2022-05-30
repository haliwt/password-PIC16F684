#include "../inc/run.h"
#include "../../main.h"



#define ADMINI     		0X00
#define USER_1     		0X11  
#define USER_2     		0X1C
#define USER_3     		0X27
#define USER_4    	 	0X32  
#define USER_5     		0X3D
#define USER_6    	 	0X48
#define USER_7    	 	0X53  
#define USER_8     		0X5E
#define USER_9     		0X69
#define USER_10    	 	0X74






unsigned char eeprom_buf[7];
KEY_T key_t;



static void CProcessDispatchRun(unsigned char sig);
static void Get_KeyValue(unsigned char sig);

/**
 * @brief 
 * 
 * @param pt 
 
 * @param sig 
 */
static void CProcessDispatchRun(unsigned char sig)
{
  
	switch(run_t.state_){ //state ? 
	
		   case is_Idle :
	
		   case is_Start:
	
				Get_KeyValue(sig);
				   
			   
			   
		   break;
	
	
		   case is_Doing:
	
		   break;
	
		   case is_Exit:
	
	
		   break;
	   
	
	
	   }
}

/*************************************************************
	*
	*Function Name:static void Get_KeyValue(unsigned char sig)
	*Function : key of value
	*Input Ref: NO
	*Retrun Ref:NO
	*
**************************************************************/
static void Get_KeyValue(unsigned char sig)
{
      switch (sig) { //signal

      case KEY_0 : //KEY_0 

      break;

      case KEY_1:
	  	 switch(run_t.cmdCtr_){

		 case 1: //the first times input password key
		 	  eeprom_buf[0] = EEPROM_Read_Byte(0x00); //address :0x00 ~0x7F (128bytes)
			
			
			if(eeprom_buf[0]==0){ //administrator of password 

                  run_t.password_low_bits = 0x02;   // 9876543210 = 
             }
			else{

				eeprom_buf[1] = EEPROM_Read_Byte(0x01); //address :0x00 ~0x7F (128bytes)
				
			    if(eeprom_buf[1] == 0x01){

					 run_t.password_low_bits = 0x02;   // 9876543210 = 	
				}
				else{
                    return ;

				}


			}

		 break;

		 case 2: //the second times input password key


		        eeprom_buf[2] = EEPROM_Read_Byte(0x02); //address :0x00 ~0x7F (128bytes)
				
			    if(eeprom_buf[2] == 0x01){

					 run_t.password_low_bits = 0x02;   // 9876543210 = 	
				}
				else{
                    return ;

				}
		 break;
				
		 case 3: //the third times input password key 
			  eeprom_buf[2] = EEPROM_Read_Byte(0x02); //address :0x00 ~0x7F (128bytes)
				
			    if(eeprom_buf[2] == 0x01){

					 run_t.password_low_bits = 0x02;   // 9876543210 = 	
				}
				else{
                    return ;

				}
		 break;

		 case 4: //the fourth times input password key

		 break;

		 case 5: //the fiveth times input password key

		 break;

		 case 6://the sixth times input password key 

		 break;

		 default :
                
                return ;              
		 break;
	  	
	  	}

    

	  //"KEY_2"

	  case KEY_2:

		switch (run_t.cmdCtr_){
		
	  	case 1:
		 	
			  eeprom_buf[1] = EEPROM_Read_Byte(0x01); //address :0x00 ~0x7F (128bytes)
				
			    if(eeprom_buf[1] == 0x02){

					 run_t.password_low_bits = 0x04;   // 98->76543210 = 	
				}
				else{
                    return ;

				}


		

		 break;

		 case 2:

		           eeprom_buf[0] = EEPROM_Read_Byte(0x00); //address :0x00 ~0x7F (128bytes)
					 
					 
					 if(eeprom_buf[0]==0){
		 
						   run_t.password_low_bits = 0x04;	 // 9876543210 = 
					  }
					 else{
		 
						 eeprom_buf[2] = EEPROM_Read_Byte(0x02); //address :0x00 ~0x7F (128bytes)
						 
						 if(eeprom_buf[2] == 0x02){
		 
							  run_t.password_low_bits = 0x04;	// 9876543210 =  
						 }
						 else{
							 return ;
		 
						 }
		 
		 
					 }
		 break;
				
		 case 3:
			  eeprom_buf[2] = EEPROM_Read_Byte(0x02); //address :0x00 ~0x7F (128bytes)
				
			    if(eeprom_buf[2] == 0x02){

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
		   eeprom_buf[0] = EEPROM_Read_Byte(0x00); //address :0x00 ~0x7F (128bytes)
		   if(eeprom_buf[0]==0){
		         run_t.head = 0; //default administrator password 
		   	}
		   else{

			 run_t.head = eeprom_buf[0] ;
		   }
				   
		
		}
		else{ //clear input Key numbers 

              run_t.password_low_bits = 0x00; 
			  run_t.cmdCtr_ = 0;

		}
	  
     break;
	  
	  case KEY_11: //"#"
	  
		break;
	  
			
	 
      }



}


/****************************************************************************
*
*Function Name:void CProcessCmdRun(void)
*Function : run is main 
*Input Ref: NO
*Retrun Ref:NO
*
****************************************************************************/
void CProcessCmdRun(void)
{
    uint8_t  sig;
   if(run_t.cmdCtr_ ==0){
         run_t.state_= is_Idle;
   }
   I2C_Simple_Read_Device(OUTPUT0_REG,&key_t.KeyValue);
   while ( key_t.KeyValue != 0) {
        BACKLIGHT_ON(); //LED ON 8s 
       run_t.cmdCtr_ ++ ;
       switch (key_t.KeyValue ){
	   	
       case 0x01: sig = KEY_6;   break; //KEY6 =6
       
       case 0x02:sig = KEY_10;   break; //KEY0 = *
       
       case 0x04: sig = KEY_7;   break; //KEY7 =7

       case 0x08: sig = KEY_1;   break; //KEY1 =1

       case 0x10: sig = KEY_8;   break; // KEY8=8

       case 0x20: sig = KEY_2;   break; //KEY2 = 2

       case 0x40: sig = KEY_9;   break; //KEY9 = 9

       case 0x80: sig = KEY_3;   break; //KEY =3

       case 0x100: sig = KEY_0;  break;  //KEY= 0

       case 0x200: sig = KEY_4;  break;  //KEY4= 4

       case 0x400: sig = KEY_11; break; //KEY11 = #

       case 0x800: sig = KEY_5;  break;  //KEY5 =5

       default: 
         break;
       }
       CProcessDispatchRun(sig); 
      
   }



}


