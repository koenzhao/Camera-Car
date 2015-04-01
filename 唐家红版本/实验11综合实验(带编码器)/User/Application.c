#include"includes.h"
/*
---------------------------------------------------------------------------
*  函数名称：void Application(void)
*  函数功能：读取图像数据，进行图像处理根据处理结果控制舵机方向与车速
*  输入形参：无	
*  返回值：无	
---------------------------------------------------------------------------
*/
void Application(void)
{  
	Change_Speed(540);
	while(1)
	{ 	
		/*如果图像数据可读*/	
		if(OV_State==Read)
		{	
			/*屏蔽中断*/
			EXTI_Config(DIS); 
			/*读取图像*/	 		
			Read_Pic();	
			/*图像处理*/		
			Image_Process();
			/*舵机、电调控制*/
			Steer_control();
			SpeedContiol(2500);
			/*图像处理完毕状态转换*/	 
			OV_State=Wait_Vsync1;
			/*打开中断*/
			EXTI_Config(EN);
		}	
	}	
}

/*
-------------------------------------------------------------------------
*  函数名称：void Board_Init(void)
*  函数功能：调用底层硬件初始化函数，供main()函数调用
*  输入形参：无  	
*  返回值：无		 	
---------------------------------------------------------------------------
*/
void Board_Init(void)
{	
	u8 i;										   
	SystemInit();		//系统时钟配置    	
	delay_init(72);		//延时函数初始化 
	TIM1_config();
	TIM4_Mode_Config();
	Motor_Init(); 		//舵机初始化
	Servo_Init(); 
	USART_Config();	   	//串口配置
	LED_Init();			//按键初始化	
	KEY_Init();	 	
	for(i=0;i<3;i++)	//等待电调中间值确定
	{
		delay_ms(1000);
	}   	
	OV7670_Init();		//最后进行摄像头初始化
}
