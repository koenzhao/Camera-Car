#ifndef __INCLUDE_H
#define __INCLUDE_H	

#define R   30
#define C   160


#define   White   244
#define   Black   0


#define STRM  530
#define STRL  680
#define STRR  370
#define mid 50
//#define STRE  1200

#define YUANBAN

extern u8 * Data;
 extern  u8 Get_a_Y();
 extern  void skip_a_row();
 extern  void Get_a_Image();


 extern u16 PixelCounter;
 extern u8 datareadyflag; 


//extern u8 data[40*160];
extern u8 data[R][C];



extern u8 InterruptLine;
extern u8 TrueLine;
extern u8 DataReadyFlag;


extern u8 BlackLineData[R];
extern u8 Left[R];
extern u8 Right[R];
//uchar Mid[R]={R/2};

extern u8 LastFieldMid1;
extern u8 LastFieldMid2;

extern u8 ThresholdValue;
extern s16 Err ;
extern s16 Errlast   ;
extern s16 Errd  ;
extern s16 Errdlast ;
extern s16 Erri ;
extern s16 Roadtype ;
extern s16 Errhistory[8];
extern u16  Steerangle  ;
extern u8  deadline;

extern const u16 SlampeLine[R];


#endif