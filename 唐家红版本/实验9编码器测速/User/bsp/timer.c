#include"includes.h"
/*
-----------------------------------------------------------
   函数名称：
   函数功能：
   输入形参：
   返回值：无  
-----------------------------------------------------------
*/

void TIM1_config(void)
{
	
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	 /*第一步开启时钟*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);	
	
  	TIM_TimeBaseStructure.TIM_Period = 7200-1;//最大数字为 65535
    /*100分频*/
  	TIM_TimeBaseStructure.TIM_Prescaler = 200-1;
 	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);
							   
  	/*
	   第三步：确定占空比，占空比设置为7%
	
	*/
  	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
  	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	/*
	 7%的占空比 计算方法 7/100=x/Cycle_Val推出x=56
	
	*/

  	TIM_OCInitStructure.TIM_Pulse = 504;	/* 获得7%的占空比 */
  	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	/*
		通道4 寄存器初始化 ，对应IO PA11,所以在IO初始化的时候要初始化PA11
	
	*/
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
//用于编码器
void TIM4_Mode_Config(void)
{
	/*第一步 声明对应的结构体*/
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_ICInitTypeDef TIM_ICInitStructure;
		
   	/*第二步 使能定时器4时钟*/
   	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE); 
   	TIM_DeInit(TIM4);
	/*第三步 配置时基寄存器*/
   	TIM_TimeBaseStructure.TIM_Period =0xffff;      
   	TIM_TimeBaseStructure.TIM_Prescaler =0;	    
   	TIM_TimeBaseStructure.TIM_ClockDivision =TIM_CKD_DIV1 ;	//设置时钟分频系数：不分频
   	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //向上计数模式
 	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
	/*第四步 配置定时器工作模式*/
	//编码配置     
	/*TIM_ICPolarity_Rising上升沿捕获*/                  
	TIM_EncoderInterfaceConfig(TIM4, TIM_EncoderMode_TI12,TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);  
    TIM_ICStructInit(&TIM_ICInitStructure);
    TIM_ICInitStructure.TIM_ICFilter = 6;         //比较滤波器
    TIM_ICInit(TIM4, &TIM_ICInitStructure);
  	TIM_ClearFlag(TIM4, TIM_FLAG_Update);
	/*Reset counter*/
    TIM4->CNT =0;
	/*使能定时器4*/
	TIM_Cmd(TIM4, ENABLE);   
}
