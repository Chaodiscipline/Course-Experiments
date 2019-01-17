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
	Mat src = imread("C:\\Users\\hp\\Desktop\\CV实验\\E7\\I3.jpg");
	Mat src_gray;
	cvtColor(src, src_gray, CV_BGR2GRAY); //转变为灰度图
	imshow("src_gray", src_gray);
	Mat edge(src.size(), src.type());
	Canny(src_gray, edge, 70, 140);
	//前两个参数是我们的输入、输出图像（8位灰度图）。第三、四个参数分别是我们的MinVal和MaxVal。第五个参数是aperture_size。它是用于查找图像梯度的Sobel核的大小。默认情况下是3。
	//最后一个参数是L2gradient ，它指定了求梯度幅值的公式。如果是True，它使用更精确的方程sqrt(Gx^2+Gy^2)，否则它使用这个函数：|Gx|+|Gy|。默认情况下，它是False。
	imshow("canny边缘检测", edge);

	// 求得x和y方向的一阶微分
	Mat sobelx;
	Mat sobely;
	Sobel(src_gray, sobelx, CV_32F, 1, 0, 3);
	Sobel(src_gray, sobely, CV_32F, 0, 1, 3);

	// 求得梯度和方向
	Mat norm;
	Mat dir;
	cartToPolar(sobelx, sobely, norm, dir);  // 直角坐标转换为极坐标，dir中每一像素点的角度0~2pi

	//建立三维动态数组并初始化
	int ***H;
	H = new int **[src.rows];
	for (int i = 0; i < src.rows; ++i)
	{
		H[i] = new int *[src.cols];
		for (int j = 0; j < src.cols; ++j)
		{
			H[i][j] = new int[src.rows/2+1];
		}
	}
	//初始化
	for (int i = 0; i < src.rows; ++i)
		for (int j = 0; j < src.cols; ++j)
			for (int k = 0; k < src.rows / 2 + 1; k++)
			{
				H[i][j][k] = 0;
			}

	Mat dst(src_gray.size(), src_gray.type(),Scalar(0,0,0));
	void paint(int, int, int, Mat, Mat);

	//投票
	int a, b;
	int a1 = 0, b1 = 0, r1 = 0;
	for ( int i = 0; i < edge.rows; i++)
		for (int j = 0; j < edge.cols; j++)
		{
			if (edge.at<uchar>(i, j) != 0)
			{
				for (int r = 1; r < src.rows / 2 + 1; r++)
				{

					a = i - r * sin(dir.at<float>(i,j));
					b = j - r * cos(dir.at<float>(i,j));
					if (a >= 0 && a < edge.rows-1 && b >= 0 && b < edge.cols-1)
					{
						H[a][b][r] += 1;
					}
				}
			}
		}
	
	//画图
	for (int a = 0; a < src.rows; a++)
		for (int b = 0; b < src.cols; b++)
			for (int r = 10; r < src.rows / 2 + 1; r++)
			{
				if (H[a][b][r] > 15)
				{
					cout << "H[" << a << "][" << b << "][" << r << "] = "<< H[a][b][r] << endl;
					a1 = a;
					b1 = b;
					r1 = r;
					paint(a1, b1, r1, dst, src);
				}
			}

	//释放动态数组的占用空间
	for (int i = 0; i < src.rows; ++i)
	{
		for (int j = 0; j < src.cols; ++j)
			delete[]H[i][j];
		delete[]H[i];
	}
	delete[]H;

	cout << "end" << endl;
	imshow("HoughCircles", dst);
	imshow("Hough Circles On Src", src);
	waitKey(0);
	return 0;
}

void paint(int a1, int b1, int r1, Mat dst, Mat src)
{
	Point heart(b1, a1);
	for (int i = 0; i < dst.rows; i++)
		for (int j = 0; j < dst.cols; j++)
		{
			circle(src, heart, r1, Scalar(0,0,255));
			circle(dst, heart, r1, Scalar(255,255,255));
		}
}