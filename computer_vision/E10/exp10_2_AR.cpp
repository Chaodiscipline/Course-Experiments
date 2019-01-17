#include "opencv2/opencv.hpp"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/nonfree/nonfree.hpp"
#include "opencv2/legacy/legacy.hpp"
#include <iostream>
using namespace cv;
using namespace std;

int main()
{
	Mat temp = imread("C:\\Users\\19843\\Desktop\\CV实验\\E10\\template1.jpg");
	VideoCapture cap1("C:\\Users\\19843\\Desktop\\CV实验\\E10\\video1.mp4");
	VideoCapture cap2("C:\\Users\\19843\\Desktop\\CV实验\\E10\\o_Trim.mp4");
	Mat frame;
	namedWindow("AR");
	Mat stitch(Mat, Mat);
	Mat H;
	Mat inset;

	VideoWriter write;
	string outVideo = "C:\\Users\\19843\\Desktop\\CV实验\\E10\\myResult.avi";
	int fps = 30;
	int height = static_cast<int>(cap1.get(CV_CAP_PROP_FRAME_HEIGHT));//读取视频的高度
	int width = static_cast<int>(cap1.get(CV_CAP_PROP_FRAME_WIDTH));//读取视频的宽度
	write.open(outVideo, CV_FOURCC('X', 'V', 'I', 'D'), fps, Size(width, height), true);
	int count = 0;
	while (1)
	{
		cap1 >> frame;
		cap2 >> inset;
		if (frame.cols==0||inset.cols==0)
			break;
		flip(frame, frame, -1);
		H = stitch(temp, frame);
		Mat homo;
		resize(inset, inset, temp.size());
		warpPerspective(inset, homo, H, frame.size());
		for (int i = 0; i < homo.cols; i++)
			for (int j = 0; j < homo.rows; j++)
			{
				Vec3b color_homo = homo.at<Vec3b>(Point(i, j));
				if (norm(color_homo) == 0)
					homo.at<Vec3b>(Point(i, j)) = frame.at<Vec3b>(Point(i, j));
			}
		imshow("AR", homo);
		waitKey(1);
		write.write(homo);
		cout << count << endl;
		count++;
	}

	return 0;
}

Mat stitch(Mat img1, Mat img2)
{
	//1.SIFT特征点提取——detect()方法
	SiftFeatureDetector siftDetector;
	vector<KeyPoint> keyPoints1, keyPoints2;
	siftDetector.detect(img1, keyPoints1);
	siftDetector.detect(img2, keyPoints2);

	//2.特征点描述符(特征向量)提取——compute()方法
	SiftDescriptorExtractor descriptor;  
	Mat description1, description2;
	descriptor.compute(img1, keyPoints1, description1);
	descriptor.compute(img2, keyPoints2, description2);

	//3.使用暴力匹配器进行暴力匹配——BruteForceMatcher类的match()方法
	BruteForceMatcher<L2<float>> matcher;//实例化暴力匹配器
	vector<DMatch> matches; //定义匹配结果变量
	matcher.match(description1, description2, matches);//实现描述符之间的匹配

	//4.对匹配结果进行筛选（依据DMatch结构体中的float类型变量distance进行筛选）
	float minDistance = 100;
	float maxDistance = 0;
	for (int i = 0; i < matches.size(); i++)
	{
		if (matches[i].distance < minDistance)
			minDistance = matches[i].distance;
		if (matches[i].distance > maxDistance)
			maxDistance = matches[i].distance;
	}

	vector<DMatch> goodMatches;
	for (int i = 0; i < matches.size(); i++)
	{
		if (matches[i].distance < 4 * minDistance)
		{
			goodMatches.push_back(matches[i]);
		}
	}

	//findHomography
	vector<Point2f> img1_pts;
	vector<Point2f> img2_pts;
	for (vector<DMatch>::iterator it = goodMatches.begin(); it != goodMatches.end(); ++it)
	{
		img1_pts.push_back(keyPoints1[it->queryIdx].pt);
		img2_pts.push_back(keyPoints2[it->trainIdx].pt);
	}
	Mat H = findHomography(img1_pts, img2_pts, CV_RANSAC);
	return H;
}