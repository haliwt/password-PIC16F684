#include "../inc/motor.h"



static void MotorStart_CW_Step(void);
static void MotorStart_CCW_Step(void);

/**
 * @brief 
 * 
 */
void Motor_Init(void)
{
	//CMCON = 0x07;
    CMCON0 = 0x07; //PIC16F684
    ANSELbits.ANS3 = 0;
    
    TRISAbits.TRISA5 = 0;
	TRISAbits.TRISA4 =0;  //as output GPIO 

	
	
	
    MOTOR_CW_OFF() ; //brake
    MOTOR_CCW_OFF(); //brake
}

/**
 * @brief 
 * 
 */
void Motor_CW_Run(void)
{
	MotorStart_CW_Step();
	MOTOR_CW_RUN();	
	MOTOR_CCW_OFF();
	
}

void Motor_CCW_Run(void)
{
	MotorStart_CCW_Step();
    MOTOR_CCW_RUN();
    MOTOR_CW_OFF();	
	
}



void Motor_Stop(void)
{
    MOTOR_CW_OFF(); //brake
    MOTOR_CCW_OFF(); //brake
}
/**
 * @brief 
 * 
 */
 static void MotorStart_CW_Step(void)//Up 
{
	
    // if(cmd_t.gmotor_upStep==0 ){//CW
	//	cmd_t.gmotor_upStep++;
        
       
        MOTOR_CCW_OFF();
        
       MOTOR_CW_RUN();	
	   __delay_ms(25);
	   MOTOR_CW_OFF();
	   __delay_ms(25);
       MOTOR_CW_RUN();	
       __delay_ms(50);
	  
   // }


}

 static void MotorStart_CCW_Step(void)
{
     //if(cmd_t.gmotor_upStep==0 ){//CW
		//cmd_t.gmotor_upStep++;
        
      	MOTOR_CW_OFF();	
	
	   MOTOR_CCW_RUN();
	   __delay_ms(50);
	    MOTOR_CCW_OFF();
	   __delay_ms(50);
       MOTOR_CCW_RUN();
	 
        
    //}



}
