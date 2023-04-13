#include "frameprocess.h"
#include "Controller.h"
#include <thread>

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
        cap >> cvImg; // 锟斤拷取锟斤拷锟斤拷头每一帧
        if (cvImg.empty()) {
            std::cerr << "Failed to capture frame." << std::endl;
            break;
        }

        std::vector<TargetBox> boxes;
        
        api.detection(cvImg, boxes);
        
        api.rectangle(cvImg, boxes, class_names);

        int rx = api.rx;
    	int ry = api.ry;
        std::cout<<"x = "<<rx <<" y = "<<ry<< std::endl;    

        controller.getCoordinate(api.ry, api.rx);
    	


        cv::imshow("Camera", cvImg); // 显示摄像头画面
        if (cv::waitKey(1) == 27) { // 按下Esc键退出循环
            api.g_quit = true;
            t1.detach();
            break;
        }
    }
    
    return 0;
}

