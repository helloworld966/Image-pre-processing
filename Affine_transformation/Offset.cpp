#include<iostream>
#include<opencv2/core.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>
#include<math.h>
using namespace std;
using namespace cv;


void Offset(Mat& origin, Mat& output, double Offset_x, double Offset_y) {
	int output_rows = origin.rows;
	int output_cols = origin.cols;

	if (origin.channels() == 1) {
		output = Mat::zeros(output_rows, output_cols, CV_8UC1);
	}
	else {
		output = Mat::zeros(output_rows, output_cols, CV_8UC3);
	}
	//仿射变换部分。只有矩阵改变，其余不变
	Mat T1 = (Mat_<double>(3, 3) << 1, 0, 0, 0, -1, 0, -0.5 * origin.cols, 0.5 * origin.rows, 1);
	Mat T2 = (Mat_<double>(3, 3) << 1, Offset_y, 0, Offset_x, 1, 0, 0, 0, 1);
	double t3[3][3] = { { 1, 0, 0 }, { 0, -1, 0 }, { 0.5 * output.cols, 0.5 * output.rows, 1 } };
	Mat T3 = cv::Mat(3, 3, CV_64FC1, t3);
	Mat T = T1 * T2 * T3;
	Mat T_inv = T.inv(); // 求逆矩阵


	for (int i = 0; i < output.rows; i++) {
		for (int j = 0; j < output.cols; j++) {
			Mat dst_coordinate = (Mat_<double>(1, 3) << j, i, 1);
			Mat src_coordinate = dst_coordinate * T_inv;
			double v = src_coordinate.at<double>(0, 0);
			double w = src_coordinate.at<double>(0, 1);

			//双线性插值
			//if (v < 0) v = 0; if (v > origin.cols - 1) v = origin.cols - 1;
			//if (w < 0) w = 0; if (w > origin.rows - 1) w = origin.rows - 1;

			if (v >= 0 && w >= 0 && v <= origin.cols - 1 && w <= origin.rows - 1) {
				int top = floor(w), bottom = ceil(w), left = floor(v), right = ceil(v);
				double pw = w - top;
				double pv = v - left;
				if (origin.channels() == 1) {
					//灰度图像
					output.at<uchar>(i, j) = (1 - pw) * (1 - pv) * origin.at<uchar>(top, left)
						+ (1 - pw) * pv * origin.at<uchar>(top, right)
						+ pw * (1 - pv) * origin.at<uchar>(bottom, left)
						+ pw * pv * origin.at<uchar>(bottom, right);
				}
				else {
					//彩色图像
					output.at<Vec3b>(i, j)[0] = (1 - pw) * (1 - pv) * origin.at<Vec3b>(top, left)[0]
						+ (1 - pw) * pv * origin.at<Vec3b>(top, right)[0]
						+ pw * (1 - pv) * origin.at<Vec3b>(bottom, left)[0]
						+ pw * pv * origin.at<Vec3b>(bottom, right)[0];
					output.at<Vec3b>(i, j)[1] = (1 - pw) * (1 - pv) * origin.at<Vec3b>(top, left)[1]
						+ (1 - pw) * pv * origin.at<Vec3b>(top, right)[1]
						+ pw * (1 - pv) * origin.at<Vec3b>(bottom, left)[1]
						+ pw * pv * origin.at<Vec3b>(bottom, right)[1];
					output.at<Vec3b>(i, j)[2] = (1 - pw) * (1 - pv) * origin.at<Vec3b>(top, left)[2]
						+ (1 - pw) * pv * origin.at<Vec3b>(top, right)[2]
						+ pw * (1 - pv) * origin.at<Vec3b>(bottom, left)[2]
						+ pw * pv * origin.at<Vec3b>(bottom, right)[2];
				}
			}
		}
	}
}
int main()
{
	Mat origin = imread("D:\\BaiduNetdiskDownload\\相关论文\\部分图片\\vis\\7.bmp");
	//cvtColor(origin, origin, CV_BGR2GRAY);灰度化
	if (origin.empty())
	{
		cout << "Failing to load image" << endl;
		return -1;
	}
	Mat output;
	double Offset_x, Offset_y;
	cout << "输入水平偏移角度：" << endl;
	cin >> Offset_x;
	cout << "输入垂直偏移角度：" << endl;
	cin >> Offset_y;

	Offset(origin, output, Offset_x, Offset_y);
	imshow("原始图像", origin);
	imshow("偏移变换", output);

	waitKey(0);

}