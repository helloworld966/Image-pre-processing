#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;
using namespace cv;



//使用opencv的GaussianBlur
void DOG(Mat& origin, Mat& output, Size wsize, double sigma) {

	Mat gaussian1, gaussian2;
	double i = 10;
	//高斯滤波
	GaussianBlur(origin, gaussian1, wsize, i * sigma);
	GaussianBlur(origin, gaussian2, wsize, sigma);

	output = gaussian1 - gaussian2;
	threshold(output, output, 0, 255, THRESH_BINARY);//通过遍历灰度图中点，将图像信息二值化，处理过后的图片只有二种色值
}
int main() {
	Mat origin;
	origin = imread("D:\\BaiduNetdiskDownload\\相关论文\\部分图片\\vis\\7.bmp");
	if (origin.empty()) {
		return -1;
	}
	if (origin.channels() > 1)
		cvtColor(origin, origin, CV_RGB2GRAY);
	Mat output;

	DOG(origin, output, Size(7, 7), 5);
	imshow("原始灰度图像", origin);
	imshow("Opencv_DOG", output);
	waitKey(0);
	return 0;
}