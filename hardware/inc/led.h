#ifndef __LED_H_
#define __LED_H_
#include "../../main.h"

#define  BACKLIGHT_ON()          (PORTAbits.RA2 =1)
#define  BACKLIGHT_OFF()         (PORTAbits.RA2 =0)

#define  BACKLIGHT_2_ON()       (PORTCbits.RC3 = 1)
#define  BACKLIGHT_2_OFF()      (PORTCbits.RC3 = 0)

#define  BAT_LED_ON()           (PORTCbits.RC4 = 0)
#define  BAT_LED_OFF()           (PORTCbits.RC4 =1 )

#define  OK_LED_ON()           (PORTAbits.RA1 = 0)
#define  OK_LED_OFF()            (PORTAbits.RA1 = 1)

#define  ERR_LED_ON()           (PORTAbits.RA0 =0)
#define  ERR_LED_OFF()             (PORTAbits.RA0 =1)

#define RESET_KEY               PORTAbits.RA3 



#define KEY1_RA3_GetValue()           PORTAbits.RA3



#define		_KEY_ALL_OFF				  0X1F

//normal times be pressed key
#define		_KEY_TRG_1_WK_UP     			0x01  //WK_UP
#define		_KEY_TRG_2_KEY_1     			0x02  //??????--???
#define		_KEY_TRG_3_TIMER     			0x04   //????
#define		_KEY_TRG_4_FILTER     			0x08
// combination of buttons 
#define		_KEY_TRG_5_WINDTI   			0x11   //?????
#define		_KEY_TRG_6_WINDTI   			0x12   //?????
#define		_KEY_TRG_7_WINDTI   			0x14   //?????
#define		_KEY_TRG_8_WINDTI   			0x18   //?????

//long times be pressed
#define		_KEY_CONT_1_WK_UP     	     0x81    //??????--???
#define		_KEY_CONT_2_KEY_1    		 0x82    //??????--???
#define		_KEY_CONT_3_TIMER     	     0x84    //?????? ?????
#define		_KEY_CONT_4_FILTER     	     0x88    //??? --?????
#define		_KEY_CONT_5_WINDTI     		 0x89




#define		_KEY_CONT_1     	    0x81    //?????
#define		_KEY_CONT_2     		0x82
#define		_KEY_CONT_3     		0x84
#define		_KEY_CONT_4     	    0x88

#define		_KEY_COM_1    		    0x91
#define		_KEY_COM_2    		    0x92
#define		_KEY_COM_3    		    0x94
#define		_KEY_COM_4    		    0x98

typedef  struct  _state_
{
 unsigned char          read;
 unsigned char         buffer;
 unsigned char        value;
 unsigned char        off_time;
 unsigned long        on_time;

 enum{
  start  = 0,
  first  = 1,
  second = 2,
  cont   = 3,
  end    = 4,
  finish = 5,
 }state;
}key_types;

//key_types key;







void System_Init(void);


unsigned char Scan_Key(void);
void KEY_ISR(void);

#endif 
