#include "../inc/buzzer.h"

#define uchar  unsigned	char
#define uint   unsigned int

void delayUS(uchar i)//US级延时子函数
{		
     while(--i);
}

void delayMS(uchar a)//MS级延时子函数
{		
     do
     {delayUS(199);}while(--a);
}



void BUZZER_Init(void)
{
     TRISCbits.TRISC5 =0 ; //I/O as output 
}
/*******************************************
*
*Function Name: void BUZZER_KeySound(void)
*Function: Key be pressed carry out sound
*
*
*******************************************/
void BUZZER_KeySound(void)
{
      unsigned int m;
	
     for(m=0;m<10;m++){
          BEEP=!BEEP;
          __delay_us(500);//delayUS(99);
         // __delay_ms(1);
     }

//     m=200;
//     while(--m){
//         BEEP=!BEEP;
//         __delay_us(60);// delayUS(199);
//     }

}

