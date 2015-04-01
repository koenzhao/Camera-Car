
/***************************************************************************
名    称： OV7670.C
功    能： 子函数定义
作    者： H&G
版    本： V1.0
创建时间： 2011-6-10
***************************************************************************/

/***************************************************************************
头文件
***************************************************************************/
#include<I2C.h>
#include<delay.h>
#include<ov7670.h>
/***************************************************************************
名    称：unsigned char WrCmos7670(unsigned char regID, unsigned char regDat)
功    能：向CMOS指定寄存器内写值
入口参数：regID  指定寄存器地址
          regDat 待写入指定寄存器的值 
出口参数：1    写入成功
          0    写入失败
说    明：
调用方法：m=WrCmos7670(0x3a,0x04);
***************************************************************************/
unsigned char WrCmos7670(unsigned char regID, unsigned char regDat)
{
	StartI2C0();
	if(0==I2CWrite0(OV7670_DEVICE_WRITE_ADDRESS))           //CMOS器件地址（写）
	{
		StopI2C0();
		return(0);
	}
	delay_us(100);
  	if(0==I2CWrite0(regID))         //CMOS寄存器地址
	{
		StopI2C0();
		return(0);
	}
	delay_us(100);
  	if(0==I2CWrite0(regDat))       //待写入指定寄存器的值
	{
		StopI2C0();
		return(0);
	}
  	StopI2C0();
	
  	return(1);
}  	

unsigned char rdCmos7670Reg(unsigned char regID)
{
	unsigned char regDat;
	StartI2C0();
	if(0==I2CWrite0(OV7670_DEVICE_WRITE_ADDRESS))
	{
        // USART_SendData(USART1,0xaa);
        //   while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
		StopI2C0();
		return(0);
	}
	delay_us(500);
  	if(0==I2CWrite0(regID))
	{
//	USART_SendData(USART1,2);
     //      while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
		StopI2C0();
		return(0);
	}
	StopI2C0();
	
	delay_us(500);

	StartI2C0();
	if(0==I2CWrite0(OV7670_DEVICE_READ_ADDRESS))
	{
//	USART_SendData(USART1,3);
        //   while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
		StopI2C0();
		return(0);
	}
	delay_us(500);
  	regDat=I2CRead0();
  	NoAck0();
  	StopI2C0();
	StopI2C0();
  	return regDat;
}

/***************************************************************************
名    称：void set_Cmos7670reg(void)
功    能：CMOS寄存器配置
入口参数：无
出口参数：无
说    明：
调用方法：set_Cmos7670reg();
***************************************************************************/
void set_Cmos7670reg(void)
{	 

	WrCmos7670(0x3a, 0x04);
	WrCmos7670(0x40, 0xd0);
	WrCmos7670(0x12, 0x14);
	WrCmos7670(0x32, 0x80);
	WrCmos7670(0x17, 0x16);
	WrCmos7670(0x18, 0x04);
	WrCmos7670(0x19, 0x02);
	WrCmos7670(0x1a, 0x7b);
	WrCmos7670(0x03, 0x06);
	WrCmos7670(0x0c, 0x00);
	WrCmos7670(0x3e, 0x00);
	WrCmos7670(0x70, 0x3a);
	WrCmos7670(0x71, 0x35);
	WrCmos7670(0x72, 0x11);
	WrCmos7670(0x73, 0x00);
	WrCmos7670(0xa2, 0x02);
	WrCmos7670(0x11, 0x81);
	
	WrCmos7670(0x7a, 0x20);
	WrCmos7670(0x7b, 0x1c);
	WrCmos7670(0x7c, 0x28);
	WrCmos7670(0x7d, 0x3c);
	WrCmos7670(0x7e, 0x55);
	WrCmos7670(0x7f, 0x68);
	WrCmos7670(0x80, 0x76);
	WrCmos7670(0x81, 0x80);
	WrCmos7670(0x82, 0x88);
	WrCmos7670(0x83, 0x8f);
	WrCmos7670(0x84, 0x96);
	WrCmos7670(0x85, 0xa3);
	WrCmos7670(0x86, 0xaf);
	WrCmos7670(0x87, 0xc4);
	WrCmos7670(0x88, 0xd7);
	WrCmos7670(0x89, 0xe8);
	
	WrCmos7670(0x13, 0xe0);
	WrCmos7670(0x00, 0x00);
	
	WrCmos7670(0x10, 0x00);
	WrCmos7670(0x0d, 0x00);
	WrCmos7670(0x14, 0x28);
	WrCmos7670(0xa5, 0x05);
	WrCmos7670(0xab, 0x07);
	WrCmos7670(0x24, 0x75);
	WrCmos7670(0x25, 0x63);
	WrCmos7670(0x26, 0xA5);
	WrCmos7670(0x9f, 0x78);
	WrCmos7670(0xa0, 0x68);
	WrCmos7670(0xa1, 0x03);
	WrCmos7670(0xa6, 0xdf);
	WrCmos7670(0xa7, 0xdf);
	WrCmos7670(0xa8, 0xf0);
	WrCmos7670(0xa9, 0x90);
	WrCmos7670(0xaa, 0x94);
	WrCmos7670(0x13, 0xe5);

	WrCmos7670(0x0e, 0x61);
	WrCmos7670(0x0f, 0x4b);
	WrCmos7670(0x16, 0x02);
	WrCmos7670(0x1e, 0x37);
	WrCmos7670(0x21, 0x02);
	WrCmos7670(0x22, 0x91);
	WrCmos7670(0x29, 0x07);
	WrCmos7670(0x33, 0x0b);
	WrCmos7670(0x35, 0x0b);
	WrCmos7670(0x37, 0x1d);
	WrCmos7670(0x38, 0x71);
	WrCmos7670(0x39, 0x2a);
	WrCmos7670(0x3c, 0x78);
	WrCmos7670(0x4d, 0x40);
	WrCmos7670(0x4e, 0x20);
	WrCmos7670(0x69, 0x00);
	WrCmos7670(0x6b, 0x60);
	WrCmos7670(0x74, 0x19);
	WrCmos7670(0x8d, 0x4f);
	WrCmos7670(0x8e, 0x00);
	WrCmos7670(0x8f, 0x00);
	WrCmos7670(0x90, 0x00);
	WrCmos7670(0x91, 0x00);
	WrCmos7670(0x92, 0x00);
	WrCmos7670(0x96, 0x00);
	WrCmos7670(0x9a, 0x80);
	WrCmos7670(0xb0, 0x84);
	WrCmos7670(0xb1, 0x0c);
	WrCmos7670(0xb2, 0x0e);
	WrCmos7670(0xb3, 0x82);
	WrCmos7670(0xb8, 0x0a);



	WrCmos7670(0x43, 0x14);
	WrCmos7670(0x44, 0xf0);
	WrCmos7670(0x45, 0x34);
	WrCmos7670(0x46, 0x58);
	WrCmos7670(0x47, 0x28);
	WrCmos7670(0x48, 0x3a);
	WrCmos7670(0x59, 0x88);
	WrCmos7670(0x5a, 0x88);
	WrCmos7670(0x5b, 0x44);
	WrCmos7670(0x5c, 0x67);
	WrCmos7670(0x5d, 0x49);
	WrCmos7670(0x5e, 0x0e);
	WrCmos7670(0x64, 0x04);
	WrCmos7670(0x65, 0x20);
	WrCmos7670(0x66, 0x05);
	WrCmos7670(0x94, 0x04);
	WrCmos7670(0x95, 0x08);
	WrCmos7670(0x6c, 0x0a);
	WrCmos7670(0x6d, 0x55);
	WrCmos7670(0x6e, 0x11);
	WrCmos7670(0x6f, 0x9f);
	WrCmos7670(0x6a, 0x40);
	WrCmos7670(0x01, 0x40);
	WrCmos7670(0x02, 0x40);
	WrCmos7670(0x13, 0xe7);
	WrCmos7670(0x15, 0x00);  
	
	
	WrCmos7670(0x4f, 0x80);
	WrCmos7670(0x50, 0x80);
	WrCmos7670(0x51, 0x00);
	WrCmos7670(0x52, 0x22);
	WrCmos7670(0x53, 0x5e);
	WrCmos7670(0x54, 0x80);
	WrCmos7670(0x58, 0x9e);
	
	WrCmos7670(0x41, 0x08);
	WrCmos7670(0x3f, 0x00);
	WrCmos7670(0x75, 0x05);
	WrCmos7670(0x76, 0xe1);
	WrCmos7670(0x4c, 0x00);
	WrCmos7670(0x77, 0x01);
	WrCmos7670(0x3d, 0xc2);	
	WrCmos7670(0x4b, 0x09);
	WrCmos7670(0xc9, 0x60);
	WrCmos7670(0x41, 0x38);
	WrCmos7670(0x56, 0x40);
	
	WrCmos7670(0x34, 0x11);
	WrCmos7670(0x3b, 0x02); 
								
	WrCmos7670(0xa4, 0x89);
	WrCmos7670(0x96, 0x00);
	WrCmos7670(0x97, 0x30);
	WrCmos7670(0x98, 0x20);
	WrCmos7670(0x99, 0x30);
	WrCmos7670(0x9a, 0x84);
	WrCmos7670(0x9b, 0x29);
	WrCmos7670(0x9c, 0x03);
	WrCmos7670(0x9d, 0x4c);
	WrCmos7670(0x9e, 0x3f);
	WrCmos7670(0x78, 0x04);
	
	WrCmos7670(0x79, 0x01);
	WrCmos7670(0xc8, 0xf0);
	WrCmos7670(0x79, 0x0f);
	WrCmos7670(0xc8, 0x00);
	WrCmos7670(0x79, 0x10);
	WrCmos7670(0xc8, 0x7e);
	WrCmos7670(0x79, 0x0a);
	WrCmos7670(0xc8, 0x80);
	WrCmos7670(0x79, 0x0b);
	WrCmos7670(0xc8, 0x01);
	WrCmos7670(0x79, 0x0c);
	WrCmos7670(0xc8, 0x0f);
	WrCmos7670(0x79, 0x0d);
	WrCmos7670(0xc8, 0x20);
	WrCmos7670(0x79, 0x09);
	WrCmos7670(0xc8, 0x80);
	WrCmos7670(0x79, 0x02);
	WrCmos7670(0xc8, 0xc0);
	WrCmos7670(0x79, 0x03);
	WrCmos7670(0xc8, 0x40);
	WrCmos7670(0x79, 0x05);
	WrCmos7670(0xc8, 0x30);
	WrCmos7670(0x79, 0x26); 
	WrCmos7670(0x09, 0x00);	



	/*
	

//        {0x3a, 0x04},//RGB
        {0x12, 0x10},//QVGA  YUV
        {0x3a, 0x14},//使用固定UV输出
        {0x3d, 0x80},//使用固定UV输出
                                                        //0         0       :      Y U Y V （3a:14 3d:80）
                                                        //0         1       :      Y V Y U  (3a:14 3d:81)
                                                        //1         0       :      U Y V Y (3a:18 3d:80)
                                                        //1         1       :      V Y U Y (3a:18 3d:81)
        {0x67, 0x11},//固定U值，0x11，方便测试
        {0x68, 0xFF},//固定V值，0xFF，方便测试
//        {0x40, 0x10},//RGB565
        {0x40, 0xC0},//初始配置，YUV模式，这个寄存器必须设置，否则不好使
//        {0x12, 0x14},//QVGA  RGB，


	   WrCmos7670(0x12, 0x10);
	   WrCmos7670 (0x3a, 0x14);
	   WrCmos7670 (0x3d, 0x80);
	   WrCmos7670(0x67, 0x11);
	   WrCmos7670(0x68, 0xFF);
	   WrCmos7670(0x40, 0xC0);
	 

	*/
	   WrCmos7670(0x12, 0x10);
	   WrCmos7670 (0x3a, 0x14);
	   WrCmos7670 (0x3d, 0x80);
	   WrCmos7670(0x67, 0x11);
	   WrCmos7670(0x68, 0xFF);
	   WrCmos7670(0x40, 0xC0);
	
	
}

/***************************************************************************
名    称：unsigned char Cmos7670_init(void)
功    能：CMOS初始化
入口参数：无
出口参数：1 初始化成功
          0 初始化失败
说    明：
调用方法：m=Cmos7670_init();
***************************************************************************/
unsigned char Cmos7670_init(void)
{

	u8 reg;
	unsigned char mmm;	

	
	InitI2C0();

	mmm=0x80;
	if(0==WrCmos7670(0x12, mmm)) 
	{
		return 0 ;
	}
	delay_ms(10);


	
		reg=rdCmos7670Reg(0x12);   //0x40
		  USART_SendData(USART1,reg);
           while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
		   	delay_ms(100);

  	set_Cmos7670reg();

	return 1; 
} 




