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

    //RESET KEY 
    TRISAbits.TRISA3 = 1;   //input Key 

}

unsigned char Scan_Key(void)
{

    unsigned int k1=0 ;
    unsigned char  value ,cnt;
   if(RESET_KEY  ==0 ){
        cnt=0;
        k1++;   
    }
 
    if(RESET_KEY  == 1 ){
        cnt++;
        if(cnt<30) return 0;
        
        cnt=0;
        if(k1 >180 && k1< 200){
            value = 0x01;
        }
        else if(k1>300){
            value = 0x81;
        }
      
    }
    return 0;
}



