#include "../inc/run.h"
#include "../../main.h"

#define MAX_VIRT    20


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

#define ADMIN_SAVE_ADD        0x80  //administrator of be save 
#define USER_SAVE_ADD_1        0X81
#define USER_SAVE_ADD_2        0x82

//#define unsigned char       uint8_t 




//unsigned long int  passwordNumbers ;








unsigned char n0,n1;




//static unsigned char CompareValue(unsigned char *pt1,unsigned char *pt2);

static void ReadPassword_EEPROM_SaveData(void);

//static void NewPassword_Administrator_Login(void);
static void Administrator_Password_Init(void);

unsigned char  InputNumber_ToSpecialNumbers(TouchKey_Numbers number);




/****************************************************************************
	*
	*Function Name:void Administrator_Password_Init(void)
	*Function : run is main 
	*Input Ref: NO
	*Retrun Ref:NO
	*
****************************************************************************/
static void Administrator_Password_Init(void)
{
    unsigned char adminiId;
	adminiId= EEPROM_Read_Byte(ADMINI); //
	if(adminiId !=1){ //don't new password be write to EEPROM
	  
	 

	

		  
		run_t.passsword_unlock=0;	
		run_t.eepromAddress=0;
		run_t.passswordsMatch = 0;
		run_t.Numbers_counter=0;

		return;
		

	  }
	  else{

	  //run_t.BackLight =1;
//			//run_t.eepromAddress++ ;	
//			Readpwd[0] = EEPROM_Read_Byte(ADMINI + 0X01);
//			Readpwd[1] = EEPROM_Read_Byte(ADMINI + 0X02);
//			Readpwd[2] = EEPROM_Read_Byte(ADMINI + 0X03);
//			Readpwd[3] = EEPROM_Read_Byte(ADMINI + 0X04);
//			Readpwd[4] = EEPROM_Read_Byte(ADMINI + 0X05);
//			Readpwd[5] = EEPROM_Read_Byte(ADMINI + 0X06);
//
//			 if(CompareValue(Readpwd,pwd1) ==1){//if(strcmp(pwd1,pwd2)==0)
//				
//				OK_LED_ON();
//				Motor_CCW_Run();//open passwordlock 
//				run_t.passsword_unlock=1;
//				run_t.admini_confirm =1;
//				run_t.resetKey++;
//				run_t.inputNumber++;
//				return ;
//
//	        }
	 }
	 run_t.passsword_unlock=0;


}
	
   

/****************************************************************************
*
*Function Name:void Password_Modify(void)
*Function : run is main 
*Input Ref: NO
*Retrun Ref:NO
*
****************************************************************************/
unsigned char CompareValue(unsigned char *pt1,unsigned char *pt2)
{
	unsigned char i ;
   for(i=1;i<5;i++){
		if(*(pt1+i) != *(pt2+i)){
			return 0;
		}
	}
	return 1;
   

   
}




/****************************************************************************
*
*Function Name:static void ReadPassword_EEPROM_SaveData(void)
*Function : run is main 
*Input Ref: NO
*Retrun Ref:NO
*
****************************************************************************/
void SavePassword_To_EEPROM(void)
{
	unsigned char eevalue;
    switch(run_t.userId){
					  
		   case 0:
		
				run_t.userId= ADMINI;
				
		   break;

		   case 1 :
		        run_t.userId = USER_1;
			break;
		  
		   case 2: 
				run_t.userId = USER_2; 
			break;
		   
		   case 3 :
		     run_t.userId = USER_3; 
				
			break;
		   
		   case 4: 
	           run_t.userId = USER_4; 
			break;

		   case 5 :
		       run_t.userId = USER_5;  
			break;
		   
		   case 6: 
		        run_t.userId = USER_6; 
			
		    break;
		   case 7 :
		
		        run_t.userId = USER_7; 
			
		    break;
		   
		   case 8: 
		
			  run_t.userId = USER_8; 
			break;
		   
		   case 9 :
	
			run_t.userId = USER_9; 
				
			break;
		  
		   case 10:
		
			run_t.userId = USER_10; 
			break;

		   case 11:
				
				run_t.userId = 0;
				//run_t.keyTime++;
				return ;
		   break;


		eevalue= EEPROM_Read_Byte(run_t.userId);
		if(eevalue==0xff){
#if 0
			EEPROM_Write_Byte(run_t.userId , 0x01);
			EEPROM_Write_Byte(run_t.userId + 0x01,pwd1[0]);
			EEPROM_Write_Byte(run_t.userId + 0x02,pwd1[1]);
			EEPROM_Write_Byte(run_t.userId + 0x03,pwd1[2]);
			EEPROM_Write_Byte(run_t.userId + 0x04,pwd1[3]);
			EEPROM_Write_Byte(run_t.userId + 0x05,pwd1[4]);
			EEPROM_Write_Byte(run_t.userId + 0x06,pwd1[5]);
#endif 
		}
		else{
			run_t.userId++;
		}
				  
	}
			  
}



/****************************************************************************
*
*Function Name:static void ReadPassword_EEPROM_SaveData(void)
*Function : run is main 
*Input Ref: NO
*Retrun Ref:NO
*
****************************************************************************/
static void ReadPassword_EEPROM_SaveData(void)
{
  
	  static  unsigned char eevalue ,ReadAddress;
	      switch(run_t.eepromAddress){

			  case 0:
                   ReadAddress = ADMINI;
			  break;
			  case 1:
                  ReadAddress = USER_1;
               
            break;

			  case 2:
			      ReadAddress = USER_2;
            break;

			case 3:
			      ReadAddress = USER_3;
            break;

			case 4:
			      ReadAddress = USER_4;
            break;

			case 5:
			     ReadAddress = USER_5;
             break;

			case 6:
			      ReadAddress = USER_6;
             break;
             
			 case 7:
			     ReadAddress = USER_7;
               break;

			  case 8:
			  
                ReadAddress = USER_8;
              break;

			  case 9:
			  
                   ReadAddress = USER_9;
            break;

			  case 10:
			  
                   ReadAddress = USER_10;
                break;

			  case 11:
                 ERR_LED_ON();
				 run_t.eepromAddress=0;
				  run_t.userId++;
                return ;
			 break;

        }

		if(ReadAddress == ADMINI){

			 Administrator_Password_Init();
		}
		else{		
			eevalue = EEPROM_Read_Byte(ReadAddress);
			if(eevalue ==1){
#if 0
					Readpwd[0] = EEPROM_Read_Byte(ReadAddress + 0X01);
					Readpwd[1] = EEPROM_Read_Byte(ReadAddress + 0X02);
					Readpwd[2] = EEPROM_Read_Byte(ReadAddress + 0X03);
					Readpwd[3] = EEPROM_Read_Byte(ReadAddress + 0X04);
					Readpwd[4] = EEPROM_Read_Byte(ReadAddress + 0X05);
					Readpwd[5] = EEPROM_Read_Byte(ReadAddress + 0X06);
					if(CompareValue(Readpwd,pwd1) ==1)//if(strcmp(pwd1,pwd2)==0)
					{
						OK_LED_ON();
						Motor_CCW_Run();//open passwordlock 
						return ;

					}
					else{
						run_t.eepromAddress++ ;	
					}
#endif 
			}
			else{
	            run_t.eepromAddress++ ;	
			}
		}
		
}

/****************************************************************************
*
*Function Name:void RunCheck_Mode(unsigned int dat)
*Function : run is main 
*Input Ref: NO
*Retrun Ref:NO
*
****************************************************************************/
void RunCheck_Mode(unsigned int dat)
{
   unsigned char temp;
   static unsigned char	temp_1,temp_2;
   static  unsigned int temp_3,temp_4;
   static  unsigned long int  temp_5,temp_6;
   unsigned char k0=0xff,k1=0xff;
 
     if(dat ==0)return ;

    if(dat !=SPECIAL_1 && dat != SPECIAL_2 && run_t.passswordsMatch ==0){

			
			if(k0 != n1){
			   k0=n1;
			run_t.passswordsMatch = 0;
			 temp = InputNumber_ToSpecialNumbers(dat); //input Numbers
		   
			  run_t.Numbers_counter ++ ;
			
			  switch(run_t.Numbers_counter){
	
			   case 1:
				   temp_1= temp;
				  // pwd[0] =temp;
			        
			   run_t.buzzer_flag =1;
	
			   break;
			   
			   case 2:
				   temp_2= temp_1 *10 + temp; // 12
				  // pwd[1] =temp;
				 
			   run_t.buzzer_flag =1;
			   break;
	
			   case 3:
					
					temp_3= temp_2*10 + temp; //120+3
					//pwd[2] =temp;
					
			   run_t.buzzer_flag =1;
	
			   break;
	
			   case 4: 
					temp_4= temp_3*10 +temp;
					//pwd[3] =temp;
					
			   run_t.buzzer_flag =1;
			   break;
	
			   case 5:
					temp_5= temp_4*10 + temp;
					//pwd[4] =temp;
					
			   run_t.buzzer_flag =1;
			   break;
	
			   case 6:
					temp_6= temp_5*10 + temp;
					//pwd[5] =temp;
					
			          run_t.buzzer_flag =1;
			   break;

			   default:
			   	run_t.passswordsMatch = 0;
			   run_t.buzzer_flag =0;

			   break;
			  
			   
			   }
			   
	
	          
	
			}


	}
    else{
	switch(dat){

	case SPECIAL_1 ://0x40: //CIN1->'*'
		
       if(k1 != n1){

	      k1 = n1;
		  temp=0;
	  
	      temp_1=0;
		  temp_2=0;
		  temp_3=0;
		  temp_4=0;
		  temp_5=0;
		  temp_6=0;
	     run_t.buzzer_flag =1;

	     run_t.Numbers_counter =0 ;
		run_t.passswordsMatch = 0;
		//run_t.passsword_error=0;  //modeify password is input mistake number error blank of flag.
		run_t.changePassword=0;
       	}
		
	break;

	

	 case SPECIAL_2://0x200: //CIN10 '#'
         if(k1 != n1){
	        k1 = n1;
	
		   if(run_t.Numbers_counter > 3 && run_t.Numbers_counter < 7){

				 

		         switch(run_t.Numbers_counter){


					case 4:
						run_t.buzzer_flag =1;
						   if(temp_4 == 1234){
						    run_t.BackLight =1;
							
						 // run_t.passswordsMatch = 0;
                           run_t.Numbers_counter = 0;

						   Buzzer_LongSound();


						   }
						   else{
   							  //run_t.passswordsMatch = 0;
						      run_t.Numbers_counter = 0;
							  return ;

						   }
                     

							

				    break;

					case 5:

					break;

					case 6:

					break;


				 }

               
	  	
	         }
		   else{

		 //   run_t.passswordsMatch = 0;
	  	     run_t.buzzer_flag =1;
	         run_t.Numbers_counter = 0;

		     return ;


		   }
		   
	   }

	 break;

	 default:
	 	  run_t.buzzer_flag =0;
	 break;


	}

}
}  

/****************************************************************************
*
*Function Name:void RunCheck_Mode(unsigned int dat)
*Function : run is main 
*Input Ref: NO
*Retrun Ref:NO
*
****************************************************************************/
void RunCommand_Unlock(void)
{


	if(run_t.passswordsMatch ==1 && run_t.changePassword==0){ //be pressed "#" is over confirm 

    

      //run_t.passswordsMatch =0;
	}
	  ///if(run_t.Numbers_counter==2)run_t.BackLight =1;

	 //  Administrator_Password_Init();
	   
	 // run_t.BackLight =1;
//
//      //virtual password  run_t.Numbers_counter > 4 &&  run_t.Numbers_counter < 20
//      if(run_t.Numbers_counter > 6  && run_t.Numbers_counter < 21){
//
//           tempCounter = run_t.Numbers_counter;
//
//	      
//		  // VirtualPwd[tempCounter] = VirtualPwd[tempCounter] <<1;
//	       pwd1[5]= VirtualPwd[tempCounter];
//		   pwd1[4]= VirtualPwd[tempCounter-1];
//		   pwd1[3]= VirtualPwd[tempCounter-2];
//		   pwd1[2]= VirtualPwd[tempCounter-3];
//		   pwd1[1]= VirtualPwd[tempCounter-4];
//		   pwd1[0]= VirtualPwd[tempCounter-5];
//		   run_t.passswordsMatch=1;
//          
//		  
//	  }
//	
//	  
//	 ReadPassword_EEPROM_SaveData();
//	 if(run_t.Numbers_counter >6){
//       VirtualPwd[tempCounter] = VirtualPwd[tempCounter] <<1;
//		   i++;
//		   if(i>run_t.Numbers_counter){
//             i=0;
//			 run_t.passsword_unlock =0;
//		     run_t.Numbers_counter=0;
//			 run_t.passswordsMatch=0;
//			 return ;
//			 
//            }
//		   
//    }
//     
	

  

   
}

/****************************************************************************
*
*Function Name:void RunCheck_Mode(unsigned int dat)
*Function : run is main 
*Input Ref: NO
*Retrun Ref:NO
*
****************************************************************************/
//void Modidy_NewPassword_Function(void)
//{
//     unsigned char setupkey;
//	 static unsigned char setInit =0xff,inputnumber=0xff;
//
//	 if(run_t.admini_confirm ==1){ //setup new user password for 10 numbers
//
//	     setupkey = Scan_Key();
//		 
//
//         if(setupkey ==0x81 || run_t.changePassword ==1){
//
//           run_t.changePassword=1;
//		   if(setInit != run_t.resetKey){
//		   	   setInit = run_t.resetKey;
//			   BUZZER_KeySound();
//           	}
//		    Administrator_Password_Init();
//		    if(run_t.passsword_unlock == 1){
//				
//		        if(inputnumber != run_t.inputNumber){
//					inputnumber = run_t.inputNumber;
//					BUZZER_KeySound();
//					BUZZER_KeySound();
//		    	}
//			
//			     } 
//		    }
//			
//			
//
//			
//			     
//    }
// }
/****************************************************************************
*
*Function Name:void RunCheck_Mode(unsigned int dat)
*Function : run is main 
*Input Ref: NO
*Retrun Ref:NO
*
****************************************************************************/
void Buzzer_Sound(void)
{
    uint8_t i;

	if(run_t.buzzer_flag ==1){
			  
		 run_t.buzzer_flag=0;

		 BUZZER_KeySound();
         i=1;
	              
	}
	else{
	
				  
	   BUZZER_PIN_OFF() ;
	}

	

   if(i==1){
   	
      __delay_ms(200);
				  n0++;
				  n1++;
				  

	 i=0;
    run_t.passswordsMatch =0;
   }
}

unsigned char  InputNumber_ToSpecialNumbers(TouchKey_Numbers number)
{
     unsigned char temp ;
	 switch(number){

      case KEY_1: 
            
	 	    temp = 1;

	  break; 

	  case KEY_2:

	       temp =2;

	  break;

	  case KEY_3:
	  	   temp =3;

	  break;

	  case KEY_4:
	  	   temp =4;
	  break;

	  case KEY_5:
	  	   temp = 5;

	  break;

	  case 	KEY_6:

	       temp =6;

	  break;

	  case KEY_7 :

	       temp =7;
	  break;

	  case KEY_8 :

	       temp =8;
	  break;

	  case KEY_9 :

	       temp =9;
	  break;

	  case KEY_0 :

	       temp =0;
	  break;


      default :

	  break;



	 }

	return temp;

}
