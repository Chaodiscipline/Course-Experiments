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
	int a = int(6 * sigma - 1);   //aΪ�˲����ڵĿ�ȣ��뱣֤Ϊ����
	cout << "the width of filter window: a = " << a << endl;
	int r = (a - 1) / 2;   //��������ں�������л����õ�
	Mat dst0(src.size(), src.type(),Scalar(0,0,0));  //ֻ�ǿ�����һ��src.size��С�Ĵ洢�ռ䣬������������ҵģ�������ʹ�á�+=��ǰ��Ҫ��ʼ��

	double core[11];   //����һά��˹�˲���
	for (int k = 0; k < (a + 1) / 2; k++)
	{
		core[k] = core[a - 1 - k] = exp(-pow((k - r), 2) / (2 * sigma*sigma));
		cout << "core[" << k << "]=" << "core[" << a - 1 - k << "]=" << core[k] << endl;
	}

	double s = 0;
	for (int k = 0; k < a; k++)
		s += core[k];
	cout << s << endl;

	//�и�˹�˲�
	for (int i = 0; i < dst0.rows; i++)
	{
		for (int j = 0; j < dst0.cols; j++)
		{
			for (int p = 0; p < a; p++)
			{
				if (j + p - r < 0 || j + p - r >= dst0.cols)  //���ڱ߽總�������ص㣬����ͼ���ⲿ���˲��˶�Ӧ�����ص��ù���������j�ԳƵ����ص����
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

	//�и�˹�˲�  ��Ҫ����һ���µ�Mat��������ԭMat�ϻ�����ۻ���Ч��
	Mat dst1(dst0.size(), dst0.type(),Scalar(0,0,0));
	for (int i = 0; i < dst1.rows; i++)
	{
		for (int j = 0; j < dst1.cols; j++)
		{
			for (int p = 0; p < a; p++)
			{
				if (i + p - r < 0 || i + p - r >= dst0.rows)  //���ڱ߽總�������ص㣬����ͼ���ⲿ���˲��˵����ص��ù���������i�ԳƵ����ص����
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