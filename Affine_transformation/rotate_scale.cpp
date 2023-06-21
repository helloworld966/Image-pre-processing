#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include <cmath>

using namespace std;
using namespace cv;



//原尺度旋转图像
int main() {

	Mat origin_image = imread("D:\\BaiduNetdiskDownload\\相关论文\\部分图片\\vis\\7.bmp", CV_LOAD_IMAGE_GRAYSCALE);
	Mat rotate(int(origin_image.rows), int(origin_image.cols), CV_8UC1, Scalar(0));
	int Angle = 90;
	cout << "输入角度"<<endl;
	cin >>Angle;
	
	float angle = (Angle * 3.1416) / 180.0f;
	
	for (int i = 0; i < rotate.rows; i++) {
		for (int j = 0; j < rotate.cols; j++) {
			int x = j - (rotate.cols / 2);
			int y = (rotate.rows / 2) - i;

			float xx = x * cos(angle) + y * sin(angle);
			float yy = -1 * x * sin(angle) + y * cos(angle);

			int xxx = xx + (rotate.cols / 2);
			int yyy = (rotate.rows / 2) - yy;

			if (xxx >= origin_image.cols || xxx < 0 || yyy >= origin_image.rows || yyy < 0) 
				continue;
			rotate.at<uchar>(i, j) = origin_image.at<uchar>(yyy, xxx);
			//彩色图像旋转
			//if (xx >= 0 && yy >= 0 && yy <= origin_image.cols - 1 && xx <= origin_image.rows - 1) {
			//	int top = floor(xx), bottom = ceil(xx), left = floor(yy), right = ceil(yy);
			//	double pw = xx - top;
			//	double pv = yy - left;
			//	if (origin_image.channels() == 1) {
			//		//单通道
			//		rotate.at<uchar>(i, j) = (1 - pw) * (1 - pv) * origin_image.at<uchar>(top, left)
			//			+ (1 - pw) * pv * origin_image.at<uchar>(top, right)
			//			+ pw * (1 - pv) * origin_image.at<uchar>(bottom, left)
			//			+ pw * pv * origin_image.at<uchar>(bottom, right);
			//	}
			//	else {
			//		//三通道
			//		rotate.at<Vec3b>(i, j)[0] = (1 - pw) * (1 - pv) * origin_image.at<Vec3b>(top, left)[0]
			//			+ (1 - pw) * pv * origin_image.at<Vec3b>(top, right)[0]
			//			+ pw * (1 - pv) * origin_image.at<Vec3b>(bottom, left)[0]
			//			+ pw * pv * origin_image.at<Vec3b>(bottom, right)[0];
			//		rotate.at<Vec3b>(i, j)[1] = (1 - pw) * (1 - pv) * origin_image.at<Vec3b>(top, left)[1]
			//			+ (1 - pw) * pv * origin_image.at<Vec3b>(top, right)[1]
			//			+ pw * (1 - pv) * origin_image.at<Vec3b>(bottom, left)[1]
			//			+ pw * pv * origin_image.at<Vec3b>(bottom, right)[1];
			//		rotate.at<Vec3b>(i, j)[2] = (1 - pw) * (1 - pv) * origin_image.at<Vec3b>(top, left)[2]
			//			+ (1 - pw) * pv * origin_image.at<Vec3b>(top, right)[2]
			//			+ pw * (1 - pv) * origin_image.at<Vec3b>(bottom, left)[2]
			//			+ pw * pv * origin_image.at<Vec3b>(bottom, right)[2];
			//	}
			//}
		}
		
	}
	
	imshow("原始图像", origin_image);
	imshow("旋转后图像", rotate);
	waitKey(0);
}