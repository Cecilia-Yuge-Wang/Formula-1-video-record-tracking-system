#include"Controller.h"
#include"motor.h"

Controller::Controller(int motor1,int motor2):Vertical(motor1),Horizontal(motor2){

};

void Controller::ServoControl(float image_y,float image_x)
{
    if(image_y>520){
        Vertical.clockwiseRotate();         //down
        delay(100);
    }else if(image_y<200){
        Vertical.antiClockRotate();         //up
        delay(100);
    }
    
    if(image_x>880){
        Horizontal.antiClockRotate();       //right
        delay(100);
    }else if(image_x<400){
        Horizontal.clockwiseRotate();       //left
        delay(100);
    }
    
}
