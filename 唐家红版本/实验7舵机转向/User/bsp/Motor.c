#include"includes.h"  
/*
------------------------------------------------------------------------
函数名称：
函数功能：
输入形参：
返回值：
------------------------------------------------------------------------
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
------------------------------------------------------------------------
函数名称：
函数功能：
输入形参：
返回值：
------------------------------------------------------------------------
*/
void Motor_Init(void)
{
	Motor_GPIO_Configration();
}

/*
------------------------------------------------------------------------
函数名称：
函数功能：
输入形参：
返回值：
------------------------------------------------------------------------
*/
void Change_Speed(uint16_t Speed)
{
	
	//TIM1->CCR4=Speed;
	TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Disable);
	TIM_SetCompare4(TIM1, Speed); 
	TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);
	
	/*通道4周期20ms 占空比5*/
}
