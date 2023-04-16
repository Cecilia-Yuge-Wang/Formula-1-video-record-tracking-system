// test2.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <opencv2/opencv.hpp>  
#include <opencv2/core/core.hpp>  
#include <opencv2/highgui/highgui.hpp>  
#include <opencv2/imgproc.hpp>  
#include<iostream>  
using namespace std;
using namespace cv;
int main()
{
	VideoCapture cap(0);
	VideoCapture cap_1(1);
	Mat img, img_2;
	Mat imgGray;
	Mat imgBlur;
	Mat imgCanny;
	
	while(true) {
		cap.read(img);
		//cap_1.read(img_2);
		cvtColor(img, imgGray, COLOR_BGR2GRAY);
		GaussianBlur(imgGray, imgBlur, Size(7, 7), 3, 0);
		Canny(img, imgCanny, 50, 150);
	


		imshow("image", img);
		imshow("imageGray", imgGray);
		imshow("imageBlur", imgBlur);
		imshow("imageCanny", imgCanny);
		//imshow("image1", img_2);
		
		waitKey(1);
	}
}