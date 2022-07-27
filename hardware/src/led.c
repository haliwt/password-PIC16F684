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
    ANSELbits.ANS7 =0 ; //gpio as digital

    TRISAbits.TRISA0 =0;
    TRISAbits.TRISA1 =0 ;
    TRISAbits.TRISA2 = 0;  //I/O as output 
    TRISCbits.TRISC4 = 0;
	TRISCbits.TRISC3 = 0; 
    //RESET KEY gpio input PORT
    TRISAbits.TRISA3 = 1;   //I/O as input
    IOCAbits.IOCA3 =1 ;    //Open interrupter flag
	INTCONbits.RAIE=1;
	INTCONbits.RAIF=0;
    
    //Setup GPIO output defult value 
    PORTAbits.RA0=1;
	PORTAbits.RA1=1;
	PORTAbits.RA2=0;  //back light led1
	PORTCbits.RC4=1;
	PORTCbits.RC3= 0; //back light led2

}

//unsigned char Scan_Key(void)
//{
//
//   static unsigned int k1=0 ;
//   static unsigned char  cnt;
//   unsigned char value;
//
//	if(RESET_KEY==0){
//        cnt=0;
//		k1++;
//
//	}
//	
//   if(RESET_KEY  == 1 ){ //key be release
//        cnt++;
//        if(cnt<10) return 0;
//        
//        cnt=0;
//        if(k1 >40 && k1< 60){
//            value = 0x01; //sort times be pressed key
//        }
//        else if(k1>181 && k1< 201 ){ //long times be pressed key
//            value = 0x81;
//		
//        }
//		else
//			value =0;
//		
//		k1=0;
//		return value;
//      
//    }
//    return 0;
//
//}

unsigned char  Scan_Key(void)
{
  unsigned char   reval = 0;
  key.read = _KEY_ALL_OFF; //0x1F 
   if(KEY1_RA3_GetValue() ==0 )
	{
		key.read &= ~0x01; // 0x1f & 0xfe =  0x1E
	}
	
	
	switch(key.state )
	{
		case start:
		{
			if(key.read != _KEY_ALL_OFF)
			{
				key.buffer   = key.read; //??:key.buffer = 0x1E  POWER KEY 
				key.state    = first;
				key.on_time  = 0;
				key.off_time = 0;
           
                
			}
			break;
		}
		case first: //shot key times 
		{
			if(key.read == key.buffer) // adjust key be down 
			{
				if(++key.on_time> 1000) //1000  0.5us -> short time key
				{
					key.value = key.buffer^_KEY_ALL_OFF; // key.value = 0x1E ^ 0x1f = 0x01, com = 0x0E ^ 0x1f = 0x11
					key.on_time = 0;
                   
					key.state   = second;
                   
                    
				}
			}
			else
			{
				key.state   = start;
			}
			break;
		}
		case second: //long key times 
		{
			if(key.read == key.buffer) //again adjust key if be pressed down 
			{
				if(++key.on_time>20000)// 10000 long key be down
				{
					
					key.value = key.value|0x80; //key.value = 0x01 | 0x80  =0x81  
					key.on_time = 0;
					key.state   = finish;
                  
                   
				}
			}
			else if(key.read == _KEY_ALL_OFF)  // loose hand 
				{
					if(++key.off_time>30) //30 don't holding key dithering
					{
						key.value = key.buffer^_KEY_ALL_OFF; // key.value = 0x1E ^ 0x1f = 0x01
						
						key.state   = finish; // loose hand
					}
				}
		   
			break;
		}
		case finish:
		{
			
			reval = key.value; // is short time  TIMER_KEY = 0x01  2. long times TIMER_KEY = 0X81
			key.state   = end;
         
			break;
		}
		case end:
		{
			if(key.read == _KEY_ALL_OFF)
			{
				if(++key.off_time>50)//50 //100
				{
					key.state   = start;
                  
				}
			}
			break;
		}
		default:
		{
			key.state   = start;
         
			break;
		}
	}
	return  reval;


}


void KEY_ISR(void)
{
   	INTCONbits.RAIF = 0;
    run_t.getKey =  Scan_Key();
}

