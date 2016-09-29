#include <stdio.h>
#include "cv.h"
#include "cxcore.h"
#include "highgui.h"
double * mbys(double * im,int imW,int imH,double *tp,int tpW,int tpH);
BOOL* Harris(IplImage* src , IplImage* dst)
{
	int totalCorner=0;

	IplImage* ImgGray;//��ŻҶ�ͼ
	BOOL* dstCorner;

	//����һ����Դͼ����ͬ��С�ĻҶ�ͼ��װ�
	int srcWidth=src->width;
	int srcHeight=src->height;

	//����һ����Դͼ����ͬ��С�ĻҶ�ͼ��װ�
	ImgGray = cvCreateImage(cvSize(srcWidth,srcHeight),IPL_DEPTH_8U,1);
	
	//�ҶȻ�
	cvCvtColor(src,ImgGray,CV_RGB2GRAY);

	//gausswidth����ά��˹���ڿ��
	//sigma����˹�����ķ���
	//size���Ǽ���ֵ���Ƶ�������
	//thresh������ȷ���ǵ��������ֵ
	int i,j,m,n,size,thresh,gausswidth;
	double sigma;

	//�����ĸ�����
	gausswidth=5;
	sigma=0.8;
	size=5;
	thresh=2000;

	uchar* grayData = (uchar*)ImgGray->imageData;//�Ҷ�ͼ������
	int step=ImgGray->widthStep;     // �Ҷ�ͼ��ÿ�е��ֽ���

	//����I��Ix��Ix2��Iy��Iy2��Ixy��cim��mx��corner����
	double *I=new double[srcWidth*srcHeight];
	double *Ix=new double[srcWidth*srcHeight];
	double *Ix2=new double[srcWidth*srcHeight];
	double *Iy=new double[srcWidth*srcHeight];
	double *Iy2=new double[srcWidth*srcHeight];
	double *Ixy=new double[srcWidth*srcHeight];
	double *cim=new double[srcWidth*srcHeight];
	double *mx=new double[srcWidth*srcHeight];

	dstCorner=new BOOL[srcWidth*srcHeight];
	memset(dstCorner, 0, srcWidth*srcHeight*sizeof(BOOL));//void *memset(void *s,int ch,size_t n); ����
                                                              //�������ͣ���s��ǰn���ֽ���ch�滻������s�� 

	//������Է������Ԫ��
	#define I(ROW,COL) I[srcWidth*(ROW)+(COL)]
	#define Ix(ROW,COL) Ix[srcWidth*(ROW)+(COL)]
	#define Ix2(ROW,COL) Ix2[srcWidth*(ROW)+(COL)]
	#define Iy(ROW,COL) Iy[srcWidth*(ROW)+(COL)]
	#define Iy2(ROW,COL) Iy2[srcWidth*(ROW)+(COL)]
	#define Ixy(ROW,COL) Ixy[srcWidth*(ROW)+(COL)]
	#define cim(ROW,COL) cim[srcWidth*(ROW)+(COL)]
	#define mx(ROW,COL) mx[srcWidth*(ROW)+(COL)]
	#define corner(ROW,COL) dstCorner[srcWidth*(ROW)+(COL)]

	//��ͼ��Ҷ�ֵ���Ƶ�I�У��ⲽ����Ҫ��
	for((1)%%%%%%%%%%%%%%%)
	{
		for(%%%%%%%%%%%%%%%%)
		{
			//��256���Ҷ�ͼ��ת��Ϊdouble��
			I(i,j)=double(grayData[i*step+j]);
		}
	}


	//--------------------------------------------------------------------------
	//                     ��һ�������ò�����Ӷ�ͼ������˲�
	//--------------------------------------------------------------------------
	
	//����ˮƽ���������Ӳ���Ix
	double dx[9]={-1,0,1,-1,0,1,-1,0,1};
	Ix=mbys(I,srcWidth,srcHeight,dx,3,3);

	//���崹ֱ���������Ӳ���Iy
	double dy[9]={-1,-1,-1,0,0,0,1,1,1};
	Iy=mbys(I,srcWidth,srcHeight,dy,3,3);

	//����Ix2��Iy2��Ixy
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
	//                  �ڶ�������Ix2/Iy2/Ixy���и�˹ƽ������ȥ������
	//--------------------------------------------------------------------------

	//������ʹ��5��5�ĸ�˹ģ��
	//����ģ�����
	double *g=new double[gausswidth*gausswidth];
	for(i=0;i<gausswidth;i++)
		for(j=0;j<gausswidth;j++)
			g[i*gausswidth+j]=exp(-((i-int(gausswidth/2))*(i-int(gausswidth/2))+
			(j-int(gausswidth/2))*(j-int(gausswidth/2)))/(2*sigma));

	//��һ����ʹģ�����֮��Ϊ1����ʵ�˲�����ʡ�ԣ�
	double total=0;
	for(i=0;i<gausswidth*gausswidth;i++)
		total+=g[i];
	for(i=0;i<gausswidth;i++)
		for(j=0;j<gausswidth;j++)
			g[i*gausswidth+j]/=total;

	//���и�˹ƽ��
	Ix2=mbys(Ix2,srcWidth,srcHeight,g,gausswidth,gausswidth);
	Iy2=mbys(Iy2,srcWidth,srcHeight,g,gausswidth,gausswidth);
	Ixy=mbys(Ixy,srcWidth,srcHeight,g,gausswidth,gausswidth);
	

	//--------------------------------------------------------------------------
	//                        ������������ǵ���
	//--------------------------------------------------------------------------
	
	//����cim����cornerness of image�����ǰ����������ǵ�����
	double cimmax=0;
	for(%%%%%%%%)
	{
		for(%%%%%%%%)
		{
			//ע�⣺Ҫ�ڷ�ĸ�м���һ����С��0.000001�Է�ֹ����Ϊ�����
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
	//                 ���Ĳ������оֲ��Ǽ���ֵ�����Ի�����սǵ�
	//--------------------------------------------------------------------------
	
	//ע����оֲ�����ֵ���Ƶ�˼·

	//const double size=7;
	double max;
	//��ÿ������������������ֵ�˲��������õ��ֵ��Ϊ�����������Ǹ�ֵ������ֵ�˲��е����ƣ�
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

	//����ȷ���ǵ�
	//const double thresh=4500;
	for((4)%%%%%%%%%%)
	{
		for(%%%%%%%%%%%)
		{	
		  //�����ص�ȡ�þֲ�����ֵ������Ȼ������趨����ֵ
				
					  if(%%%%%%%%%%%%%%%)
						  if(%%%%%%%%%%%%%%%%)
						  {
			
				                  corner(i,j)=1;   //�������������������ǽǵ�
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
	
	//��ͼ���л����ǵ�

	CvPoint pt1,pt2;
        //��д��ѭ�����������ڽǵ�λ�û�����cvLine�����
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