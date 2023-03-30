#include<wiringPi.h>
#include<softPwm.h>

using namespace std;

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
    
};