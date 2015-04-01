/******************** (C) COPYRIGHT 2010 STMicroelectronics ********************
* File Name          : stm32f10x_it.c
* Author             : MCD Application Team
* Version            : V3.2.1
* Date               : 07/05/2010
* Description        : Main Interrupt Service Routines.
*                      This file provides template for all exceptions handler
*                      and peripherals interrupt service routine.
********************************************************************************
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include <stm32f10x_it.h>
#include <usart.h>
#include <tft.h>
#include <ov7670.h>
#include "include.h"

//#include <stdio.h>


#define RGB565_MASK_RED    0xF800
#define RGB565_MASK_GREEN  0x07E0
#define RGB565_MASK_BLUE   0x001F


u8 Vsync_Flag=0;
u16 i,j,t1,t2;

u16 Y;


/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
u8 KEY  = 0;
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

/*******************************************************************************
* Function Name  : NMI_Handler
* Description    : This function handles NMI exception.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void NMI_Handler(void)
{
}

/*******************************************************************************
* Function Name  : HardFault_Handler
* Description    : This function handles Hard Fault exception.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/*******************************************************************************
* Function Name  : MemManage_Handler
* Description    : This function handles Memory Manage exception.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/*******************************************************************************
* Function Name  : BusFault_Handler
* Description    : This function handles Bus Fault exception.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/*******************************************************************************
* Function Name  : UsageFault_Handler
* Description    : This function handles Usage Fault exception.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/*******************************************************************************
* Function Name  : SVC_Handler
* Description    : This function handles SVCall exception.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void SVC_Handler(void)
{
}

/*******************************************************************************
* Function Name  : DebugMon_Handler
* Description    : This function handles Debug Monitor exception.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void DebugMon_Handler(void)
{
}

/*******************************************************************************
* Function Name  : PendSV_Handler
* Description    : This function handles PendSVC exception.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void PendSV_Handler(void)
{
}

/*******************************************************************************
* Function Name  : SysTick_Handler
* Description    : This function handles SysTick Handler.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void SysTick_Handler(void)
{
}

/******************************************************************************/
/*            STM32F10x Peripherals Interrupt Handlers                        */
/******************************************************************************/

#ifndef STM32F10X_CL
/*******************************************************************************
* Function Name  : USB_HP_CAN1_TX_IRQHandler
* Description    : This function handles USB High Priority or CAN TX interrupts requests
*                  requests.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void USB_HP_CAN1_TX_IRQHandler(void)
{
  //CTR_HP();
}

/*******************************************************************************
* Function Name  : USB_LP_CAN1_RX0_IRQHandler
* Description    : This function handles USB Low Priority or CAN RX0 interrupts
*                  requests.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void USB_LP_CAN1_RX0_IRQHandler(void)
{
  //USB_Istr();
}
#endif /* STM32F10X_CL */

#if defined(STM32F10X_HD) || defined(STM32F10X_XL) 
/*******************************************************************************
* Function Name  : SDIO_IRQHandler
* Description    : This function handles SDIO global interrupt request.
*                  requests.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void SDIO_IRQHandler(void)
{ 
  /* Process All SDIO Interrupt Sources */
  //SD_ProcessIRQSrc();
  
}
#endif /* STM32F10X_HD | STM32F10X_XL*/

#ifdef STM32F10X_CL
/*******************************************************************************
* Function Name  : OTG_FS_IRQHandler
* Description    : This function handles USB-On-The-Go FS global interrupt request.
*                  requests.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void OTG_FS_IRQHandler(void)
{
  STM32_PCD_OTG_ISR_Handler(); 
}
#endif /* STM32F10X_CL */

/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/

void USART_COM1_IRQHandler(void)
{
	USART1_RxIntHandler();
}

void USART_COM2_IRQHandler(void)
{
  	USART2_RxIntHandler();
}


void EXTI0_IRQHandler(void)
{
  	 /*
	 if(EXTI_GetITStatus(EXTI_Line0) != RESET)
   {
    
    EXTI->PR |=(1<<0);  //清楚悬挂标记位；
    EXTI->IMR &=~(1<<0);  //屏蔽中断
    EXTI->IMR &=~(1<<4);  //屏蔽中断
 
   GPIO_WriteBit( GPIOB,GPIO_Pin_0, 1);
   delay_ms(10);
    GPIO_WriteBit( GPIOB,GPIO_Pin_0, 0);
  // delay_ms(1000);
  	USART_SendData(USART1,22);
           while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
		   	delay_ms(100);
 
    EXTI->IMR |=(1<<0);  //开中断
    EXTI->IMR |=(1<<4);  //开中断
    }
	*/	

	
  // delay_ms(1000);
	
	EXTI_ClearITPendingBit(EXTI_Line0);  		//清除EXTI4线路挂起位     //清楚中断标志位
	Vsync_Flag++;
	if(Vsync_Flag==1)    //FIFO写指针复位
	{
		FIFO_WRST=1;
		FIFO_WRST=0;
 		for(i=0;i<40;i++);
		FIFO_WRST=1;      
		FIFO_WR=1;	   //允许CMOS数据写入FIF
		
	}
	if(Vsync_Flag==2)
	{
	  	 u16 t3;
		u8 heibai;

		TrueLine=0;
		PixelCounter=0; 

	 	FIFO_WR=0; 
		EXTI->IMR&=~(1<<0);	 //禁止外部中断，准备从FIFO中取数据

		FIFO_RRST=0;  //FIFO读指针复位 
		FIFO_RCK=0;                
		FIFO_RCK=1;	
		FIFO_RCK=0;
		FIFO_RCK=1;
	  	FIFO_RRST=1;

			delay_us(50);


		FIFO_OE=0;			  //允许FIFO输出
//以下代码完成，图像的采集，并显示在tft上
				 							
		for(i = 0; i < 240; i ++)	 
		 {	
		   	 // if(i%6==1)
		  if(i==SlampeLine[TrueLine]) //该行是否为采样行)
			{
			 	for(j = 0; j < 320; j ++)
				{
				
	
				  if (j<160)
				  {
				    //获得一个Y分量的过程										
					FIFO_RCK=0;					
					FIFO_RCK=1;		 				
					data[TrueLine][j]=(0x00ff&GPIOC->IDR);	 				
					FIFO_RCK=0;						
					FIFO_RCK=1;						

	
					//跳过一个点，隔开取点
				    FIFO_RCK=0;					
					FIFO_RCK=1;		 				
						
					FIFO_RCK=0;						
					FIFO_RCK=1;						
							//0x0000->黑色  0xffff->白色


					}
	    	}
		  TrueLine++;
		}else {	  //否则跳过这些像素点
	      	for(j = 0; j < 320; j ++)
				{

					FIFO_RCK=0;					
					FIFO_RCK=1;		 				
					//t2=(0x00ff&GPIOC->IDR);	 				
					FIFO_RCK=0;						
					FIFO_RCK=1;						
					//t2=(0x00ff&GPIOC->IDR);
				}
		}
	}



		  FIFO_OE=1;		 	  //禁止FIFO输出
		 Vsync_Flag=0;
		 	datareadyflag=1;   //标记图像采集完成，可以处理
	} 		
					
		
}
