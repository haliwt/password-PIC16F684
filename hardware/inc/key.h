#ifndef __KEY_H_
#define __KEY_H_
#include "../../main.h"

#define OUTPUT0_REG          0x08  //Touch of status register output address
//#define OUTPUT1_REG          0x09 //Touch of status register output address CH[11:0]

#define SAMP0_REG            0x0A  //touch of value be save reg output address
//#define SAMP1_REG             0x0B 


typedef struct _KEY_T{

    unsigned int KeyValue;


}KEY_T;

extern KEY_T key_t;



void KEY_Initial(void);


void SC12B_Init_Function(void);

uint8_t SC12B_To_Write_Reg(unsigned char deviceAddr,unsigned char reg,unsigned char *dat8);
uint8_t I2C_Simple_Read_Device(uint8_t deviceAddr,unsigned int *dat16);

uint8_t I2C_Read_Device(uint8_t deviceAddr,uint8_t reg,unsigned int *dat16);
#endif 
