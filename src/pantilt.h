#include<wiringPi.h>
#include<softPwm.h>
#include<iostream>
#include"../src/motor.h"

using namespace std;

class pantilt
{
public:
    pantilt(int verticalPin, int horizontalPin):horizontal(horizontalPin),vertical(verticalPin){};
    void left();
    void right();
    void up();
    void down();

private:
    motor horizontal;
    motor vertical;
};