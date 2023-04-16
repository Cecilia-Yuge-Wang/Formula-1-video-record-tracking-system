#include "frameprocess.h"
#include <thread>

int main()
{   
    
    CNN api;
    
    const char* filename = "./dataset/classnames.txt"; 
    api.read_class_names(filename);
    
    api.loadModel("./model/F1F1-opt.param",
                  "./model/F1F1-opt.bin");
   
    cv::VideoCapture cap(0);
    if (!cap.isOpened()) {
        std::cerr << "Failed to open camera." << std::endl;
        return -1;
    }

    std::thread t1(&CNN::processThread, &api, std::ref(cap));
    
    cv::Mat cvImg;
    cap >> cvImg;
    if (cvImg.empty()) {
        std::cerr << "Failed to capture frame." << std::endl;
        return -1;
    }
     std::thread t2(&CNN::showThread, &api, std::ref(cvImg));
    
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
	
        
        if (cv::waitKey(1) == 27) { // Press Esc to exit the loop
            api.g_quit = true;
            t1.detach();
            t2.detach();
            break;
        }
    }
    
    return 0;
}

