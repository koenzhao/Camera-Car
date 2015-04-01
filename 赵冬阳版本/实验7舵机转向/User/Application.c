#include"includes.h"

void Application(void)
{  
	while(1)
	{ 	
		Change_Direction(700);
		delay_ms(1000);
		Change_Direction(300);
		delay_ms(1000);
	}	
}

/*
-------------------------------------------------------------------------
*  函数名称：
*  函数功能：
*  输入形参：  	
*  返回值：		 	
---------------------------------------------------------------------------
*/
void Board_Init(void)
{	
	//系统时钟配置
	SystemInit();
	//延时函数初始化		    	
	delay_init(72);
	//定时器1初始化		 
	TIM1_config();
	//舵机初始化
	Servo_Init(); 
	//串口配置
	USART_Config();
	//串口中断配置	   
	NVIC_Config();
	//LED初始化	
	LED_Init();
	//按键初始化				
	KEY_Init();	 	

}
