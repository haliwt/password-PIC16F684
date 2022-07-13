#ifndef __KEY_H_
#define __KEY_H_
#include "../../main.h"



//IIC SDA RC1 IO  direction setup
#define SDA_IO_Input()            		do { TRISCbits.TRISC1 = 1; } while(0)
#define SDA_IO_Output()           		do { TRISCbits.TRISC1 = 0; } while(0)

//IIC SCL RC2 IO direction setup

#define SCL_IO_Input()  				  	do { TRISCbits.TRISC2 = 1; } while(0)
#define SCL_IO_Output()   				    do { TRISCbits.TRISC2 = 0; } while(0)


//IO ouput 
#define I2C_SDA_SetHigh()                  do{PORTCbits.RC1 = 1;}while(0)
#define I2C_SDA_SetLow()                   do{PORTCbits.RC1 = 0;}while(0)

#define I2C_SCL_SetHigh()                 do{PORTCbits.RC2 =1;}while(0)
#define I2C_SCL_SetLow()                  do{PORTCbits.RC2 =0;}while(0)

// IO input 
#define I2C_SDA()    PORTCbits.RC1
#define I2C_SCL()    PORTCbits.RC2

#define IO_OUT          0         								//定义 IO口输出方向值
#define IO_IN           1        		              //定义 IO口输入方向值
#define IO_HIGH         1         								//定义 IO口高电平值
#define IO_LOW          0        		              //定义 IO口低电平值


#define SC12B_ADDR    0x40         //ASEL 引脚悬空，设备的地址


#define OUTPUT0_REG          0x08  //Touch of status register output address
//#define OUTPUT1_REG          0x09 //Touch of status register output address CH[11:0]

#define SAMP0_REG            0x0A  //touch of value be save reg output address
//#define SAMP1_REG             0x0B 


#define SenSet0_REG         0x00                //SC12B为对应CIN3 通道灵敏度的设置地址 


#define SenSet0_REG                  0x00    //CIN4 channel sensitivity of address
#define SenSetCom_REG                0x01    //others channel CINx sensitivity  of address 
#define CTRL0_REG                    0x02    //CTRL0 control register setup of address
#define CTRL1_REG                    0x03    //CTRL1  control register setup of address
#define OUPUT_REG                    0x08    //output register state output of address
#define SAMP_REG                     0x0A    //touch data be save value output address 

#define RTM0                         0 
#define RTM1                         1
#define RTM2                         2
#define RTM3                         3


#define KVF_STOP_CORREC              (1<<2)  //touch is avail ,touch don't need calibration 
#define KVF_50S_CORREC              (0<<2)  //touch is avail ,50s start  calibration
#define HOLD             (1<<3)  //base line  ,don't need  calibration
#define NOTHOLD         (0<<3)    //base line ,continue calibration
#define SLPCYC_LGT       (0<<5)   //infint maxmium 
#define SLPCYC_0R5T       (1<<5)   //to sleep for sample interval 60ms 
#define SLPCYC_0R5T       (1<<5)   //to sleep for sample interval 60ms 
#define SLPCYC_5R5T       (6<<5)   //to sleep for sample interval 660ms 
#define SLPCYC_6R5T       (7<<5)   //to sleep for sample interval 780ms 

#define FAST_T0_SLEEP      (1<<4)    //fast input sleep 


#define TOUCH_KEY_SPEC_1              0x40    //'*' 
#define TOUCH_KEY_6                   0x80
#define TOUCH_KEY_7   

extern uint8_t SC_Data[2];


typedef enum
{
    UNDONE = 0x00,
    DONE   = 0x01
}Complete_Status;  


typedef enum 
{
   SPECIAL_1 =0x40,KEY_1=0x10, KEY_2=0x04, KEY_3=0x01, KEY_4=0x400, KEY_5=0x100,
   KEY_6= 0x80, KEY_7=0x20, KEY_8=0x08, KEY_9=0x02, KEY_0=0x800, SPECIAL_2=0x200

}TouchKey_Numbers;




void KEY_Initial(void);


void SC12B_Init_Function(void);





void ICman_Init_SET(unsigned char SC_ADDR);  //IC->SC12B Initialize funciton

uint8_t I2C_SimpleRead_From_Device(uint8_t *dat8);



Complete_Status I2C_Simple_Read_From_Device(unsigned char deviceAddr,unsigned char* target,unsigned char len);
Complete_Status I2C_Read_From_Device(unsigned char deviceAddr,unsigned char REG,unsigned char* target,unsigned char len);

#endif 
