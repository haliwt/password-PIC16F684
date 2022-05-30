#ifndef __MOTOR_H_
#define __MOTOR_H_
#include "../../main.h"

#define MOTOR_CCW_RUN()        (PORTAbits.RA5 = 1)
#define MOTOR_CCW_OFF()        (PORTAbits.RA5 = 0)

#define MOTOR_CW_RUN()         (PORTAbits.RA4 =1)
#define MOTOR_CW_OFF()		   (PORTAbits.RA4 = 0)


void Motor_Init(void);
void Motor_CCW_Run(void);
void Motor_CW_Run(void);
void Motor_Stop(void);





#endif 
