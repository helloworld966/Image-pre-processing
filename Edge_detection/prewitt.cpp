#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include<math.h>
using namespace std;
using namespace cv;

//prewitt算子边缘检测
int innerMatrixIndex = 3;//内部矩阵索引3*3
int horiz[3][3] = { { -1,0,1 },{ -1,0,1 },{ -1,0,1 } };//横向矩阵
int vert[3][3] = { { -1,-1,-1 },{ 0,0,0 },{ 1,1,1 } };//纵向矩阵



//纵向prewitt算子检测结果
void PrewittH(Mat& image, Mat& PrewittH)
{
	//图像横向矩阵加和求绝对值
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


//横向prewitt算子检测结果，横向和纵向除矩阵变化之外，其余没变化
void PrewittV(Mat& image, Mat& PrewittV)
{
	//图像纵向矩阵加和求绝对值
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


//横纵相加
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
	//imshow("横向prewitt算子边缘检测", prewittHR);
	//imshow("纵向prewitt算子边缘检测", prewittVR);
	imshow("prewitt算子边缘检测", prewitt_output);
}
int main()
{
	Mat image = imread("D:\\BaiduNetdiskDownload\\相关论文\\部分图片\\vis\\7.bmp", CV_LOAD_IMAGE_GRAYSCALE);
	//Mat blur(image.rows, image.cols, CV_8UC1);//图像模糊
	//Mat filtroMediana(image.rows, image.cols, CV_8UC1);//中值滤波，降低图像椒盐噪声
	Mat prewitt_V(image.rows, image.cols, CV_32FC1, Scalar(0));
	Mat prewitt_H(image.rows, image.cols, CV_32FC1, Scalar(0));
	Mat prewitt(image.rows, image.cols, CV_32FC1, Scalar(0));
	PrewittH(image, prewitt_H);
	PrewittV(image, prewitt_V);
	PrewittH_V(image, prewitt_H, prewitt_V, prewitt);
	imshow("原始图像", image);
	waitKey(0);
}