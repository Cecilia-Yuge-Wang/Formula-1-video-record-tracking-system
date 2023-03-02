
#include <opencv2/opencv.hpp>  
#include <opencv2/core/core.hpp>  
#include <opencv2/highgui/highgui.hpp>  
#include <opencv2/imgproc.hpp>  
#include<iostream>  
using namespace std;
using namespace cv;

void getContours(Mat imgDil, Mat img) {

	vector<vector<Point>> contours;
	vector<Vec4i> hierachy;
	
	findContours(imgDil, contours, hierachy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
	//filter
	for (int i = 0; i < contours.size(); i++) {

		vector<vector<Point>> conPoly(contours.size());
		vector<Rect> boundRect(contours.size());

		int area = contourArea(contours[i]);
		//cout << area << endl;
		if (area > 500) {
			float peri = arcLength(contours[i], true);
			approxPolyDP(contours[i], conPoly[i], 0.02 * peri, true);
			drawContours(img, conPoly, i, Scalar(0, 255, 255), 2);
			cout << conPoly[i].size() << endl;
			boundRect[i] = boundingRect(conPoly[i]);
			rectangle(img, boundRect[i].tl(), boundRect[i].br(), Scalar(0, 255, 0), 5);
		}
	}
	

}

int main()
{
	VideoCapture cap(0);
	Mat img;
	Mat imgGray;
	Mat imgBlur;
	Mat imgCanny;
	Mat imgDil;


	while (true) {
		cap.read(img);
		cvtColor(img, imgGray, COLOR_BGR2GRAY);
		GaussianBlur(imgGray, imgBlur, Size(7, 7), 3, 0);
		Canny(imgBlur, imgCanny, 50, 150);
		
		Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
		dilate(imgCanny, imgDil, kernel);

		getContours(imgDil, img);

		imshow("image", img);
		imshow("imageGray", imgGray);
		imshow("imageBlur", imgBlur);
		imshow("imageCanny", imgCanny);
		imshow("imageDilate", imgDil);

		waitKey(1);
	}
}
