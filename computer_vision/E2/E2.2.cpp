#include <iostream>  
#include <math.h>
#include <opencv2/core/core.hpp>  
#include <opencv2/highgui/highgui.hpp>  
#include <opencv2/opencv.hpp>		//用于滤波函数的包含头文件

using namespace std;
using namespace cv;

int main()
{
	const int T=10000;
	double s;
	Mat I = imread("D:\\opencv pictures\\I.png",-1);
	Mat B = imread("D:\\opencv pictures\\B.jpg");
	Mat result=Mat(I.rows, I.cols, CV_8UC1);
	Mat result1 = Mat(I.rows, I.cols, CV_8UC1);
	//Mat result = I.clone();  //四通道
	
	for (int i = 0; i < I.rows; i++)
	{
		for (int j = 0; j < I.cols; j++)
		{
			s = 0;
			for (int k = 0; k < 3; k++)
			{
				s += pow((I.at<Vec4b>(i,j)[k] - B.at<Vec3b>(i,j)[k]), 2);  //.at后（i，j）表示第i行第j列的像素点，与（x，y）坐标相反
			}
			if (s > T)
				//result.at<Vec4b>(i,j) = Vec4b(255,255,255, 255);	//四通道 
				result.at<uchar>(i, j) = 255;
			else
				//result.at<Vec4b>(i,j) = Vec4b(0,0,0, 255);		//四通道 
				result.at<uchar>(i, j) = 0;
		}
	}
	medianBlur(result, result1, 5);    //中值滤波
	namedWindow("background_Subtract");
	imshow("background_Subtract", result);
	imshow("blur", result1);
	waitKey(0);
	return 0;
}

