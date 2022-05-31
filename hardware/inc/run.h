#ifndef __RUN_H_
#define __RUN_H_
#include "../../main.h"




typedef struct __RUN_T{
    unsigned char cmdCtr_;   //event order cunter
    unsigned char overFlag;
    unsigned char adminiId;
    unsigned char resetKey;
    unsigned char getKeyTran;
    unsigned char userId;
    unsigned char number;
    unsigned char timer_base;
    unsigned int KeyValue;
}RUN_T;


RUN_T run_t;

void Password_Modify(void);
void CProcessCmdRun(void);
#endif 
