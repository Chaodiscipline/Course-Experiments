#include <iostream>  
#include <cmath>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/imgproc.hpp>
using namespace cv;
using namespace std;

Rect rect; //选的框
Point tl; //框的左上角，每次鼠标单击时记录一下
int xx, yy;  //框的右下角坐标

int main()
{
	VideoCapture cap("C:\\Users\\hp\\Desktop\\CV实验\\E5\\道路监控视频\\1.avi");
	Mat frame; //帧
	namedWindow("物体跟踪");
	void mouseEvent(int event, int x, int y, int flags, void* userdata);
	setMouseCallback("物体跟踪", mouseEvent);
	
	cap >> frame;  //读取帧
	imshow("物体跟踪", frame);
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
	imshow("物体跟踪", frame);
	waitKey(1000);

	cout << "左上角坐标" << tl.x << ", " << tl.y << endl;
	int count = 0;
	int w = xx - tl.x;  //矩形框的宽度
	int h = yy - tl.y;  //矩形框的高度
	int x0 = tl.x;      
	int y0 = tl.y;      //框的左上角坐标      //目标矩形框的左上角坐标

	while (count<2000) 
	{
		cap >> frame;  //读取帧
		for (int xxx = x0 - 30; xxx < x0+30; xxx++)  //不是x0，y0 而应该是前一帧矩形框的左上角坐标点
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
					cout << "新框位置("<<xxx << "," << yyy << ")" << " : " << "ncos= " << ncos <<"\t"<<"deltaD= "<<deltaD<< endl;
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
		imshow("物体跟踪", frame);
		waitKey(100);
		count++;
	}
	return 0;
}

void mouseEvent(int event, int x, int y, int flags, void* userdata)
{
	if (event == EVENT_LBUTTONDOWN) { //每次鼠标按下记录一次
		tl = { x,y };
	}
	else if (event == EVENT_MOUSEMOVE && flags == EVENT_FLAG_LBUTTON) {   //左键按下拖动拉框
		rect = { tl.x,tl.y,x - tl.x,y - tl.y };
		xx = x;
		yy = y;  //将鼠标左键松开前的坐标值（矩形框右下角的坐标）赋给xx，yy
	}
}
