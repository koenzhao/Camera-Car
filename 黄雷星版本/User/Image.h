 #ifndef __IMAGE_H
#define __IMAGE_H

 u8 Get_a_Y();
 void skip_a_row();
 void Get_a_Image();


  u8 Abs8(u8 a);
  void send_pic(void);
  void ImageProcess();
  void DataAnalyse(u8 l);
  void SmoothMid();
  void mygetLmr();
  void AddMtoPic(void);
  void Steer_control(void);
  void SpeedContiol(u16 speed);
  void send_sting(u8 *p);

#endif