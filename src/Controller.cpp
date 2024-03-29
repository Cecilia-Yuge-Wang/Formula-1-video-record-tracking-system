#include"Controller.h"
#include"motor.h"
#include<thread>
#include<iostream>
#include<time.h>
#include<chrono>



Controller::Controller(int motor1,int motor2):Vertical(motor1),Horizontal(motor2)
{
        std::cout<<"pantilt is initialized"<<std::endl;
};

//in this function, the central coordinate of the object will be compared with the center area of the screen. if the coordiante is much far 
//away from the central area, the servo class will be called to perform the rotate to make the pantilt tracking the object.

void Controller::ServoControl(float image_y,float image_x)
{
    if(image_y>420){
        Vertical.clockwiseRotate();         //down
        //delay(100);
    }else if(image_y<300){
        Vertical.antiClockRotate();         //up
        //delay(100);
    }
    
    if(image_x>680){
        Horizontal.antiClockRotate();       //right
        //delay(100);
    }else if(image_x<600){
        Horizontal.clockwiseRotate();       //left
        //delay(100);
    }
    

}

//this function is a callback function to get the coordiante of the object central from frameprocess class.
void Controller::getCoordinate(float y, float x) 
{
    image_y = y;
    image_x = x;
    //std::cout<<"the coordinate received in class is: x = "<<image_x<<" y = "<<image_y<<std::endl;
}


//this function is used to print the coordinate input from get function for testing
void Controller::printCoordinate()
{
    std::cout<<"x = " <<image_x<<", y = "<<image_y<<std::endl;
}

void Controller::control()
{
    int deter_x = 0;
    std::chrono::milliseconds dura( 100 );
    
    while (true)
    {
        if (deter_x != image_x)
        {
            ServoControl(image_y, image_x);
        }

        deter_x = image_x;
        std::this_thread::sleep_for( dura );
    }
    
}


void Controller::controlThread()
{
    std::thread pantiltThread(&Controller::control, this);
    pantiltThread.detach();
}
