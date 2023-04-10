#include "frameprocess.h"
#include<wiringPi.h>
#include<softPwm.h>
#include<iostream>
#include "Controller.h"

#define motor1 17 // Vertical
#define motor2 27 // Horizontal



int main()
{   

    Controller Controller(motor1,motor2);
    
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
    
    int Deter_x = 0;
    
    while (true){
        
        cap.read(cvImg); // ¶ÁÈ¡ÉãÏñÍ·Ã¿Ò»Ö¡
        if (cvImg.empty()) {
            std::cerr << "Failed to capture frame." << std::endl;
            break;
        }

        std::vector<TargetBox> boxes;
        
        api.detection(cvImg, boxes);
        
        api.rectangle(cvImg, boxes, class_names);
        
       
    	
	
        cv::imshow("Camera", cvImg); // ÏÔÊ¾ÉãÏñÍ·»­Ãæ
        if (cv::waitKey(1) == 27) { // °´ÏÂEsc¼üÍË³öÑ­»·
            break;
        }
        //cv::imwrite("output.png", cvImg);
    
        int rx = api.rx;
    	int ry = api.ry;
    
        
        
        if (Deter_x != rx){
            Controller.ServoControl(ry,rx);
        }
        
        Deter_x = rx;
        

    }

    
    
    return 0;
}

