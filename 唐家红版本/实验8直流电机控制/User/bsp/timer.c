#include"includes.h"
/*
-----------------------------------------------------------
   函数名称：void TIM1_config(void)
   函数功能：配置TIM1为PWM模式，并根据参数配置其占空比
   输入形参：无 
   返回值：无
   说明:
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
	/*从0开始计数到7199一共计数7200次,预分频为200那么周期=(200/72M)x7200=20MS*/
  	TIM_TimeBaseStructure.TIM_Period = 7200-1;//最大数字为 65535
    /*200分频*/
  	TIM_TimeBaseStructure.TIM_Prescaler = 200;
 	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);
							   
  	/*
	   第三步：配置定时器工作模式为PWM波模式，并配置占空比数值
	
	*/
  	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
  	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	/*
	 7%的占空比 计算方法 7/100=x/7200推出x=504
	
	*/	 
  	TIM_OCInitStructure.TIM_Pulse = 504;	/* 获得7%的占空比 */
  	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	/*
	初始化TIM1的通道1和通道4，对应的管脚请查阅相关手册	
	
	*/
	TIM_OC1Init(TIM1, &TIM_OCInitStructure); 
  	TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);
	TIM_OC4Init(TIM1, &TIM_OCInitStructure); 
  	TIM_OC4PreloadConfig(TIM1, TIM_OCPreload_Enable);  	
	/*使能重载*/
  	TIM_ARRPreloadConfig(TIM1, ENABLE);	
  	/* 使能定时器1 */
  	TIM_Cmd(TIM1, ENABLE); 
  	/* 下面这句话对于TIM1和TIM8是必须的，对于TIM2-TIM6则不必要 */
  	TIM_CtrlPWMOutputs(TIM1, ENABLE);
}
