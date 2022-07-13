#ifndef __RUN_H_
#define __RUN_H_
#include "../../main.h"


enum Signal {                   /* enumeration for CParser signals */
     TOUCH_KEY_SIG,IN_NUMBER_SIG,  ZERO_SIG
};


enum State {                     /* enumeration for CParser states */
   INPUTKEY, MODIFYPSWD, EXIT
};


typedef struct __RUN_T{
	enum State state_;
    unsigned char cmdCtr_;   //event order cunter

    unsigned char adminiId;
	unsigned char admini_confirm;
    unsigned char resetKey;
    unsigned char getKeyTran;
    unsigned char userId;
    unsigned char number;     
    unsigned char timer_base;
    unsigned char timer_Core;
    unsigned char timer_led;
	unsigned char timer_20ms;
	unsigned char timer_60ms;
    unsigned char eePasswordOver; //eeprom be save 10 USER numbers
    unsigned char OpenPasswrod ;
    unsigned char firstInPassword;
	unsigned char keyTime;       //keyTime;
	unsigned char eepromAddress;
	unsigned char BackLight;
	unsigned char InputPasswordNumber_counter;
	unsigned char passswordsMatch;
	unsigned char passsword_unlock;
	unsigned char passsword_error;
    unsigned int KeyValue;
	
}RUN_T;


RUN_T run_t;



void Password_Modify(void);
void CProcessCmdRun(void);

void RunCheck_Mode(unsigned int dat);
void RunCommand_Unlock(void);

void Modidy_NewPassword_Function(void);


#endif 
