#include "frameprocess.h"
#include <thread>


int main()
{   
    static const char* class_names[] = {"Ferrari"};
    
    CNN api;

    api.loadModel("./model/F1F1-opt.param",
                  "./model/F1F1-opt.bin");
   
    cv::VideoCapture cap(0);
    if (!cap.isOpened()) {
        std::cerr << "Failed to open camera." << std::endl;
        return -1;
    }

    std::thread t1(&CNN::processThread, &api, std::ref(cap));
    
    cv::Mat cvImg;
    while (true){
        cap >> cvImg; // ��ȡ����ͷÿһ֡
        if (cvImg.empty()) {
            std::cerr << "Failed to capture frame." << std::endl;
            break;
        }

        std::vector<TargetBox> boxes;
        
        api.detection(cvImg, boxes);
        
        api.rectangle(cvImg, boxes, class_names);

        int rx = api.rx;
    	int ry = api.ry;
    	std::cout<<"x = "<<rx << std::endl;
	
        cv::imshow("Camera", cvImg); // ��ʾ����ͷ����
        if (cv::waitKey(1) == 27) { // ����Esc���˳�ѭ��
            break;
        }
    }

    t1.join();
    
    return 0;
}

