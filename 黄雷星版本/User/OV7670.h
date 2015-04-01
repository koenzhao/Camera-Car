
#ifndef OV7670_H
#define OV7670_H

#define OV7670_DEVICE_WRITE_ADDRESS    0x42
#define OV7670_DEVICE_READ_ADDRESS     0x43



/*OV7670FIFO模块控制引脚定义*/ 
//原版

/*

#define Cmos_CS    PAout(11)     //新班子中不用  
#define CMOS1_RST  PCout(14)   //  PBout(12)
#define CMOS1_PWDN PCout(15)

#define FIFO_WR    PCout(10) 
#define FIFO_WRST  PAout(13)
#define FIFO_RCK   PCout(9)
#define FIFO_RRST  PAout(15)
#define FIFO_OE	   PAout(14)
//新版
*/

#define CMOS1_RST   PBout(12)
#define CMOS1_PWDN  PAout(12)

#define FIFO_WR    PBout(14) 
#define FIFO_WRST  PCout(8)
#define FIFO_RCK   PBout(13)
#define FIFO_RRST  PCout(9)
#define FIFO_OE	   PBout(15)





void set_Cmos7670reg(void);	
unsigned char Cmos7670_init(void);
unsigned char WrCmos7670(unsigned char regID, unsigned char regDat);
unsigned char rdCmos7670Reg(unsigned char regID);
void Cmos7670_Size(unsigned int Startx,unsigned int Starty,unsigned int width,unsigned int height);

#endif

