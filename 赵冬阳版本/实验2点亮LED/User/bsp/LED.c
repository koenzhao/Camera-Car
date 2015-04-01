#include"includes.h"
/*
-----------------------------------------------------------------------
  函数名称：void LED_Init(void)
  函数功能：初始化LED控制端口
  输入形参：无  	
  返回值：无	
-----------------------------------------------------------------------
*/
void LED_Init(void)
{
	/*通用GPIO结构体声明*/
	GPIO_InitTypeDef GPIO_InitStructure;
	/*第一步 开启GPIO时钟*/
	RCC_APB2PeriphClockCmd(LED_1_Clock,ENABLE);
	RCC_APB2PeriphClockCmd(LED_2_Clock,ENABLE);
	/*第二步 配置GPIO结构体参数*/	
	
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;/*推挽输出*/ 	
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;/*配置速度*/ 	
	//GPIO_InitStructure.GPIO_Pin=LED_1_Pin;/*LED_1控制管脚号设置*/  
	GPIO_InitStructure.GPIO_Pin=LED_1_Pin | LED_2_Pin; //替换上句
	
	//GPIO_Init(LED_1_Port,&GPIO_InitStructure);	/*根据设置初始化管脚分组*/		
	//GPIO_InitStructure.GPIO_Pin=LED_2_Pin;/*LED_2控制管脚号设置*/  	
	//GPIO_Init(LED_2_Port,&GPIO_InitStructure);/*根据设置初始化管脚分组*/
	GPIO_Init(GPIOB,&GPIO_InitStructure);	//替换
	LED_1(OFF);
	LED_2(OFF);		
}
