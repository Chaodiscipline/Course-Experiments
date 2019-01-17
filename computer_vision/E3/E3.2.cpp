#include <iostream>
#include <cmath>
#include <opencv2/core/core.hpp>  
#include <opencv2/highgui/highgui.hpp>

using namespace cv;
using namespace std;


int main()
{
	Mat src = imread("D:\\opencv pictureS\\E3.jpg");
	Mat dst(src.rows, src.cols, src.type());
	void anamorphose(Mat src, Mat dst);
	anamorphose(src, dst);
	imshow("src", src);
	waitKey(0);        //��������waitKey��0��һ��������󣬷��������벻ִ��
	return 0;
}

void anamorphose(Mat src, Mat dst)
{
	double x0 = 0.5*dst.rows;
	double y0 = 0.5*dst.cols;   //ͼ�����ĵ�����
	for(int x=0;x<dst.rows;x++)
		for (int y = 0; y < dst.cols; y++)
		{
			double xc = (x - x0) / x0;
			double yc = (y - y0) / y0;    //���Ĺ�һ������
			double r = sqrt(pow(xc, 2) + pow(yc, 2));
			if (r >= 1)
				for (int k = 0; k < 3; k++)
				{
					dst.at<Vec3b>(x, y)[k] = src.at<Vec3b>(x, y)[k];
				}
			else
			{
				double theta = pow((1 - r), 2);

				for (int k = 0; k < 3; k++)
				{
					dst.at<Vec3b>((xc*cos(theta) - yc * sin(theta))*x0 + x0, (xc*sin(theta) + yc * cos(theta))*y0 + y0);
					//dst.at<Vec3b>(x,y)[k] = src.at<Vec3b>((xc*cos(theta)+yc*sin(theta))*x0+x0, (yc * cos(theta)-xc*sin(theta))*y0+y0)[k];   //����ɲ��ֵ�ȱʧ
				}
			}		
		}
	imshow("dst", dst);
	waitKey(0);
}
