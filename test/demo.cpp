#include "frameprocess.h"

int main()
{   
    static const char* class_names[] = {"Ferrari"};
    
    CNN api;

    api.loadModel("./model/F1F1.param",
                  "./model/F1F1.bin");
   
    
    cv::VideoCapture cap(0);
    //cv::Mat cvImg = cv::imread("test.jpg"); 
    if (!cap.isOpened()) {
        std::cerr << "Failed to open camera." << std::endl;
        return -1;
    }

    
    cv::Mat cvImg; 
    //int rx, ry;
    while (true){
        
        cap.read(cvImg); // ��ȡ����ͷÿһ֡
        if (cvImg.empty()) {
            std::cerr << "Failed to capture frame." << std::endl;
            break;
        }

        std::vector<TargetBox> boxes;
        
        api.detection(cvImg, boxes);
        
        api.rectangle(cvImg, boxes, class_names);
        
       // api.rectangleT(cvImg, boxes, class_names);
        
        int rx = api.rx;
    	int ry = api.ry;
    	std::cout<<"x = "<<rx << std::endl;
	
        cv::imshow("Camera", cvImg); // ��ʾ����ͷ����
        if (cv::waitKey(1) == 27) { // ����Esc���˳�ѭ��
            break;
        }
    //cv::imwrite("output.png", cvImg);
    }
    
    
    
    return 0;
}

