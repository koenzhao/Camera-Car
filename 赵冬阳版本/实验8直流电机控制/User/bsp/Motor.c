#include"includes.h"  
/*
-----------------------------------------------
函数名称：void Motor_GPIO_Configration(void)
函数功能：配置电调控制接口为复用输出
输入形参：无
返回值：无
-----------------------------------------------
*/
void Motor_GPIO_Configration(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	/* 第二步根据通道决定开启哪路GPIO口时钟  */		
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE); 
	RCC_APB2PeriphClockCmd(MOTOR_Clock , ENABLE);
	/*第三步 根据Channel 配置不同的 GPIO*/
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;		    
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin =  MOTOR_Pin;
	GPIO_Init(MOTOR_Port, &GPIO_InitStructure); 	 //PA8

}
/*
-----------------------------------------------
函数名称：电调初始化
函数功能：向上提供的函数接口
输入形参：无
返回值：无
-----------------------------------------------
*/
void Motor_Init(void)
{
	Motor_GPIO_Configration();
}

/*
-----------------------------------------------
函数名称：void Change_Speed(uint16_t Speed)
函数功能：改变PWM波占空比达到控制直流电机速度的目的
输入形参：速度值
返回值： 无
-----------------------------------------------
*/
void Change_Speed(uint16_t Speed)
{ 
	/*禁止TIM1的通道4的计数重载*/
	TIM_OC4PreloadConfig(TIM1, TIM_OCPreload_Disable);
	/*设置占空比数值*/
	TIM_SetCompare4(TIM1, Speed); 
	/*使能TIM1通道4计数重载*/
	TIM_OC4PreloadConfig(TIM1, TIM_OCPreload_Enable);
}
