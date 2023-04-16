#ifndef motor_H
#define motor_H

#include<wiringPi.h>


class motor
{
private:
    int pinNumber;
    int currentAngle = 90;
    int pin;


public:
    motor(int i);
    void clockwiseRotate();
    void antiClockRotate();
    
};

#endif 