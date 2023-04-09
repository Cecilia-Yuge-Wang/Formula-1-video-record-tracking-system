#ifndef Controller_H
#define Controller_H

#include"motor.h"

class Controller
{
private:
    motor Vertical;
    motor Horizontal;
public:
    Controller(int motor1, int motor2);
    void ServoControl(float image_y, float image_x);
};

#endif