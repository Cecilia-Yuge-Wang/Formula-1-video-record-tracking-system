#include<wiringPi.h>
#include<softPwm.h>


class motor
{
private:
    int pinNumber;
    int pin;


public:
    motor(int i);
    void Rotate(float angle);

};