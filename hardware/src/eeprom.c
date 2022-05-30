#include "../inc/EEPROM.h"
#include "../../main.h"

/**
 * @brief 
 * EEPROM of address is 0x00 ~ 0x80 (0~127)
 * 
 */
void EEPROM_Write_Byte(unsigned char addr,unsigned char data)
{
     EEADR=addr;		//写地址;		
     EEDATA=data;		//写数据;

     WREN=1;		    //允许写操作
     
     EECON2=0X55;		//送55H到EECON2(固定的是这么写的而且要按这个顺序)
     EECON2=0XAA;		//送AAH到EECON2(固定的是这么写的而且要按这个顺序)
     WR=1;	            //启动写操作

     while(EEIF==0);    //等待写完成（该位为1时说明写EEPROM完成）

	 EEIF=0;            //清写EEPROM完成标志（该位不会自动清必须软件清）
	 WREN=0;            //禁止写操作发生    		    	
}



unsigned char EEPROM_Read_Byte(unsigned char addr)
{
      EEADR=addr;		//读地址;
      RD=1;	 		    //读操作开始;
      while(RD==1);     //等等读结束，该位不能由软件清0
      return(EEDATA);   //返回读到的数据;

}


void EEEPROM_Password_Init(void)
{
   

}