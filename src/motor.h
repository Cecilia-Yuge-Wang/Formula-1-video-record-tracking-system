#include<wiringPi.h>
#include<softPwm.h>


class motor
{
private:
    int pinNumber;
    int currentAngle = 1;
    int pin;


public:
    motor(int i);
    void clockwiseRotate();
    void antiClockRotate();
    void Rotate(float angle);
    
};