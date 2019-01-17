#include <iostream>
#include <cmath>
#include <opencv2/core/core.hpp>  
#include <opencv2/highgui/highgui.hpp>

using namespace cv;
using namespace std;


int main()
{
	const float Pi= 3.1415926;
	Mat I0 = imread("D:\\opencv pictureS\\E3.jpg");		//���Խ�I0�Ƶ�һ�����󴰿ڵ����룬�Ա�������ת������ͼƬ���ضϣ����ǵ���ת���Ĺ�Զ��ת�Ƕȹ���ʱ�Ի����ͼƬ�ض�
	Mat dst0(I0.rows*2+200 , I0.cols*2 , I0.type());
	void rotate(Mat src, Mat dst0, int x0, int y0, float angle);
	rotate(I0, dst0, 347, 0, -60*Pi/180);
	imshow("I0", I0);
	waitKey(0);        //��������waitKey��0��һ��������󣬷��������벻ִ��
	return 0;
}

void rotate(Mat src, Mat dst0,int x0, int y0, float angle)
{
	void WarpAffine(Mat , Mat , float S[2][3]);
	void mat33Multiple(float M1[3][3], float M2[3][3],float *p);
	float S1[3][3] = { {1,0,-x0},{0,1,-y0},{0,0,1} };
	float S2[3][3] = { {cos(angle),-sin(angle),0},{sin(angle),cos(angle),0},{0,0,1} };
	float S3[3][3] = { {1,0,x0},{0,1,y0},{0,0,1} };
	float R1[3][3] = { { },{ },{0,0,1} };
	float R2[2][3];  //���ĳ˻���2*3�����ʾ�����һ��һ����0��0��1��
	float *p1 = &R1[0][0];
	float *p2 = &R2[0][0];
	mat33Multiple(S2, S1, p1);
	mat33Multiple(S3, R1, p2);
	WarpAffine(src, dst0, R2);
}


void mat33Multiple(float M1[3][3], float M2[3][3],float *p)      //�������׷�����ˣ������ǰ���У�����p��ָ��ľ���
{
	*(p+0) = M1[0][0] * M2[0][0] + M1[0][1] * M2[1][0] + M1[0][2] * M2[2][0];
	*(p+1) = M1[0][0] * M2[0][1] + M1[0][1] * M2[1][1] + M1[0][2] * M2[2][1];
	*(p+2) = M1[0][0] * M2[0][2] + M1[0][1] * M2[1][2] + M1[0][2] * M2[2][2];
	*(p+3) = M1[1][0] * M2[0][0] + M1[1][1] * M2[1][0] + M1[1][2] * M2[2][0];
	*(p+4) = M1[1][0] * M2[0][1] + M1[1][1] * M2[1][1] + M1[1][2] * M2[2][1];
	*(p+5) = M1[1][0] * M2[0][2] + M1[1][1] * M2[1][2] + M1[1][2] * M2[2][2];
}

void WarpAffine(Mat src, Mat dst, float S[2][3])
{
	float t = 1 / (S[0][0] * S[1][1] - S[1][0] * S[0][1]);
	cout << t << endl;
	float M[3][3] = {
		{S[1][1],-S[0][1],S[0][1] * S[1][2] - S[0][2] * S[1][1]},
		{-S[1][0],S[0][0],S[1][0] * S[0][2] - S[0][0] * S[1][2]},
		{0,0,S[0][0] * S[1][1] - S[1][0] * S[0][1]}
	};                                                            //��ӳ��
	cout << M[0][0] << " " << M[0][1] << " " << M[0][2] << endl;
	cout << M[1][0] << " " << M[1][1] << " " << M[1][2] << endl;
	cout << M[2][0] << " " << M[2][1] << " " << M[2][2] << endl;
	float x1, y1;
	int x, y;
	for (int i = 0; i < dst.rows; i++)  //���һ�л����
	{
		for (int j = 0; j < dst.cols; j++)   //���һ�л����
		{
			x1 = t * (M[0][0] * i + M[0][1] * j + M[0][2]);
			y1 = t * (M[1][0] * i + M[1][1] * j + M[1][2]);
			//cout << i<<","<<j<<"   "<<x<< "," << y << endl;
			if (x1 >= 0 && x1 < src.rows-1&&y1 >= 0 && y1 < src.cols-1)
			{
				x = floor(x1);
				y = floor(y1);
				for (int k = 0; k < 3; k++)
				{
					dst.at<Vec3b>(i, j)[k] =  (1 - y1 + y)*(1 - x1 + x)*src.at<Vec3b>(x, y)[k]		//˫���Բ�ֵ
											+ (1 - y1 + y)*(x1 - x)*src.at<Vec3b>(x + 1, y)[k] 
											+ (y1 - y)*(1 - x1 + x)*src.at<Vec3b>(x, y + 1)[k] 
											+ (y1 - y)*(x1 - x)*src.at<Vec3b>(x + 1, y + 1)[k];
				}
			}
			
			if (x1 == src.rows - 1 && y1>=0&&y1<=src.cols-1)	//�߽紦�� ���ڽ���ֵ
			{
				x = int(x1+0.5);
				y = int(y1+0.5);
				//cout << x << "," << y << endl;
				dst.at<Vec3b>(i, j)[0] = src.at<Vec3b>(x, y)[0];
				dst.at<Vec3b>(i, j)[1] = src.at<Vec3b>(x, y)[1];
				dst.at<Vec3b>(i, j)[2] = src.at<Vec3b>(x, y)[2];
			}
			if (y1 == src.cols - 1 && x1 >= 0 && x1 < src.rows - 1)	//�߽紦�� ���ڽ���ֵ
			{
				x = int(x1 + 0.5);
				y = int(y1 + 0.5);
				//cout << x << "," << y << endl;
				dst.at<Vec3b>(i, j)[0] = src.at<Vec3b>(x, y)[0];
				dst.at<Vec3b>(i, j)[1] = src.at<Vec3b>(x, y)[1];
				dst.at<Vec3b>(i, j)[2] = src.at<Vec3b>(x, y)[2];
			}
		}
	}
	imshow("Affine",dst);
	waitKey(0);
}
