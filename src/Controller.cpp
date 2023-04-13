#include"../Formula-1-video-record-tracking-system/src/Controller.h"
#include"../Formula-1-video-record-tracking-system/src/motor.h"
#include<thread>
#include<iostream>
#include<time.h>



Controller::Controller(int motor1,int motor2):Vertical(motor1),Horizontal(motor2)
{
        std::cout<<"pantilt is initialized"<<std::endl;
};

void Controller::controlThread()
{
    std::thread pantiltThread(&Controller::ServoControl, this);
    pantiltThread.detach();
}

//in this function, the central coordinate of the object will be compared with the center area of the screen. if the coordiante is much far 
//away from the central area, the servo class will be called to perform the rotate to make the pantilt tracking the object.

void Controller::ServoControl()
{
    char running = true;
    while (running)
    {
        if(image_y>520)
            {
                Vertical.clockwiseRotate();         //down
            }

        else if(image_y<200)
            {
                Vertical.antiClockRotate();         //up
            }
    
        else if(image_x>880)
            {
                Horizontal.antiClockRotate();    //right
            }

        else if(image_x<400)
            {
                Horizontal.clockwiseRotate();    //left
            }
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(10));   
}

//this function is a callback function to get the coordiante of the object central from frameprocess class.
void Controller::getCoordinate(float y, float x) 
{
    image_y = y;
    image_x = x;
}

