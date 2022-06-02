#include "../inc/run.h"
#include "../../main.h"

#define MAX_SIZE    6

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

unsigned char Readpwd[MAX_SIZE];
unsigned char pwd1[MAX_SIZE];
unsigned char pwd2[MAX_SIZE];

unsigned char getKeyTran;
unsigned char Top =0;


static void CProcessDispatch(unsigned char sig);

static unsigned char CompareValue(unsigned char *pt1,unsigned char *pt2);

void InputKey_To_Number(void);

static void ReadPassword_EEPROM_SaveData(void);
static void Push(unsigned char *pt,unsigned char data);
static void Pop(void);

static void TheFirst_Administrator_Login(void);
static void NewPassword_Administrator_Login(void);


/**
 * @brief 
 * 
 */
static void Push(unsigned char *pt,unsigned char data)
{
	if( Top == MAX_SIZE){
		return ;
	}
	*(pt) = data;
	Top++;
}
static void Pop(void)
{
	// if(top== -1){
	// 	return ;
	// }
	Top = 0 ;//top -- ;
}

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
	if(Top == 0){
		return 0;
	}
    for(i=0;i<MAX_SIZE;i++){
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
   
 
   unsigned char eev,i;
    

        //adjust the first login in be usd to password "*1234#"
	
          run_t.firstInPassword = EEPROM_Read_Byte(ADMINI);
		

		switch(run_t.firstInPassword){

			case 0: //the first login administrator password "*1234#"
			  
					TheFirst_Administrator_Login();
			break;

			case 1: //has been woten new administrator password  "xxxxxx"
					NewPassword_Administrator_Login();
			break;

			default:

			   run_t.keyTime++;

			   return ;

			break;

        }
}

/**
 * @brief 
 * 
 */


static void TheFirst_Administrator_Login(void)
{
		  static unsigned char adminiFirst;

         switch(run_t.adminiId){
			
			case 0:
				if(run_t.KeyValue ==0x02 ) //"*" -> the first be used to 
				{
					//the first administrator be used to password "*1234#"
					run_t.adminiId =1;
						
				}
				
            break;

			case 1:
			 if(run_t.adminiId==1 && run_t.KeyValue != 0x02){ //administrator password 
				if(run_t.KeyValue ==0x08) //KEY= "1"
				{
					adminiFirst++;
				}
				else if(run_t.KeyValue ==0x20 && adminiFirst ==1) //KEY = "2"
				{
					adminiFirst++;
				}
				else if(run_t.KeyValue ==0x80 && adminiFirst==2) //KEY = "3"
				{
					adminiFirst++;
				}
				else if(run_t.KeyValue == 0x200 && adminiFirst==3) //KEY = "4"
				{
					adminiFirst++;
				}

				if(run_t.KeyValue == 0x400 && adminiFirst==4) //KEY = "#"
				{
					
				    run_t.adminiId =2;
					adminiFirst=0;
				//	run_t.firstInPassword= 1;
				    run_t.keyTime++;
					OK_LED_ON();

					return ;
					
				  

				}
				else{ //ERROR of key input 
					ERR_LED_ON();
					run_t.adminiId = 0;
					adminiFirst=0;
					run_t.keyTime++;
				}
		    }
			if(run_t.KeyValue == 0x02){ // "*" be clear input numbers

                    run_t.adminiId = 0;
					adminiFirst=0;
                    run_t.keyTime++;
			}


			break;

			case 2:

			     if(run_t.adminiId ==2){

				    run_t.firstInPassword= 1;

				 }

			break;

			default:
            
			break;
            
			//run_t.keyTime++;
		 }
}

/**
 * @brief 
 * 
 */

static void NewPassword_Administrator_Login(void)
{
      static  unsigned char eepromReadAdmin,eev;

	  switch(eepromReadAdmin){

        case 0: 
        
		if(run_t.firstInPassword !=2){
			Readpwd[0] = EEPROM_Read_Byte(ADMINI + 0X01);
			Readpwd[1] = EEPROM_Read_Byte(ADMINI + 0X02);
			Readpwd[2] = EEPROM_Read_Byte(ADMINI + 0X03);
			Readpwd[3] = EEPROM_Read_Byte(ADMINI + 0X04);
			Readpwd[4] = EEPROM_Read_Byte(ADMINI + 0X05);
			Readpwd[5] = EEPROM_Read_Byte(ADMINI + 0X06);
		}

		eepromReadAdmin =1;
	   
	   break; 

	   case 1:

	    if(run_t.KeyValue != 0x02 || run_t.KeyValue != 0x400 ){ //"*" || "#"
          
			if(run_t.overFlag == 0){ //limit password numbers lenght maximum 6
				if(run_t.number ==0){ //the first times input password 
					if(run_t.KeyValue > 0x80){
						InputKey_To_Number();
						 Push(&pwd1[Top],getKeyTran);
					}
					else //
					     Push(&pwd1[Top],run_t.KeyValue); //pwd1[run_t.cmdCtr_] = run_t.KeyValue;
				}
				else{
					if(run_t.KeyValue > 0x80){
						InputKey_To_Number();
					    Push(&pwd2[Top],getKeyTran);	   // pwd2[run_t.cmdCtr_]= getKeyTran;
					}
					else
					    Push(&pwd2[Top],run_t.KeyValue); //pwd2[run_t.cmdCtr_] = run_t.KeyValue;
				}
			
				if(Top == MAX_SIZE ){  // input password is 4 ~ 6bytes
						run_t.overFlag =1;
						if(run_t.adminiId==0)
						   eepromReadAdmin =2;
						else if(run_t.adminiId==1)
						   eepromReadAdmin = 3;
				}
            }
		} 

		if(run_t.KeyValue == 0x02){ //"*" be clear input number
                Pop();
				run_t.keyTime++;
                return ;
		}

		if(run_t.KeyValue == 0x400){ //"#" key accomplish input over task
		     if(Top > 3 && Top < 7){ //has 4 number passwords
                        run_t.overFlag =1;
					if(run_t.adminiId==0)
						   eepromReadAdmin =2;
					else if(run_t.adminiId==1)
						   eepromReadAdmin = 3;

			}
			else{
			     ERR_LED_ON();
			     run_t.keyTime++;
                return ;
			}	 
		}

        break; 


		case 2:

        if(run_t.KeyValue == 0x400){ //"#" key accomplish input over task
			if(CompareValue(Readpwd,pwd1) ==1)//if(strcmp(pwd1,pwd2)==0)
			{
					run_t.adminiId=1;
					run_t.number = 0;
					eepromReadAdmin =1; //
					Pop();
					OK_LED_ON();
					

			}
			else{

					ERR_LED_ON();
					run_t.number = 0;
					run_t.adminiId=0;
					run_t.keyTime++;
					return ; 

			}
		}

	
		if(run_t.KeyValue == 0x02){ //"*" be clear input number
                Pop();
				run_t.keyTime++;
                return ;
		}

		break;

		case 3:
         if(run_t.KeyValue == 0x400){ //"#" key accomplish input over task
			if(CompareValue(pwd1,pwd2) ==1)//if(strcmp(pwd1,pwd2)==0)
			{
					eepromReadAdmin =4; //
					run_t.adminiId=1;
					run_t.number = 0; 
					OK_LED_ON();
					

			}
			else{

					ERR_LED_ON();
					run_t.number = 0;
					run_t.adminiId=0;
					run_t.keyTime++;
					return ; 

			}
		 }
		 if(run_t.KeyValue == 0x02){ //"*" be clear input number
                Pop();
				run_t.keyTime++;
                return ;
		}

		break;


		case 4: //be saved new password 
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
							ERR_LED_ON();
							run_t.cmdCtr_ = 0;
							run_t.keyTime++;
							return ;
					   break;


					eev = EEPROM_Read_Byte(run_t.userId);
					if(eev==0){
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
			  
			 break;

		}
		if(run_t.cmdCtr_ >11 ){
        
        	run_t.cmdCtr_=0;
        }
		run_t.keyTime++;
}
/**
 * @brief 
 * 
 */

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
     
	 unsigned char getKeyTran ,i;
   
     if(run_t.KeyValue != 0x02 || run_t.KeyValue != 0x400 ){ //"*"  and "#"
		       if(Top < 6){ //limit password numbers lenght maximum 6
				 //the first times input password 
					  if(run_t.KeyValue > 0x80){
						   InputKey_To_Number();
						   Push(&pwd1[Top],getKeyTran);
					  }
					  else //
						    Push(&pwd1[Top],run_t.KeyValue);//pwd1[topnumber] = run_t.KeyValue;
				 }
				 
				 
	   }
      if(run_t.KeyValue == 0x02){ // "*" is clear 
          Pop();
				
		}
        //
		if(run_t.KeyValue == 0x400){ // "#" over 
			 if(Top > 3 && Top < 7){
                 Top=0;
                 ReadPassword_EEPROM_SaveData();
 			 }
			 else{
                  ERR_LED_ON();
				  Pop();
				
			}
		     
		}
}

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
   static unsigned char currkey=0xff;
   unsigned char sig;
   run_t.resetKey =  Scan_Key();
   
   I2C_Simple_Read_Device(OUTPUT0_REG,&run_t.KeyValue);
   while ( run_t.KeyValue != 0) {
	    BACKLIGHT_ON(); //LED ON 8s 
        if(run_t.keyTime != currkey){
		 	currkey = run_t.keyTime;
	          BUZZER_KeySound();
        }
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





