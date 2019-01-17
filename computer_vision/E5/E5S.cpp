#include <iostream>  
#include <cmath>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/imgproc.hpp>
using namespace cv;
using namespace std;

Rect rect; //ѡ�Ŀ�
Point tl; //������Ͻǣ�ÿ����굥��ʱ��¼һ��
int xx, yy;  //������½�����

int main()
{
	VideoCapture cap("C:\\Users\\hp\\Desktop\\CVʵ��\\E5\\��·�����Ƶ\\1.avi");
	Mat frame; //֡
	namedWindow("�������");
	void mouseEvent(int event, int x, int y, int flags, void* userdata);
	setMouseCallback("�������", mouseEvent);
	
	cap >> frame;  //��ȡ֡
	imshow("�������", frame);
	waitKey(4000);

	int a[256][3] = { 0 };
	for (int k = 0; k < 3; k++)
	{
		for (int i = tl.y; i < yy; i++)
			for (int j = tl.x; j < xx; j++)
			{
				a[frame.at<Vec3b>(i, j)[k]][k]++;
			}
	}

	rectangle(frame, rect, { 0,255,255 }, 3);
	imshow("�������", frame);
	waitKey(1000);

	cout << "���Ͻ�����" << tl.x << ", " << tl.y << endl;
	int count = 0;
	int w = xx - tl.x;  //���ο�Ŀ��
	int h = yy - tl.y;  //���ο�ĸ߶�
	int x0 = tl.x;      
	int y0 = tl.y;      //������Ͻ�����      //Ŀ����ο�����Ͻ�����

	while (count<2000) 
	{
		cap >> frame;  //��ȡ֡
		for (int xxx = x0 - 30; xxx < x0+30; xxx++)  //����x0��y0 ��Ӧ����ǰһ֡���ο�����Ͻ������
		{
			if (xxx <= 0)
				xxx = 0;
			for (int yyy = y0 - 30  ; yyy < y0+30; yyy++)
			{
				if (yyy <= 0)
					yyy = 0;
				int b[256][3] = { 0 };
				for (int k = 0; k < 3; k++)
					for (int i = yyy; i < yyy + h; i++)
						for (int j = xxx; j < xxx + w; j++)
						{
							b[frame.at<Vec3b>(i, j)[k]][k]++;
						}

				double  c1 = 0, c2 = 0, d = 0;
				for (int m = 0; m < 256; m++)
				{
					for (int n = 0; n < 3; n++)
					{
						d += b[m][n]*a[m][n];
						c1 += a[m][n] * a[m][n];
						c2 += b[m][n] * b[m][n];
					}
				}
				double d1 = sqrt(c1), d2 = sqrt(c2);
				double ncos = d / (d1*d2);
				double deltaD = (d1 - d2) / d1;
				if (ncos > 0.7) 
				{
					x0 = xxx;
					y0 = yyy;
					cout << "�¿�λ��("<<xxx << "," << yyy << ")" << " : " << "ncos= " << ncos <<"\t"<<"deltaD= "<<deltaD<< endl;
					goto paint;
				}
			}
		}
	paint:
		if (x0 < frame.cols - w && y0 < frame.rows - h)
		{
			rect = { x0,y0,w,h };
			rectangle(frame, rect, { 0,255,255 }, 3);
		}
		else
		{
			return 0;
		}
		imshow("�������", frame);
		waitKey(100);
		count++;
	}
	return 0;
}

void mouseEvent(int event, int x, int y, int flags, void* userdata)
{
	if (event == EVENT_LBUTTONDOWN) { //ÿ����갴�¼�¼һ��
		tl = { x,y };
	}
	else if (event == EVENT_MOUSEMOVE && flags == EVENT_FLAG_LBUTTON) {   //��������϶�����
		rect = { tl.x,tl.y,x - tl.x,y - tl.y };
		xx = x;
		yy = y;  //���������ɿ�ǰ������ֵ�����ο����½ǵ����꣩����xx��yy
	}
}
