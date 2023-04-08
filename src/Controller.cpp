#include"Controller.h"
#include"motor.h"


void Controller::ServoControl(float image_y,float image_x)
{
    if(image_y>380)
    {
        if(image_x>660){
            Horizontal.antiClockRotate(); //right
            delay(50);
            Vertical.clockwiseRotate(); //down
            delay(50);
        }else if(image_x<620){
            Horizontal.clockwiseRotate(); //left
            delay(50);
            Vertical.clockwiseRotate(); //down
            delay(50);
        }
            
    }else if(image_y<340){
        if(image_x>660){
            Horizontal.antiClockRotate(); //right
            delay(50);
            Vertical.antiClockRotate(); //up
            delay(50);
        }else if (image_x<620){
            Horizontal.clockwiseRotate(); //left
            delay(50);
            Vertical.antiClockRotate(); //up
            delay(50);
        }
    }
}