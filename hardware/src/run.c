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


unsigned char pwd1[6];
unsigned char pwd2[6];

unsigned char getKeyTran;

static unsigned char CompareValue(void);

void InputKey_Tlo_Number(void);





/****************************************************************************
*
*Function Name:void Password_Modify(void)
*Function : run is main 
*Input Ref: NO
*Retrun Ref:NO
*
****************************************************************************/
void InputKey_Tlo_Number(void)
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
	         getKeyTran =0;  //break;  //KEY= 0
       else if(run_t.KeyValue == 0x200)
            getKeyTran =4;   // break;  //KEY4= 4
       else if(run_t.KeyValue == 0x800)
             getKeyTran =5;  //break;  //KEY5 =5

     
 }
     
      
   


/****************************************************************************
*
*Function Name:void Password_Modify(void)
*Function : run is main 
*Input Ref: NO
*Retrun Ref:NO
*
****************************************************************************/
static unsigned char CompareValue(void)
{
	unsigned char i ;
	for(i=0;i<6;i++){
		if(pwd1[i] != pwd2[i]){
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
   
   static unsigned char userNumbers =0 ,i;
   I2C_Simple_Read_Device(OUTPUT0_REG,&run_t.KeyValue);
   while ( run_t.KeyValue != 0) {
        BACKLIGHT_ON(); //LED ON 8s 
	   
       
	   if(run_t.KeyValue ==0x02) //"*"
	   {
            run_t.adminiId =1;
	   }
	   if(run_t.adminiId==1){

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
				 run_t.cmdCtr_ = 1;
				 i=0;
				 run_t.adminiId =0;
			}
       }

       if(run_t.cmdCtr_ == 1 && run_t.resetKey == 0x01){

	       if(run_t.KeyValue != 0x02 && run_t.KeyValue != 0x400  ){
             i=0;
			 run_t.adminiId =0;
			if(run_t.overFlag == 0){
				if(run_t.number ==0){
					if(run_t.KeyValue > 0x80){
						InputKey_Tlo_Number();
						 pwd1[run_t.cmdCtr_]= getKeyTran;
					}
					else
					     pwd1[run_t.cmdCtr_] = run_t.KeyValue;
				}
				else{
					if(run_t.KeyValue > 0x80){
						InputKey_Tlo_Number();
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
	        
			if(run_t.KeyValue == 0x02){ // "*" is clear 
			    pwd1[5]=0;
				pwd2[5]=0;
				pwd1[4]=0;
				pwd2[4]=0;
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
			
				break;
			}

	   }
	   if(run_t.number == 2){
         if(CompareValue() ==1)//if(strcmp(pwd1,pwd2)==0)
		 {
			   OK_LED_ON();
			   ERR_LED_OFF();
			   run_t.cmdCtr_=0;
			  run_t.overFlag =0;
              run_t.number=0;
			  userNumbers ++;
              
			  if(userNumbers < 11){
                   switch(userNumbers){
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
				  }
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
	}
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
         

}
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





