#ifndef __TIMER3_H__
#define __TIMER3_H__
void TIM2_Configuration(void);	 
void TIM2_NVIC_Configuration(void);	
extern uint32_t time;
#define START_TIME  time=0;RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2 , ENABLE);TIM_Cmd(TIM2, ENABLE)
#define STOP_TIME  time=0;TIM_Cmd(TIM2, DISABLE);RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2 , DISABLE)
#endif
