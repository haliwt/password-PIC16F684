#include "../inc/buzzer.h"

#define Do 262

#define Re 294

#define Mi 330

#define Fa 349

#define Sol 392

#define La 440

#define Si 494


static void PlayTone(unsigned char *ptone, unsigned int *duration);

unsigned int tempo = 300;   //cadence



uint8_t  SONG_TONE[]={Do,Re,Mi,Fa,Sol,La,Si}; 


uint8_t  SONG_LONG[]={1,1,1,1,1,1,1};


void BUZZER_Init(void)
{
     TRISCbits.TRISC5 =0 ; //I/O as output 
}

/**
 * @brief  
 * Buzzer output music 
 * 
 */
static void PlayTone(unsigned char *ptone, unsigned int *duration)
{
     unsigned int timeout,dur;
     unsigned char i;
     
     BUZZER_PIN_ON();
     timeout = *(ptone +i);
     while(--timeout);

     BUZZER_PIN_OFF();
     dur = *(duration +i) * tempo  ;
     while(--dur);
     i++;
     if(i==8)i=0;

}
/**
 * @brief 
 * 
 */

void PlayMusi_Buzzer(void)
{
    PlayTone(SONG_TONE,SONG_LONG);
}