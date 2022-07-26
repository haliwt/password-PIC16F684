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

static unsigned char n0,n1,n2;
unsigned char pwd1[6];
unsigned char pwd2[6];



static unsigned char CompareValue(unsigned char *pt1,unsigned char *pt2);

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
    static unsigned char adminiId,fail;
	unsigned char Readpwd[6];
	
	adminiId= EEPROM_Read_Byte(ADMINI); //
	if(adminiId !=1){ //don't new password be write to EEPROM

	     if(pwd_4 == 1234){
						   
				
			run_t.BackLight=2;
		
		    run_t.passsword_unlock=1;	
		
			

		}
		else{

		    fail =1;
			
		


		}
		

	  }
	  else{

	       
			Readpwd[0] = EEPROM_Read_Byte(ADMINI + 0X01);
			Readpwd[1] = EEPROM_Read_Byte(ADMINI + 0X02);
			Readpwd[2] = EEPROM_Read_Byte(ADMINI + 0X03);
			Readpwd[3] = EEPROM_Read_Byte(ADMINI + 0X04);
			Readpwd[4] = EEPROM_Read_Byte(ADMINI + 0X05);
			Readpwd[5] = EEPROM_Read_Byte(ADMINI + 0X06);

			 if(CompareValue(Readpwd,&pwd_4) ==1){//if(strcmp(pwd1,pwd2)==0)
				
				
				run_t.passsword_unlock=1;

			
			}
			else{

               fail =1;

			}
	 }

	 if(fail == 1){

		OK_LED_OFF();
		ERR_LED_ON();
		run_t.passswordsMatch = 0;
		run_t.Numbers_counter = 0;
		 run_t.passsword_unlock=0;	
		run_t.eepromAddress=0;
		run_t.passswordsMatch = 0;
        fail ++;


	 }

	 if(run_t.passsword_unlock ==1){

	  
		 run_t.Numbers_counter =0 ;
		 ERR_LED_OFF();
		 OK_LED_ON();
		 Buzzer_LongSound();
		 Motor_CCW_Run();//open passwordlock 
		run_t.passswordsMatch = 0;

	    run_t.passsword_unlock++;
 
	 }
	


}
	
   

/****************************************************************************
*
*Function Name:void Password_Modify(void)
*Function : run is main 
*Input Ref: NO
*Retrun Ref:NO
*
****************************************************************************/
static unsigned char CompareValue(unsigned char *pt1,unsigned char *pt2)
{
	unsigned char i ;
   for(i=1;i<6;i++){
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

	
	eevalue= EEPROM_Read_Byte(run_t.userId);
	if(eevalue ==1)run_t.userId++;
	
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
				
				return ;
		   break;


		
				  
	}

	
	

	  if(run_t.Confirm ==1){
         if(run_t.inputPwdTimes ==2){
				run_t.BackLight =1;
			 if(CompareValue(pwd1, pwd2)){
			         EEPROM_Write_Byte(run_t.userId , 0x01);
					 EEPROM_Write_Byte(run_t.userId + 0x01,pwd1[0]);
					 EEPROM_Write_Byte(run_t.userId + 0x02,pwd1[1]);
					 EEPROM_Write_Byte(run_t.userId + 0x03,pwd1[2]);
					 EEPROM_Write_Byte(run_t.userId + 0x04,pwd1[3]);
					 EEPROM_Write_Byte(run_t.userId + 0x05,pwd1[4]);
					 EEPROM_Write_Byte(run_t.userId + 0x06,pwd1[5]);

                     OK_LED_ON();
					 run_t.Confirm =0;
			    	run_t.inputPwdTimes =0;

					return;

			 }
			 else{
				ERR_LED_ON();
				run_t.Confirm =0;
			    run_t.inputPwdTimes =0;
				return ;

			 }
			  

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
 
   static  unsigned int temp_3;
   //static  unsigned long int  temp_5,temp_6;
   static unsigned char k0=0xff,k1=0xff,k2=0xff,key,spec;
 
   

    switch(dat){

	  

	case SPECIAL_1 ://0x40: //CIN1->'*'
		
       if(k0 != n0){

	      k0 = n0;
		  run_t.BackLight=1;
		  temp=0;
	  
	      temp_1=0;
		  temp_2=0;
		  temp_3=0;
		  pwd_4=0;
		  pwd_5=0;
		  pwd_6=0;
		  ERR_LED_OFF();
		  OK_LED_OFF();
	     run_t.buzzer_flag =1;
		 spec=1;
	     run_t.Numbers_counter =0 ;
		run_t.passswordsMatch = 0;
		//run_t.inputPwdTimes = 0;
		run_t.changePassword=0;
       }
		
	break;

	

	 case SPECIAL_2://0x200: //CIN10 '#' ->confirm 
         if(k1 != n1){
	        k1 = n1;
			spec=1;
		 run_t.buzzer_flag =1;
		
		 if(run_t.passsword_unlock ==1){
                run_t.Confirm = 1;
				run_t.inputPwdTimes ++ ;
		        

		 }
		 else run_t.passswordsMatch = 1;
		 	 
		 if(run_t.Numbers_counter > 3 && run_t.Numbers_counter < 7){

				 

		         switch(run_t.Numbers_counter){
             

//					case 4:
//			
//						   if(pwd_4 == 1234){
//						   
//				
//                          run_t.BackLight=2;
//						  run_t.Numbers_counter =0 ;
//						  ERR_LED_OFF();
//						  OK_LED_ON();
//						   Buzzer_LongSound();
//
//
//						   }
//						   else{
//						   	  OK_LED_OFF();
//   							  ERR_LED_ON();
//							  run_t.passswordsMatch = 0;
//						      run_t.Numbers_counter = 0;
//							  
//
//						   }
//                     
//
//							
//
//				    break;

					case 5:
						
						   if(pwd_5 == 12345){
						  run_t.BackLight=2;
							
						   run_t.Numbers_counter =0 ;
						   ERR_LED_OFF();
						   OK_LED_ON();
						   Buzzer_LongSound();


						   }
						   else{
						   	  OK_LED_OFF();
   							  ERR_LED_ON();
							  run_t.passswordsMatch = 0;
						      run_t.Numbers_counter = 0;
							 

						   }
                     

					break;

					case 6:
						
						   if(pwd_6 == 123456){
						    run_t.BackLight =2;
							
					       run_t.Numbers_counter =0 ;
						  ERR_LED_OFF();
						  OK_LED_ON();
								
						   Buzzer_LongSound();


						   }
						   else{
						   	  OK_LED_OFF();
   							  ERR_LED_ON();
							  run_t.passswordsMatch = 0;
						      run_t.Numbers_counter = 0;
							 
						   }
                     

					break;


				 }

               
	  	
	         }
		   else{
		   	 OK_LED_OFF();
			ERR_LED_ON();
			run_t.Numbers_counter = 0;

		    run_t.passswordsMatch = 0;
	  	   
	      }
		   
	   }

	 break;

	 
	case KEY_0:
		if(key==0){
     
		     key=1;
			 spec=0;
			 
		}

	 break;

    case KEY_1 :

		if(key==0){
     	
		     key=1;
			 spec=0;
			
			 
		}
			
    case KEY_2:
          if(key==0){
     	
		     key=1;
		    spec=0;
			
		}
	case  KEY_3:
		if(key==0){
  
		     key=1;
			 spec=0;
			  
		}
			
	case KEY_4:
			if(key==0){
     
		     key=1;
			 spec=0;
			 
		}
	break;
			
	case KEY_5:
			if(key==0){
     
		     key=1;
			 spec=0;
			  
		}
	break;
			
	case KEY_6:
		if(key==0){
    
		     key=1;
			 spec=0;
			 
		}
	break;
	case KEY_7:
		if(key==0){
    
		     key=1;
			 spec=0;
			
		}
	break;
			
	case KEY_8:
			if(key==0){
     	
		     key=1;
			 spec=0;
			
		}
   break;
			
	case KEY_9:
		  if(key==0 ){
		  	 key=1;
		     spec=0;
		
		}
	break;
		  

	}  

	
	  if(k2 != n2 && key==1 && spec ==0){
				k2=n2;
		        key = 0;
			    spec =1;
				
//				 run_t.Numbers_counter++;
//				 if(run_t.Numbers_counter ==1){
//
//                       OK_LED_ON();
//				 }
//				 if(run_t.Numbers_counter==2)ERR_LED_ON();
//
//				 if(run_t.Numbers_counter == 3){
//
//				          BAT_LED_ON();
//
//				 }	
//
//				 if(run_t.Numbers_counter ==4) 
//				 {
//				       
//						BAT_LED_OFF();
//				 	}
//
//				 if(run_t.Numbers_counter ==5) OK_LED_OFF();
//				 if(run_t.Numbers_counter ==6){
//
//				        ERR_LED_OFF();
//						BAT_LED_OFF();
//				         OK_LED_OFF();
//				        run_t.Numbers_counter =0;
//
//				 }
                run_t.Numbers_counter ++ ;
				run_t.buzzer_flag =1;
			
				temp = InputNumber_ToSpecialNumbers(dat); //input Numbers
				
			
			    #if 1
				 
			 
				 switch(run_t.Numbers_counter){
	        
				 	
				  case 1:
					  temp_1= temp;
				      if(run_t.inputPwdTimes ==1)pwd2[0]=temp;
					  else  pwd1[0] =temp;
					
				break;
				  
				  case 2:
					  temp_2= temp_1 *10 + temp; // 12
					  if(run_t.inputPwdTimes ==1) pwd2[1]=temp;
					  else pwd1[1] = temp;
					
				 break;
	   
				  case 3:
					   
					   temp_3= temp_2*10 + temp; //120+3
					   if(run_t.inputPwdTimes ==1)pwd2[2] =temp;
					   else pwd1[2]= temp;
					  
				 break;
	   
				  case 4: 
					   pwd_4= temp_3*10 +temp;
					   if(run_t.inputPwdTimes ==1)pwd2[3] =temp;
					   else pwd1[3] = temp;
					   
				  break;
	   
				  case 5:
					   pwd_5= pwd_4*10 + temp;
					   if(run_t.inputPwdTimes ==1) pwd2[4] = temp;
					   else pwd1[4] =temp;
				break;
	   
				  case 6:
					   pwd_6= pwd_5*10 + temp;
					   if(run_t.inputPwdTimes ==1) pwd2[5] =temp;
					   else pwd1[5]= temp;
					
				  break;
	            
				 
				 
				  
				  }
				  
	         
				 
	   
				   #endif 
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

           Administrator_Password_Init();
   	}
//	   
//	 run_t.BackLight =2;
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
    unsigned char  i;

	if(run_t.buzzer_flag ==1 ){
			  
		 run_t.buzzer_flag=0;
	//	 run_t.Numbers_counter++;

		 BUZZER_KeySound();
	   
         i=1;
	              
	}
	else{
	
				  
	   BUZZER_PIN_OFF() ;
	}

   

   if(i==1){
   	
      __delay_ms(300);
				  n0++;
				  n1++;
				  n2++;
		
				  

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

void BackLight_Fun(void)
{
	 if(run_t.BackLight ==1 ){

			  run_t.BackLight =0;
		      BACKLIGHT_ON() ;
		    
	}
	else{

              BACKLIGHT_OFF() ;
			 
			 
    }

	 if(run_t.BackLight==2){
	 	 run_t.BackLight =0;
	 	
	    BACKLIGHT_2_ON();
	    BACKLIGHT_ON() ;

     }
	 else{

	     BACKLIGHT_OFF() ;
         BACKLIGHT_2_OFF();

	 }
	

		 

}
