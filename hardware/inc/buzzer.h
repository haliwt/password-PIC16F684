#ifndef __BUZZER_H_
#define __BUZZER_H_
#include "../../main.h"


#define  BEEP                   PORTCbits.RC5
#define  BUZZER_PIN()           PORTCbits.RC5
#define  BUZZER_PIN_ON()         (PORTCbits.RC5 = 1)
#define  BUZZER_PIN_OFF()        (PORTCbits.RC5= 0)

void BUZZER_Init(void);


void BUZZER_KeySound(void);

void PlayMusi_Buzzer(void);
void Buzzer_LongSound(void);

void Buzzer_ResetSond(void);





#endif 
