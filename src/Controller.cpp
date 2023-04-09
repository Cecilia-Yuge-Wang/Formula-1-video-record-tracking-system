#include"Controller.h"
#include"motor.h"

Controller::Controller(int motor1,int motor2):Vertical(motor1),Horizontal(motor2){};

void Controller::ServoControl(float image_y,float image_x)
{
    if(image_y>380 && image_x>660){         //Direction: Bottom Right
        Horizontal.antiClockRotate();       //right
        delay(50);
        Vertical.clockwiseRotate();         //down
        delay(50);
    }else if(image_y>380 && image_x<620){   //Direction: Bottom Left
        Horizontal.clockwiseRotate();       //left
        delay(50);
        Vertical.clockwiseRotate();         //down
        delay(50);
    }else if(image_y<340 && image_x>660){   //Direction: Top Right
        Horizontal.antiClockRotate();       //right
        delay(50);
        Vertical.antiClockRotate();         //up
        delay(50);
    }else if(image_y<340 && image_x<620){   //Direction: Top Left
        Horizontal.clockwiseRotate();       //left
        delay(50);
        Vertical.antiClockRotate();         //up
        delay(50);
    }
}
