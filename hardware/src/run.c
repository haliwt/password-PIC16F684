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

unsigned char Readpwd[6];
unsigned char Inputpwd[6];
unsigned char pwd1[6];
unsigned char pwd2[6];

unsigned char getKeyTran;


static void CProcessDispatch(unsigned char sig);

static unsigned char CompareValue(unsigned char *pt1,unsigned char *pt2);

void InputKey_To_Number(void);

static void ReadPassword_EEPROM_SaveData(void);

/****************************************************************************
*
*Function Name:void Password_Modify(void)
*Function : run is main 
*Input Ref: NO
*Retrun Ref:NO
*
****************************************************************************/
void InputKey_To_Number(void)
{
      

	 #if 0
	   	
       case 0x01: getKeyTran =6;   break; //KEY6 =6
       
       case 0x02: getKeyTran = 10;   break; //KEY0 = *
       
       case 0x04: getKeyTran =7;   break; //KEY7 =7

       case 0x08: getKeyTran = 1;   break; //KEY1 =1

       case 0x10: getKeyTran =8;   break; // KEY8=8

       case 0x20: getKeyTran =2;   break; //KEY2 = 2

       case 0x40: getKeyTran =9;   break; //KEY9 = 9

       case 0x80: getKeyTran =3;   break; //KEY =3
	   #endif 

       if(run_t.KeyValue == 0x100 )
	         run_t.getKeyTran =0;  //break;  //KEY= 0
       else if(run_t.KeyValue == 0x200)
            run_t.getKeyTran =4;   // break;  //KEY4= 4
       else if(run_t.KeyValue == 0x800)
             run_t.getKeyTran =5;  //break;  //KEY5 =5

     
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
*Function Name:void Password_Modify(void)
*Function : run is main 
*Input Ref: NO
*Retrun Ref:NO
*
****************************************************************************/
void Password_Modify(void)
{
   
   static unsigned char userNumbers =0 ,currkey=0xff;
   unsigned char eev,i;
  // I2C_Simple_Read_Device(OUTPUT0_REG,&run_t.KeyValue);
   while ( run_t.KeyValue != 0) {
         BACKLIGHT_ON(); //LED ON 8s 
         if(run_t.keyTime != currkey){
		 	  currkey = run_t.keyTime;
	          BUZZER_KeySound();
         }
	   if(run_t.resetKey == 0x01){ //be pressed key shot times 
	     	
	     //adjust the first add user password and be changed this administrator password
		if(run_t.KeyValue ==0x02 && run_t.OpenPasswrod ==0) //"*" -> the first be used to 
		{
			    run_t.firstInPassword = EEPROM_Read_Byte(0x00);
				if(run_t.firstInPassword == 1){
					for(i=0;i<6;i++){
 						pwd1[i]=0;
					}
					run_t.adminiId =0;
					return ;
				}
				else{
					run_t.adminiId =1;
				}
		}
		else{
			 if(run_t.firstInPassword !=2){ //administrator password . every one read administrator 
					
					run_t.firstInPassword = EEPROM_Read_Byte(0x00);
					if(run_t.firstInPassword == 1){
						
						Readpwd[0] = EEPROM_Read_Byte(ADMINI + 0X01);
						Readpwd[1] = EEPROM_Read_Byte(ADMINI + 0X02);
						Readpwd[2] = EEPROM_Read_Byte(ADMINI + 0X03);
						Readpwd[3] = EEPROM_Read_Byte(ADMINI + 0X04);
						Readpwd[4] = EEPROM_Read_Byte(ADMINI + 0X05);
						Readpwd[5] = EEPROM_Read_Byte(ADMINI + 0X06);
					}
					else{
						return ;
					}
				}
		}
	
        if(run_t.adminiId==1 && run_t.KeyValue != 0x02){ //administrator password 

				i++;
				if(run_t.KeyValue ==0x08 && i==1) //KEY= "1"
				{
					run_t.cmdCtr_ = 0;
				}
				else if(run_t.KeyValue ==0x20 && i==2) //KEY = "2"
				{
					run_t.cmdCtr_ = 0;
				}
				else if(run_t.KeyValue ==0x80 && i==3) //KEY = "3"
				{
					run_t.cmdCtr_ = 0;
				}
				else if(run_t.KeyValue == 0x200 && i==4) //KEY = "4"
				{
					run_t.cmdCtr_ = 0;
				}
				else if(run_t.KeyValue == 0x400 && i==5) //KEY = "#"
				{
					run_t.OpenPasswrod = 1;
					i=0;
					run_t.adminiId =0;
					OK_LED_ON();
				//	Motor_CCW_Run(); //open password lock
				    return ;

				}
				else{
					run_t.adminiId = 0;
					i=0;
				}
		    }

	   
        
	    if(run_t.KeyValue != 0x02 || run_t.KeyValue != 0x400 ){
             i=0;
			 run_t.adminiId =0;
			if(run_t.overFlag == 0){ //limit password numbers lenght maximum 6
				if(run_t.number ==0){ //the first times input password 
					if(run_t.KeyValue > 0x80){
						InputKey_To_Number();
						 pwd1[run_t.cmdCtr_]= getKeyTran;
					}
					else //
					     pwd1[run_t.cmdCtr_] = run_t.KeyValue;
				}
				else{
					if(run_t.KeyValue > 0x80){
						InputKey_To_Number();
						 pwd2[run_t.cmdCtr_]= getKeyTran;
					}
					else
					     pwd2[run_t.cmdCtr_] = run_t.KeyValue;
				}
				run_t.cmdCtr_++;
				if(run_t.cmdCtr_ == 6 ){  // input password is 4 ~ 6bytes
						run_t.overFlag =1;
				}
            }
		} 

		if(run_t.KeyValue == 0x02){ // "*" is clear 
			 for(i=0;i<6;i++){
			 	if(run_t.number ==0)
 					     pwd1[i]=0;
				else if(run_t.number ==1)
					   pwd2[i]=0;
				}
				run_t.overFlag =0;
				run_t.cmdCtr_=0;
		}

		if(run_t.KeyValue == 0x400){ // "#" over 
			   if(run_t.cmdCtr_ > 3 && run_t.cmdCtr_ < 7){
				   run_t.cmdCtr_ = 0;
				  run_t.overFlag =0;
                  run_t.number ++ ;
				  if(run_t.number ==2) run_t.overFlag =1;
				}
				else{
                    run_t.overFlag =1;
				}
			
		}
		//check administrator password is correct ,after permit access new USER password 
        if(run_t.number ==1 && run_t.firstInPassword==1){
            if(CompareValue(Readpwd,pwd1) ==1)//if(strcmp(pwd1,pwd2)==0)
			{
                  run_t.firstInPassword =2;
				  run_t.adminiId=1;
				  run_t.number = 0; 
				   OK_LED_ON();
			      

			}
			else{

				 ERR_LED_ON();
				 run_t.number = 0;
				 run_t.adminiId=0;
				 return ; 

			}
		}
	   //adjust 
	   if(run_t.number == 2){
         if(CompareValue(pwd1,pwd2) ==1)//if(strcmp(pwd1,pwd2)==0)
		 {
			   OK_LED_ON();
			   ERR_LED_OFF();
			   run_t.cmdCtr_=0;
			  run_t.overFlag =0;
              run_t.number=0;
			 // Motor_CCW_Run();//open passwordlock 
              
			  if(userNumbers < 11){
                   switch(userNumbers){
					  
					   case 0:
					    eev = EEPROM_Read_Byte(0x00);
						if(eev ==1){
							userNumbers=1; //don't cover before write data
						}
						else{
							run_t.userId= ADMINI;
							
						}
					   break;

					   case 1 :
					    eev = EEPROM_Read_Byte(USER_1);
						if(eev ==1){
							userNumbers=2; //don't cover before write data
						}
						else
						{
							run_t.userId = USER_1;
							
						}   
					  break;
					  
					   case 2: 
					    eev = EEPROM_Read_Byte(USER_2);
						if(eev ==1){
							userNumbers=3; //don't cover before write data
						}
						else
						{
							run_t.userId = USER_2; 
							
						}
					   break;
					   
					   case 3 :
					    eev = EEPROM_Read_Byte(USER_3);
						if(eev ==1){
							userNumbers=4; //don't cover before write data
						}
						else
						{
							run_t.userId = USER_3; 
							
						}    
                       break;
					   
					   case 4: 
					    eev = EEPROM_Read_Byte(USER_4);
						if(eev ==1){
							userNumbers=5; //don't cover before write data
						}
						else
						{
					      run_t.userId = USER_4; 
						
						} 
					   break;

					   case 5 :
					    eev = EEPROM_Read_Byte(USER_5);
						if(eev ==1){
							userNumbers=6; //don't cover before write data
						}
						else
						{
					       run_t.userId = USER_5;  
						
						}   
                       break;
					   
					   case 6: 
					    eev = EEPROM_Read_Byte(USER_6);
						if(eev ==1){
							userNumbers=7; //don't cover before write data
						}
						else
						{
					       run_t.userId = USER_6; 
						
						}
					   break;
					   
					    case 7 :
						eev = EEPROM_Read_Byte(USER_7);
						if(eev ==1){
							userNumbers=8; //don't cover before write data
						}
						else
						{
					        run_t.userId = USER_7; 
						
						}    
                       break;
					   
					   case 8: 
					     eev = EEPROM_Read_Byte(USER_8);
						if(eev ==1){
							userNumbers=9; //don't cover before write data
						}
						else
						{
							run_t.userId = USER_8; 
							
						}
					   break;
					   
					   case 9 :
					    eev = EEPROM_Read_Byte(USER_9);
						if(eev ==1){
							userNumbers=10; //don't cover before write data
						}
						else
						{
							run_t.userId = USER_9; 
							
						}    
                       break;
					  
					   case 10:
					    eev = EEPROM_Read_Byte(USER_10);
						if(eev ==1){
							userNumbers=11; //don't cover before write data
						}
						else
						{ 
							run_t.userId = USER_10; 
							
						} 
					   break;

					   case 11:
							ERR_LED_ON();
							run_t.eePasswordOver =1;
							return ;
					   break;
					 


				}
				userNumbers ++;
					run_t.firstInPassword =0;
					EEPROM_Write_Byte(run_t.userId , 0x01);
					EEPROM_Write_Byte(run_t.userId + 0x01,pwd1[0]);
					EEPROM_Write_Byte(run_t.userId + 0x02,pwd1[1]);
					EEPROM_Write_Byte(run_t.userId + 0x03,pwd1[2]);
					EEPROM_Write_Byte(run_t.userId + 0x04,pwd1[3]);
					EEPROM_Write_Byte(run_t.userId + 0x05,pwd1[4]);
					EEPROM_Write_Byte(run_t.userId + 0x06,pwd1[5]);
				  

			  }
			  else
			  {
				 userNumbers = 0;
			  }

		   }
		   else
		   {
			   ERR_LED_ON();
			   OK_LED_OFF();
			  run_t.overFlag =0;
              run_t.number=0;
		   }

		

	   }
	 }//Be pressed value 
	}


}
/****************************************************************************
*
*Function Name:void Input_Password(void)
*Function : run is main 
*Input Ref: NO
*Retrun Ref:NO
*
****************************************************************************/
void Input_Password(void)
{

	   unsigned char getKeyTran,i;
      

       if(run_t.KeyValue != 0x02 || run_t.KeyValue != 0x400 ){ //"*"  and "#"
		       if(run_t.cmdCtr_ < 6){ //limit password numbers lenght maximum 6
				  if(run_t.number ==0){ //the first times input password 
					  if(run_t.KeyValue > 0x80){
						   InputKey_To_Number();
						   pwd1[run_t.cmdCtr_]= run_t.getKeyTran;
					  }
					  else //
						   pwd1[run_t.cmdCtr_] = run_t.KeyValue;
				  }
				  run_t.cmdCtr_++;
				 
			  }
		 } 


		if(run_t.KeyValue == 0x02){ // "*" is clear 
			 for(i=0;i<6;i++){
			 	   pwd1[i]=0;
			 	}
				run_t.cmdCtr_=0;
		}
        //
		if(run_t.KeyValue == 0x400){ // "#" over 
			 if(run_t.cmdCtr_ > 3 && run_t.cmdCtr_ < 7){
				   run_t.cmdCtr_ = 0;

				ReadPassword_EEPROM_SaveData();


              
			 }
			 else{
                  ERR_LED_ON();
				 for(i=0;i<6;i++){
			 	   pwd1[i]=0;
			 	 }
				
			}
		     
			 
      }
}

static void ReadPassword_EEPROM_SaveData(void)
{
  
	   unsigned char eevalue ,i,ReadAddress;
	      switch(run_t.eepromAddress){

			  case 0:
                   eevalue = EEPROM_Read_Byte(ADMINI);
					if(eevalue ==1){
						ReadAddress = ADMINI;
					}
					else{
						run_t.eepromAddress =1;
					}
			  break;
			  
			 case 1:

			    eevalue = EEPROM_Read_Byte(USER_1);
			    if(eevalue ==1){
                   ReadAddress = USER_1;
                 }
				 else{
				 	run_t.eepromAddress=2;
                    
				 }
                      
			  break;

			  case 2:
			  	eevalue = EEPROM_Read_Byte(USER_2);
			    if(eevalue ==1){
                   ReadAddress = USER_2;
                 }
				 else{
				 	run_t.eepromAddress=3;
                    
				 }

			  break;

			  case 3:
			  	eevalue = EEPROM_Read_Byte(USER_3);
			    if(eevalue ==1){
                   ReadAddress = USER_3;
                 }
				 else{
				 	run_t.eepromAddress=4;
                    
				 }

			  break;

			  case 4:
			  	eevalue = EEPROM_Read_Byte(USER_4);
			    if(eevalue ==1){
                   ReadAddress = USER_4;
                 }
				 else{
				 	run_t.eepromAddress=5;
                    
				 }

			  break;

			  case 5:
			   	eevalue = EEPROM_Read_Byte(USER_5);
			    if(eevalue ==1){
                   ReadAddress = USER_5;
                 }
				 else{
				 	run_t.eepromAddress=6;
                    
				 }

			  break;

			  case 6:
			  	eevalue = EEPROM_Read_Byte(USER_6);
			    if(eevalue ==1){
                   ReadAddress = USER_6;
                 }
				 else{
				 	run_t.eepromAddress=7;
                    
				 }

			  break;

			  case 7:
			  	eevalue = EEPROM_Read_Byte(USER_7);
			    if(eevalue ==1){
                   ReadAddress = USER_7;
                 }
				 else{
				 	run_t.eepromAddress=8;
                    
				 }

			  break;

			  case 8:
			  	eevalue = EEPROM_Read_Byte(USER_8);
			    if(eevalue ==1){
                   ReadAddress = USER_8;
                 }
				 else{
				 	run_t.eepromAddress=9;
                    
				 }

			  break;

			  case 9:
			  	eevalue = EEPROM_Read_Byte(USER_9);
			    if(eevalue ==1){
                   ReadAddress = USER_9;
                 }
				 else{
				 	run_t.eepromAddress=10;
                    
				 }

			  break;

			  case 10:
			  	eevalue = EEPROM_Read_Byte(USER_10);
			    if(eevalue ==1){
                   ReadAddress = USER_10;
                 }
				 else{
				 	run_t.eepromAddress=10;
                    
				 }

			  break;

			  case 11:
                 ERR_LED_ON();
				 for(i=0;i<6;i++){
			 	   Readpwd[i]=0;
				 }
				 run_t.eepromAddress=0;
                return ;
			 break;

        }
				
			
			
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
   
   unsigned char sig;
   run_t.resetKey =  Scan_Key();
   
   I2C_Simple_Read_Device(OUTPUT0_REG,&run_t.KeyValue);
   while ( run_t.KeyValue != 0) {
       switch (run_t.resetKey) {
       case 0x00: run_t.state_ = INPUTKEY; sig = TOUCH_KEY_SIG; break;  //Input password 
       case 0x01: run_t.state_= MODIFYPSWD;sig = IN_NUMBER_SIG;  break;  //modify password
       default:  run_t.state_= EXIT;       sig = ZERO_SIG;  break;
       }
       CProcessDispatch(sig);
     
   }      

}


static void CProcessDispatch(unsigned char sig)
{
	switch(run_t.state_){

	    case INPUTKEY: //state be open password 
	        switch(sig){

			   case  TOUCH_KEY_SIG:

                       Input_Password();
			   break;

			   case ZERO_SIG:


			   break;


			}


	    break;


		case MODIFYPSWD:
			switch(sig){

              case IN_NUMBER_SIG:
                     Password_Modify();
			  break;

			  case ZERO_SIG:

			  break;

			}


		break;


		default :

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

/*********************************************/
#if 0
   {
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

#endif 





