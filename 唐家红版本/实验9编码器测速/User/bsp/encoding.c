#include"includes.h"	
/*用于记录脉冲个数*/
s16 encoder_num;
/*
************************************************************
*函数名称：void Encorder_GPIO_Config(void)
*函数功能：编码器接口初始化
*输入形参：无
*返回值：	 无
************************************************************
*/
void Encorder_GPIO_Config(void)
{
	/*第一步 声明GPIO结构体*/
	GPIO_InitTypeDef GPIO_InitStructure; 
	/*第二时钟步 使能外设*/	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);  
  	/*第三步 配置结构体参数 */
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	/*第四步 调用外设初始化函数*/
  	GPIO_Init(GPIOB, &GPIO_InitStructure);
}

/*
************************************************************
*函数名称：void Encoder_Init(void)
*函数功能：编码器初始化函数供外部调用
*输入形参：无
*返回值：无
************************************************************
*/
void Encoder_Init(void)
{
	TIM4_Mode_Config();
	Encorder_GPIO_Config();
}
