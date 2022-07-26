#ifndef __RUN_H_
#define __RUN_H_
#include "../../main.h"

#define MAX_SIZE        11


enum Signal {                   /* enumeration for CParser signals */
     TOUCH_KEY_SIG,IN_NUMBER_SIG,  ZERO_SIG
};


enum State {                     /* enumeration for CParser states */
   INPUTKEY, MODIFYPSWD, EXIT
};


typedef struct __RUN_T{
	//enum State state_;
    //unsigned char cmdCtr_;   //event order cunter

    unsigned char adminiId;
	unsigned char Confirm;
	unsigned char inputPwdTimes;

	unsigned char changePassword;
   


    unsigned char userId;
    

    unsigned char eepromAddress;
	unsigned char BackLight;
	unsigned char buzzer_flag;
	unsigned char Numbers_counter;
	unsigned char passswordsMatch;
	unsigned char passsword_unlock;
	



	//unsigned int KeyValue;
	
}RUN_T;


RUN_T run_t;

unsigned int pwd_4;

unsigned long int pwd_5,pwd_6;

void RunCheck_Mode(unsigned int dat);
void RunCommand_Unlock(void);

//void Modidy_NewPassword_Function(void);
//unsigned char CompareValue(unsigned char *pt1,unsigned char *pt2);

void Buzzer_Sound(void);
void BackLight_Fun(void);

void SavePassword_To_EEPROM(void);

#endif 
