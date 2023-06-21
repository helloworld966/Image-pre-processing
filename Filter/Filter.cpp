#include <opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
using namespace std;
using namespace cv;


//滤波器实现，包括高斯滤波、均值滤波、中值滤波等

int innerMatrixIndex = 3;
int gaussMatrix[3][3] = { { 1,2,1 },{ 2,4,2 },{ 1,2,1 } };


//高斯滤波
void GaussianFilter(Mat& origin, Mat& gaussiano)
{
	for (int i = 0; i < origin.rows; i++)
	{
		for (int j = 0; j < origin.cols; j++)
		{
			int sum = 0;
			int promedio = 0;

			int y = 0;
			for (int a = -(innerMatrixIndex / 2); a <= innerMatrixIndex / 2; a++)
			{
				int x = 0;
				for (int b = -(innerMatrixIndex / 2); b <= innerMatrixIndex / 2; b++)
				{
					if ((i + a) >= 0 && (i + a) < origin.rows && (j + b) >= 0 && (j + b) < origin.cols)
					{
						sum += int(origin.at<uchar>(i + a, j + b) * gaussMatrix[y][x]);
					}
					x++;
				}
				y++;
			}
			//高斯模糊
			promedio = int(sum / 16);
			gaussiano.at<uchar>(i, j) = promedio;
		}
	}
}

//中值滤波
void MedianFilter(Mat& origin, Mat& Median)
{
	float mediana = 0;
	vector<float> myVector;
	for (int i = 0; i < origin.rows; i++)
	{
		for (int j = 0; j < origin.cols; j++)
		{
			mediana = 0;
			myVector.clear();
			for (int a = -(innerMatrixIndex / 2); a <= innerMatrixIndex / 2; a++)
			{
				for (int b = -(innerMatrixIndex / 2); b <= innerMatrixIndex / 2; b++)
				{
					if ((i + a) >= 0 &&(i + a) < origin.rows &&(j + b) >= 0 &&(j + b) < origin.cols)
					{
						myVector.push_back(origin.at<uchar>(i + a, j + b));
					}
				}
			}
			sort(myVector.begin(), myVector.end());
			mediana = myVector.at(myVector.size() / 2);
			Median.at<uchar>(i, j) = mediana;
		}
	}
}

//均值滤波
void MeanFilater(Mat& origin, Mat& blur) {
	for (int i = 0; i < origin.rows; i++)
	{
		for (int j = 0; j < origin.cols; j++)
		{
			int sum = 0;
			int promedio = 0;
			for (int a = -(innerMatrixIndex / 2); a <= innerMatrixIndex / 2; a++)
			{
				for (int b = -(innerMatrixIndex / 2); b <= innerMatrixIndex / 2; b++)
				{
					if ((i + a) >= 0 && (i + a) < origin.rows && (j + b) >= 0 && (j + b) < origin.cols)
					{
						sum += origin.at<uchar>(i + a, j + b);
					}
				}
			}
			promedio = float(sum / float(innerMatrixIndex * innerMatrixIndex));
			blur.at<uchar>(i, j) = promedio;
		}
	}
}

int main() {
	Mat origin = imread("D:\\BaiduNetdiskDownload\\相关论文\\部分图片\\vis\\7.bmp");
	Mat Blur(origin.rows, origin.cols, CV_8UC1);
	Mat Gaussiano(origin.rows, origin.cols, CV_8UC1);
	Mat Median(origin.rows, origin.cols, CV_8UC1);
	Mat diferencia(origin.rows, origin.cols, CV_8UC1);
	cvtColor(origin, origin, CV_RGB2GRAY);
	GaussianFilter(origin, Gaussiano);
	MeanFilater(origin,Blur);
	MedianFilter(origin, Median);
	imshow("原始图像", origin);
	imshow("高斯滤波", Gaussiano);
	imshow("均值滤波", Blur);
	imshow("中值滤波", Median);
	waitKey(0);
}