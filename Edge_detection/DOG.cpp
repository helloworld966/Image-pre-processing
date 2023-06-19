#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;
using namespace cv;



//ʹ��opencv��GaussianBlur
void DOG(Mat& origin, Mat& output, Size wsize, double sigma) {

	Mat gaussian1, gaussian2;
	double i = 10;
	//��˹�˲�
	GaussianBlur(origin, gaussian1, wsize, i * sigma);
	GaussianBlur(origin, gaussian2, wsize, sigma);

	output = gaussian1 - gaussian2;
	threshold(output, output, 0, 255, THRESH_BINARY);//ͨ�������Ҷ�ͼ�е㣬��ͼ����Ϣ��ֵ������������ͼƬֻ�ж���ɫֵ
}
int main() {
	Mat origin;
	origin = imread("D:\\BaiduNetdiskDownload\\�������\\����ͼƬ\\vis\\7.bmp");
	if (origin.empty()) {
		return -1;
	}
	if (origin.channels() > 1)
		cvtColor(origin, origin, CV_RGB2GRAY);
	Mat output;

	DOG(origin, output, Size(7, 7), 5);
	imshow("ԭʼ�Ҷ�ͼ��", origin);
	imshow("Opencv_DOG", output);
	waitKey(0);
	return 0;
}