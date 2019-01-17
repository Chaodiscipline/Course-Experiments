#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main()
{
	void MeanFilter(Mat, Mat, int);
	Mat src = imread("D:\\opencv pictures\\M4.jpg");
	imshow("src", src);
	waitKey(0);

	int a;  //滤波窗口宽度须为奇数
	cout << "please enter the width(odd number) of filter window:" << endl;
	cin >> a;
	int w = (a - 1) / 2;
	//边界扩展为src1
	Mat src1;
	copyMakeBorder(src, src1, w + 1, w, w + 1, w, IPL_BORDER_REFLECT);
	cout << "原图大小:" << src.size() << endl;
	cout << "扩展之后:" << src1.size() << endl;
	imshow("边界扩展", src1);
	waitKey(0);

	Mat dst(src.size(), src.type());
	//积分图 两遍扫描 方向：从左向右、从上向下
	Mat integrogram(src1.size(), CV_32FC3, Scalar(0.0f, 0.0f, 0.0f));
	//列方向上的积分，得到的图像每个像素点的值是原图同位置其上方所有像素点值的和
	for (int k = 0; k < 3; k++)
	{
		for (int v = 0; v < integrogram.cols; v++)
		{
			integrogram.at<Vec3f>(0, v)[k] = src1.at<Vec3b>(0, v)[k];
		}
		for (int v = 0; v < integrogram.cols; v++)
		{
			for (int u = 1; u < integrogram.rows; u++)
			{
				integrogram.at<Vec3f>(u, v)[k] = integrogram.at<Vec3f>(u - 1, v)[k] + src1.at<Vec3b>(u, v)[k];
			}
		}
	}
	//在前一次扫描得到的图像的基础上，将每个像素点的值加上其左边像素点的值作为该像素点的新值，扫描结束即得到积分图
	for (int k = 0; k < 3; k++)
	{
		for (int v = 1; v < integrogram.cols; v++)
		{
			for (int u = 0; u < integrogram.rows; u++)
			{
				integrogram.at<Vec3f>(u, v)[k] += integrogram.at<Vec3f>(u, v-1)[k];
			}
		}
	}

	MeanFilter(integrogram, dst, w);

	return 0;
}

void MeanFilter(Mat S, Mat dst, int w)
{
	int z = (2*w+1) * (2*w+1);
	for (int k = 0; k < 3; k++)
	{

		for (int u = 0; u < dst.rows; u++)   
		{
			for (int v = 0; v < dst.cols; v++)
			{
				dst.at<Vec3b>(u, v)[k] = (S.at<Vec3f>(u + 2*w+1, v + 2*w+1)[k] + S.at<Vec3f>(u, v)[k] - S.at<Vec3f>(u + 2*w+1, v)[k] - S.at<Vec3f>(u, v + 2*w+1)[k]) / z;   //不要想当然，一定要完全理解
			}
		}
	}

	cout << "滤波之后最终的图像" << dst.size() << endl;
	imshow("meanfiltering", dst);
	waitKey(0);
}