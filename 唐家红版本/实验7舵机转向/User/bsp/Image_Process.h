#ifndef __IMAGE_PROCESS_H__
#define __IMAGE_PROCESS_H__

#define ThresholdValue 		130

#define White				244
#define Black				0
#define STRM  500
#define STRL  330
#define STRR  670

void Image_Process(void);
void Data_Process(void);
void Get_Mid_Line(void);
s8 Abs8(s8 a);
void SmoothMid(void);
void Steer_control(void);


extern uint8_t *Data_Point;
extern int time_count;//¼ÆÊý

#endif

