#include <opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
using namespace std;
using namespace cv;


//�˲���ʵ�֣�������˹�˲�����ֵ�˲�����ֵ�˲���

int innerMatrixIndex = 3;
int gaussMatrix[3][3] = { { 1,2,1 },{ 2,4,2 },{ 1,2,1 } };


//��˹�˲�
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
			//��˹ģ��
			promedio = int(sum / 16);
			gaussiano.at<uchar>(i, j) = promedio;
		}
	}
}

//��ֵ�˲�
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

//��ֵ�˲�
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
	Mat origin = imread("D:\\BaiduNetdiskDownload\\�������\\����ͼƬ\\vis\\7.bmp");
	Mat Blur(origin.rows, origin.cols, CV_8UC1);
	Mat Gaussiano(origin.rows, origin.cols, CV_8UC1);
	Mat Median(origin.rows, origin.cols, CV_8UC1);
	Mat diferencia(origin.rows, origin.cols, CV_8UC1);
	cvtColor(origin, origin, CV_RGB2GRAY);
	GaussianFilter(origin, Gaussiano);
	MeanFilater(origin,Blur);
	MedianFilter(origin, Median);
	imshow("ԭʼͼ��", origin);
	imshow("��˹�˲�", Gaussiano);
	imshow("��ֵ�˲�", Blur);
	imshow("��ֵ�˲�", Median);
	waitKey(0);
}