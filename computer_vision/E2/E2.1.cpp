#include <iostream>  
#include <math.h>
#include <opencv2/core/core.hpp>  
#include <opencv2/highgui/highgui.hpp>  
using namespace std;
using namespace cv;

int w ;		//w��sigmoid�����Ĳ���
Mat I0 = imread("D:\\opencv pictures\\I0.jpg");
Mat fI0;
void callback(int, void *);
int main()
{
	void on_ThreshChange(int, void*);
	namedWindow("constrast");
	createTrackbar("����w", "constrast", &w, 100, callback);
	callback(0, 0);
	return 0;
}

void callback(int, void *)
{
	void gray_transform(float *data, int width, int height, int step);
	I0.convertTo(fI0, CV_32FC3, 1.0 / 255, 0.5); //���Ҷ�������uchar��Ϊfloat��������ֵ��һ����0~1
	float *img = &fI0.at<Vec3f>(0, 0)[0];
	gray_transform(img, 1080, I0.rows, 1080 * 3);		//�Ҷȱ任
	imshow("constrast", fI0);
	waitKey();
}
void gray_transform(float *data, int width, int height, int step)
{
	float Transform(float);
	float *row = data;
	for (int yi = 0; yi < height; ++yi, row += step)
	{
		float *px = row;
		for (int xi = 0; xi < width * 3; ++xi, px++)
		{
			*px = Transform(*px);
		}
	}
}

float Transform(float p)
{
	float s = 1 / (1 + exp(-w*(p * 20 - 10)/100));		//sigmoid����
	return s;
}