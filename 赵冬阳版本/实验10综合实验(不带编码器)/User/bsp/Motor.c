#include"includes.h" 
 
/*
------------------------------------------------------------------------
  函数名称：void Motor_GPIO_Config(void)
  函数功能：配置控制GPIO为复用输出功能
  输入形参：无
  返回值：无
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
  函数名称：void Motor_Init(void)
  函数功能：电调控制接口初始化，供上层函数调用
  输入形参：无
  返回值：无
------------------------------------------------------------------------
*/
void Motor_Init(void)
{
	Motor_GPIO_Configration();
}

/*
------------------------------------------------------------------------
  函数名称：void Change_Speed(uint16_t Speed)
  函数功能：改变TIM1定时器第四通道占空比
  输入形参：填入CCR寄存器的数据
  返回值：无
------------------------------------------------------------------------
*/
void Change_Speed(uint16_t Speed)
{
	
	TIM_OC4PreloadConfig(TIM1, TIM_OCPreload_Disable);
	TIM_SetCompare4(TIM1, Speed); 
	TIM_OC4PreloadConfig(TIM1, TIM_OCPreload_Enable);
}
