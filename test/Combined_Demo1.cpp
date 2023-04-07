#include "frameprocess.h"
#include<wiringPi.h>
#include<softPwm.h>
#include<iostream>
#include "motor.h"
#define motor1 17 // Vertical
#define motor2 27 // Horizontal



int main()
{   float image_y;
    float image_x;

    motor Vertical(motor1);
    motor Horizontal(motor2);
    
    static const char* class_names[] = {"Ferrari"};
    
    CNN api;

    api.loadModel("./model/F1.param",
                  "./model/F1.bin");
   
    
    cv::VideoCapture cap(0);
    //cv::Mat cvImg = cv::imread("test.jpg"); 
    if (!cap.isOpened()) {
        std::cerr << "Failed to open camera." << std::endl;
        return -1;
    }

    
    cv::Mat cvImg; 
    //int rx, ry;
    while (true){
        
        cap.read(cvImg); // ¶ÁÈ¡ÉãÏñÍ·Ã¿Ò»Ö¡
        if (cvImg.empty()) {
            std::cerr << "Failed to capture frame." << std::endl;
            break;
        }

        std::vector<TargetBox> boxes;
        
        api.detection(cvImg, boxes);
        
        api.rectangle(cvImg, boxes, class_names);
        
       
    	//std::cout<<"x = "<<rx << std::endl;
	
        cv::imshow("Camera", cvImg); // ÏÔÊ¾ÉãÏñÍ·»­Ãæ
        if (cv::waitKey(1) == 27) { // °´ÏÂEsc¼üÍË³öÑ­»·
            break;
        }
    //cv::imwrite("output.png", cvImg);
    
    
    




        int rx = api.rx;
    	int ry = api.ry;
        
        image_y = ry;
        image_x = rx;
        
        if(image_y>360)
        {
            if(image_x>640){
                Horizontal.antiClockRotate(); //right
                delay(100);
                Vertical.clockwiseRotate(); //down
                delay(100);
            }else{
                Horizontal.clockwiseRotate(); //left
                delay(100);
                Vertical.clockwiseRotate(); //down
                delay(100);
            }
            
        }else if(image_y<360){
            if(image_x>640){
                Horizontal.antiClockRotate(); //right
                delay(100);
                Vertical.antiClockRotate(); //up
                delay(100);
            }else{
                Horizontal.clockwiseRotate(); //left
                delay(100);
                Vertical.antiClockRotate(); //up
                delay(100);
            }
        }
    }

    
    
    
    
    
    
    
    
    return 0;
}

