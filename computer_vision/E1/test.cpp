#include <iostream>  
#include <opencv2/core/core.hpp>  
#include <opencv2/highgui/highgui.hpp>  
using namespace std;
using namespace cv;

int main()
{

	Mat inimg = imread("D:\\opencv pictures\\a.png", CV_LOAD_IMAGE_UNCHANGED); // ��ȡ͸��ͨ��

/*
// ���RGBA��ֵ
	cout << (int)inimg.at<Vec4b>(0, 0)[0] <<endl
		<< (int)inimg.at<Vec4b>(0, 0)[1] <<endl
		<< (int)inimg.at<Vec4b>(0, 0)[2] << endl
		<< (int)inimg.at<Vec4b>(0, 0)[3] << endl;
*/
	Mat ma1(inimg.rows, inimg.cols, CV_8UC1);
	/*
	CV_8UC  1 ��8λ��ͨ����Ϊ�Ҷ�ͼ��
		   1�ǵ�ͨ��
	CV_64UC3  64λ��ͨ��
	*/
	for (int i = 0; i < inimg.rows; i++)
	{
		for (int j = 0; j < inimg.cols; j++)
		{
			ma1.at<uchar>(i, j) = inimg.at<Vec4b>(i, j)[3];
		}
	}
	namedWindow("alpha channel", 0);
	imshow("alpha channel", ma1);
	waitKey(0);

	Mat frontView = inimg;
	//imread("D:\\opencv pictures\\a.png", CV_LOAD_IMAGE_UNCHANGED);
	Mat backGround = imread("D:\\opencv pictures\\IMG_0041.jpg", CV_LOAD_IMAGE_UNCHANGED);
	Mat mat(frontView.rows, frontView.cols, CV_8UC4);
	for (int i = 0; i < frontView.rows; i++)
	{
		for (int j = 0; j < frontView.cols; j++)
		{
			//double temp = frontView.at<Vec4b>(i, j)[3] / 255;
			double temp = frontView.at<Vec4b>(i, j)[3] / 255.00;//���پ�ݣ����Ӿ���

			mat.at<Vec4b>(i, j)[0] = (1 - temp)*backGround.at<Vec4b>(i + 100, j + 100)[0] + temp * frontView.at<Vec4b>(i, j)[3];
			mat.at<Vec4b>(i, j)[1] = (1 - temp)*backGround.at<Vec4b>(i + 100, j + 100)[1] + temp * frontView.at<Vec4b>(i, j)[3];
			mat.at<Vec4b>(i, j)[2] = (1 - temp)*backGround.at<Vec4b>(i + 100, j + 100)[2] + temp * frontView.at<Vec4b>(i, j)[3];
			mat.at<Vec4b>(i, j)[3] = (1 - temp)*backGround.at<Vec4b>(i + 100, j + 100)[3] + temp * frontView.at<Vec4b>(i, j)[3];


		}
	}
	namedWindow("alpha�ϳ�");
	imshow("alpha�ϳ�", mat);
	waitKey(0);
	return 0;
}
