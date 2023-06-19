#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <math.h>
using namespace std;
using namespace cv;
void image_rotate(Mat& origin, Mat& output_image, double Angle) {
	double angle = Angle * CV_PI / 180.0;
	
	int output_image_rows = round(fabs(origin.rows * cos(angle)) + fabs(origin.cols * sin(angle)));
	int output_image_cols = round(fabs(origin.cols * cos(angle)) + fabs(origin.rows * sin(angle)));

	if (origin.channels() == 1) {
		output_image = Mat::zeros(output_image_rows, output_image_cols, CV_8UC1); //灰度图初始
	}
	else {
		output_image = Mat::zeros(output_image_rows, output_image_cols, CV_8UC3); //RGB图初始
	}

	Mat T1 = (Mat_<double>(3, 3) << 1.0, 0.0, 0.0, 0.0, -1.0, 0.0, -0.5 * origin.cols, 0.5 * origin.rows, 1.0);
	Mat T2 = (Mat_<double>(3, 3) << cos(angle), -sin(angle), 0.0, sin(angle), cos(angle), 0.0, 0.0, 0.0, 1.0); 
	double t3[3][3] = { { 1.0, 0.0, 0.0 }, { 0.0, -1.0, 0.0 }, { 0.5 * output_image.cols, 0.5 * output_image.rows ,1.0} }; 
	Mat T3 = Mat(3.0, 3.0, CV_64FC1, t3);
	Mat T = T1 * T2 * T3;
	Mat T_inv = T.inv(); 

	for (double i = 0.0; i < output_image.rows; i++) {
		for (double j = 0.0; j < output_image.cols; j++) {
			cv::Mat dst_coordinate = (cv::Mat_<double>(1, 3) << j, i, 1.0);
			cv::Mat src_coordinate = dst_coordinate * T_inv;
			double v = src_coordinate.at<double>(0, 0); // 原图像的横坐标，列，宽
			double w = src_coordinate.at<double>(0, 1); // 原图像的纵坐标，行，高

			//双线性插值
			if (int(Angle) % 90 == 0) {
				if (v < 0) v = 0; if (v > origin.cols - 1) v = origin.cols - 1;
				if (w < 0) w = 0; if (w > origin.rows - 1) w = origin.rows - 1;
			}
			if (v >= 0 && w >= 0 && v <= origin.cols - 1 && w <= origin.rows - 1) {
				int top = floor(w), bottom = ceil(w), left = floor(v), right = ceil(v); 
				double pw = w - top; 
				double pv = v - left; 
				if (origin.channels() == 1) {
					//单通道
					output_image.at<uchar>(i, j) = (1 - pw) * (1 - pv) * origin.at<uchar>(top, left) 
						+ (1 - pw) * pv * origin.at<uchar>(top, right) 
						+ pw * (1 - pv) * origin.at<uchar>(bottom, left) 
						+ pw * pv * origin.at<uchar>(bottom, right);
				}
				else {
					//三通道
					output_image.at<Vec3b>(i, j)[0] = (1 - pw) * (1 - pv) * origin.at<Vec3b>(top, left)[0] 
						+ (1 - pw) * pv * origin.at<Vec3b>(top, right)[0] 
						+ pw * (1 - pv) * origin.at<Vec3b>(bottom, left)[0] 
						+ pw * pv * origin.at<Vec3b>(bottom, right)[0];
					output_image.at<Vec3b>(i, j)[1] = (1 - pw) * (1 - pv) * origin.at<Vec3b>(top, left)[1] 
						+ (1 - pw) * pv * origin.at<Vec3b>(top, right)[1] 
						+ pw * (1 - pv) * origin.at<Vec3b>(bottom, left)[1] 
						+ pw * pv * origin.at<Vec3b>(bottom, right)[1];
					output_image.at<Vec3b>(i, j)[2] = (1 - pw) * (1 - pv) * origin.at<Vec3b>(top, left)[2] 
						+ (1 - pw) * pv * origin.at<Vec3b>(top, right)[2] 
						+ pw * (1 - pv) * origin.at<Vec3b>(bottom, left)[2] 
						+ pw * pv * origin.at<Vec3b>(bottom, right)[2];
				}
			}
		}
	}
}
int main() {
	Mat origin = imread("D:\\BaiduNetdiskDownload\\相关论文\\部分图片\\vis\\7.bmp");
	//cvtColor(src, src, CV_BGR2GRAY);灰度化
	if (origin.empty()) {
		cout << "Failure to load image" <<endl;
		return -1;
	}
	Mat output_image;
	
	double angle = 45;  //旋转角度
	image_rotate(origin, output_image, angle);

	imshow("原始图像", origin);

	imshow("旋转后图像", output_image);
	//string img_name = "C:\\Users\\24174\\source\\repos\\image-processing\\" + to_string(i) + ".png";
	imwrite("img_name", output_image);
	waitKey(0);
	
}