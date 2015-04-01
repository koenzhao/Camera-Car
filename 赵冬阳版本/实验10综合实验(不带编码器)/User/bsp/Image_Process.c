#include"includes.h"  

//数组指针的声明
uint8_t *Data_Point;
uint8_t BlackLineData[R]={80};	//记录各行中点的值
uint8_t LastFieldMid1=80;
u8 LastFieldMid2=80;

u8 left[R]={1};	   //记录第i行左边黑线边界位置
u8 right[R]={C-1};	  //记录第i行右边黑线边界位置
s8 Err;
s8 Last_Err=0;
s8 Current_Err=0;
u16 Steerangle  = 0;
u16 Current_Direction;
u16 Next_Direction;		   
int time_count=0;//计数
int control_count;
PID_ParameterTypeDef PID;
uint8_t y[R]={80};

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
	//滤波本例程只提供一个样板其中还有很多可以优化的地方，比如下面的这段代码，有兴趣的同学可以研究一下
	for (i=0;i<R;i++)
	{
		
		for(j=1;j<C-1;j++)
		{
			if( PIC[i][j-1]==White && PIC[i][j]==Black && PIC[i][j+1]==White )	 //滤了白黑白的情况
			{
				PIC[i][j]=White;
			}
			else if( PIC[i][j-1]==Black && PIC[i][j]==White && PIC[i][j+1]==Black )	//滤了黑白黑的情况
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
说明:该程序起一个抛砖引玉的作用其中还有许多不足需要同学问进行完善
-------------------------------------------------------------------
*/

void Image_Process(void)
{	
	int end = R-5;
	int start = end-7;
		
	Data_Point=&PIC[0][0];	
	
	//二值化处理
	Data_Process();

	//得到 中间值
	Get_Mid_Line();
	
	//平滑处理
	SmoothMid();

	//最小二乘法进一步平滑处理
	for (;start>=4;start -= 6, end -= 6)
	{
		Least_Squares(start, end);
	}
	//Least_Squares(4, R-5);
	
	//显示中心黑线
	//DisplayBlackLine();
}
/*
--------------------------------------------------------------------
  函数名称：void Get_Mid_Line(void)
  函数功能：提取中线
  输入形参：无
  返回值：无
--------------------------------------------------------------------
*/	
void Get_Mid_Line(void)
{
	uint8_t i;
	uint8_t pLeft;
	uint8_t pRight;
    //char bMidEnd=0;	
	/*记录赛道图像各行中线的位置，初始值为80*/
	BlackLineData[R-1]=((LastFieldMid1+LastFieldMid2)/2);
	
	/*从倒数第二行开始计算，一共40行也就是说从第38行开始计算*/
	for (i=R-2;i>3&&C!=1;i--) //这是行
    { 	
		//向左扫描
        for(pLeft=BlackLineData[i+1];pLeft>2;pLeft--) //从i+1行的中点位置 循环一次 左移一次进行扫描
		{
			if(PIC[i][pLeft]==Black)//如果在 扫描过程中遇到黑点,那么就停止此行的扫描  要多判断几个点
			{
				left[i]=pLeft--;//记录i行左边界的位置
				if(PIC[i][pLeft]==Black) //确认下一列也是黑点
				{
					pLeft=1;//结束此次循环 扫描下一行	
				}
			}
			else
			{
				//如果没有检测到黑点，那么此行的中点位置记为 1
				left[i]=1;
			}  		 
		} 	
		//向右扫描
		for (pRight=BlackLineData[i+1];pRight<C-3;pRight++)
        {
        	if (PIC[i][pRight]==Black)	//找到了右边边界
            {               
                right[i]=pRight++; //记录i行右边界的位置
				if(PIC[i][pRight]==Black)
				{
					pRight=C-1;//结束此次循环 扫描下一行	
				}
				               
			}
			else
			{
			 	right[i]=C-1;//如果没有检测到右边界或者 检测结束也没有发现黑线，那么
			}
      	}
       	//左右黑线边界确定之后计算中点，第i行的中点
		BlackLineData[i]=((left[i]+right[i]))/2;
        //左右边线采集结束，开始逻辑处理，易错，小心！！！ 以上的部分代码安全
	
    }
	
	/*应记录图像中高两行的值*/
	//LastFieldMid1= BlackLineData[R-5];
    //LastFieldMid2= BlackLineData[R-6];
	LastFieldMid1= BlackLineData[4];
    LastFieldMid2= BlackLineData[5];
	
}
/*
--------------------------------------------------------------------
  函数名称：s8 Abs8(s8 a)
  函数功能：取绝对值
  输入形参：
  返回值：
--------------------------------------------------------------------
*/	
s8 Abs8(s8 a)
{
	s8 temp;
	temp=a;
	if (temp>=0)
  	{
  	}
  	else
  	{
    	temp=0-temp;
	}
	return temp;
}
/*
--------------------------------------------------------------------
  函数名称：SmoothMid()
  函数功能：平滑中线
  输入形参：无
  返回值：无
--------------------------------------------------------------------
*/	
void SmoothMid(void)
{
	uint8_t  i;
	uint8_t temp;
	uint8_t temp1;
 	for (i=R-1;i>3;i--) 
	{
		if(BlackLineData[i] != BlackLineData[i-1])
		{
			temp = Abs8(BlackLineData[i-1]-BlackLineData[i]);
		}
		/*else
		{
		 	temp=BlackLineData[i]-BlackLineData[i-1];	
		}*/

		if(BlackLineData[i] != BlackLineData[i+1])
		{
		 	temp1 = Abs8(BlackLineData[i+1]-BlackLineData[i]);
		}
		/*else
		{
		 	temp1=BlackLineData[i]-BlackLineData[i+1];	
		} */

		if (((temp>5)&&(temp1>5)) || ((BlackLineData[i-1]<BlackLineData[i])&&(BlackLineData[i+1]<BlackLineData[i])) || ((BlackLineData[i-1]>BlackLineData[i])&&(BlackLineData[i+1]>BlackLineData[i])))	 //两个差都大于5的话做修正或不在上下中点的中间
		{
			BlackLineData[i]=(BlackLineData[i-1]+BlackLineData[i+1])/2;
		}
	}
}
/*
-----------------------------------------------------------------------------
函数名称：Curve()
函数功能：计算图像上半部分的中心线弯曲程度
输入形参：
返回值：PIC中第4行到14行中心黑线的弯曲程度
说明：通过此值可提前判别弯道
-----------------------------------------------------------------------------
*/
s8 Curve(void)
{
	int8_t i;
	s8 sum_BlackLine=0;
	s8 average_BlackLine=0;
	s8 curve_BlackLine=0;
	s8 differ_BlackLine=0;
	for(i=14, sum_BlackLine=0; i>=4; i--)
	{
		sum_BlackLine+=BlackLineData[i];
	}
	average_BlackLine = sum_BlackLine / 10;
	for(i=14, curve_BlackLine=0;i>=14;i--)
	{
		differ_BlackLine= Abs8(BlackLineData[i]-average_BlackLine);
		curve_BlackLine += differ_BlackLine;
	}
	return curve_BlackLine;
}
/*
-----------------------------------------------------------------------------
函数名称：Least_Squares()
函数功能：用最小二乘法进一步平滑曲线
输入形参：start,end
返回值：
说明：对BlackLineData[]从start到end进行最小二乘法平滑
-----------------------------------------------------------------------------
*/
void Least_Squares(int start, int end)
{
	uint8_t i=0;
	double A=0, B=0, D=0, F=0, Delta;
	
	
	double a,b;
	int t;

	for (i=end;i>=start;i--)
	{
		//BlackLineData[i]=y[i];
		y[i]=BlackLineData[i];
	}

	
	for (i=start;i<=end;i++)
	{
		A += i*i; //pow(i,2)
		B += i;
 		D += i*y[i];
		F += y[i];
	}
	
	
	t = end-start+1;
	Delta = A*t-B*B;
	a = (D*t-B*F)/Delta;
	b = (A*F-D*B)/Delta;
	
	
	for (i=start;i<=end;i++)
	{
		BlackLineData[i]=(a*i+b);
	}
	
	
	A=0;
	B=0;
	D=0;
	F=0;
	
	//y[]={0};
}
/*
-----------------------------------------------------------------------------
函数名称：DisplayBlackLine()
函数功能：将中心黑线加入图像PIC中
输入形参：
返回值：
说明：可在调用的时候将中心黑线加入PIC，无论处理前还是处理后
-----------------------------------------------------------------------------
*/

void DisplayBlackLine(void)
{
	uint8_t i;
	for (i=R-2;i>3;i--)
	{
		PIC[i][BlackLineData[i]] = Black;
	}
}
				   

/*
-----------------------------------------------------------------------------
	函数名称：void Steer_control
	函数功能：控制舵机转向
	输入形参：无
   	返回值：无
	说明：舵机的方向控制还可以用PD控制算法
-----------------------------------------------------------------------------
*/
void  Steer_control(void)
{
	s16 steererr  = 0;
  	PID.CurErr=((BlackLineData[11]+BlackLineData[12]+BlackLineData[13]+BlackLineData[14]+BlackLineData[15])/5)-80;
  	PID.P=6;//比例
    PID.I=0;
	PID.D=1;
  	steererr  = PID.P * (PID.CurErr-PID.LastErr)+PID.D * (PID.CurErr-2*PID.LastErr+PID.PreErr);
	//steererr = PID.P * Err;
	// 500+ 或- 该向左转的时候 大于500 ，该向右转的时候小于500
  	Steerangle  = STRM-steererr;   		
	LED_1(ON);
	LED_2(ON);
	if(Steerangle>STRR)
	{
		Steerangle=600;	
		LED_1(ON);
		LED_2(OFF);
	}
	if(Steerangle<STRL)
	{
		Steerangle=400;//1 ms高电平
		LED_1(OFF);
		LED_2(ON);
		
	}
	Change_Direction(Steerangle); 
}


