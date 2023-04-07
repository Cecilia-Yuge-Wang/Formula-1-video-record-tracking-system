#ifndef pantilt_H
#define pantilt_H

#include<wiringPi.h>
#include<softPwm.h>
#include<iostream>
#include"../src/motor.h"

using namespace std;

class pantilt
{
public:
    pantilt(int verticalPin, int horizontalPin);
    void left();
    void right();
    void up();
    void down();

private:
    motor horizontal;
    motor vertical;
};

#endif