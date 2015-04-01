#include"includes.h"
/*
-----------------------------------------------------------
   函数名称：TIM1_config()
   函数功能：配置TIM1,用于控制舵机
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
	/*
	   第二步：根据分频系数、重装载值确定		周期
		预分频 3600，那么 定时器计数一次 所用时间为
		3600*10^6/(72*10^6)=50us
		所以记到Cycle_Val次共需要 50*Cycle_Val us 
	*/
	/*确定周期1-100ms*/
	/*从0开始计数到799一共计数800次,所以计数周期为20ms*/
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
	
	/*为什么要配置TIM1_CH4!!!!!!?*/
	TIM_OC4Init(TIM1, &TIM_OCInitStructure); 
  	TIM_OC4PreloadConfig(TIM1, TIM_OCPreload_Enable);
  	
	/* 使能重载	*/
  	TIM_ARRPreloadConfig(TIM1, ENABLE);	
  	/* TIM1 enable counter */
  	TIM_Cmd(TIM1, ENABLE); 
  	/* 下面这句话对于TIM1和TIM8是必须的，对于TIM2-TIM6则不必要 */
  	TIM_CtrlPWMOutputs(TIM1, ENABLE);

}
																		
 /* -----------------------------------------------------------------------   
	定时器3的时钟源并不是直接来自RCC_APB1，在这个过程中经理了一个倍频器	

	函数名称：void TIM3_config(uint8_t Channel,uint8_t Cycle,uint16_t Duty)
	函数功能：初始化定时器、使之产生需要的PWM波形												
	输入形参：Channel:定时器通道、 Cycle周期(1-100ms) duty：占空比
	返回值：无													   
  ----------------------------------------------------------------------- */

void TIM3_config(uint8_t Channel)	
{

	TIM_TimeBaseInitTypeDef TIM1_TimeBaseStructure;
  	TIM_OCInitTypeDef TIM_OCInitStructure;
	/*第一步 开启 定时器时钟*/
  	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); 
	/*计数值*/		 	
  	TIM1_TimeBaseStructure.TIM_Period = 400-1;    
	/*分频系数7200，定时器 时钟源速度将变为72MHz*/                                 
  	TIM1_TimeBaseStructure.TIM_Prescaler = 3600-1;                          
  	TIM1_TimeBaseStructure.TIM_ClockDivision = 0x0;
	/*向上计数*/
  	TIM1_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;                                                              
  	TIM_TimeBaseInit(TIM3, &TIM1_TimeBaseStructure);                      
  
  	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
  	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	/*--------------------------------------------------------------------------
	 TIM_Pulse计算公式:根据占空比 ，计算这个数值
	 Duty/100 = Pulse/Count_Val推出 Pulse=Count_Val*Duty/100
	---------------------------------------------------------------------------*/
	
  	TIM_OCInitStructure.TIM_Pulse =28;                                   
  	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	switch(Channel)
	{
		case 1:	
		/*定时器通道1初始化*/ 
		TIM_OC1Init(TIM3,&TIM_OCInitStructure);                     
  		TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);
		break;
		case 2:
		/*定时器通道2初始化*/ 
		TIM_OC2Init(TIM3,&TIM_OCInitStructure);                     
  		TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);
		case 3:	
		/*定时器通道1初始化*/ 
		TIM_OC3Init(TIM3,&TIM_OCInitStructure);                     
  		TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);
		break;
		case 4:
		/*定时器通道2初始化*/ 
		TIM_OC4Init(TIM3,&TIM_OCInitStructure);                     
  		TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Enable);
		default:break;
	}

	TIM_ARRPreloadConfig(TIM3, ENABLE);                                         //!@#$%^&*()~
  	TIM_Cmd(TIM3,ENABLE);
}
//用于编码器
void TIM4_Mode_Config(void)
{

	GPIO_InitTypeDef GPIO_InitStructure;
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_ICInitTypeDef TIM_ICInitStructure;
	/*----------------------------------------------------------------*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
  	/* Configure PB.06,07 as encoder input */
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	/*----------------------------------------------------------------*/	
 
   	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE); //使能ＴＩＭ4
   	TIM_DeInit(TIM4);
   	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
	
   	TIM_TimeBaseStructure.TIM_Period =0xffff;       //
   	TIM_TimeBaseStructure.TIM_Prescaler =0;	    //设置预分频：
   	TIM_TimeBaseStructure.TIM_ClockDivision =TIM_CKD_DIV1 ;	//设置时钟分频系数：不分频
   	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //向上计数模式
 	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
	
	/*-----------------------------------------------------------------*/
	//编码配置                        编码模式
	TIM_EncoderInterfaceConfig(TIM4, TIM_EncoderMode_TI12, 
                             TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);  //TIM_ICPolarity_Rising上升沿捕获
    TIM_ICStructInit(&TIM_ICInitStructure);
    TIM_ICInitStructure.TIM_ICFilter = 6;         //比较滤波器
    TIM_ICInit(TIM4, &TIM_ICInitStructure);
  	TIM_ClearFlag(TIM4, TIM_FLAG_Update);
	//Reset counter
    TIM4->CNT =0;
	TIM_Cmd(TIM4, ENABLE);   //使能定时器3
}
