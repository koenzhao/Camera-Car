#ifndef __MOTOR_H__
#define __MOTOR_H__
//向上提供两个接口函数1、初始化	  2、调速函数
#define  MOTOR_Port		GPIOA
#define  MOTOR_Pin      GPIO_Pin_11
#define  MOTOR_Clock    RCC_APB2Periph_GPIOA
void Motor_GPIO_Configration(void);	  
void Motor_Init(void);
void Change_Speed(uint16_t Speed);
#endif


