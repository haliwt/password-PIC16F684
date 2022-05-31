#include "../inc/key.h"




//IIC SDA RC1
#define SDA_RC1_SetDigitalInput()    do { TRISCbits.TRISC1 = 1; } while(0)
#define SDA_RC1_SetDigitalOutput()   do { TRISCbits.TRISC1 = 0; } while(0)

//IIC SCL RC2

#define SCL_RC1_SetDigitalInput()    do { TRISCbits.TRISC2 = 1; } while(0)
#define SCL_RC1_SetDigitalOutput()   do { TRISCbits.TRISC2 = 0; } while(0)

#define I2C_SDA()    PORTCbits.RC1
#define I2C_SCL()    PORTCbits.RC2

#define SC12B_ADDR       0x40   //ASEL NC of address

#define  SENSET0_REG        0x00  //CIN4 channel sensitivity
#define SENSETCOM_REG       0x01  //other channel sensitivity
#define CTRL0_REG           0x02  //CTRL0 control register set address
#define CTRL1_REG           0x03  //CTRL1 control register set address



#define RTM0                0    // 3 pcs sample of period time is active, 1 pcs sample period adjust invalid
#define RTM1                1    // 4 pcs sample of period time is active, 2 pcs sample period adjust invalid
#define RTM2                2    // 5 pcs sample of period time is active, 3 pcs sample period adjust invalid
#define RTM3                3    // 6 pcs sample of period time is active, 4 pcs sample period adjust invalid

#define KVF_STOP_CORREC     (1<<2)   //key be pressed is active ,touch don't calibration
#define KVF_50S_CORREC     (1<<2)   //key be pressed is active ,50s  calibration
#define HOLD                (1<<3)     //to base line ,don't calibration
#define NOTHOLD             (0<<3)     // to base line ,continue calibration

#define SLPCYC_LGT          (0<<5)   //infinity
#define SLPCYC_0R5T         (1<<5)   //sleep after sample interval 60ms
#define SLPCYC_0R5T         (2<<5)   //sleep after sample interval 180ms
#define SLPCYC_0R5T         (3<<5)   //sleep after sample interval 300ms
#define SLPCYC_0R5T         (4<<5)   //sleep after sample interval 420ms
#define SLPCYC_0R5T         (5<<5)   //sleep after sample interval 540ms
#define SLPCYC_0R5T         (6<<5)   //sleep after sample interval 660ms
#define SLPCYC_0R5T         (7<<5)   //sleep after sample interval 780ms

#define FAST_TO_SLEEP       (1<<4)  //fast input sleep
#define SLOW_TO_SLEEP       (0<<4)  //75s input sleep


static void I2C_Start(void);
static void I2C_Stop(void);
void I2C_Respond(unsigned char acksig);
static unsigned char SendByte_GetNACK(unsigned char data);
static unsigned char I2C_Receive8bit(void);



/**
 * @brief 
 * 
 */
void SC12B_Init_Function(void)
{
   
    CMCON  = 0x07;          //关闭比较器功能 ->PORTA 
    ANSELbits.ANS5 = 0;
    ANSELbits.ANS6=0;     //

    TRISCbits.TRISC1 = 0;
    TRISCbits.TRISC2= 0;

}
/**
 * @brief 
 * 
 */
static void I2C_Start(void)
{
   SDA_RC1_SetDigitalOutput();
   SCL_RC1_SetDigitalOutput();

   I2C_SDA() = 1;
   I2C_SCL() =1;
   __delay_us(1);
   I2C_SDA() =0;
   __delay_us(1);
   I2C_SCL() =0;
   __delay_us(1);

}

static void I2C_Stop(void)
{
    I2C_SCL() =0;
    SDA_RC1_SetDigitalOutput();
    I2C_SDA() = 0;
    __delay_us(1);
    I2C_SCL() =1;
    __delay_us(1);
    I2C_SDA() =1;
}
/**
 * @brief  IIC send byte and get answer signal
 *  
 */
unsigned char SendByte_GetNACK(unsigned char senddata)
{
    uint8_t i;
    uint8_t ack;
    SDA_RC1_SetDigitalOutput();

    for(i=0;i<8;i++){
        I2C_SCL() = 0;
        __delay_us(1);
        I2C_SDA() = (senddata >>7) & 0x01; //high  bit the first front to send 
        __delay_us(1);
        I2C_SCL()  =1; 
        __delay_us(1);
        senddata<<=1;
    }
    I2C_SCL() = 0; //free bus 
    __delay_us(3);
    SDA_RC1_SetDigitalInput();
    __delay_us(3);
    I2C_SCL() =1;
    __delay_us(1);
    i=250;
    while(i--)
    {
        if(I2C_SDA()==0){
            I2C_SCL() =0;
            return 0;
        }
    }
    I2C_SCL()= 0;
    return 1;
}

/**
 * @brief read one byte ,and send answer order
 * 
 */
void I2C_Respond(unsigned char acksig)
{
   SDA_RC1_SetDigitalOutput();
   I2C_SDA() =0;
   I2C_SCL() =0;
   I2C_SDA() = acksig;
   __delay_us(1);
   I2C_SCL() =1;
   __delay_us(1);
   I2C_SCL() =0;

}
/**
 * @brief 
 * 
 */
unsigned char I2C_Receive8bit(void)
{
    uint8_t i,buffer;
    SDA_RC1_SetDigitalInput();
    I2C_SCL() = 0;
    for(i=0;i<8;i++){
        __delay_us(1);
        I2C_SCL()= 1;
        buffer =(buffer<<1) | I2C_SDA();
        __delay_us(1);
        I2C_SCL() =0;
    }
    return buffer;
}



/**
 * @brief 
 * 
 * @param deviceAddr 
 * @param reg 
 * @param dat8 
 */
uint8_t SC12B_To_Write_Reg(unsigned char deviceAddr,
                 unsigned char reg,unsigned char *dat8)
{
    I2C_Start();
    if(SendByte_GetNACK(deviceAddr <<1) & ~0x01){
        I2C_Stop();
        return 0;
    }

     if(SendByte_GetNACK(reg)){
        I2C_Stop();
        return 0;
    }
    if(SendByte_GetNACK(*dat8)){
        I2C_Stop();
        return 0;
    }
    I2C_Stop();
    return 1;

}

/**
 * @brief 
 * 
 */
uint8_t I2C_Simple_Read_Device(uint8_t deviceAddr,unsigned int *dat16)
{
    uint8_t buf1,buf2;
      I2C_Start();
    if(SendByte_GetNACK(deviceAddr <<1) & ~0x01){
        I2C_Stop();
        return 0;
    }

    buf1 = I2C_Receive8bit();
    I2C_Respond(0);

    buf2 = I2C_Receive8bit();
    I2C_Respond(1);

    I2C_Stop();
    *dat16=(unsigned int)buf1<<8 | buf2;

    return 1;

}

/****
 * 
 * Function Name :
 * Function : IC SC12B read register value 
 * Input Ref: deviceAddr  ->device address ,reg -register address,dat16 -> read of address value
 * 
*/
uint8_t I2C_Read_Device(uint8_t deviceAddr,uint8_t reg,unsigned int *dat16)
{
    uint8_t buf1,buf2;
    
    I2C_Start();
    if(SendByte_GetNACK(deviceAddr <<1) & ~0x01){
        I2C_Stop();
        return 0;
    }
     if(SendByte_GetNACK(reg)){
        I2C_Stop();
        return 0;
    }
    I2C_Stop();
    I2C_Start();
     I2C_Start();
    if(SendByte_GetNACK(deviceAddr <<1) & ~0x01){
        I2C_Stop();
        return 0;
    }

    buf1 = I2C_Receive8bit();
    I2C_Respond(0);

    buf2 = I2C_Receive8bit();
    I2C_Respond(1);

    I2C_Stop();
    *dat16=(unsigned int)buf1<<8 | buf2;

    return 1;
}







