#ifndef __RUN_H_
#define __RUN_H_
#include "../../main.h"



enum Signal{
     KEY_0,KEY_1,KEY_2,KEY_3,KEY_4,KEY_5,KEY_6,KEY_7,KEY_8,KEY_9,KEY_10,KEY_11
};

enum State{
      is_Idle,is_Start,is_KeyRelease,is_Doing,is_Exit

};





typedef struct __RUN_T{
    enum State state_;          //the scalar state variable
    unsigned char cmdCtr_;   //event order cunter
    unsigned char first_seq;
    unsigned char eeprom_buf[6];
    unsigned char password_low_bits;
    unsigned char password_high_bits;
    unsigned char head;
    unsigned char tail;
}RUN_T;


RUN_T run_t;


void CProcessCmdRun(void);
#endif 
