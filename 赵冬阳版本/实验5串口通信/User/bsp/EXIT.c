#include"includes.h"
//外部中断配置
void EXTI_Config(void)
{
	
	NVIC_InitTypeDef NVIC_InitStructure;/*声明嵌套中断结构体*/ 	
  	EXTI_InitTypeDef EXTI_InitStructure;/*声明中断配置结构体*/		
	GPIO_InitTypeDef GPIO_InitStructure;/*声明通用IO口配置结构体*/ 	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC|RCC_APB2Periph_AFIO,ENABLE);/*开启GPIO与AFIO时钟*/
	/*选择中断优先级第2组*/
  	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	    	
	/*外部中断10 */
 	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;
	/*抢占优先级 1*/					
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;    
	/*子优先级0*/ 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;			  
 	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;	/*使能*/				 
  	NVIC_Init(&NVIC_InitStructure);	
	 //PC10
   	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource10);/*外部中断配置AFIO--ETXI10*/		    
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	/*中断模式*/
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;/*下降沿触发*/	 
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE; 
	EXTI_InitStructure.EXTI_Line = EXTI_Line10;//PC10 				  
  	EXTI_Init(&EXTI_InitStructure);

	 //PC11
	 	/*外部中断10 */
 	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;
	/*抢占优先级 2*/					
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;    
	/*子优先级0*/ 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;			  
 	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;	/*使能*/				 
  	NVIC_Init(&NVIC_InitStructure);	

	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource11);/*外部中断配置AFIO--ETXI11*/
	EXTI_InitStructure.EXTI_Line = EXTI_Line11;	//PC11 			 
  	EXTI_Init(&EXTI_InitStructure);	  
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10|GPIO_Pin_11;	         	 	
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;   	 		//内部上拉输入
  	GPIO_Init(GPIOC, &GPIO_InitStructure);
}
