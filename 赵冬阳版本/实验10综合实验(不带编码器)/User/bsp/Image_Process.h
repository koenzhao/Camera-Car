#ifndef __IMAGE_PROCESS_H__
#define __IMAGE_PROCESS_H__

#define ThresholdValue 		100	//二值化阀值 130

#define White				254
#define Black				0
#define STRM  500
#define STRL  330
#define STRR  670


void Image_Process(void);
void Data_Process(void);
void Get_Mid_Line(void);
s8 Abs8(s8 a);
void SmoothMid(void);
void Least_Squares(int start, int end);
void Steer_control(void);
void DisplayBlackLine(void);
s8 Curve(void);
typedef struct
{
	int SP;//Set Point 目标值
	u8 P;//比例系数
	u8 I;//积分系数
	u8 D;//微分系数
	s8 CurErr;//当前偏差值
	s8 LastErr;//上一次偏差值
	s8 PreErr;//上上次偏差值
}PID_ParameterTypeDef;


extern uint8_t *Data_Point;
extern int time_count;//计数

#endif

