#ifndef __I2C_H__
#define __I2C_H__ 

void I2C_Configuration(void);
void I2C_Start(void);/*I2C总线启动函数*/ 
void I2C_Stop(void);/*I2C总线释放函数*/
uint8_t I2C_WaitAck(void);/*I2C总线检测从机应答函数*/
void I2C_SendByte(uint8_t _ucByte);/*I2C总线写数据函数*/
uint8_t I2C_ReadByte(void);
void I2C_Ack(void);
void I2C_NAck(void);
int I2C_WriteByte( uint16_t WriteAddress , uint8_t SendByte) ;
uint8_t I2C_ReadOneByte(uint8_t Address);

#endif	 






















