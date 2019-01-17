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
	cout << "��������ƴ�ӵ�ͼƬ����(����1��:" << endl;
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
		cout << "����ƴ��......." << filename << endl;
		picture = imread("C:\\Users\\19843\\Desktop\\CVʵ��\\E10\\"+filename);
		imgs.push_back(picture);
	}
	cout << "......" << endl;
	Mat pano;
	Stitcher stitcher = Stitcher::createDefault(false);
	Stitcher::Status status = stitcher.stitch(imgs, pano);
	if (status != Stitcher::OK)
	{
		cout << "�޷�ƴ�ӣ�" << endl;
		return -1;
	}
	imshow("Stitch", pano);
	waitKey(0);
	imwrite("result.jpg", pano);
	return 0;
}
*/


/*
//������img3ƴ��

//1.SIFT��������ȡ����detect()����
Mat img3 = imread("C:\\users\\19843\\Desktop\\CVʵ��\\E10\\3.png", CV_LOAD_IMAGE_COLOR);    //img3

Mat dstImg3;
vector<KeyPoint> keyPoints3;
siftDetector.detect(img3, keyPoints3);
drawKeypoints(img3, keyPoints3, dstImg3);

//2.������������(��������)��ȡ����compute()����
Mat description3;
descriptor.compute(img3, keyPoints3, description3);

//3.ʹ�ñ���ƥ�������б���ƥ�䡪��BruteForceMatcher���match()����
vector<DMatch> matches1; //����ƥ��������
matcher.match(description3, description2, matches1);//ʵ��������֮���ƥ��

//4.��ƥ��������ɸѡ������DMatch�ṹ���е�float���ͱ���distance����ɸѡ��
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
//5.����ƥ��������dr awMatches()
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