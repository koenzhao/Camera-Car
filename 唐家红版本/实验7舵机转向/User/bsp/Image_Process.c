#include"includes.h"  

//数组指针的声明
uint8_t *Data_Point;
uint8_t BlackLineData[R]={80};
uint8_t LastFieldMid1=80;
u8 LastFieldMid2=80;

u8 left[R]={1};
u8 right[R]={C-1};
s8 Err;
s8 Last_Err=0;
s8 Current_Err=0;
u16  Steerangle  = 0;
u16  Current_Direction;
u16 Next_Direction;		   
int time_count=0;//计数
int control_count;
/*
-------------------------------------------------------------------
函数名称：void Data_Process(void)
函数功能：对采集到的图像数据进行二值化处理(0/1)
输入形参：无
返回值：无
-------------------------------------------------------------------
*/
void Data_Process(void)
{
	int i=0;
	int j=0;
	 //二值化 	
	for (i=0; i<R ;i++)	//行
	{
		for(j=0; j<C ;j++) //列
		{  			
			 if(PIC[i][j]>ThresholdValue)
			 {
			 	PIC[i][j]=White;		
			 }
			 else
			 {
			 	PIC[i][j]=Black;	
			 }
		}  	
	}
	//滤波
	for (i=0;i<R;i++)
	{
		
		for(j=1;j<C-1;j++)
		{
			if( PIC[i][j-1]==White && PIC[i][j]==Black && PIC[i][j+1]==White )
			{
				PIC[i][j]=White;
			}
			else
		   	if( PIC[i][j-1]==Black && PIC[i][j]==White && PIC[i][j+1]==Black )
			{
				PIC[i][j]=Black;
			}
		}
	}
}

/*
-------------------------------------------------------------------
函数名称：void Image_Process(void)
函数功能：供外部调用，图像处理部分函数
输入形参：无
返回值：无
-------------------------------------------------------------------
*/

void Image_Process(void)
{	
	Data_Point=&PIC[0][0];	
	//二值化处理
	Data_Process();
	//得到 中间值
	Get_Mid_Line();
	//平滑处理
	SmoothMid();
}
/*
-----------------------------------------------------------------------------
向左扫描、向右扫描、左右边线采集结束，计算中线

说明： BlackLineData数组用于记录路径的中点位置
left 用于记录左边黑线边界位置
Righe 用于记录右边边界 黑线位置


-----------------------------------------------------------------------------
*/
void Get_Mid_Line(void)
{
	uint8_t  i;
	uint8_t pLeft;
	uint8_t pRight;
    char bMidEnd=0;	
	/*记录赛道图像各行中线的位置，初始值为80*/
	BlackLineData[R-1]=LastFieldMid1;
	/*从倒数第二行开始计算，一共40行也就是说从第38行开始计算*/
	for (i=R-2;i>3&&C!=1;i--) //这是行
    { 	
		//向左扫描
        for(pLeft=BlackLineData[i+1];pLeft>2;pLeft--) //从i+1行的中点位置 循环一次 左移一次进行扫描
		{
			if(PIC[i][pLeft]==Black)//如果在 扫描过程中遇到黑点,那么就停止此行的扫描
			{
				left[i]=pLeft;//将黑点的位置保存在数组中
				pLeft=1;//结束此次循环 扫描下一行 
			}
			else
			{
				//如果没有检测到黑点，那么此行的中点位置记为 1
				left[i]=1;
			}  		 
		} 	
		//向右扫描
		for (pRight=BlackLineData[i+1];pRight<C-2;pRight++)
        {
        	if (PIC[i][pRight]==Black)	//找到了右边边界
            {               
                right[i]=pRight; //记录i行右边界的位置
				pRight=C-1;//结束此次循环               
			}
			else
			{
			 	right[i]=C-1;//如果没有检测到右边界或者 检测结束也没有发现黑线，那么
			}
      	}
       	//左右黑线边界确定之后计算中点
		BlackLineData[i]=((left[i]+right[i]))/2;
        //左右边线采集结束，开始逻辑处理，易错，小心！！！ 以上的部分代码安全
		if ((BlackLineData[i]>C-4)||BlackLineData[i]<4)
		{
			bMidEnd=1;
		}
    }
	 LastFieldMid1= BlackLineData[ R-5];
     LastFieldMid2=BlackLineData[ R-6];
}
/*
-----------------------------------------------------------------------------
向左扫描、向右扫描、左右边线采集结束，计算中线




-----------------------------------------------------------------------------
*/
s8 Abs8(s8 a)
{
	 s8 temp;
	 temp=a;
	if (temp>0||temp==0)
  	{
  	}
  	else
  	{
    	temp=0-temp;
	}
	return temp;
}
/*
-----------------------------------------------------------------------------
向左扫描、向右扫描、左右边线采集结束，计算中线




-----------------------------------------------------------------------------
*/
void SmoothMid(void)
{
	u8  i;
	uint8_t temp;
	uint8_t temp1;
 	for (i=R-3;i>2;i--) 
	{

		 if(BlackLineData[i]<BlackLineData[i-1])
		 {
		 	temp=BlackLineData[i-1]-BlackLineData[i];
		 }
		 else
		 {
		 	temp=BlackLineData[i]-BlackLineData[i-1];	
		 }

		 if(BlackLineData[i]<BlackLineData[i+1])
		 {
		 	temp1=BlackLineData[i+1]-BlackLineData[i];
		 }
		 else
		 {
		 	temp1=BlackLineData[i]-BlackLineData[i+1];	
		 }

		if (temp>5&&temp1>5 )
		{
			BlackLineData[i]=(BlackLineData[i-1]+BlackLineData[i+1] )/2;
		}
	}
}
/*
-----------------------------------------------------------------------------
	函数名称：void Steer_control
	函数功能：控制舵机转向
	输入形参：无
   	返回值：无
-----------------------------------------------------------------------------
*/
void  Steer_control(void)
{

  	u8 kp,kd,ki;
  	s16 steererr  = 0;
  	Err=((BlackLineData[11]+BlackLineData[12]+BlackLineData[13]+BlackLineData[14]+BlackLineData[15])/5)-80;
  	kp=8;
  	kd=0;
  	ki=0;	   
  	steererr  = kp*Err;
	// 500+ 或- 该向左转的时候 大于500 ，该向右转的时候小于500
  	Steerangle  = STRM-steererr;   		
	LED_1(ON);
	LED_2(ON);
	if(Steerangle>STRR)
	{
		Steerangle=700;	
		LED_1(ON);
		LED_2(OFF);
	}
	if(Steerangle<STRL)
	{
		Steerangle=330;//1 ms高电平
		LED_1(OFF);
		LED_2(ON);
		
	}
	Change_Direction(Steerangle); 
}
