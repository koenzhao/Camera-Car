/********************************************************************************
  快乐的实验室                        
  *******************************************************************************/
#include "encoder.h"
//volatile s16 encoder_num;
// void TIM2_Mode_Config(void)
// {
//   TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
//   RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); //使能ＴＩＭ３
//   TIM_TimeBaseStructure.TIM_Period =5000;       //当定时器从0计数到999，即为1000次，为一个定时周期
//   TIM_TimeBaseStructure.TIM_Prescaler =7200-1;	    //设置预分频：
//   TIM_TimeBaseStructure.TIM_ClockDivision =0 ;	//设置时钟分频系数：不分频
//   TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //向上计数模式
// 	/*初始化TIM2定时器 */
//   TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
// 	/* 使能TIM2中断 */
// 	TIM_ITConfig(TIM2,TIM_IT_Update, ENABLE);
// 	/* 使能TIM2定时器 */
// 	TIM_Cmd(TIM2, ENABLE);
// }

void TIM3_Mode_Config(void)
{
	//u16 CCR1_Val = 2500;
	//u16 CCR2_Val = 1000;
	GPIO_InitTypeDef GPIO_InitStructure;
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_ICInitTypeDef TIM_ICInitStructure;
	//TIM_OCInitTypeDef  TIM_OCInitStructure;
	
/*----------------------------------------------------------------*/
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
  
	
  GPIO_StructInit(&GPIO_InitStructure);
  /* Configure PA.06,07 as encoder input */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
	
/*----------------------------------------------------------------*/	

	
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); //使能ＴＩＭ３
	TIM_DeInit(TIM3);
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
	
  TIM_TimeBaseStructure.TIM_Period =0xffff;       //
  TIM_TimeBaseStructure.TIM_Prescaler =0;	    //设置预分频：
  TIM_TimeBaseStructure.TIM_ClockDivision =TIM_CKD_DIV1 ;	//设置时钟分频系数：不分频
  //TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //向上计数模式
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_CenterAligned1; 
	/*初始化TIM2定时器 */
  TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
	
	/*-----------------------------------------------------------------*/
	//编码配置                        编码模式
	TIM_EncoderInterfaceConfig(TIM3, TIM_EncoderMode_TI12, 
                             TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);  //TIM_ICPolarity_Rising上升沿捕获
  TIM_ICStructInit(&TIM_ICInitStructure);
  TIM_ICInitStructure.TIM_ICFilter = 6;         //比较滤波器
  TIM_ICInit(TIM3, &TIM_ICInitStructure);
  
	//TIM_ARRPreloadConfig(TIM3, ENABLE);
 // Clear all pending interrupts
  TIM_ClearFlag(TIM3, TIM_FLAG_Update);
  TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);   //使能中断
  //Reset counter
  TIM3->CNT =0;
	
	
	TIM_Cmd(TIM3, ENABLE);   //使能定时器3
}
void TIM_Init(void)
{
  TIM3_Mode_Config();
}


void TIM4_Mode_Config(void)
{

	GPIO_InitTypeDef GPIO_InitStructure;
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_ICInitTypeDef TIM_ICInitStructure;
	//TIM_OCInitTypeDef  TIM_OCInitStructure;
	
/*----------------------------------------------------------------*/
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
  
	
  GPIO_StructInit(&GPIO_InitStructure);
  /* Configure PA.06,07 as encoder input */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
	
/*----------------------------------------------------------------*/	

	
  RCC_APB1PeriphClockCmd( RCC_APB1Periph_TIM4, ENABLE); //使能ＴＩＭ4
	TIM_DeInit(TIM4);
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
	
  TIM_TimeBaseStructure.TIM_Period =0xffff;       //
  TIM_TimeBaseStructure.TIM_Prescaler =0;	    //设置预分频：
  TIM_TimeBaseStructure.TIM_ClockDivision =TIM_CKD_DIV1 ;	//设置时钟分频系数：不分频
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //向上计数模式
  //TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_CenterAligned1; 
	/*初始化TIM2定时器 */
  TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
	
	/*-----------------------------------------------------------------*/
	//编码配置                        编码模式
	TIM_EncoderInterfaceConfig(TIM4, TIM_EncoderMode_TI1, 
                             TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);  //TIM_ICPolarity_Rising上升沿捕获
  TIM_ICStructInit(&TIM_ICInitStructure);
  TIM_ICInitStructure.TIM_ICFilter = 6;         //比较滤波器
  TIM_ICInit(TIM4, &TIM_ICInitStructure);
 
 // Clear all pending interrupts
  TIM_ClearFlag(TIM4, TIM_FLAG_Update);
  TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);   //使能中断
  //Reset counter
  TIM4->CNT =0;
	
	
	TIM_Cmd(TIM4, ENABLE);   //使能定时器4
}
void TIM4_Init(void)
{
  TIM4_Mode_Config();
}

