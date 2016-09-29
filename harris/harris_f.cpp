#include <stdio.h>
#include "cv.h"
#include "cxcore.h"
#include "highgui.h"
double * mbys(double * im,int imW,int imH,double *tp,int tpW,int tpH);
BOOL* Harris(IplImage* src , IplImage* dst)
{
	int totalCorner=0;

	IplImage* ImgGray;//存放灰度图
	BOOL* dstCorner;

	//创建一个与源图像相同大小的灰度图像底板
	int srcWidth=src->width;
	int srcHeight=src->height;

	//创建一个与源图像相同大小的灰度图像底板
	ImgGray = cvCreateImage(cvSize(srcWidth,srcHeight),IPL_DEPTH_8U,1);
	
	//灰度化
	cvCvtColor(src,ImgGray,CV_RGB2GRAY);

	//gausswidth：二维高斯窗口宽度
	//sigma：高斯函数的方差
	//size：非极大值抑制的邻域宽度
	//thresh：最终确定角点所需的阈值
	int i,j,m,n,size,thresh,gausswidth;
	double sigma;

	//输入四个参数
	gausswidth=5;
	sigma=0.8;
	size=5;
	thresh=2000;

	uchar* grayData = (uchar*)ImgGray->imageData;//灰度图像数据
	int step=ImgGray->widthStep;     // 灰度图像每行的字节数

	//创建I、Ix、Ix2、Iy、Iy2、Ixy、cim、mx、corner数组
	double *I=new double[srcWidth*srcHeight];
	double *Ix=new double[srcWidth*srcHeight];
	double *Ix2=new double[srcWidth*srcHeight];
	double *Iy=new double[srcWidth*srcHeight];
	double *Iy2=new double[srcWidth*srcHeight];
	double *Ixy=new double[srcWidth*srcHeight];
	double *cim=new double[srcWidth*srcHeight];
	double *mx=new double[srcWidth*srcHeight];

	dstCorner=new BOOL[srcWidth*srcHeight];
	memset(dstCorner, 0, srcWidth*srcHeight*sizeof(BOOL));//void *memset(void *s,int ch,size_t n); 　　
                                                              //函数解释：将s中前n个字节用ch替换并返回s； 

	//定义宏以方便访问元素
	#define I(ROW,COL) I[srcWidth*(ROW)+(COL)]
	#define Ix(ROW,COL) Ix[srcWidth*(ROW)+(COL)]
	#define Ix2(ROW,COL) Ix2[srcWidth*(ROW)+(COL)]
	#define Iy(ROW,COL) Iy[srcWidth*(ROW)+(COL)]
	#define Iy2(ROW,COL) Iy2[srcWidth*(ROW)+(COL)]
	#define Ixy(ROW,COL) Ixy[srcWidth*(ROW)+(COL)]
	#define cim(ROW,COL) cim[srcWidth*(ROW)+(COL)]
	#define mx(ROW,COL) mx[srcWidth*(ROW)+(COL)]
	#define corner(ROW,COL) dstCorner[srcWidth*(ROW)+(COL)]

	//将图像灰度值复制到I中，这步很重要！
	for((1)%%%%%%%%%%%%%%%)
	{
		for(%%%%%%%%%%%%%%%%)
		{
			//将256级灰度图像转化为double型
			I(i,j)=double(grayData[i*step+j]);
		}
	}


	//--------------------------------------------------------------------------
	//                     第一步：利用差分算子对图像进行滤波
	//--------------------------------------------------------------------------
	
	//定义水平方向差分算子并求Ix
	double dx[9]={-1,0,1,-1,0,1,-1,0,1};
	Ix=mbys(I,srcWidth,srcHeight,dx,3,3);

	//定义垂直方向差分算子并求Iy
	double dy[9]={-1,-1,-1,0,0,0,1,1,1};
	Iy=mbys(I,srcWidth,srcHeight,dy,3,3);

	//计算Ix2、Iy2、Ixy
	for(%%%%%%%)
	{
		for(%%%%%%%%)
		{	
             (2)  %%%%%%%%%%%%%%%%%%%%
				  %%%%%%%%%%%%%%%%%%%%
				  %%%%%%%%%%%%%%%%%%%%%

		}
	}

	//--------------------------------------------------------------------------
	//                  第二步：对Ix2/Iy2/Ixy进行高斯平滑，以去除噪声
	//--------------------------------------------------------------------------

	//本例中使用5×5的高斯模板
	//计算模板参数
	double *g=new double[gausswidth*gausswidth];
	for(i=0;i<gausswidth;i++)
		for(j=0;j<gausswidth;j++)
			g[i*gausswidth+j]=exp(-((i-int(gausswidth/2))*(i-int(gausswidth/2))+
			(j-int(gausswidth/2))*(j-int(gausswidth/2)))/(2*sigma));

	//归一化：使模板参数之和为1（其实此步可以省略）
	double total=0;
	for(i=0;i<gausswidth*gausswidth;i++)
		total+=g[i];
	for(i=0;i<gausswidth;i++)
		for(j=0;j<gausswidth;j++)
			g[i*gausswidth+j]/=total;

	//进行高斯平滑
	Ix2=mbys(Ix2,srcWidth,srcHeight,g,gausswidth,gausswidth);
	Iy2=mbys(Iy2,srcWidth,srcHeight,g,gausswidth,gausswidth);
	Ixy=mbys(Ixy,srcWidth,srcHeight,g,gausswidth,gausswidth);
	

	//--------------------------------------------------------------------------
	//                        第三步：计算角点量
	//--------------------------------------------------------------------------
	
	//计算cim：即cornerness of image，我们把它称做‘角点量’
	double cimmax=0;
	for(%%%%%%%%)
	{
		for(%%%%%%%%)
		{
			//注意：要在分母中加入一个极小量0.000001以防止除数为零溢出
			(3)%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
				if (cim(i,j)>cimmax)
				cimmax=cim(i,j);
		}
	}
    IplImage * cimImage=0;
	cimImage = cvCreateImage(cvSize(srcWidth,srcHeight),IPL_DEPTH_8U,1);
	uchar* cimData = (uchar*)cimImage->imageData;
		for(i = 0; i < srcHeight; i++)
	{
		for(j = 0; j < srcWidth; j++)
		{
		
			cimData[i*step+j]=uchar((cim(i,j)/cimmax)*255);
		}
	}
	cvNamedWindow( "R", 1 );
	cvShowImage( "R", cimImage); 
    
	//--------------------------------------------------------------------------
	//                 第四步：进行局部非极大值抑制以获得最终角点
	//--------------------------------------------------------------------------
	
	//注意进行局部极大值抑制的思路

	//const double size=7;
	double max;
	//对每个点在邻域内做极大值滤波：即将该点的值设为邻域中最大的那个值（跟中值滤波有点类似）
	for(i = 0; i < srcHeight; i++)
	{
		for(j = 0; j < srcWidth; j++)
		{
			max=-1000000;
			if(i>int(size/2) && i<srcHeight-int(size/2) && j>int(size/2) && j<srcWidth-int(size/2))
				for(m=0;m<size;m++)
				{
					for(n=0;n<size;n++)
						{						
							if(cim(i+m-int(size/2),j+n-int(size/2))>max)
								max=cim(i+m-int(size/2),j+n-int(size/2));
						}
				}
			if(max>0)
				mx(i,j)=max;
			else
				mx(i,j)=0;
		}
	}

	//最终确定角点
	//const double thresh=4500;
	for((4)%%%%%%%%%%)
	{
		for(%%%%%%%%%%%)
		{	
		  //当像素点取得局部极大值，并且然后大于设定的阈值
				
					  if(%%%%%%%%%%%%%%%)
						  if(%%%%%%%%%%%%%%%%)
						  {
			
				                  corner(i,j)=1;   //满足上两个条件，才是角点
								  totalCorner++;
						  }
						
				
		}
	}
    IplImage * maxImage=0;
	maxImage = cvCreateImage(cvSize(srcWidth,srcHeight),IPL_DEPTH_8U,1);
	uchar* maxData = (uchar*)maxImage->imageData;
		for(i = 0; i < srcHeight; i++)
	{
		for(j = 0; j < srcWidth; j++)
		{
		
			maxData[i*step+j]=uchar(corner(i,j)*255);
		}
	}
	cvNamedWindow( "max", 1 );
	cvShowImage( "max", maxImage); 


	delete I;
	delete Ix;
	delete Ix2;
	delete Iy;
	delete Iy2;
	delete Ixy;
	delete cim;
	delete mx;	
	
	//在图像中画出角点

	CvPoint pt1,pt2;
        //请写出循环条件，并在角点位置画出（cvLine）标记
	(5)%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
		%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
		//		pt1.x=j-5;
		//		pt1.y=i;
		//		pt2.x=j+5;
		//		pt2.y=i;
		//		cvLine(dst,pt1,pt2,CV_RGB(255,0,0),1,CV_AA,0);  //CV_RGB(0,255,0)
		//		pt1.x=j;
		//		pt1.y=i-5;
		//		pt2.x=j;
		//		pt2.y=i+5;
		//		cvLine(dst,pt1,pt2,CV_RGB(255,0,0),1,CV_AA,0);
	
	return dstCorner;
}