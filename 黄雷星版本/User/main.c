
#include <stm32f10x.h>
#include <stdio.h>
#include <usart.h>
#include <Nvic_Exit.h>
#include <delay.h>
#include <tft.h>
#include <ov7670.h>
#include<I2C.h>
#include "stm32f10x_tim.h"
#include "include.h"
#include "Image.h"

#define YUANBAN

void RCC_Configuration(void);
void GPIO_Configuration(void);
void USART_Configuration(void);
void NVIC_Configuration(void);
void EXIT_configuration();
void IO_Init(void);	
void Timer3_configuration();
void Timer1_configuration();

//void delay_ms(u16 nms);	
extern u8 KEY;


u16 PixelCounter;   //用于像素计数
u8 datareadyflag;

u8 data[R][C];
u8 * Data;
u8 deadline=0;

//#define   White   244
//#define   Black   0

u8 InterruptLine=0;
u8 TrueLine;
u8 DataReadyFlag=0;


u8 BlackLineData[R];
u8 Left[R]={1};
u8 Right[R]={C-1};
//uchar Mid[R]={R/2};

u8 LastFieldMid1=80;
u8 LastFieldMid2=80;

u8 ThresholdValue=130;
s16 Err = 0;
s16 Errlast   = 0;
s16 Errwhy = 0;
s16 Errd  = 0;
s16 Errdlast  = 0;
s16 Erri  = 0;
s16 Roadtype  = 0;
s16 Errhistory[8]={0};
u16  Steerangle  = 0;

const u16 SlampeLine[R]=     //采样行，校准纵向畸变
  {
     57,//107.5
     59,//104
     60,//100.5
     62,//97
     64,//93.5
     66,//90
     68,//86.5
     70,//83
     72,//79.5
     74,//76
     75,//72.5
     76, //69
     78,//65.5
     83,//62
     88,//58.5
     91,//55
     95,//51.5
     99,//48
     103,//44.5
     108,//41
     113,//37.5
    
	
     118,//34
     123,//30.5
     129,//27
     135,//23.5cm
     141,//20cm
     148,//16.5cm
	 155,
     163,//13cm
	 171
     
  };






int main()
{ 
	RCC_Configuration();;//系统时钟设置
	delay_init(72);		//延时初始化

	IO_Init(); 
 	GPIO_Configuration();
	NVIC_Configuration();
	USART_Configuration();

	Timer3_configuration();
  	//Timer1_configuration();	
	EXIT_configuration();

   
	CMOS1_PWDN=0;
	CMOS1_RST=0;
	delay_ms(20);
	CMOS1_RST=1;
	InitI2C0();	 
	while(1!=Cmos7670_init());   //CMOS初始化	
	Exit_Init(GPIOA, GPIO_Pin_0, GPIO_Mode_IPU, EXTI_Trigger_Falling, 2, 5);	//VSYNC

   delay_ms(1000);
   TIM3->CCR1 = 530;
   GPIO_WriteBit( GPIOB,GPIO_Pin_0, 1);
   GPIO_WriteBit( GPIOB,GPIO_Pin_1, 1);
   delay_ms(1000);
   delay_ms(1000);
   delay_ms(1000);
   delay_ms(1000);
      
   	
   SpeedContiol(560);
  
  	while(1) 
	{
	
		    static int w=0; 
			static int z=0;
		//static int =0;
		
		if (datareadyflag==1)//10行相当于20行
		{
		/*	q++;
			if(q==1)
			{   GPIO_WriteBit( GPIOB,GPIO_Pin_1, 1);
			}
			if(q==2)
				{   GPIO_WriteBit( GPIOB,GPIO_Pin_1, 0);q=0;
			}*/
				
			 EXTI->IMR &=~(1<<0);  //屏蔽中断           
			 EXTI->PR |=(1<<0);  //清楚悬挂标记位；
			 datareadyflag=0;
			//-----------------------------------------------------------------------
			DataAnalyse(1);
			mygetLmr();
			SmoothMid() ;
			Steer_control();
			
			 if(Err<15&&Err>-15)					//弯道
			 {
				 w=0;
				 z++;
				 if(z<=4)
				 SpeedContiol(541);    // 范围 400~600之间，越大越快
				 if(z>4)
				SpeedContiol(546);
			 }
			  if(Err>15||Err<-15)				//S弯
			  {
				  w++;
				  z=0;
				  if(w<=3)
				  SpeedContiol(537); 
				  if(w>3)
				  SpeedContiol(547);	
			  }
			  

			//-----------------------------------------------------------------------
			 EXTI->IMR|=(1<<0);	  //允许外部中断，以便接收下帧图像数据
			   
		}			
	}
}


 
void RCC_Configuration(void)
{
   SystemInit();
   // Enable GPIO clock 
   RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA
                          |RCC_APB2Periph_GPIOB
                          |RCC_APB2Periph_GPIOC
                          |RCC_APB2Periph_AFIO
                          |RCC_APB2Periph_TIM1                            
                          |RCC_APB2Periph_USART1,ENABLE);
  
   // Enable USART2 Clock 
   RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2
                         
                          |RCC_APB1Periph_TIM3,ENABLE);
 
}
void IO_Init(void)
{

  	RCC->APB2ENR|=1<<0;//开启辅助时钟
	RCC->APB2ENR|=1<<2;//先使能外设PORTA时钟
	RCC->APB2ENR|=1<<3;//先使能外设PORTB时钟
 	RCC->APB2ENR|=1<<4;//先使能外设PORTC时钟


	GPIOC->CRL=0X88888888; //PORTC 输入	   //摄像头 八位输入
	GPIOC->CRH=0X33333333; 
	GPIOC->ODR=0XFFFF;	


	GPIOA->CRH=0X33333333; //PORTA上拉输出	   //摄像头输出
	GPIOA->CRL=0X33333333;
	GPIOA->ODR=0XFFFF;	 

	GPIOB->CRL=0X33333333; //PB0-7   上拉输出
	GPIOB->CRH=0X33333333; //PB8-15  上拉输出
	GPIOA->ODR=0XFFFF;



		    
   	JTAG_Set(JTAG_SWD_DISABLE);	 //JTAG功能禁止，复用JTAG端口
}


//保持原有配置
void GPIO_Configuration(void)
{

GPIO_InitTypeDef GPIO_InitStructure;

 //****** TIM3 CH1  ch2 (PA6   pa7) ******************************
  GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_6 | GPIO_Pin_7;	
  GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;       //复用推完输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  
  //******** 外部中断 GPIO 初始化 ***************
  GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_0|GPIO_Pin_4;	
  GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN_FLOATING;       //浮空输入
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

 

    /* 设置USART1的Tx脚（PA.9）为第二功能推挽输出模式 */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA , &GPIO_InitStructure);
    
    /* 设置USART1的Rx脚（PA.10）为浮空输入脚 */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA , &GPIO_InitStructure);


}



/*******************************************************************************
* 函数名  		: USART_Configuration	     保持原有配置
* 函数描述    	: 设置USART1
* 输入参数      : None
* 输出结果      : None
* 返回值        : None
*******************************************************************************/
void USART_Configuration(void)
{
    /* 定义USART初始化结构体 USART_InitStructure */
    USART_InitTypeDef USART_InitStructure;
    
    /*	
    *	波特率为9600bps
    *	8位数据长度
    *	1个停止位，无校验
    *	禁用硬件流控制
    *	禁止USART时钟
    *	时钟极性低
    *	在第2个边沿捕获数据
    *	最后一位数据的时钟脉冲不从 SCLK 输出
    */ 
    USART_InitStructure.USART_BaudRate = 115200;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No ;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_Init(USART1 , &USART_InitStructure);
    
    /* 使能USART1 */
    USART_Cmd(USART1 , ENABLE);
}

void NVIC_Configuration(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;//中断默认参数

  // Configure the NVIC Preemption Priority Bits
                                         

  //********** 外部中断 (PA0 PA4)****************************************
  NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;             //更新事件
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;   //抢占优先级0
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;          //响应优先级1
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;             //允许中断
  NVIC_Init(&NVIC_InitStructure);
  
 
}
void EXIT_configuration()
{

  EXTI_InitTypeDef EXTI_InitStructure;
  EXTI_ClearITPendingBit(EXTI_Line0);
  GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource0); 
  EXTI_InitStructure.EXTI_Line = EXTI_Line0; 
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);
  EXTI_GenerateSWInterrupt(EXTI_Line0);
 

}

//timer1 的通道1  输出电机控制pwm pa8

void Timer1_configuration()
{
  //TIM_DeInit(TIM1);
  TIM_TimeBaseInitTypeDef TIM1_TimeBaseStructure;
    TIM_OCInitTypeDef TIM_OCInitStructure;

  TIM1_TimeBaseStructure.TIM_Period = 7200-1;                              // 0xFFFF; 计数初值         !@#$%^&*()~
  TIM1_TimeBaseStructure.TIM_Prescaler = 200;                          //0xF;   分频
  TIM1_TimeBaseStructure.TIM_ClockDivision = 0x0;
  TIM1_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  //TIM1_TimeBaseStructure.TIM1_RepetitionCounter= 1000-1;        //设置了周期计数器值;RCR向下计数器每次计数至0，会产生 !@#$%^&*()~
                                                            //一个更新事件且计数器重新由RCR值（N）开始计数。周期???
  TIM_TimeBaseInit(TIM1, &TIM1_TimeBaseStructure);             // 高速总线时钟频率72MHz,周期=72M/(36000-1+1)/1000

  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;
  TIM_OCInitStructure.TIM_Pulse = 540;
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
  TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_Low;
  TIM_OC1Init(TIM1,&TIM_OCInitStructure);
  TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);                           //!@#$%^&*()~
  TIM_ARRPreloadConfig(TIM1, ENABLE);                                         //!@#$%^&*()~
  TIM_Cmd(TIM1,ENABLE);
  TIM_CtrlPWMOutputs(TIM1,ENABLE);
}

//********************* 舵机 PWM ******************
void Timer3_configuration()
{
  //TIM_DeInit(TIM1);
  TIM_TimeBaseInitTypeDef TIM1_TimeBaseStructure;
  TIM_OCInitTypeDef TIM_OCInitStructure;

  TIM1_TimeBaseStructure.TIM_Period = 7200-1;                              // 0xFFFF; 计数初值         !@#$%^&*()~
  TIM1_TimeBaseStructure.TIM_Prescaler = 200;                          //0xF;   分频
  TIM1_TimeBaseStructure.TIM_ClockDivision = 0x0;
  TIM1_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;                                                              //一个更新事件且计数器重新由RCR值（N）开始计数。周期???
  TIM_TimeBaseInit(TIM3, &TIM1_TimeBaseStructure);                      // 高速总线时钟频率36MHz,周期=36M/(36000-1+1)/1000
  
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = 504;                                    //这里设置504   504/7119=7%,是舵机中间位置
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
  TIM_OC1Init(TIM3,&TIM_OCInitStructure);                     
  TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);
  TIM_OC2Init(TIM3,&TIM_OCInitStructure);                     
  TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);
  TIM_ARRPreloadConfig(TIM3, ENABLE);                                         //!@#$%^&*()~
  TIM_Cmd(TIM3,ENABLE);
  
  TIM_ARRPreloadConfig(TIM3, ENABLE);                                         //!@#$%^&*()~
  TIM_Cmd(TIM3,ENABLE);

}



