#ifndef __BUZZER_H_
#define __BUZZER_H_
#include "../../main.h"

#define BUZZER_PIN()           PORTCbits.RC5
#define  BUZZER_PIN_ON()       (PORTCbits.RC5 = 0)
#define  BUZZER_PIN_OFF()       (PORTCbits.RC5= 1)

void BUZZER_Init(void);



void PlayMusi_Buzzer(void);





#endif 
