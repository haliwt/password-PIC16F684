#ifndef __LED_H_
#define __LED_H_
#include "../../main.h"

#define  BACKLIGHT_ON()          (PORTAbits.RA2 =0)
#define  BACKLIGHT_OFF()         (PORTAbits.RA2 =1)

#define  BAT_LED_ON()           (PORTCbits.RC4 = 0)
#define  BAT_LED_OFF()           (PORTCbits.RC4 =1 )

#define  OK_LED_ON()           (PORTAbits.RA1 = 0)
#define  OK_LED_OFF()            (PORTAbits.RA1 = 1)

#define  ERR_LED_ON()           (PORTAbits.RA0 =0)
#define  ERR_LED_OFF()             (PORTAbits.RA0 =1)


void System_Init(void);





#endif 
