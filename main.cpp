#include "frameprocess.h"
#include <thread>
#include "Controller.h"
#define motor1 13 // Vertical
#define motor2 18 // Horizontal



int main()
{   
    Controller controller(motor1,motor2);
    
    CNN api;
    
    const char* filename = "./dataset/classnames.txt"; 
    api.read_class_names(filename);
    
    api.loadModel("../model/F1F1-opt.param",
                  "../model/F1F1-opt.bin");
   
    cv::VideoCapture cap(0);
    if (!cap.isOpened()) {
        std::cerr << "Failed to open camera." << std::endl;
        return -1;
    }
    controller.controlThread();
    std::thread t1(&CNN::processThread, &api, std::ref(cap));
    
    cv::Mat cvImg;
    
    while (true){
        cap >> cvImg; // Read every frame from the webcamera
        if (cvImg.empty()) {
            std::cerr << "Failed to capture frame." << std::endl;
            break;
        }

        std::vector<TargetBox> boxes;
        
        api.detection(cvImg, boxes);
        
        api.rectangle(cvImg, boxes/*, class_names*/);

        int x = api.getX();
    	int y = api.getY();
    	std::cout<<"x = "<< x << std::endl;
    	
	controller.getCoordinate(y, x);
        controller.printCoordinate();
        cv::imshow("Camera", cvImg); // Show the webcamera image
        if (cv::waitKey(1) == 27) { // Press Esc to exit the loop
            api.g_quit = true;
            t1.detach();
            break;
        }
    }
    
    return 0;
}

