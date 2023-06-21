#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include <cmath>

using namespace std;
using namespace cv;

//ֱ��ͼ���⻯
int inc = 750 / 256;
int arr[256] = { 0 };
float arr2[256] = { 0 };
float arr3[256] = { 0 };

//ֱ��ͼ���⻯
void origin_image_histogram(Mat&origin_image,Mat & Histogram,Mat & histogram,Mat &myMat)
{
	
	for (int i = 0; i < origin_image.rows; i++) {
		for (int j = 0; j < origin_image.cols; j++) {
			int index = (int)(origin_image.at<uchar>(i, j));
			arr[index]++;
		}
	}
	int max = 0;
	for (int i = 0; i < 255; i++) {
		if (arr[i] > max) {
			max = arr[i];
		}
	}
	for (int i = 0; i < 255; i++) {
		rectangle(Histogram, Point(inc * i, Histogram.rows), Point((inc * (i + 1) - 1), Histogram.rows - ((arr[i] * Histogram.rows) / (max))), Scalar(255, 255, 255, 0), CV_FILLED);
	}

	//PMF��������������������������ɢ����������ڸ��ض�ȡֵ�ϵĸ��ʡ�
	float total = origin_image.cols * origin_image.rows;
	for (int i = 0; i < 255; i++)
	{
		arr2[i] = float(arr[i]) / total;
	}
	arr3[0] = arr2[0];

	//CDF�ۻ��ֲ��������ֽзֲ��������Ǹ����ܶȺ����Ļ��֣�������ʾ��ɢ���������x�ĸ��ʷֲ���
	for (int i = 1; i < 255; i++)
	{
		arr3[i] = arr2[i] + arr3[i - 1];
	}
	for (int i = 0; i < origin_image.rows; i++) {
		for (int j = 0; j < origin_image.cols; j++) {

			myMat.at<uchar>(i, j) = floor((256 - 1) * arr3[origin_image.at<uchar>(i, j)]);

		}
	}
	//���⻯��ͼ��
	int h2[256] = { 0 };
	for (int i = 0; i < myMat.rows; i++) {
		for (int j = 0; j < myMat.cols; j++) {
			int index = (int)(myMat.at<uchar>(i, j));
			h2[index]++;
		}
	}
	int maxH2 = 0;
	for (int i = 0; i < 255; i++) {
		if (h2[i] > maxH2) {
			maxH2 = h2[i];
		}
	}
	//���⻯ֱ��ͼ
	for (int i = 0; i < 255; i++) {
		rectangle(histogram, Point(inc * i, histogram.rows), Point((inc * (i + 1) - 1), histogram.rows - ((h2[i] * histogram.rows) / (maxH2))), Scalar(255, 255, 255, 0), CV_FILLED);
	}
	
}
int main() {
	Mat image = imread("D:\\BaiduNetdiskDownload\\�������\\����ͼƬ\\vis\\7.bmp", CV_LOAD_IMAGE_GRAYSCALE);
	Mat Histog(750, 750, CV_8U, Scalar(0));
	Mat histog(750, 750, CV_8U, Scalar(0));
	int height = image.rows;
	int width = image.cols;
	Mat MyMat(height, width, CV_8U, Scalar(0));
	origin_image_histogram(image, Histog,histog,MyMat);
	imshow("ԭʼͼ��", image);
	imshow("ԭʼͼ��ֱ��ͼ", Histog);
	imshow("���⻯ͼ��ֱ��ͼ", histog);
	imshow("���⻯", MyMat);
	
	waitKey(0);
}
