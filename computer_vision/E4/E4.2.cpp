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

	int a;  //�˲����ڿ����Ϊ����
	cout << "please enter the width(odd number) of filter window:" << endl;
	cin >> a;
	int w = (a - 1) / 2;
	//�߽���չΪsrc1
	Mat src1;
	copyMakeBorder(src, src1, w + 1, w, w + 1, w, IPL_BORDER_REFLECT);
	cout << "ԭͼ��С:" << src.size() << endl;
	cout << "��չ֮��:" << src1.size() << endl;
	imshow("�߽���չ", src1);
	waitKey(0);

	Mat dst(src.size(), src.type());
	//����ͼ ����ɨ�� ���򣺴������ҡ���������
	Mat integrogram(src1.size(), CV_32FC3, Scalar(0.0f, 0.0f, 0.0f));
	//�з����ϵĻ��֣��õ���ͼ��ÿ�����ص��ֵ��ԭͼͬλ�����Ϸ��������ص�ֵ�ĺ�
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
	//��ǰһ��ɨ��õ���ͼ��Ļ����ϣ���ÿ�����ص��ֵ������������ص��ֵ��Ϊ�����ص����ֵ��ɨ��������õ�����ͼ
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
				dst.at<Vec3b>(u, v)[k] = (S.at<Vec3f>(u + 2*w+1, v + 2*w+1)[k] + S.at<Vec3f>(u, v)[k] - S.at<Vec3f>(u + 2*w+1, v)[k] - S.at<Vec3f>(u, v + 2*w+1)[k]) / z;   //��Ҫ�뵱Ȼ��һ��Ҫ��ȫ���
			}
		}
	}

	cout << "�˲�֮�����յ�ͼ��" << dst.size() << endl;
	imshow("meanfiltering", dst);
	waitKey(0);
}