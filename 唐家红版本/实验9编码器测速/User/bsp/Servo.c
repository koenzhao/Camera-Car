#include"includes.h"
/*
------------------------------------------------------------------------
  函数名称：void Servo_GPIO_Configration(void)
  函数功能：配置舵机控制接口为复用输出
  输入形参：无  	
  返回值：无	
------------------------------------------------------------------------
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
------------------------------------------------------------------------
  函数名称：void Servo_Init(void)
  函数功能：舵机接口初始化供上层函数调用
  输入形参：无  	
  返回值：无	
------------------------------------------------------------------------
*/
void Servo_Init(void)
{
	Servo_GPIO_Configration(); 	
}
/*
------------------------------------------------------------------------
  函数名称：void Change_Direction(uint16_t direction)
  函数功能：改变舵机方向
  输入形参：要填入TIM1->CCR1寄存器的数据  	
  返回值：无	
------------------------------------------------------------------------
*/
void Change_Direction(uint16_t direction)
{
		
	TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Disable);    
	TIM_SetCompare1(TIM1, direction); 
	TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);    
}

