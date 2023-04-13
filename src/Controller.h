#ifndef Controller_H
#define Controller_H
#include<thread>
#include<time.h>
#include"motor.h"

class Controller
{
private:
    motor Vertical;
    motor Horizontal;
    float image_y;
    float image_x;

public:
    Controller(int motor1, int motor2);
    void getCoordinate(float y, float x);
    void ServoControl(float image_y, float image_x);
    void controlThread();
    void printCoordinate();
    void control();
};

#endif