#include"includes.h"    
/*
--------------------------------------------------------------------
说明：
1、电调控制线接 马达电调(M2)，舵机控制线接转向舵机(M1)，注意接线顺序
黑色朝外，摄像头模块接扩展接口 注意 接线顺序
2、上电顺序，先打开控制板开关，然后再打开车模电源开关，等待3s后听到长
嘀 一声 证明 电调中间值已确定
3、实验现象：车速一会快一会慢
*/
int main(void)
{
	Board_Init();
	Application();
	return 0;
}
