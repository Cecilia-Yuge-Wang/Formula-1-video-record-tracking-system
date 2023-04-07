  while (true) {  
    cvtColor(img, imgGray, COLOR_BGR2GRAY);
		GaussianBlur(imgGray, imgBlur, Size(7, 7), 3, 0);
		Canny(imgBlur, imgCanny, 50, 150);
		//Laplacian(imgGray, imgCanny, CV_8U, 3);
		
		Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
		dilate(imgCanny, imgDil, kernel);
		erode(imgDil, imgErode, kernel);
    
    waitKey(1);
	}
