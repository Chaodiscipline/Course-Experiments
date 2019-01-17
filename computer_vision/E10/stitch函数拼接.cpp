/*
#include <iostream>  
#include <fstream>  
#include "opencv2/highgui/highgui.hpp"  
#include "opencv2/stitching/stitcher.hpp"  
using namespace std;
using namespace cv;

int main(int argc, char* argv[])
{
	int n;
	cout << "请输入想拼接的图片数量(大于1）:" << endl;
	cin >> n;
	vector<Mat> imgs;
	Mat picture;
	for (int k = 1; k <= n; k++)
	{
		stringstream stream;
		string str;
		stream << k;
		stream >> str;
		string filename = str + ".png";
		cout << "正在拼接......." << filename << endl;
		picture = imread("C:\\Users\\19843\\Desktop\\CV实验\\E10\\"+filename);
		imgs.push_back(picture);
	}
	cout << "......" << endl;
	Mat pano;
	Stitcher stitcher = Stitcher::createDefault(false);
	Stitcher::Status status = stitcher.stitch(imgs, pano);
	if (status != Stitcher::OK)
	{
		cout << "无法拼接！" << endl;
		return -1;
	}
	imshow("Stitch", pano);
	waitKey(0);
	imwrite("result.jpg", pano);
	return 0;
}
*/


/*
//继续与img3拼接

//1.SIFT特征点提取——detect()方法
Mat img3 = imread("C:\\users\\19843\\Desktop\\CV实验\\E10\\3.png", CV_LOAD_IMAGE_COLOR);    //img3

Mat dstImg3;
vector<KeyPoint> keyPoints3;
siftDetector.detect(img3, keyPoints3);
drawKeypoints(img3, keyPoints3, dstImg3);

//2.特征点描述符(特征向量)提取——compute()方法
Mat description3;
descriptor.compute(img3, keyPoints3, description3);

//3.使用暴力匹配器进行暴力匹配——BruteForceMatcher类的match()方法
vector<DMatch> matches1; //定义匹配结果变量
matcher.match(description3, description2, matches1);//实现描述符之间的匹配

//4.对匹配结果进行筛选（依据DMatch结构体中的float类型变量distance进行筛选）
minDistance = 100;
maxDistance = 0;
for (int i = 0; i < matches1.size(); i++)
{
	if (matches1[i].distance < minDistance)
		minDistance = matches1[i].distance;
	if (matches1[i].distance > maxDistance)
		maxDistance = matches1[i].distance;
}
//cout << "minDistance: " << minDistance << endl;
//cout << "maxDistance: " << maxDistance << endl;
vector<DMatch> goodMatches1;
for (int i = 0; i < matches1.size(); i++)
{
	if (matches1[i].distance < 2 * minDistance)
	{
		goodMatches1.push_back(matches1[i]);
	}
}
//5.绘制匹配结果——dr awMatches()
//Mat dstImg4;
//drawMatches(img3, keyPoints3, img2, keyPoints2, goodMatches1, dstImg4);
//imshow("match", dstImg3);
//waitKey(0);

//findHomography
vector<Point2f> img3_pts;
for (vector<DMatch>::iterator it = goodMatches.begin(); it != goodMatches.end(); ++it)
{
	img3_pts.push_back(keyPoints3[it->queryIdx].pt);
}
Mat H1 = findHomography(img3_pts, img2_pts, CV_RANSAC);
cout << H1 << endl;

Mat homo2;
warpPerspective(img3, homo2, H1, img2.size());
//imshow("homo1", homo1);
//waitKey(0);

for (int i = 0; i < img2.cols; i++)
	for (int j = 0; j < img2.rows; j++)
	{
		Vec3b color_homo2 = homo2.at<Vec3b>(Point(i, j));
		Vec3b color_img2 = img2.at<Vec3b>(Point(i, j));
		if (norm(color_img2) == 0)
			img2.at<Vec3b>(Point(i, j)) = color_homo2;
	}
imshow("img2", img2);
waitKey(0);
*/