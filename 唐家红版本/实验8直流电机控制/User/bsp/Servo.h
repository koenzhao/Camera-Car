#ifndef __SERVO_H__
#define __SERVO_H__
/*						
该头文件向上提供两个函数，第一个是 初始化 函数 ，第二个是 改变 舵机方向的函数

*/

#define Servo_Port		GPIOA
#define Servo_Pin		GPIO_Pin_8
#define Servo_Clock		RCC_APB2Periph_GPIOA

void Servo_Init(void);
//舵机转向函数
void Change_Direction(uint16_t direction);
void Servo_GPIO_Configration(void);

#endif
