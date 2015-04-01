#include"includes.h"
//外部中断配置
void EXTI_Config(void)
{
	
	NVIC_InitTypeDef NVIC_InitStructure;/*声明嵌套中断结构体*/ 	
  	EXTI_InitTypeDef EXTI_InitStructure;/*声明中断配置结构体*/		
	GPIO_InitTypeDef GPIO_InitStructure;/*声明通用IO口配置结构体*/ 	
	 	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC|RCC_APB2Periph_AFIO,ENABLE);
	/*开启GPIO与AFIO时钟*/


    /*第一次中断配置*/ 

	/*中断分组*/
  	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	   /*设置优先级分组（先占优先级和从优先级）；送入优先级分组长度 */	
	/*以上设置的结果是：先占优先级2位，从优先级2位*/
 
 	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;/*外部中断10 */					
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;           	/*抢占优先级 1*/    
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;	/*子优先级0*/ 		  
 	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;	/*使能*/				 
  	NVIC_Init(&NVIC_InitStructure);
	/*外部中断源配置*/
   	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource10);/*外部中断配置AFIO--ETXI10；选择GPIO_C端口的10管脚*/
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource11);/*外部中断配置AFIO--ETXI11；选择GPIO_C端口的11管脚*/
	
	/*中断方式配置*/

	/*中断模式*/
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
	/*下降沿触发*/
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;	 
	/*使能中断*/
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE; 
	/*选择中断线路*/
	
	EXTI_InitStructure.EXTI_Line = EXTI_Line10; //PC10
	EXTI_Init(&EXTI_InitStructure);	/*根据传入参数初始化EXIT寄存器*/
	EXTI_InitStructure.EXTI_Line = EXTI_Line11;	//PC11 			 
  	EXTI_Init(&EXTI_InitStructure);	

	
	/*
	//优先级配置
 	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;//外部中断10					
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;	//抢占优先级 1    
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;	//子优先级0	  
 	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;	//使能				 
  	NVIC_Init(&NVIC_InitStructure);	
	//外部中断源配置
	//GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource11);//外部中断配置AFIO--ETXI11
	//中断方式配置
	*/	    
	  			
	
	/*IO口配置 */
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10|GPIO_Pin_11;	         	 	
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;   	 		//内部上拉输入
  	GPIO_Init(GPIOC, &GPIO_InitStructure);
}
