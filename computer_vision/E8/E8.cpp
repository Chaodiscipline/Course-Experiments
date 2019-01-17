#include <iostream>  
#include <cmath>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;
using namespace std;

int main()
{
	Mat srcImage = imread("C:\\Users\\hp\\Desktop\\CV实验\\E8\\I2.jpg");
	imshow("【原图】", srcImage);

	//因为角点检测的输入图像是单通道的，所以需要一个灰度图
	Mat grayImage;
	cvtColor(srcImage, grayImage, CV_BGR2GRAY);

	//进行Harris角点检测
	Mat dstImage;
	cornerHarris(grayImage, dstImage, 2, 3, 0.01);
	//函数调用后，得到的是  一组被检测到的角点的灰度值的集合（dstImage是角点灰度值的矩阵）
	//而且灰度值很小，所以如果直接显示，肉眼将无法分辨


	//阀值后显示
	Mat thredImage;
	srcImage.copyTo(thredImage);
	//threshold(dstImage, thredImage, 0.0001, 255, CV_THRESH_BINARY);
	float threshold1 = 0.0001;
	for (int i = 0; i < grayImage.rows; i++)
		for (int j = 0; j < grayImage.cols; j++)
		{
			if (dstImage.at<float>(i, j) > threshold1)
			{
				Point heart(j, i);
				circle(thredImage, heart, 4, Scalar(0, 0, 0));
			}
		}
	imshow("cornerHarris函数检测", thredImage);


	Mat Ix;
	Mat Iy;
	Sobel(grayImage, Ix, CV_32F, 1, 0, 3);
	Sobel(grayImage, Iy, CV_32F, 0, 1, 3);
	//imshow("Ix", Ix);
	//imshow("Iy", Iy);


	Mat squareIx(Ix.size(),Ix.type());
	Mat squareIy(Iy.size(),Iy.type());
	Mat IxIy(Ix.size(), Ix.type());

	for (int i = 0;i < grayImage.rows; i++)
		for (int j = 0; j < grayImage.cols; j++)
		{
			squareIx.at<float>(i, j) = pow(Ix.at<float>(i, j), 2);
			squareIy.at<float>(i, j) = pow(Iy.at<float>(i, j), 2);
			IxIy.at<float>(i, j) = Ix.at<float>(i, j) * Iy.at<float>(i, j);
		}

	//imshow("squareIx", squareIx);
	//imshow("squareIy", squareIy);
	//imshow("IxIy", IxIy);

	Mat g_squareIx(Ix.size(), Ix.type());
	Mat g_squareIy(Iy.size(), Iy.type());
	Mat g_IxIy(Ix.size(), Ix.type());
	GaussianBlur(squareIx, g_squareIx, Size(7,7), 0);
	GaussianBlur(squareIy, g_squareIy, Size(7,7), 0);
	GaussianBlur(IxIy, g_IxIy, Size(7,7), 0);
	//imshow("g_squareIx", g_squareIx);
	//imshow("g_squareIy", g_squareIy);
	//imshow("IxIy", IxIy);
	
	float alpha = 0.05;

	Mat R(Ix.size(), Ix.type());
	double max = 0;
	for (int i = 0; i < grayImage.rows; i++)
		for (int j = 0; j < grayImage.cols; j++)
		{
			R.at<float>(i, j) = g_squareIx.at<float>(i, j)*g_squareIy.at<float>(i, j) - IxIy.at<float>(i, j)*IxIy.at<float>(i, j) - alpha * pow((g_squareIx.at<float>(i, j) + g_squareIy.at<float>(i, j)), 2);
			if (R.at<float>(i, j) > max)
				max = R.at<float>(i, j);
		}
	imshow("corner response", R);
	float threshold2 = max *0.4;
	for (int i = 0; i < grayImage.rows; i++)
		for (int j = 0; j < grayImage.cols; j++)
		{
			if (R.at<float>(i, j) > threshold2)
			{
				Point heart(j, i);
				circle(srcImage, heart, 4, Scalar(0, 0, 255));
			}
		}
	imshow("cornerDetect", srcImage);
	waitKey(0);
	return 0;
}