#include<wiringPi.h>
#include<softPwm.h>
#include<iostream>
#include"../src/motor.h"
#include"../src/pantilt.h"

using namespace std;

pantilt::pantilt(int verticalPin, int horizontalPin):horizontal(horizontalPin),vertical(verticalPin)
{
    std::cout<<"pantilt is initialized"<<std::endl;
};


void pantilt::left()
{
    horizontal.antiClockRotate();
    delay(50);
}

void pantilt::right()
{
    horizontal.clockwiseRotate();
    delay(50);
}

void pantilt::up()
{
    vertical.clockwiseRotate();
    delay(50);
}

void pantilt::down()
{
    vertical.antiClockRotate();
    delay(50);
}