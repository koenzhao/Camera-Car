#include"includes.h"

uint8_t PIC[R][C];
//当前的状态
//下一步的状态
OV7670_State OV_State=Wait_Vsync1;
u16 TrueLine;
u8 datareadyflag=0;



/*
	摄像头模块初始化

*/
void Data_Bus_Config(void)
{					  
	
	/*通用GPIO结构体声明*/
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;	
	/*开启时钟*/	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);		
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);		
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);

	GPIO_InitStructure.GPIO_Pin=D0_Pin;		
	GPIO_Init(D0_Port,&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin=D1_Pin;		
	GPIO_Init(D1_Port,&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin=D2_Pin;		
	GPIO_Init(D2_Port,&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin=D3_Pin;		
	GPIO_Init(D3_Port,&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin=D4_Pin;		
	GPIO_Init(D4_Port,&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin=D5_Pin;		
	GPIO_Init(D5_Port,&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin=D6_Pin;		
	GPIO_Init(D6_Port,&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin=D7_Pin;		
	GPIO_Init(D7_Port,&GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	//PWDN
	GPIO_InitStructure.GPIO_Pin=PWDN_Pin;
	GPIO_Init(PWDN_Port,&GPIO_InitStructure);
	//RESET
	GPIO_InitStructure.GPIO_Pin=RESET_Pin;
	GPIO_Init(RESET_Port,&GPIO_InitStructure);
	//FIFO_RCK
	GPIO_InitStructure.GPIO_Pin=FIFO_RCK_Pin;
	GPIO_Init(FIFO_RCK_Port,&GPIO_InitStructure);
	//FIFO_EO
	GPIO_InitStructure.GPIO_Pin=FIFO_OE_Pin;
	GPIO_Init(FIFO_OE_Port,&GPIO_InitStructure);
	//FIFO_RRST
	GPIO_InitStructure.GPIO_Pin=FIFO_RRST_Pin;
	GPIO_Init(FIFO_RRST_Port,&GPIO_InitStructure);
	//FIFO_WR
	GPIO_InitStructure.GPIO_Pin=FIFO_WR_Pin;
	GPIO_Init(FIFO_WR_Port,&GPIO_InitStructure);
	//FIFO_WRST
	GPIO_InitStructure.GPIO_Pin=FIFO_WRST_Pin;
	GPIO_Init(FIFO_WRST_Port,&GPIO_InitStructure);
	//STORBE
	GPIO_InitStructure.GPIO_Pin=STORBE_Pin;
	GPIO_Init(STORBE_Port,&GPIO_InitStructure);
}
void OV7670_Init(void)
{
	/*I2C控制引脚初始化*/
	I2C_Configuration();
	/*数据总线与控制总线初始化*/
	Data_Bus_Config();
	OV7670_Register_Init();
	/*以上初始化结束之后才可以初始化下面的*/
	EXTI_ClearITPendingBit(EXTI_Line0);
	EXTI_Config(EN);

	
}
void OV7670_Register_Init(void)
{
	PWDN_L;/*电源工作方式*/
	RESET_L;//寄存器复位
	delay_ms(20);
	RESET_H;

	//YUV格式
	I2C_WriteByte(0x12, 0x80);
	I2C_WriteByte(0x3a, 0x04);
	I2C_WriteByte(0x40, 0xd0);
	I2C_WriteByte(0x12, 0x14);
	I2C_WriteByte(0x32, 0x80);
	I2C_WriteByte(0x17, 0x16);
	I2C_WriteByte(0x18, 0x04);
	I2C_WriteByte(0x19, 0x02);
	I2C_WriteByte(0x1a, 0x7b);
	I2C_WriteByte(0x03, 0x06);
	I2C_WriteByte(0x0c, 0x00);
	I2C_WriteByte(0x3e, 0x00);
	I2C_WriteByte(0x70, 0x3a);
	I2C_WriteByte(0x71, 0x35);
	I2C_WriteByte(0x72, 0x11);
	I2C_WriteByte(0x73, 0x00);
	I2C_WriteByte(0xa2, 0x02);
	I2C_WriteByte(0x11, 0x81); 	
	I2C_WriteByte(0x7a, 0x20);
	I2C_WriteByte(0x7b, 0x1c);
	I2C_WriteByte(0x7c, 0x28);
	I2C_WriteByte(0x7d, 0x3c);
	I2C_WriteByte(0x7e, 0x55);
	I2C_WriteByte(0x7f, 0x68);
	I2C_WriteByte(0x80, 0x76);
	I2C_WriteByte(0x81, 0x80);
	I2C_WriteByte(0x82, 0x88);
	I2C_WriteByte(0x83, 0x8f);
	I2C_WriteByte(0x84, 0x96);
	I2C_WriteByte(0x85, 0xa3);
	I2C_WriteByte(0x86, 0xaf);
	I2C_WriteByte(0x87, 0xc4);
	I2C_WriteByte(0x88, 0xd7);
	I2C_WriteByte(0x89, 0xe8);	
	I2C_WriteByte(0x13, 0xe0);
	I2C_WriteByte(0x00, 0x00); 	
	I2C_WriteByte(0x10, 0x00);
	I2C_WriteByte(0x0d, 0x00);
	I2C_WriteByte(0x14, 0x28);
	I2C_WriteByte(0xa5, 0x05);
	I2C_WriteByte(0xab, 0x07);
	I2C_WriteByte(0x24, 0x75);
	I2C_WriteByte(0x25, 0x63);
	I2C_WriteByte(0x26, 0xA5);
	I2C_WriteByte(0x9f, 0x78);
	I2C_WriteByte(0xa0, 0x68);
	I2C_WriteByte(0xa1, 0x03);
	I2C_WriteByte(0xa6, 0xdf);
	I2C_WriteByte(0xa7, 0xdf);
	I2C_WriteByte(0xa8, 0xf0);
	I2C_WriteByte(0xa9, 0x90);
	I2C_WriteByte(0xaa, 0x94);
	I2C_WriteByte(0x13, 0xe5);
	I2C_WriteByte(0x0e, 0x61);
	I2C_WriteByte(0x0f, 0x4b);
	I2C_WriteByte(0x16, 0x02);
	I2C_WriteByte(0x1e, 0x37);
	I2C_WriteByte(0x21, 0x02);
	I2C_WriteByte(0x22, 0x91);
	I2C_WriteByte(0x29, 0x07);
	I2C_WriteByte(0x33, 0x0b);
	I2C_WriteByte(0x35, 0x0b);
	I2C_WriteByte(0x37, 0x1d);
	I2C_WriteByte(0x38, 0x71);
	I2C_WriteByte(0x39, 0x2a);
	I2C_WriteByte(0x3c, 0x78);
	I2C_WriteByte(0x4d, 0x40);
	I2C_WriteByte(0x4e, 0x20);
	I2C_WriteByte(0x69, 0x00);
	I2C_WriteByte(0x6b, 0x60);
	I2C_WriteByte(0x74, 0x19);
	I2C_WriteByte(0x8d, 0x4f);
	I2C_WriteByte(0x8e, 0x00);
	I2C_WriteByte(0x8f, 0x00);
	I2C_WriteByte(0x90, 0x00);
	I2C_WriteByte(0x91, 0x00);
	I2C_WriteByte(0x92, 0x00);
	I2C_WriteByte(0x96, 0x00);
	I2C_WriteByte(0x9a, 0x80);
	I2C_WriteByte(0xb0, 0x84);
	I2C_WriteByte(0xb1, 0x0c);
	I2C_WriteByte(0xb2, 0x0e);
	I2C_WriteByte(0xb3, 0x82);
	I2C_WriteByte(0xb8, 0x0a); 
	I2C_WriteByte(0x43, 0x14);
	I2C_WriteByte(0x44, 0xf0);
	I2C_WriteByte(0x45, 0x34);
	I2C_WriteByte(0x46, 0x58);
	I2C_WriteByte(0x47, 0x28);
	I2C_WriteByte(0x48, 0x3a);
	I2C_WriteByte(0x59, 0x88);
	I2C_WriteByte(0x5a, 0x88);
	I2C_WriteByte(0x5b, 0x44);
	I2C_WriteByte(0x5c, 0x67);
	I2C_WriteByte(0x5d, 0x49);
	I2C_WriteByte(0x5e, 0x0e);
	I2C_WriteByte(0x64, 0x04);
	I2C_WriteByte(0x65, 0x20);
	I2C_WriteByte(0x66, 0x05);
	I2C_WriteByte(0x94, 0x04);
	I2C_WriteByte(0x95, 0x08);
	I2C_WriteByte(0x6c, 0x0a);
	I2C_WriteByte(0x6d, 0x55);
	I2C_WriteByte(0x6e, 0x11);
	I2C_WriteByte(0x6f, 0x9f);
	I2C_WriteByte(0x6a, 0x40);
	I2C_WriteByte(0x01, 0x40);
	I2C_WriteByte(0x02, 0x40);
	I2C_WriteByte(0x13, 0xe7);
	I2C_WriteByte(0x15, 0x00);  	
	I2C_WriteByte(0x4f, 0x80);
	I2C_WriteByte(0x50, 0x80);
	I2C_WriteByte(0x51, 0x00);
	I2C_WriteByte(0x52, 0x22);
	I2C_WriteByte(0x53, 0x5e);
	I2C_WriteByte(0x54, 0x80);
	I2C_WriteByte(0x58, 0x9e); 	
	I2C_WriteByte(0x41, 0x08);
	I2C_WriteByte(0x3f, 0x00);
	I2C_WriteByte(0x75, 0x05);
	I2C_WriteByte(0x76, 0xe1);
	I2C_WriteByte(0x4c, 0x00);
	I2C_WriteByte(0x77, 0x01);
	I2C_WriteByte(0x3d, 0xc2);	
	I2C_WriteByte(0x4b, 0x09);
	I2C_WriteByte(0xc9, 0x60);
	I2C_WriteByte(0x41, 0x38);
	I2C_WriteByte(0x56, 0x40);	
	I2C_WriteByte(0x34, 0x11);
	I2C_WriteByte(0x3b, 0x02); 								
	I2C_WriteByte(0xa4, 0x89);
	I2C_WriteByte(0x96, 0x00);
	I2C_WriteByte(0x97, 0x30);
	I2C_WriteByte(0x98, 0x20);
	I2C_WriteByte(0x99, 0x30);
	I2C_WriteByte(0x9a, 0x84);
	I2C_WriteByte(0x9b, 0x29);
	I2C_WriteByte(0x9c, 0x03);
	I2C_WriteByte(0x9d, 0x4c);
	I2C_WriteByte(0x9e, 0x3f);
	I2C_WriteByte(0x78, 0x04);	
	I2C_WriteByte(0x79, 0x01);
	I2C_WriteByte(0xc8, 0xf0);
	I2C_WriteByte(0x79, 0x0f);
	I2C_WriteByte(0xc8, 0x00);
	I2C_WriteByte(0x79, 0x10);
	I2C_WriteByte(0xc8, 0x7e);
	I2C_WriteByte(0x79, 0x0a);
	I2C_WriteByte(0xc8, 0x80);
	I2C_WriteByte(0x79, 0x0b);
	I2C_WriteByte(0xc8, 0x01);
	I2C_WriteByte(0x79, 0x0c);
	I2C_WriteByte(0xc8, 0x0f);
	I2C_WriteByte(0x79, 0x0d);
	I2C_WriteByte(0xc8, 0x20);
	I2C_WriteByte(0x79, 0x09);
	I2C_WriteByte(0xc8, 0x80);
	I2C_WriteByte(0x79, 0x02);
	I2C_WriteByte(0xc8, 0xc0);
	I2C_WriteByte(0x79, 0x03);
	I2C_WriteByte(0xc8, 0x40);
	I2C_WriteByte(0x79, 0x05);
	I2C_WriteByte(0xc8, 0x30);
	I2C_WriteByte(0x79, 0x26); 
	I2C_WriteByte(0x09, 0x00);	



/*
	

//      {0x3a, 0x04},//RGB
        {0x12, 0x10},//QVGA  YUV
        {0x3a, 0x14},//使用固定UV输出
        {0x3d, 0x80},//使用固定UV输出
                                                        //0         0       :      Y U Y V（3a:14 3d:80）
                                                        //0         1       :      Y V Y U (3a:14 3d:81)
                                                        //1         0       :      U Y V Y (3a:18 3d:80)
                                                        //1         1       :      V Y U Y (3a:18 3d:81)
        {0x67, 0x11},//固定U值，0x11，方便测试
        {0x68, 0xFF},//固定V值，0xFF，方便测试
//      {0x40, 0x10},//RGB565
        {0x40, 0xC0},//初始配置，YUV模式，这个寄存器必须设置，否则不好使
//      {0x12, 0x14},//QVGA  RGB，


	   I2C_WriteByte(0x12, 0x10);
	   I2C_WriteByte(0x3a, 0x14);
	   I2C_WriteByte(0x3d, 0x80);
	   I2C_WriteByte(0x67, 0x11);
	   I2C_WriteByte(0x68, 0xFF);
	   I2C_WriteByte(0x40, 0xC0);
	 

*/
	   I2C_WriteByte(0x12, 0x10);
	   I2C_WriteByte(0x3a, 0x14);
	   I2C_WriteByte(0x3d, 0x80);
	   I2C_WriteByte(0x67, 0x11);
	   I2C_WriteByte(0x68, 0xFF);
	   I2C_WriteByte(0x40, 0xC0);

	   LED_1(ON);
	   LED_2(ON);
}

void Read_Pic(void)
{
	u16 i,j;
	u16 t1,t2;
//以下代码完成，图像的采集，并显示在tft上				 							
	for(i = 0; i < 240; i ++)	 
	{	
		 if(i%6==1)
		{
			for(j = 0; j < 320; j ++)
			{
				if (j<160)
				{
				    //获得一个Y分量的过程										
					FIFO_RCK_L;					
					FIFO_RCK_H;		 				
					t1=(0x00ff&GPIOC->IDR);	 				
					FIFO_RCK_L;						
					FIFO_RCK_H;						
					t2=(0x00ff&GPIOC->IDR);
	
					//跳过一个点，隔开取点
				    FIFO_RCK_L;					
					FIFO_RCK_H;		 				
					t2=(0x00ff&GPIOC->IDR);	 				
					FIFO_RCK_L;						
					FIFO_RCK_H;						
					t2=(0x00ff&GPIOC->IDR);
					PIC[TrueLine][j]=t1; 
					}
	    	}
		  TrueLine++;
		}
		else
		{	  //否则跳过这些像素点
	      	for(j = 0; j < 320; j ++)
			{
				FIFO_RCK_L;					
				FIFO_RCK_H;		 				
				t2=(0x00ff&GPIOC->IDR);	 				
				FIFO_RCK_L;						
				FIFO_RCK_H;						
				t2=(0x00ff&GPIOC->IDR);
			}
		}
	}
	FIFO_OE_H;		 	  //禁止FIFO输出
}
void Send_Pic(void)
{
	u8 i;
	u8 j;
	USART_ClearFlag(USART1, USART_FLAG_TC); 
	USART_SendData(USART1,0xff);
  	while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);
	for(i=0;i<40;i++)
	{
		for(j=0;j<160;j++)
		{
			USART_ClearFlag(USART1, USART_FLAG_TC); 
		  	USART_SendData(USART1,PIC[i][j]);
  			while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);
		}
	}
}
