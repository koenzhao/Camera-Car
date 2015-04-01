
#include <stm32f10x.h>
#include <stdio.h>
#include <usart.h>
#include <Nvic_Exit.h>
#include <delay.h>
#include <tft.h>
#include <ov7670.h>
#include<I2C.h>
#include "Image.h"
#include "include.h"

char txtbuf[12];
 

void send_string(char ch[])
{
	unsigned char ptr=0;
	while(ch[ptr])
	{
		USART_SendChar(COM1,ch[ptr++]);
	}
}			 

 u8 Get_a_Y()
 {
	 u8 t1,t2;
	            //获得一个Y分量的过程
				
														
				FIFO_RCK=0;					
				FIFO_RCK=1;		 				
				t1=(0x00ff&GPIOB->IDR);	 				
				FIFO_RCK=0;						
				FIFO_RCK=1;						
				t2=(0x00ff&GPIOB->IDR);


				//跳过一个像素
			    FIFO_RCK=0;					
				FIFO_RCK=1;		 				
				t2=(0x00ff&GPIOB->IDR);	 				
				FIFO_RCK=0;						
				FIFO_RCK=1;						
				t2=(0x00ff&GPIOB->IDR);




  return t1;
    
 }


 void skip_a_row()
 {
     u16 i;
	 u8 temp;
	for (i=0;i<320;i++)
	{
				//跳过一个像素
	         	FIFO_RCK=0;					
				FIFO_RCK=1;		 				
				temp=(0x00ff&GPIOB->IDR);	 				
				FIFO_RCK=0;						
				FIFO_RCK=1;						
				temp=(0x00ff&GPIOB->IDR);

	}
 }

 void Get_a_Image()

 {
   u16 i,j;
   for (i=0;i<R;i++)
   {
   		for(j=0;j<C;j++)
		{
         // data[i][j]= Get_a_Y();

		}

	   //跳过紧接着的5行
		skip_a_row();
		skip_a_row();
		skip_a_row();
	    skip_a_row();
	    skip_a_row();    
	} 
 }




 u8 Abs8(u8 a)
{
  if (a>=0)
  {
    return a;
  }
  else
  {
    return -a;

  }
}


void send_pic(void)
{
       u8 i,j;
        USART_SendData(USART1,0xFF);
        while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
       for (i=0;i<R;i++)
       {

         for (j=0;j<C;j++)
         {
           
		    if(data[i][j]==255) data[i][j]--;
            USART_SendData(USART1,data[i][j]);
           while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);

         }
       }
}




//*************************************************************//
//函数名: DataAnalyse
//函数类型：void  参数：l：图像数组号
//功能：图像数据分析
//*************************************************************//
void DataAnalyse(u8 l)
{


    Data=&data[0][0];

   ImageProcess();

}

///////////////////////////////////////////

//全局变量，要改
///////////////////////////////////////////
void ImageProcess()
{
	int i=0,j=0;
	u8 *p=0;
	u8 hd_count = 0;
	u8 hh_count = 0;
	//unsigned char *q=0;
        //ThresholdValue = otsu ((unsigned char *)Data, C, 0, 0, R, C);
        //ThresholdValue = 130;
	
        //均值滤波

//        for(i=0;i<38;i++)
//        {
//          for (p=Data+i*C+3;p<Data+(i+1)*C-3;p++)
//          {
//              *p=(*p+*(p+1)+*(p-1))/3;  //使用均值滤波的方式滤波
//          }
//        }

        //二值化

	for(i=R;i>0;i--)
	{
		hd_count=0;
	    for(j=0;j<C;j++)
	    {
	    	if(data[i][j]>ThresholdValue) 
				data[i][j]=White;
		 	else  
			{
				data[i][j]=Black;
		 		if(data[i][j]<ThresholdValue-110&&i<R-5&&i>5) 
					hd_count++;
			}

		if(hd_count>150) hh_count++;
			else hh_count=0;
		}
		if(hh_count>4)
		{
			deadline=1;
		}	//	printf("deadflag\n")	
	}
		
	
	
          //滤波
	for (i=0;i<R;i++)
	{
		p = Data+i*C+1;
		j=0;
		while (j<C-2)
		{
			if (*(p-1) == White && *p == Black && *(p+1) == White)
			{
				*p = White;
			}
			else if (*(p-1) == Black && *p == White && *(p+1) == Black)
			{
				*p = Black;
			}
			j++;
			p++;
		}
	}
}



void mygetLmr()
{

        u8 i=0;
        u8 j=0;


      	u8 pLeft,pRight ;
      	u8 bFoundLeft = 0;
      	u8 bFoundRight = 0;
      ///	unsigned char TripLen = 4;
        char bLeftEnd=0;
        char bRightEnd=0;
        char bMidEnd=0;


        BlackLineData[R-1]=LastFieldMid1;
        for (i=R-2;i>3&&bMidEnd!=1;i--)
        {


            //清零，以备下一行使用
              bFoundLeft=0;
              bFoundRight=0;


          //向左扫描

            for (pLeft=BlackLineData[i+1];pLeft>2;pLeft--)
            {
              if (*(Data+i*C+pLeft)==Black)
              {

                  bFoundLeft=1;
                  Left[i]=pLeft;
                  pLeft=1;

              }
            }
            if(bFoundLeft!=1)
             Left[i]=1;

            //检测是否到了尽头

            //向右扫描

            for (pRight=BlackLineData[i+1];pRight<C-2;pRight++)
            {
              if (*(Data+i*C+pRight)==Black)//&&*(Data+i*C+pRight+1)==Black)
              {
                bFoundRight=1;
                Right[i]=pRight;
                pRight=C;

              }
            }
            if (bFoundRight!=1)
             Right[i]=C-1;


            BlackLineData[i]=((Left[i]+Right[i]))/2;
            //左右边线采集结束，开始逻辑处理，易错，小心！！！ 以上的部分代码安全
           /*
            if ( *(Data+i*C+ BlackLineData[i])==Black)
            bMidEnd=1;
            */


            if ((BlackLineData[i]>C-4)||BlackLineData[i]<4)
            bMidEnd=1;

        }

        LastFieldMid1= BlackLineData[ R-5];
        LastFieldMid2=BlackLineData[ R-6];


}
void SmoothMid()
{
 u8  i;
 for (i=R-3;i>2;i--)
	{
		if (Abs8(BlackLineData[i]-BlackLineData[i-1])>5&& Abs8(BlackLineData[i]-BlackLineData[i+1])>5 )

         BlackLineData[i]=(BlackLineData[i-1]+BlackLineData[i+1] )/2;
    }
 }


 
void AddMtoPic(void)
{
  u8 i;
  for(i=0;i<R;i++)
  {
    data[i][BlackLineData[i]]=Black;
    data[i][80]=Black;
  }
}


void Steer_control(void)
{

	float kp,kd,ki;
	s16 steererr = 0;
	static u8 flag=0;
	static u16 i=0;
	u8 fx;
	
	// Err=(s16)((BlackLineData[25]+BlackLineData[26]+BlackLineData[27]+BlackLineData[28])/4)-80;
	Err=(s16)((BlackLineData[10]+BlackLineData[11])/2)-80;   //看近点，使得出十字弯道可以调整好
	
	Errd=Err-Errlast;
	if(Errd<=-40&&Errlast>35||Errd>=40&&Errlast<-35) //防止窜道
	{
		Err = Errlast;
		Errd = Errdlast;
	}

/*	if(Err>-20&&Err<20)
	{
		
		kp=2.5;
		kd=0.6;
	}
	if((Err>=20&&Err<mid)||(Err<=-20&&Err>-mid))
	{
		kp=2.8;
		kd=1.2;
	}
					  
*/				 
	if(Err>=-mid&&Err<0)					   //普通弯道
	{
		
		kp=2.6+0.01*(-Err);
		kd=0.8;
	}
	if(Err<=mid&&Err>0)						   //S弯或者曲率半径大的弯道
	{
		
		kp=2.5+0.01*Err;
		kd=0.8;
	}
	if(Err<mid&&Err>-mid)
	{	
		i=0; 
		steererr =(s16)(kp*Err+kd*Errd);
		Steerangle  = (u16)(STRM-steererr);
	}

	if(Err<=-mid||Err>=mid)
	{
		i++;
		if(i==1)
		{
			if(Err>mid)
			{
				Steerangle=STRR;
				flag=1;
			}
			if(Err<-mid)
			{
				 Steerangle=STRL;
				 flag=2;
			}		
		}
		if(i>1)
		{
			if(flag==1)
				Steerangle=STRR;
			if(flag==2)
				Steerangle=STRL;
		}

	}
	if(Steerangle<=STRR) Steerangle=STRR;
	if(Steerangle>=STRL) Steerangle=STRL;
	Errlast = Err;	   //存储上一次的Err
	//Errdlast = Errd;
	  sprintf(txtbuf,"\r\n%03d %03d",Err,Steerangle);send_string(txtbuf);
	//for(fx=0;fx<40;fx++) data[fx][BlackLineData[fx]] = Black;send_pic();

	TIM3->CCR1 = Steerangle;
}


void SpeedContiol(u16 speed)
{
   TIM3->CCR2 =speed;
}