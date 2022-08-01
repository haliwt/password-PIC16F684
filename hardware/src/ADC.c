#include "../inc/ADC.h"


void ADC_Init(void)
{
     //CMCON = 0x07; //PIC16F676
     CMCON0 = 0x07;  //PIC16F684
     ANSELbits.ANS4 = 1 ; //I/O as analog  CHANNEL 4 
     WPU = 0x00;
     TRISCbits.TRISC0 = 1 ; 

     ADCON0 = 0x90;  // analog channel 4,Operiation is not  
}

/**
 * @brief 
 * 
 * @return 
 */
unsigned int ADC_ReadVoltage(void)
{
    unsigned int cTemp;
  

         

        // ADCON0        = 0x8d;                //A/D 控制寄存器选择AN3
        // ADCON0=0X9D;           //选择ＡＮ７通道
                                //转换结果右对齐
                                //选择ＶＤＤ作为参考电压
         ADCON0 =0x93;  //选择ＡＮ4通道
        //  ADCON0bits.ADON = 1;
   // __delay_ms(2);
  // ADCON0bits.GO_DONE =1;
   
         __delay_ms(2);
         GO_DONE = 1;           //启动ＡＤ转换
         while(GO_DONE == 1);   //等待转换完成
         cTemp  = ADRESH;       //读取ＡＤ转换结果高位
         cTemp &= 0x03;
         cTemp <<= 8;           //
         cTemp += ADRESL;       //读取ＡＤ转换低８位并加上高位
         return(cTemp);         //返回ＡＤ转换结果    

  

}