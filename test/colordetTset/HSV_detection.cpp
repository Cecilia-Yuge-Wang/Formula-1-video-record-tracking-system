
//

#include <opencv2/opencv.hpp>  
#include <opencv2/core/core.hpp>  
#include <opencv2/highgui/highgui.hpp>  
#include <opencv2/imgproc.hpp>  
#include<iostream>  
using namespace std;
using namespace cv;

Mat imgHSV, mask;
int hmin = 0, smin = 0, vmin = 0;
int hmax = 179, smax = 255, vmax = 255;

Point getContours(Mat imgDil, Mat img ) {

	vector<vector<Point>> contours;
	vector<Vec4i> hierachy;

	findContours(imgDil, contours, hierachy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
	drawContours(img, contours, -1, Scalar(255, 255, 0),10);


	vector<vector<Point>> conPoly(contours.size());
	vector<Rect> boundRect(contours.size());



	int maxAreaIdx = -1;
	int maxArea = 0;
	for (int i = 0; i < contours.size(); i++) {
		int area = contourArea(contours[i]);
		if (area > maxArea) {
			maxArea = area;
			maxAreaIdx = i;
		}
	}
	if (maxAreaIdx >= 0) {
		float peri = arcLength(contours[maxAreaIdx], true);
		approxPolyDP(contours[maxAreaIdx], conPoly[maxAreaIdx], 0.02 * peri, true);
		drawContours(img, conPoly, maxAreaIdx, Scalar(0, 255, 255), 2);
		cout << conPoly[maxAreaIdx].size() << endl;
		boundRect[maxAreaIdx] = boundingRect(conPoly[maxAreaIdx]);
		rectangle(img, boundRect[maxAreaIdx].tl(), boundRect[maxAreaIdx].br(), Scalar(0, 255, 0), 5);
		//cout center point
		Point center(boundRect[maxAreaIdx].x + boundRect[maxAreaIdx].width / 2, boundRect[maxAreaIdx].y + boundRect[maxAreaIdx].height / 2);
		cout << "Center coordinates: (" << center.x << ", " << center.y << ")" << endl;

		return center;
	}

	return Point(-1, -1);
}

int main()
{
	VideoCapture cap(1);
	Mat img;
	Mat imgGray;
	Mat imgBlur;
	Mat imgCanny;
	Mat imgDil;

	namedWindow("Trackbars", (640, 200));
	createTrackbar("Hue Min", "Trackbars", &hmin, 179);
	createTrackbar("Hue Max", "Trackbars", &hmax, 179);
	createTrackbar("Sat Min", "Trackbars", &smin, 255);
	createTrackbar("Sat Max", "Trackbars", &smax, 255);
	createTrackbar("Val Min", "Trackbars", &vmin, 255);
	createTrackbar("Val Max", "Trackbars", &vmax, 255);

	while (true) {
		cap.read(img);
		cvtColor(img, imgHSV, COLOR_BGR2HSV);
		//GaussianBlur(imgGray, imgBlur, Size(7, 7), 3, 0);
		//Canny(imgHSV, imgCanny, 50, 150);
		Scalar lower(hmin, smin, vmin);
		Scalar upper(hmax, smax, vmax);
		inRange(imgHSV, lower, upper, mask);
		Canny(mask, imgCanny, 50, 150);
		Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
		dilate(imgCanny, imgDil, kernel);
		Point center =	getContours(imgDil, img);

		imshow("image", img);
		//imshow("imageGray", imgGray);
		//imshow("imageBlur", imgBlur);
		imshow("imageHSV", imgHSV);
		imshow("imageMask", mask);
		imshow("imageCanny", imgCanny);
		imshow("imageDilate", imgDil);

		waitKey(1);
	}
}
