#include"includes.h"
/*私有函数声明，这些函数是不能直接被外部调用的*/

/*
************************************************************************
*  函数名称：Servo_GPIO_Configration()
*  函数功能：配置舵机的端口
*  输入形参：  	
*  返回值：	
*
************************************************************************
*/
void Servo_GPIO_Configration(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	/* 第二步根据通道决定开启哪路GPIO口时钟  */		
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE); 
	RCC_APB2PeriphClockCmd(Servo_Clock , ENABLE);
	/*第三步 根据Channel 配置不同的 GPIO*/
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;		    
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin =  Servo_Pin;
	GPIO_Init(Servo_Port, &GPIO_InitStructure); 	 //PA8
}
/*
************************************************************************
*  函数名称：
*  函数功能：
*  输入形参：  	
*  返回值：	
*
************************************************************************
*/
void Servo_Init(void)
{
	Servo_GPIO_Configration(); 	
}
/*
************************************************************************
*  函数名称：
*  函数功能：
*  输入形参：  	
*  返回值：	
*
************************************************************************
*/
void Change_Direction(uint16_t direction)
{
	/*TIM1的通道1禁止重装载*/	
	TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Disable); 
	/*配置占空比寄存器*/   
	TIM_SetCompare1(TIM1, direction); 
	/*使能重装载*/
	TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);    

}
