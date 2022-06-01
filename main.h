/* 
 * File:   main.h
 * Author: YYJ-2
 *
 * Created on May 24, 2022, 1:51 PM
 */

#ifndef MAIN_H
#define	MAIN_H
#include <stdio.h>
#include <stdlib.h>
//#include  <string.h>
#include <xc.h>

#include "hardware/inc/buzzer.h"
#include "hardware/inc/key.h"
#include "hardware/inc/led.h"
//#include "hardware/inc/tim0.h"
#include "hardware/inc/tim1.h"
#include "hardware/inc/interrupt.h"
#include "hardware/inc/run.h"
#include "hardware/inc/ADC.h"
#include "hardware/inc/eeprom.h"
#include "hardware/inc/led.h"
#include "hardware/inc/motor.h"


#define _XTAL_FREQ         4000000  //PIC16F684 default 

typedef  unsigned char   uint8_t ;


#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* MAIN_H */

