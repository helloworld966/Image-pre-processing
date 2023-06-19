#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;
using namespace cv;


int main() {
	Mat origin = imread("D:\\BaiduNetdiskDownload\\相关论文\\部分图片\\vis\\7.bmp");
	if (origin.empty()) {
		return -1;
	}
	if (origin.channels() > 1)
		cvtColor(origin, origin, CV_RGB2GRAY);
	Mat  output;

	//Canny
	//Edge_Canny(src, edge, 50, 128);

	//opencv自带Canny
	Canny(origin, output, 50, 150);

	imshow("src", origin);
	imshow("Opencv_canny", output);
	waitKey(0);
	return 0;
}
