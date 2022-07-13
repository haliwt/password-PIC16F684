#include "../inc/key.h"







static void I2C_Start(void);
static void I2C_Stop(void);
void I2C_Respond(unsigned char acksig);
static unsigned char SendByte_GetNACK(unsigned char data);
static unsigned char I2C_Receive8bit(void);
unsigned char SendByteAndGetNACK(unsigned char dataToSend);



/**
 * @brief 
 * 
 */
void SC12B_Init_Function(void)
{
   
   // CMCON  = 0x07;          //关闭比较器功能 ->PORTA 
    CMCON0 = 0x07 ; //PIC16F684
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
   SDA_IO_Output();
   SCL_IO_Output();

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
    SDA_IO_Output();
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


/**
 * @brief read one byte ,and send answer order
 * 
 */
void I2C_Respond(unsigned char acksig)
{
   SDA_IO_Output();
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
    SDA_IO_Input();
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
/************************************************************
*
*Function Name: uint8_t uint8_t Send_OneByte_Ack(uint8_t dat)
*Function : I2C to send one byte data
*Input Ref: send data
*Return Ref: 0 -fail 1 -success
*
************************************************************/
uint8_t Send_OneByte_Ack(uint8_t dat)
{
    uint8_t i,temp;
    SDA_IO_Output() ;//I2C_SDA_IO_OUT();
    for(i=0;i<8;i++){
       I2C_SCL_SetLow();
          __delay_us(2);//Delay_I2C(1);
         temp = (dat >>7)&0x01;
        if(temp & 0x01){
           I2C_SDA_SetHigh();
        }
        else{
           I2C_SDA_SetLow();
        }
         __delay_us(1);//Delay_I2C(1);
        I2C_SCL_SetHigh();
         __delay_us(1);//Delay_I2C(1);
        I2C_SCL_SetLow();
        
        dat<<=1;   //MSB the first ahead ,LSB the last end
    }
    I2C_SCL_SetLow();
    
     __delay_us(3);//Delay_I2C(3);
  SDA_IO_Input()   ;//I2C_SDA_IO_IN();
     __delay_us(3);//Delay_I2C(3);
    I2C_SCL_SetHigh();
     __delay_us(1);//Delay_I2C(1);
    i=250;
    while(i--){
        
        if(I2C_SDA()==0){
              I2C_SCL_SetLow();
              return 0;
        }
        
    }
    
    I2C_SCL_SetLow();
    return 1;
    
}

/**
 * @brief 
 * 
 */
/*****************************************************************************
						* 发送一个字节数据，并获取应答
******************************************************************************/
unsigned char SendByteAndGetNACK(unsigned char dataToSend)
{
		unsigned char i,temp;
		SDA_IO_Output();//SDA_OUT_OR_IN = IO_OUT;
		for (i = 0; i < 8; i++) {
			I2C_SCL_SetLow();//SCL = IO_LOW;
			 __delay_ms(5);//I2C_Delay();
			//SDA = (dataToSend>>7) &0x01;
          temp = (dataToSend >>7)&0x01;
        if(temp & 0x01){
           I2C_SDA_SetHigh();
        }
        else{
           I2C_SDA_SetLow();
        }
			 __delay_ms(5);//I2C_Delay();
			I2C_SCL_SetHigh();//SCL = IO_HIGH;
			 __delay_ms(5);//I2C_Delay();
			dataToSend <<= 1;
		}
		I2C_SCL_SetLow();//SCL = IO_LOW;
		 SDA_IO_Input();           //SDA_OUT_OR_IN = IO_IN;
		 __delay_ms(5);//I2C_Delay();
		I2C_SCL_SetHigh();//I2C_SCL = IO_HIGH;
	   __delay_ms(5);//I2C_Delay();
		i= 250;
		while(i--)
		{
			//if(!SDA_IN){ SCL = IO_LOW; return 0;}
			 if(I2C_SDA()==0){
              I2C_SCL_SetLow();
              return 0;
        	  }
        
			
		}
		I2C_SCL_SetLow();//SCL = IO_LOW;
		return (1);
}

/*****************************************************************************
									* 读取一个字节函数
******************************************************************************/
unsigned char I2C_Receive8Bit(void)
{
		unsigned char i,buffer = 0;
		 SDA_IO_Input()  ;         //SDA_OUT_OR_IN = IO_IN;
		I2C_SCL_SetLow();//SCL = IO_LOW;
		for (i = 0; i < 8; i++)
		{
			 __delay_ms(5);//I2C_Delay();
			I2C_SCL_SetHigh();//SCL = IO_HIGH;
			//buffer = (buffer<<1)|SDA_IN;
			buffer = (buffer<<1)| I2C_SDA();
			 __delay_ms(5);//I2C_Delay();
			I2C_SCL_SetLow();//SCL = IO_LOW;
		}		
		return (buffer);
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


/*****************************************************************************
				* SC系列B版本芯片 写寄存器参数运用函数
deviceAddr 设置器件地址 REG 设置寄存器地址 DAT8 写入数据内容的地址
******************************************************************************/
Complete_Status I2C_Write_To_Device(unsigned char deviceAddr,unsigned char REG,unsigned char*DAT8)
{
			I2C_Start();
			if (Send_OneByte_Ack((deviceAddr<<1) & ~0x01)) {
					I2C_Stop();
				return UNDONE;
			}
			if (Send_OneByte_Ack(REG)) {
					I2C_Stop();
					return UNDONE;
			}
			if (Send_OneByte_Ack(*DAT8)) {
					I2C_Stop();
					return UNDONE;
			}
			I2C_Stop();
			return DONE;
}

/*****************************************************************************
					*SC系列B系列芯片初始化功能函数，如无特殊运用，无需初始化
					如需对那个型号芯片初始化，只需将对应地址写入即可，
					对应的设定参数在初始化函数里面修改
******************************************************************************/
void ICman_Init_SET(unsigned char SC_ADDR)
{
		 unsigned char databuf;
		 #ifdef SPECIAL_APP		
		 //灵敏度从低到高 0x04  0 0x15    0x25  0x36  0x47  0x58  0x68  0x79 
     //               0x8A  0x9B  0xAC  0xBC  0xCD  0xDE  0xEF  0xFF 	
				databuf = 0xFF;
				while(I2C_Write_To_Device(SC_ADDR,SenSet0_REG,&databuf) !=DONE);	
				//databuf = 0x79;
				//while(I2C_Write_To_Device(SC_ADDR,SenSetCOM_REG,&databuf) !=DONE);	
			 //////////非必要，不建议修改，不用直接注释掉/////////////////////////////
			 //databuf = SLPCYC_3R5T | SLOW_TO_SLEEP | NOTHOLD | KVF_50S_CORREC | RTM3;
			 //while(I2C_Write_To_Device(SC_ADDR,CTRL0_REG,&databuf)!=DONE);	
				
				//////////无必要，不建议修改，不用直接注释掉/////////////////////////
				//databuf =0b1000;
				//while(I2C_Write_To_Device(SC_ADDR,CTRL1_REG,&databuf)!=DONE);	
				
		 #endif
}


/*********************************************************************************************
*
*Function Name: uint8_t I2C_SimpleRead_From_Device(uint16_t *dat16)
*Function : I2C to send one byte data
*Input Ref: device address= 0x40 ,device register address =0x08,0x09 , read data is dat16
*Return Ref: 0--fail  1 - success
*
*********************************************************************************************/
uint8_t I2C_SimpleRead_From_Device(uint8_t *dat8)
{
    uint8_t buf1;
    
   I2C_Start();
   if(Send_OneByte_Ack(SC12B_ADDR << 1)| 0x01){
            
          I2C_Stop();
          return 0;
   }
   
   buf1 = I2C_Receive8Bit(); //reg address = 0x08
   I2C_Respond(0); //acknowledge
   
    I2C_Receive8Bit(); //reg address = 0x09
   I2C_Respond(1); //don't ack
   
   I2C_Stop();
   
   //*dat16 = ((uint16_t)buf1) <<8 | buf2; //
    *dat8 = buf1;
   
   return 1;
   
}
/*********************************************************************************************
*
*Function Name: uint8_t I2C_Read_From_Device(uint8_t reg, uint16_t *dat16)
*Function : I2C to send one byte data
*Input Ref: device address =0x40 ,device register address , read data is dat16
*Return Ref: 0--fail  1 - success
*
*********************************************************************************************/


/***************************************************************************************************************************
SC系列B版本芯片 简易读取按键值函数（默认直接读取）
此函数只有初始化配置默认的情况下，直接调用，如果在操作前有写入或者其他读取不能调用默认
**********************************************************************************************************************************/
Complete_Status I2C_Simple_Read_From_Device(unsigned char deviceAddr,unsigned char* target,unsigned char len)
{
			unsigned char i;
			unsigned char *p;
			p = target;
			I2C_Start();
			if (Send_OneByte_Ack((deviceAddr<<1) | 0x01)) {
					I2C_Stop();
					return UNDONE;
			}
			for(i = 0; i < len; i++)
			{
			 		*p= I2C_Receive8Bit();
			 		 p++;
				 	if(i < len-1)
			  			I2C_Respond(0);
			 		else 
			 	 			I2C_Respond(1);
			}
			I2C_Stop();
			return DONE;
}
/*******************************************************************************************************************************
* SC系列B版本芯片
deviceAddr 设置器件地址, REG 设置寄存器地址, target 读取地址对应数据内容。
**************************************************************************************************************************************/
Complete_Status I2C_Read_From_Device(unsigned char deviceAddr,unsigned char REG,unsigned char* target,unsigned char len)
{
	  unsigned char i;
		unsigned char *p;
	  p = target;
		I2C_Start();
		if (Send_OneByte_Ack((deviceAddr<<1) & ~0x01)) {
				I2C_Stop();
				return UNDONE;
		}
		if (Send_OneByte_Ack(REG)) {
			I2C_Stop();
			return UNDONE;
		}
		I2C_Stop();
		I2C_Start();
		if (Send_OneByte_Ack((deviceAddr<<1) | 0x01)) {
			I2C_Stop();
			return UNDONE;
		}
		for(i = 0; i < len; i++)
		{
			 	*p= I2C_Receive8Bit();
			 	p++;
				if(i < len-1)
			  	 I2C_Respond(0);
			  else 
			 	 	 I2C_Respond(1);
		}
		I2C_Stop();
		return DONE;
}





