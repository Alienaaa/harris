//harris��ȡ������
#include <stdio.h>
#include <time.h>
#include "cv.h"
#include "highgui.h"
#include "harris_f.cpp"


int totalCorner=0;//��¼������ĸ���

//����ģ�����㺯��
//im������ͼ��  tp��ģ�����

BOOL* Harris(IplImage* src , IplImage* dst);
double * mbys(double * im,int imW,int imH,double *tp,int tpW,int tpH)
{
	double * out=new double[imW*imH];
	memset(out, 0, imW*imH*sizeof(double));
	int i,j,m,n;
	#define im(ROW,COL) im[imW*(ROW)+(COL)]
	#define tp(ROW,COL) tp[tpW*(ROW)+(COL)]
	#define out(ROW,COL) out[imW*(ROW)+(COL)]
	double a;
	for(i=0;i<imH;i++)
		for(j=0;j<imW;j++)
		{
			a=0;
			//ȥ�������߽����
			if(i>int(tpH/2) && i<imH-int(tpH/2) && j>int(tpW/2) && j<imW-int(tpW/2))
				for(m=0;m<tpH;m++)
					for(n=0;n<tpW;n++)
					{
						a+=im(i+m-int(tpH/2),j+n-int(tpW/2))*tp(m,n);
					}
			out(i,j)=a;
		}
	return out;
}



void main()
{
	IplImage *Image1 = 0;
	IplImage *Image2 = 0;
	char* filename1 = (char*)"1.bmp";  //ע�����·��

	
	Image1 = cvLoadImage(filename1, 1);

	IplImage* copImg1 = cvCloneImage(Image1);


	
	
	BOOL* corner1 = Harris(Image1,copImg1);
	
	printf("ͼһ�����㹲 %d �� \n",totalCorner);




	cvNamedWindow( filename1, 1 );
	cvShowImage( filename1, copImg1); 




    cvReleaseImage(&Image1);
	cvReleaseImage(&copImg1);

	cvWaitKey(0); 
}