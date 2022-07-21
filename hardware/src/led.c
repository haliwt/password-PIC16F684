#include "../inc/led.h"

static void LED_Init(void);

void System_Init(void)
{
    LED_Init();
    BUZZER_Init();

}

static void LED_Init(void)
{
    //CMCON = 0x07;
    CMCON0 = 0x07; //PIC16F684
    ANSELbits.ANS0 = 0;
    ANSELbits.ANS1 = 0;
    ANSELbits.ANS2 =0 ; //I/O as digital 

    TRISAbits.TRISA0 =0;
    TRISAbits.TRISA1 =0 ;
    TRISAbits.TRISA2 = 0;  //I/O as output 
    TRISCbits.TRISC4 = 0;
    //RESET KEY gpio input PORT
    TRISAbits.TRISA3 = 1;   //I/O as input
    
    //Setup GPIO output defult value 
    PORTAbits.RA0=1;
	PORTAbits.RA1=1;
	PORTAbits.RA2=0;  //back light
	PORTCbits.RC4=1;

}

unsigned char Scan_Key(void)
{

   static unsigned int k1=0 ;
    unsigned char  cnt;


	if(RESET_KEY==0){
        if(k1<181)
			k1++;

	}
	else{
      k1=0;
	}


	if(k1==180){ //be pressed key continue

       cnt=0x01;
	   return cnt;

	}
	return 0;

#if 0
   if(RESET_KEY  ==0 ){
        cnt=0;
        k1++;   
    }
 
    if(RESET_KEY  == 1 ){ //key be release
        cnt++;
        if(cnt<30) return 0;
        
        cnt=0;
        if(k1 >180 && k1< 182){
            value = 0x01; //sort times be pressed key
        }
        else if(k1>300){ //long times be pressed key
            value = 0x81;
		
        }
		else
			value =0;
		
		k1=0;
		return value;
      
    }
    return 0;
#endif 
}



