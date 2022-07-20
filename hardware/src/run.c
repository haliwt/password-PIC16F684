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

unsigned char Readpwd[MAX_SIZE];
unsigned char pwd1[MAX_SIZE];
unsigned char pwd2[MAX_SIZE];
unsigned char tempArr[MAX_SIZE]={0,1,2,3,4};



unsigned char VirtualPwd[MAX_VIRT];





unsigned char n0,n1,n2,n3,n4,n5,n6,n7,n8,n9,n10,n11;




//static unsigned char CompareValue(unsigned char *pt1,unsigned char *pt2);

static void ReadPassword_EEPROM_SaveData(void);

//static void NewPassword_Administrator_Login(void);
static void Administrator_Password_Init(void);





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
	if(adminiId ==0xff || adminiId ==0){ //don't new password be write to EEPROM
	  
	 

	   // if(run_t.Numbers_counter ==2)run_t.BackLight =1;
      //if(CompareValue(pwd1,tempArr) ==1){// default password    is "1 2 3 4"
          if(pwd1[1] ==1){
			  if(pwd1[2]==2){
                  if(pwd1[3]==3){
                     if(pwd1[4]==4){
							Motor_CCW_Run();//open passwordlock 
					        __delay_ms(500);
							run_t.passsword_unlock=1;
							run_t.eepromAddress=0;
							run_t.Numbers_counter=0;
							 run_t.BackLight =1;
							return ;


					 }

				  }
			  }


		  }

		  
		run_t.passsword_unlock=0;	
		run_t.eepromAddress=0;
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
    switch(run_t.cmdCtr_){
					  
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
				
				run_t.cmdCtr_ = 0;
				//run_t.keyTime++;
				return ;
		   break;


		eevalue= EEPROM_Read_Byte(run_t.userId);
		if(eevalue==0xff){
			EEPROM_Write_Byte(run_t.userId , 0x01);
			EEPROM_Write_Byte(run_t.userId + 0x01,pwd1[0]);
			EEPROM_Write_Byte(run_t.userId + 0x02,pwd1[1]);
			EEPROM_Write_Byte(run_t.userId + 0x03,pwd1[2]);
			EEPROM_Write_Byte(run_t.userId + 0x04,pwd1[3]);
			EEPROM_Write_Byte(run_t.userId + 0x05,pwd1[4]);
			EEPROM_Write_Byte(run_t.userId + 0x06,pwd1[5]);
		}
		else{
			run_t.cmdCtr_++;
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
				  run_t.cmdCtr_++;
                return ;
			 break;

        }

		if(ReadAddress == ADMINI){

			 Administrator_Password_Init();
		}
		else{		
			eevalue = EEPROM_Read_Byte(ReadAddress);
			if(eevalue ==1){

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
   unsigned char i;
   unsigned char k0,k1=0xff,k2= 0xff,k3=0xff,k4=0xff,k5=0xff,k6=0xff,k7=0xff,k8=0xff,k9=0xff,k10=0xff,k11=0xff;

	switch(dat){

	

	case SPECIAL_1 ://0x40: //CIN1->'*'
		
       if(k0 != n0){

	      k0 = n0;
	   
	     run_t.buzzer_flag =1;

	     run_t.Numbers_counter =0 ;
		run_t.passswordsMatch = 0;
		run_t.passsword_error=0;  //modeify password is input mistake number error blank of flag.
		run_t.changePassword=0;
       	}
		
	break;

	 case KEY_6://0x80: //CIN0  //09H -> D7~D4  , 08H -> D7~D0 -> CIN0 -> D7, CIN1->D6
    

          if(k6 != n6){
		  	  k6 =n6;
			
			  run_t.buzzer_flag =1;
			  run_t.Numbers_counter ++ ;
		
			  
	          VirtualPwd[6]=6;
	          pwd1[6]=6;
		    
	          
			if(run_t.keyTime==1){
				  pwd2[6]=6;
		   }
		 
		  run_t.passswordsMatch = 0;

          }
	   
	 break;

	 

	 case KEY_7://0x20: //CIN2

	    if(k7 != n7){
			k7 = n7;
		
		    run_t.buzzer_flag =1;
		    run_t.Numbers_counter ++ ;
		 
		  
		    VirtualPwd[7]=7;
			pwd1[7]=7;
		  
		  if(run_t.keyTime==1){
				  pwd2[7]=7;
		   }
		 

		     run_t.passswordsMatch = 0;
	    }
	   
	 break;

	  case KEY_1: //0x1000: //CIN3

	     if(k1 != n1){
		 	k1=n1;
		
			run_t.buzzer_flag =1;
			run_t.Numbers_counter ++ ;

			VirtualPwd[11]=1; //i=0
			pwd1[1]=1;

			run_t.passswordsMatch = 0;
			if(run_t.keyTime==1){
			pwd2[1]=1;
			}


			run_t.passswordsMatch = 0;

	     	}

	 break;

	 case   KEY_8://0x08: //CIN4

	  if(k8 !=n8){
          k8 = n8;
		
	      run_t.buzzer_flag =1;
		 run_t.Numbers_counter ++ ;
		
		 
		 VirtualPwd[8]=8;
		   pwd1[8]=8;
		  
			
		if(run_t.keyTime==1){
				  pwd2[8]=8;
		 }
		
		 run_t.passswordsMatch = 0;

	  	}

     
	 break;

	 case KEY_2://0x400: //CIN5

	    if(k2 != n2){
           k1= n2;
	
		 run_t.buzzer_flag =1;
		 run_t.Numbers_counter ++ ;

		
		 VirtualPwd[2]=2;
		 pwd1[2]=2;
		
		   
		 if(run_t.keyTime==1){
				 pwd2[2]=2;
		   }

		
		  
		   run_t.passswordsMatch = 0;
		 
	    }

	 break;


	 case KEY_9://0x02: //CIN6

		if(k9 !=n9){
			k9 = n9;
		
		run_t.buzzer_flag =1;
		run_t.Numbers_counter ++ ;
	  
		VirtualPwd[9]=9;
		pwd1[9]=9;

		if(run_t.keyTime==1){
			pwd2[9]=9;
		}
	

	
		run_t.passswordsMatch = 0;
		}

	 break;

	 case KEY_3://0x100: //CIN7

	    if(k3 != n3){
			k3= n3;
		
		run_t.buzzer_flag =1;
		run_t.Numbers_counter ++ ;
	
		
		VirtualPwd[3]=3;
		pwd1[3]=3;

		
		if(run_t.keyTime==1){
			pwd2[3]=3;
		}
		

   
		run_t.passswordsMatch = 0;
	    }

	 break;

	 case KEY_0://0x800: //CIN8

	    if(k10 != n10){
			k10 = n10;
		
		run_t.buzzer_flag =1;
		run_t.Numbers_counter ++ ;
	
		VirtualPwd[10]=0;
		pwd1[10]=0;

	
		if(run_t.keyTime==1){
			pwd2[10]=0;
		}
		
       run_t.passswordsMatch = 0;
	
	    }
	 break;

	 case KEY_4://0x400: //CIN9

	   if(k4 != n4){
	   	  k4 = n4;
		
		 run_t.buzzer_flag =1;
		  run_t.Numbers_counter ++ ;
		
		 
		 VirtualPwd[4]=4;
		 pwd1[4]=4;
		 

		   
		 if(run_t.keyTime==1){
				  pwd2[4]=4;
		   }
		   run_t.passswordsMatch = 0;
	   	}
	 break;

	case KEY_5://0x10: //CIN11
	  if(k5 != n5){
	  	  k5 = n5;
		
			 run_t.buzzer_flag =1;
			 run_t.Numbers_counter ++ ;
			
			 VirtualPwd[5]=5;
			 pwd1[5]=5;
			
			
			  if(run_t.keyTime==1){
		          pwd2[5]=5;

			  }
			run_t.passswordsMatch = 0;
	  	}

	 break;

	 case SPECIAL_2://0x200: //CIN10 '#'
         if(k11 != n11){
	        k11 = n11;
		 	run_t.buzzer_flag =1;
		    run_t.passswordsMatch = 1;

         	}

	 break;

	 default:
	 	
	 // run_t.BackLight =0;
	  run_t.buzzer_flag =0;
	  

	 break;


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

      run_t.passswordsMatch =0;
	  // if(pwd1[0]==1  && pwd1[1]==2)run_t.BackLight =1;
	  ///if(run_t.Numbers_counter==2)run_t.BackLight =1;

	   Administrator_Password_Init();
	   
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
			  
	
				  BUZZER_KeySound();
                  i=1;
	              
	}
	else{
	
				  
	   BUZZER_PIN_OFF() ;
	}

	

   if(i==1){
   	 i=0;
      __delay_ms(300);
				  n0++;
				  n1++;
				  n2++;
				  n3++;
				  n4++;
				  n5++;
				  n6++;
				  n7++;
				  n8++;
				  n9++;
				  n10++;
				  n11++;


   }
}


