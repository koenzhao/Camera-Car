#ifndef __ENCODING_H__
#define __ENCODING_H__
/*在encoding.c文件中定义的变量 供外部使用时必须添加
extern关键字
*/
/*用于存储编码器脉冲数目*/
extern s16 encoder_num;
/*编码器控制接口初始化*/
void Encorder_GPIO_Config(void);
/*供外部调用的编码器初始化函数*/
void Encoder_Init(void);
#endif
