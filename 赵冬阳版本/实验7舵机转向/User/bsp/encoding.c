#include"includes.h"
float kp= 0.007;
float kd= 0.0007;
s16 err,err_last;
volatile s16 encoder_num;
void SpeedContiol(u16 speed)   
{
	s16 car_speed;
	s16 pwm;	
	encoder_num=TIM_GetCounter(TIM4);
	car_speed=encoder_num;
	TIM4->CNT=0;
	err=speed-car_speed;	 
    pwm=540+kp*err+kd*(err-err_last);
	err_last=err;
	//限制车速
	if (pwm>600) pwm=600;
	if (pwm<400) pwm=400;
	//TIM1->CCR4 =pwm; 
	Change_Speed(pwm);   
}
