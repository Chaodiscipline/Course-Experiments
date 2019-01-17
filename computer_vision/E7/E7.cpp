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
	Mat src = imread("C:\\Users\\hp\\Desktop\\CVʵ��\\E7\\I3.jpg");
	Mat src_gray;
	cvtColor(src, src_gray, CV_BGR2GRAY); //ת��Ϊ�Ҷ�ͼ
	imshow("src_gray", src_gray);
	Mat edge(src.size(), src.type());
	Canny(src_gray, edge, 70, 140);
	//ǰ�������������ǵ����롢���ͼ��8λ�Ҷ�ͼ�����������ĸ������ֱ������ǵ�MinVal��MaxVal�������������aperture_size���������ڲ���ͼ���ݶȵ�Sobel�˵Ĵ�С��Ĭ���������3��
	//���һ��������L2gradient ����ָ�������ݶȷ�ֵ�Ĺ�ʽ�������True����ʹ�ø���ȷ�ķ���sqrt(Gx^2+Gy^2)��������ʹ�����������|Gx|+|Gy|��Ĭ������£�����False��
	imshow("canny��Ե���", edge);

	// ���x��y�����һ��΢��
	Mat sobelx;
	Mat sobely;
	Sobel(src_gray, sobelx, CV_32F, 1, 0, 3);
	Sobel(src_gray, sobely, CV_32F, 0, 1, 3);

	// ����ݶȺͷ���
	Mat norm;
	Mat dir;
	cartToPolar(sobelx, sobely, norm, dir);  // ֱ������ת��Ϊ�����꣬dir��ÿһ���ص�ĽǶ�0~2pi

	//������ά��̬���鲢��ʼ��
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
	//��ʼ��
	for (int i = 0; i < src.rows; ++i)
		for (int j = 0; j < src.cols; ++j)
			for (int k = 0; k < src.rows / 2 + 1; k++)
			{
				H[i][j][k] = 0;
			}

	Mat dst(src_gray.size(), src_gray.type(),Scalar(0,0,0));
	void paint(int, int, int, Mat, Mat);

	//ͶƱ
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
	
	//��ͼ
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

	//�ͷŶ�̬�����ռ�ÿռ�
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