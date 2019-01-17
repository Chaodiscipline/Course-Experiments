#include "opencv2/opencv.hpp"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/nonfree/nonfree.hpp"//SIFT相关
#include "opencv2/legacy/legacy.hpp"//匹配器相关
#include <iostream>
using namespace cv;
using namespace std;

int main()
{
	Mat img1 = imread("C:\\users\\19843\\Desktop\\CV实验\\E10\\01.jpg", CV_LOAD_IMAGE_COLOR);
	Mat img2 = imread("C:\\users\\19843\\Desktop\\CV实验\\E10\\02.jpg", CV_LOAD_IMAGE_COLOR);
	Mat img3 = imread("C:\\users\\19843\\Desktop\\CV实验\\E10\\03.jpg", CV_LOAD_IMAGE_COLOR);
	resize(img1, img1, Size(421, 316));
	resize(img2, img2, Size(421, 316));
	resize(img3, img3, Size(421, 316));
	Mat trans_mat = (Mat_<double>(2, 3) << 1, 0, 600, 0, 1, 150);
	warpAffine(img2, img2, trans_mat, Size(3 * img2.cols+400, 2 * img2.rows));
	Mat stitch(Mat, Mat);
	Mat homoL = stitch(img1, img2);
	Mat homoR = stitch(img3, img2);

	for (int i = 0; i < img2.cols; i++)
		for (int j = 0; j < img2.rows; j++)
		{
			Vec3b color_img2 = img2.at<Vec3b>(Point(i, j));
			if (norm(color_img2) == 0)
				img2.at<Vec3b>(Point(i, j)) = homoL.at<Vec3b>(Point(i, j)) + homoR.at<Vec3b>(Point(i, j));
		}
	imwrite("C:\\users\\19843\\Desktop\\CV实验\\E10\\stitch_result1.jpg", img2);
	imshow("result", img2);
	waitKey(0);
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
	cout << "minDistance: " << minDistance << endl;
	cout << "maxDistance: " << maxDistance << endl;
	vector<DMatch> goodMatches;
	for (int i = 0; i < matches.size(); i++)
	{
		if (matches[i].distance < 2 * minDistance)
		{
			goodMatches.push_back(matches[i]);
		}
	}
	//5.绘制匹配结果——dr awMatches()
	//Mat dstImg3;
	//drawMatches(img1, keyPoints1, img2, keyPoints2, goodMatches, dstImg3);

	//findHomography
	vector<Point2f> img1_pts;
	vector<Point2f> img2_pts;
	for (vector<DMatch>::iterator it = goodMatches.begin(); it != goodMatches.end(); ++it) 
	{
		img1_pts.push_back(keyPoints1[it->queryIdx].pt);
		img2_pts.push_back(keyPoints2[it->trainIdx].pt);
	}
	Mat H = findHomography(img1_pts, img2_pts, CV_RANSAC);
	cout << H << endl;

	Mat homo;
	warpPerspective(img1, homo, H, img2.size());
	return homo;
}
