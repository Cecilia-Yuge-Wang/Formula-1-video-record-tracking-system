#include "frameprocess.h"
#include <thread>


int main()
{   
    static const char* class_names[] = {"Ferrari"};
    
    CNN api;

    api.loadModel("./model/F1F1-opt.param",
                  "./model/F1F1-opt.bin");
   
    
   /* cv::VideoCapture cap(0);
    //cv::Mat cvImg = cv::imread("test.jpg"); 
    if (!cap.isOpened()) {
        std::cerr << "Failed to open camera." << std::endl;
        return -1;
    } */


    cv::VideoCapture cap(0);
    /*if (!cap.isOpened()) {
        std::cerr << "Failed to open camera." << std::endl;
        return -1;
    }*/
    std::thread t1(&CNN::processThread, &api,  cap);
    t1.join();


    
    cv::Mat cvImg = api.srcImg; 
    //int rx, ry;
    while (true){
        
       /* cap.read(cvImg); // 读取摄像头每一帧
        if (cvImg.empty()) {
            std::cerr << "Failed to capture frame." << std::endl;
            break;
        } */

        std::vector<TargetBox> boxes;
        
        api.detection(/*cvImg,*/ boxes);
        
        api.rectangle(/*cvImg,*/ boxes, class_names);
        
       // api.rectangleT(cvImg, boxes, class_names);
        
        int rx = api.rx;
    	int ry = api.ry;
    	std::cout<<"x = "<<rx << std::endl;
	
	
        cv::imshow("Camera", cvImg); // 显示摄像头画面
        if (cv::waitKey(1) == 27) { // 按下Esc键退出循环
            break;
        }
    //cv::imwrite("output.png", cvImg);
    }
    
    
    
    return 0;
}

