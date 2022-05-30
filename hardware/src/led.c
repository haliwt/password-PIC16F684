#include "../inc/led.h"

static void LED_Init(void);

void System_Init(void)
{
    LED_Init();
    BUZZER_Init();

}

static void LED_Init(void)
{
    CMCON = 0x07;
    ANSELbits.ANS0 = 0;
    ANSELbits.ANS1 = 0;
    ANSELbits.ANS2 =0 ; //I/O as digital 

    TRISAbits.TRISA0 =0;
    TRISAbits.TRISA1 =0 ;
    TRISAbits.TRISA2 = 0;  //I/O as output 
    TRISCbits.TRISC4 = 0;

}

