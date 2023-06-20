#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include<math.h>
using namespace std;
using namespace cv;

//prewitt���ӱ�Ե���
int innerMatrixIndex = 3;//�ڲ���������3*3
int horiz[3][3] = { { -1,0,1 },{ -1,0,1 },{ -1,0,1 } };//�������
int vert[3][3] = { { -1,-1,-1 },{ 0,0,0 },{ 1,1,1 } };//�������



//����prewitt���Ӽ����
void PrewittH(Mat& image, Mat& PrewittH)
{
	//ͼ��������Ӻ������ֵ
	for (int i = 0; i < image.rows; i++)
	{
		for (int j = 0; j < image.cols; j++)
		{
			int sum = 0;
			int y = 0;
			for (int a = -(innerMatrixIndex / 2); a <= innerMatrixIndex / 2; a++)
			{
				int x = 0;
				for (int b = -(innerMatrixIndex / 2); b <= innerMatrixIndex / 2; b++)
				{
					if ((i + a) >= 0 &&	(i + a) < image.rows &&(j + b) >= 0 &&(j + b) < image.cols)
					{
						sum += (image.at<uchar>(i + a, j + b) * horiz[y][x]);
					}
					x++;
				}
				y++;
			}
			PrewittH.at<float>(i, j) = abs(sum);
		}
	}
}


//����prewitt���Ӽ��������������������仯֮�⣬����û�仯
void PrewittV(Mat& image, Mat& PrewittV)
{
	//ͼ���������Ӻ������ֵ
	for (int i = 0; i < image.rows; i++)
	{
		for (int j = 0; j < image.cols; j++)
		{
			int sum = 0;
			int y = 0;
			for (int a = -(innerMatrixIndex / 2); a <= innerMatrixIndex / 2; a++)
			{
				int x = 0;
				for (int b = -(innerMatrixIndex / 2); b <= innerMatrixIndex / 2; b++)
				{
					if ((i + a) >= 0 &&(i + a) < image.rows &&(j + b) >= 0 &&(j + b) < image.cols)
					{
						sum += (image.at<uchar>(i + a, j + b) * vert[y][x]);
					}
					x++;
				}
				y++;
			}
			PrewittV.at<float>(i, j) = abs(sum);
		}
	}
}


//�������
void PrewittH_V(Mat& image, Mat& PrewittH,Mat& PrewittV,Mat&prewitt)
{
	for (int i = 0; i < image.rows; i++)
	{
		for (int j = 0; j < image.cols; j++)
		{
			float x = (PrewittH.at<float>(i, j) * PrewittH.at<float>(i, j));
			float y = (PrewittV.at<float>(i, j) * PrewittV.at<float>(i, j));
			prewitt.at<float>(i, j) = (sqrt(x + y));
		}
	}
	double minH = 0, maxH = 0, minR = 0, maxR = 0, minV = 0, maxV = 0;

	Mat prewittHR(image.rows, image.cols, CV_8UC1, Scalar(0));
	Mat prewittVR(image.rows, image.cols, CV_8UC1, Scalar(0));
	Mat prewitt_output(image.rows, image.cols, CV_8UC1, Scalar(0));
	minMaxLoc(PrewittH, &minH, &maxH);
	minMaxLoc(PrewittV, &minV, &maxV);
	minMaxLoc(prewitt, &minR, &maxR);

	for (int i = 0; i < image.rows; i++)
	{
		for (int j = 0; j < image.cols; j++)
		{
			float valH = 0;
			float valV = 0;
			float valR = 0;
			valH = (255 * (PrewittH.at<float>(i, j) - minH)) / (maxH - minH);
			valV = (255 * (PrewittV.at<float>(i, j) - minV)) / (maxV - minV);
			valR = (255 * (prewitt.at<float>(i, j) - minR)) / (maxR - minR);
			prewittHR.at<uchar>(i, j) = abs(valH);
			prewittVR.at<uchar>(i, j) = abs(valV);
			prewitt_output.at<uchar>(i, j) = abs(valR);
		}
	}
	//imshow("����prewitt���ӱ�Ե���", prewittHR);
	//imshow("����prewitt���ӱ�Ե���", prewittVR);
	imshow("prewitt���ӱ�Ե���", prewitt_output);
}
int main()
{
	Mat image = imread("D:\\BaiduNetdiskDownload\\�������\\����ͼƬ\\vis\\7.bmp", CV_LOAD_IMAGE_GRAYSCALE);
	//Mat blur(image.rows, image.cols, CV_8UC1);//ͼ��ģ��
	//Mat filtroMediana(image.rows, image.cols, CV_8UC1);//��ֵ�˲�������ͼ��������
	Mat prewitt_V(image.rows, image.cols, CV_32FC1, Scalar(0));
	Mat prewitt_H(image.rows, image.cols, CV_32FC1, Scalar(0));
	Mat prewitt(image.rows, image.cols, CV_32FC1, Scalar(0));
	PrewittH(image, prewitt_H);
	PrewittV(image, prewitt_V);
	PrewittH_V(image, prewitt_H, prewitt_V, prewitt);
	imshow("ԭʼͼ��", image);
	waitKey(0);
}