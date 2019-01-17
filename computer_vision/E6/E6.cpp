#include <iostream>  
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui.hpp>

using namespace std;
using namespace cv;

int main()
{
	Mat src = imread("C:\\Users\\19843\\Desktop\\CV实验\\E6\\picture1.png", IMREAD_GRAYSCALE);
	Mat dst(src.size(), CV_8UC3);
	//原图不是二值图，需要阈值处理
	for (int i = 0;i<src.rows;i++)
		for (int j = 0; j < src.cols; j++)
		{
			if (src.at<uchar>(i, j) >= 128)
				src.at<uchar>(i, j) = 255;
			else
				src.at<uchar>(i, j) = 0;
		}

	//标记不同连通域的二维数组
	int** label = new int*[src.rows];   //246*328
	for (int i = 0; i < src.rows; i++)
	{
		label[i] = new int[src.cols];
	}
	label[0][0] = 0;

	int minlabel;  
	int c = 0;
	//对第一行
	for (int j = 1; j < src.cols; j++)
	{
		if (src.at<uchar>(0, j) == src.at<uchar>(0, j - 1))
			label[0][j] = label[0][j - 1];
		else
		{
			c++;
			label[0][j] = c;
		}
	}
	for (int i = 1;i<src.rows;i++)
		for (int j = 0; j < src.cols; j++)
		{
			if (j == 0) //对第一列
			{
				if (src.at<uchar>(i, j) == src.at<uchar>(i - 1, j))
					label[i][j] = label[i - 1][j];
				else
				{
					c++;
					label[i][j] = c;
				}
			}
			else
			{
				if (src.at<uchar>(i, j) == src.at<uchar>(i, j - 1))
				{
					label[i][j] = label[i][j-1];
					if (src.at<uchar>(i, j) == src.at<uchar>(i - 1, j) && label[i][j - 1] != label[i - 1][j])
					{
						minlabel = (label[i][j - 1] < label[i - 1][j]) ? label[i][j - 1] : label[i - 1][j];
						for (int r = 0; r <= i; r++)
							for (int s = 0; s <= src.cols; s++)
							{
								if (label[r][s] == label[i][j - 1] || label[r][s] == label[i - 1][j])
									label[r][s] = minlabel;
							}
					}
				}
				else
				{
					if (src.at<uchar>(i, j) == src.at<uchar>(i - 1, j))
						label[i][j] = label[i-1][j];
					else
					{
						c++;
						label[i][j] = c;
					}
				}
			} 
		}
	cout <<"c = "<< c << endl;    //最后c为103

	int * a = new int[c];
	for (int i = 0; i <= c; i++)
	{
		a[i] = 0;
	}
	for (int i = 0; i < src.rows; i++)
		for (int j = 0; j < src.cols; j++)
		{
			a[label[i][j]]++;
		}
	int k = 0;
	for (int r = 0;r<=c;r++)
		if (a[r] != 0)
		{
			for (int i = 0; i < src.rows; i++)
				for (int j = 0; j < src.cols; j++)
				{
					if (label[i][j] == r)
					{
						label[i][j] = k;
					}
				}
			k++;
		}

	for (int i = 0; i<src.rows;i++)
		for (int j = 0; j < src.cols; j++)
		{
			switch (label[i][j])
			{
			case 0: dst.at<Vec3b>(i, j) = Vec3b(255, 0, 0); break;
			case 1: dst.at<Vec3b>(i, j) = Vec3b(0, 255, 0); break;
			case 2: dst.at<Vec3b>(i, j) = Vec3b(0, 0, 255); break;
			case 3: dst.at<Vec3b>(i, j) = Vec3b(0, 255, 255); break;
			case 4: dst.at<Vec3b>(i, j) = Vec3b(255, 0, 255); break;
			case 5: dst.at<Vec3b>(i, j) = Vec3b(255, 255, 0); break;
			case 6: dst.at<Vec3b>(i, j) = Vec3b(128, 0, 0); break;
			case 7: dst.at<Vec3b>(i, j) = Vec3b(0, 128, 0); break;
			case 8: dst.at<Vec3b>(i, j) = Vec3b(0, 0, 128); break;
			case 9: dst.at<Vec3b>(i, j) = Vec3b(0, 128, 128); break;
			default: dst.at<Vec3b>(i, j) = Vec3b(255, 255, 255);
			}
		}

	cv::namedWindow("dst", WINDOW_NORMAL);
	cv::imshow("dst", dst);


	int n = 0, maxindex = 0, t = a[1]; //假设标签为1的为最大连通域
	for (int i = 1; i < c; i++)
	{
		if (a[i] != 0)
			n++;
		cout << a[i] << endl;
		if (a[i] > t)
		{
			t = a[i];   //记录前景中最大连通域的大小
			maxindex = n;        //记录前景中最大连通域的标签
		}
	}
	cout << "最大连通域的标签为：" << n << endl;
	cout << "最大连通域的大小为：" << t << endl;

	Mat dst1(dst.size(), CV_8UC1);
	for (int i = 0; i < src.rows; i++)
		for (int j = 0; j < src.cols; j++)
		{
			if (label[i][j] == maxindex)
			{
				dst1.at<uchar>(i, j) = 255;
			}
			else
			{
				dst1.at<uchar>(i, j) = 0;
			}
		}

	namedWindow("dst1", WINDOW_NORMAL);
	imshow("dst1", dst1);
	
	Mat dst2(src.size(), CV_8UC1);
	Mat dst3(src.size(), CV_32SC1);
	distanceTransform(src, dst2, dst3, DIST_L2, 5, DIST_LABEL_PIXEL);
	cout << dst2.channels() << endl;
	cv::normalize(dst2,dst2, 0, 1, cv::NORM_MINMAX);
	imshow("distanceTransform", dst2);
	imshow("2Dlabel", dst3);
	waitKey(0);
	return 0;
}
