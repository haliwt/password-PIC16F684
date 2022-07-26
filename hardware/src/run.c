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
unsigned char Fail;
unsigned char pwd1[6];
unsigned char pwd2[6];
unsigned char initpwd[6]={1,2,3,4,0,0};


enum __PWD{FAIL,SUCCESS};



static unsigned char CompareValue(unsigned char *pt1,unsigned char *pt2);


static void ReadPassword_EEPROM_SaveData(void);

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
   
	
	ReadPassword_EEPROM_SaveData();
	
	

	 if(Fail == 1){

		OK_LED_OFF();
		ERR_LED_ON();
		run_t.passswordsMatch = 0;
		run_t.Numbers_counter = 0;
		 run_t.passsword_unlock=0;	
		run_t.eepromAddress=0;
		run_t.passswordsMatch = 0;
        Fail ++;


	 }

	 if(run_t.passsword_unlock ==1){

	     run_t.eepromAddress=0;
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
   for(i=0;i<6;i++){
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
	unsigned char eevalue,value;

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
		   	    run_t.userId = 10;
				ERR_LED_ON();
				__delay_ms(500);
		        ERR_LED_OFF();
				__delay_ms(500);
				ERR_LED_ON();
				__delay_ms(500);
				ERR_LED_OFF();
				__delay_ms(500);
				ERR_LED_ON();
				
				
				return ;
		   break;

		  


		
				  
	}

	eevalue= EEPROM_Read_Byte(run_t.userId);
	if(eevalue ==1)run_t.userId++;
	
         if(run_t.userId < 11){
	
         if(run_t.inputPwdTimes ==2){
		 	value =CompareValue(pwd1, pwd2);
			
			 if(value ==1){
			         EEPROM_Write_Byte(run_t.userId , 0x01);
					 EEPROM_Write_Byte(run_t.userId + 0x01,pwd1[0]);
					 EEPROM_Write_Byte(run_t.userId + 0x02,pwd1[1]);
					 EEPROM_Write_Byte(run_t.userId + 0x03,pwd1[2]);
					 EEPROM_Write_Byte(run_t.userId + 0x04,pwd1[3]);
					 EEPROM_Write_Byte(run_t.userId + 0x05,pwd1[4]);
					 EEPROM_Write_Byte(run_t.userId + 0x06,pwd1[5]);

					 ERR_LED_OFF();
					 OK_LED_ON();
					 run_t.BackLight =2;
					 Buzzer_LongSound();
					 run_t.Confirm =0;
			    	run_t.inputPwdTimes =0;
					run_t.passsword_unlock=0;

			

			 }
			 else{
				ERR_LED_ON();
				run_t.Confirm =0;
			    run_t.inputPwdTimes =0;
				run_t.passsword_unlock=0;
				

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
      static unsigned char value ,Readpwd[6];
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

				 case 12:
					run_t.eepromAddress=0;
				
				   Fail = 1;
				   return ;
				break;
	
		   }


	   if(run_t.eepromAddress <11){
		   eevalue = EEPROM_Read_Byte(ReadAddress);
		   if(eevalue ==1){

					Readpwd[0] = EEPROM_Read_Byte(ReadAddress + 0X01);
					Readpwd[1] = EEPROM_Read_Byte(ReadAddress + 0X02);
					Readpwd[2] = EEPROM_Read_Byte(ReadAddress + 0X03);
					Readpwd[3] = EEPROM_Read_Byte(ReadAddress + 0X04);
					Readpwd[4] = EEPROM_Read_Byte(ReadAddress + 0X05);
					Readpwd[5] = EEPROM_Read_Byte(ReadAddress + 0X06);

					value = CompareValue(Readpwd,pwd1);
					
					if(value==1)//if(strcmp(pwd1,pwd2)==0)
					{
						run_t.BackLight=2;
		
		                run_t.passsword_unlock=1;
						return ;

					}
					else{
						run_t.eepromAddress++ ;	
					}

			}
			else{

			     if(ReadAddress == ADMINI){
					value =CompareValue(initpwd, pwd1);

				     if(value==1){
									   
							
						run_t.BackLight=2;
					
					    run_t.passsword_unlock=1;	
					
						return ;

					}
					else{

					    	run_t.eepromAddress++ ;	
						
					}
				 }
				 else
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
   unsigned char temp, i;
  
   //static  unsigned long int  temp_5,temp_6;
   static unsigned char k0=0xff,k1=0xff,k2=0xff,key,spec;
 
   

    switch(dat){

	  

	case SPECIAL_1 ://0x40: //CIN1->'*'
		
       if(k0 != n0){

	      k0 = n0;
		  run_t.BackLight=1;

		  if(run_t.inputPwdTimes ==1){
		        for(i=0;i<6;i++){
					  pwd2[i]=0;
					
				 }
					

         }
		 else{
	        for(i=0;i<6;i++){
		  	   pwd1[i]=0;
		
		  }
		  
	  
			  ERR_LED_OFF();
			  OK_LED_OFF();
		     run_t.buzzer_flag =1;
			 spec=1;
		     run_t.Numbers_counter =0 ;
			run_t.passswordsMatch = 0;
			run_t.changePassword=0;
		  }
       }
		
	break;

	

	 case SPECIAL_2://0x200: //CIN10 '#' ->confirm 
         if(k1 != n1){
	        k1 = n1;
			spec=1;
		 run_t.buzzer_flag =1;
		
		  switch(run_t.Numbers_counter){
             
					case 4:
			           pwd1[4]=0;
		 			   pwd2[4]=0;

					   pwd1[5]=0;
		 			   pwd2[5]=0;
						  
                     break;

					 case 5:
					   pwd1[5]=0;
		 			   pwd2[5]=0;

					 break;

		}

		 if(run_t.passsword_unlock ==2){
                run_t.Confirm = 1;
				run_t.inputPwdTimes ++ ;
		        run_t.Numbers_counter=0;

		 }
		 else run_t.passswordsMatch = 1;
		   
	  	   
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
				run_t.Numbers_counter ++ ;
				run_t.buzzer_flag =1;
			
				temp = InputNumber_ToSpecialNumbers(dat); //input Numbers
				
			
			    #if 1
				 
			 
				 switch(run_t.Numbers_counter){
	        
				 	
				  case 1:
					 
				      if(run_t.inputPwdTimes ==1)pwd2[0]=temp;
					  else  pwd1[0] =temp;
					
				break;
				  
				  case 2:
					 
					  if(run_t.inputPwdTimes ==1) pwd2[1]=temp;
					  else pwd1[1] = temp;
					
				 break;
	   
				  case 3:
					   
					
					   if(run_t.inputPwdTimes ==1)pwd2[2] =temp;
					   else pwd1[2]= temp;
					  
				 break;
	   
				  case 4: 
					
					   if(run_t.inputPwdTimes ==1)pwd2[3] =temp;
					   else pwd1[3] = temp;
					   
				  break;
	   
				  case 5:
					 
					   if(run_t.inputPwdTimes ==1) pwd2[4] = temp;
					   else pwd1[4] =temp;
				break;
	   
				  case 6:
					
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


 }


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
