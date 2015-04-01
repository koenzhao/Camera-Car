#include"includes.h"
/*
-----------------------------------------------------------
   函数名称：TIM1_config()
   函数功能：Channel 通道 Cycle 周期
   输入形参： 
   返回值：
   说明:分频的次数越少，定时器就越灵敏，车也就更好控制
-----------------------------------------------------------
*/

void TIM1_config(void)
{
	
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	 /*第一步开启时钟*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);	
	/*
	   第二步：根据分频系数、重装载值确定周期
	
	*/	 
	/*从0开始计数到7199一共计数7200次,所以计数周期为20ms*/
  	TIM_TimeBaseStructure.TIM_Period = 7200-1;//最大数字为 65535  自动重装载寄存器周期
    /*200分频*/
  	TIM_TimeBaseStructure.TIM_Prescaler = 200; //预分频值
 	TIM_TimeBaseStructure.TIM_ClockDivision = 0;	//时钟分割
  	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;		//计数器模式 TIM向上计数模式
  	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);
							   
  	/*
	   第三步：配置TIM1的通道工作模式
	   （配置定时器的4个通道）
	
	*/
  	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;  //TIM脉冲宽度调制模式1
  	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	/*
	 7%的占空比 计算方法 7/100=x/7200推出x=504
	
	*/

  	TIM_OCInitStructure.TIM_Pulse = 504;	/* 获得7%的占空比 脉冲*/
  	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;	//TIM输出极性高 
	//初始化TIM1的通道1和4
	TIM_OC1Init(TIM1, &TIM_OCInitStructure); 
  	TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);
	TIM_OC4Init(TIM1, &TIM_OCInitStructure); 
 	TIM_OC4PreloadConfig(TIM1, TIM_OCPreload_Enable);
  	
	// 使能重载
  	TIM_ARRPreloadConfig(TIM1, ENABLE);	
  	/* TIM1 enable counter */
  	TIM_Cmd(TIM1, ENABLE); 
  	/* 下面这句话对于TIM1和TIM8是必须的，对于TIM2-TIM6则不必要 */
  	TIM_CtrlPWMOutputs(TIM1, ENABLE);

}
