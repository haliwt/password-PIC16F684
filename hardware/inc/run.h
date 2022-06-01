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
    unsigned char overFlag;  //limit password numbers maximum 6 
    unsigned char adminiId;
    unsigned char resetKey;
    unsigned char getKeyTran;
    unsigned char userId;
    unsigned char number;     
    unsigned char timer_base;
    unsigned char timer_Core;
    unsigned char timer_led;
    unsigned char eePasswordOver; //eeprom be save 10 USER numbers
    unsigned char OpenPasswrod ;
    unsigned char firstInPassword;
	unsigned char keyTime;       //keyTime;
	unsigned char eepromAddress;
    unsigned int KeyValue;
	
}RUN_T;


RUN_T run_t;

void Password_Modify(void);
void Input_Password(void);
void CProcessCmdRun(void);
#endif 
