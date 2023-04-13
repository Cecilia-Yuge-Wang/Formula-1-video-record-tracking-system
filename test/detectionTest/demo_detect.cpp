#include "frameprocess.h"
#include <thread>
#include "Controller.h"
#define motor1 17 // Vertical
#define motor2 27 // Horizontal


int main()
{   
    Controller controller(motor1,motor2);
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

        int x = api.getX();
    	int y = api.getY();
    	std::cout<<"x = "<< x << std::endl;
        controller.getCoordinate(y, x);


	
        cv::imshow("Camera", cvImg); // ��ʾ����ͷ����
        if (cv::waitKey(1) == 27) { // ����Esc���˳�ѭ��
            api.g_quit = true;
            t1.detach();
            break;
        }
    }
    
    return 0;
}

