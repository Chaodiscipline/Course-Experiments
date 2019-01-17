#include <iostream>  
#include <cmath>
#include <opencv2/core/core.hpp>  
#include <opencv2/highgui/highgui.hpp>  
using namespace std;
using namespace cv;

int main()
{
	void Gaussian(Mat src, double sigma);
	Mat src = imread("D:\\opencv pictures\\M4.2.jpg");
	imshow("src", src);
	waitKey(0);
	double sigma;
	cout << "please enter sigma:" << endl;
	cout << "suggest 0.667,1,1.334,1.667,2, which are corresponding to width 3,5,7,9,11" << endl;
	cin >> sigma;
	Gaussian(src, sigma);

	return 0;
}

void Gaussian(Mat src, double sigma)
{
	int a = int(6 * sigma - 1);   //a为滤波窗口的宽度，须保证为奇数
	cout << "the width of filter window: a = " << a << endl;
	int r = (a - 1) / 2;   //这个变量在后面程序中会多次用到
	Mat dst0(src.size(), src.type(),Scalar(0,0,0));  //只是开辟了一个src.size大小的存储空间，里面的数据是乱的，所以在使用“+=”前需要初始化

	double core[11];   //计算一维高斯滤波核
	for (int k = 0; k < (a + 1) / 2; k++)
	{
		core[k] = core[a - 1 - k] = exp(-pow((k - r), 2) / (2 * sigma*sigma));
		cout << "core[" << k << "]=" << "core[" << a - 1 - k << "]=" << core[k] << endl;
	}

	double s = 0;
	for (int k = 0; k < a; k++)
		s += core[k];
	cout << s << endl;

	//行高斯滤波
	for (int i = 0; i < dst0.rows; i++)
	{
		for (int j = 0; j < dst0.cols; j++)
		{
			for (int p = 0; p < a; p++)
			{
				if (j + p - r < 0 || j + p - r >= dst0.cols)  //对于边界附近的像素点，落在图像外部的滤波核对应的像素点用关于列坐标j对称的像素点代替
				{
					dst0.at<Vec3b>(i, j)[0] += src.at<Vec3b>(i, j - p + r)[0] * core[p] / s;
					dst0.at<Vec3b>(i, j)[1] += src.at<Vec3b>(i, j - p + r)[1] * core[p] / s;
					dst0.at<Vec3b>(i, j)[2] += src.at<Vec3b>(i, j - p + r)[2] * core[p] / s;
				}
				else
				{
					dst0.at<Vec3b>(i, j)[0] += src.at<Vec3b>(i, j + p - r)[0] * core[p] / s;
					dst0.at<Vec3b>(i, j)[1] += src.at<Vec3b>(i, j + p - r)[1] * core[p] / s;
					dst0.at<Vec3b>(i, j)[2] += src.at<Vec3b>(i, j + p - r)[2] * core[p] / s;
				}
			}
		}
	}

	imshow("Gaussion filtering (row)", dst0);
	waitKey(0);

	//列高斯滤波  需要建立一个新的Mat，否则在原Mat上会产生累积的效果
	Mat dst1(dst0.size(), dst0.type(),Scalar(0,0,0));
	for (int i = 0; i < dst1.rows; i++)
	{
		for (int j = 0; j < dst1.cols; j++)
		{
			for (int p = 0; p < a; p++)
			{
				if (i + p - r < 0 || i + p - r >= dst0.rows)  //对于边界附近的像素点，落在图像外部的滤波核的像素点用关于行坐标i对称的像素点代替
				{
					dst0.at<Vec3b>(i, j)[0] += src.at<Vec3b>(i - p + r, j)[0] * core[p] / s;
					dst0.at<Vec3b>(i, j)[1] += src.at<Vec3b>(i - p + r, j)[1] * core[p] / s;
					dst0.at<Vec3b>(i, j)[2] += src.at<Vec3b>(i - p + r, j)[2] * core[p] / s;
				}
				else
				{
					dst1.at<Vec3b>(i, j)[0] += dst0.at<Vec3b>(i + p - r, j)[0] * core[p] / s;
					dst1.at<Vec3b>(i, j)[1] += dst0.at<Vec3b>(i + p - r, j)[1] * core[p] / s;
					dst1.at<Vec3b>(i, j)[2] += dst0.at<Vec3b>(i + p - r, j)[2] * core[p] / s;
				}
			}
		}
	}

	imshow("Gaussion filtering", dst1);
	waitKey(0);
}