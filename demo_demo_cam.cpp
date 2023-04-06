#include "yolo-fastestv2.h"

int main()
{   
    static const char* class_names[] = {"Ferrari","1","2"};
    
    yoloFastestv2 api;

    api.loadModel("./model/F1.param",
                  "./model/F1.bin");
   
    
    cv::VideoCapture cap(0);
    //cv::Mat cvImg = cv::imread("test.jpg");
    
    if (!cap.isOpened()) {
        std::cerr << "Failed to open camera." << std::endl;
        return -1;
    }

    

    while (true) {
        cv::Mat cvImg;
        cap.read(cvImg); // 读取摄像头每一帧
        if (cvImg.empty()) {
            std::cerr << "Failed to capture frame." << std::endl;
            break;
        }

        std::vector<TargetBox> boxes;
        api.detection(cvImg, boxes);


        for (int i = 0; i < boxes.size(); i++) {
            std::cout << boxes[i].x1 << " " << boxes[i].y1 << " " << boxes[i].x2 << " " << boxes[i].y2
                << " " << boxes[i].score << " " << boxes[i].cate << std::endl;

            char text[256];
            sprintf(text, "%s %.1f%%", class_names[boxes[i].cate], boxes[i].score * 100);

            int baseLine = 0;
            cv::Size label_size = cv::getTextSize(text, cv::FONT_HERSHEY_SIMPLEX, 0.5, 1, &baseLine);

            int x = boxes[i].x1;
            int y = boxes[i].y1 - label_size.height - baseLine;
            if (y < 0)
                y = 0;
            if (x + label_size.width > cvImg.cols)
                x = cvImg.cols - label_size.width;
	    if (boxes[i].score > 0.5){
            cv::rectangle(cvImg, cv::Rect(cv::Point(x, y), cv::Size(label_size.width, label_size.height + baseLine)),
                cv::Scalar(255, 255, 255), -1);

            cv::putText(cvImg, text, cv::Point(x, y + label_size.height),
                cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(0, 0, 0));

            cv::rectangle(cvImg, cv::Point(boxes[i].x1, boxes[i].y1),
                cv::Point(boxes[i].x2, boxes[i].y2), cv::Scalar(255, 255, 0), 2, 2, 0);
                	
                	
            cv::Point center((boxes[i].x2-boxes[i].x1)/2+boxes[i].x1, (boxes[i].y2-boxes[i].y1)/2+boxes[i].y1);
            
            cv::circle(cvImg, center, 5, cv::Scalar(0, 255, 0), -1);

                
                
                
                
        	}
	}
        cv::imshow("Camera", cvImg); // 显示摄像头画面
        if (cv::waitKey(1) == 27) { // 按下Esc键退出循环
            break;


    }
    //cv::imwrite("output.png", cvImg);
    }
    return 0;
}

