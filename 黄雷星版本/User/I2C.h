

#ifndef I2C_H
#define I2C_H
/***************************************************************************
头文件
***************************************************************************/
#include "sys.h"



#define SDA_IN0()  {GPIOB->CRH&=0XFFFF0FFF;GPIOB->CRH|=8<<12;}
#define SDA_OUT0() {GPIOB->CRH&=0XFFFF0FFF;GPIOB->CRH|=3<<12;}

/////////////////////////////////////////////////////////////////
//IO操作函数
//原版
	 
#define I2C_SCL0    PBout(10)  // PCout(12) //SCL
#define I2C_SDA0    PBout(11) //SDA	 PCout(11) //SDA	 
#define SDA_STATE0  PBin(11)  //输入SDA 





void InitI2C0(void);   //I2C初始化
void StartI2C0(void);  //起始信号
void StopI2C0(void);  //停止信号
void NoAck0(void);   //非应答信号
void Ack0(void);
unsigned char TestAck0(void);
unsigned char I2CWrite0(unsigned char DData);   //写一个字节
unsigned char I2CRead0(void);  //读一个字节

#endif 
