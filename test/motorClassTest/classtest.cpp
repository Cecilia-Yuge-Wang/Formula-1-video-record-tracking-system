#include<wiringPi.h>
#include<softPwm.h>

#define motor1 27;//方向机
#define motor2 17;//高低机

using namespace std;

class motor
{
private:
    int pinNumber;
    int currentAngle = 0;
    int pin;


public:
    motor(int i);
    void clockwiseRotate();
    void antiClockRotate();
    
};

motor::motor(int i)
{
    pin = i;
    wiringPiSetupSys();
    softPwmCreate(pin, 0, 100);
}

void motor::clockwiseRotate()
{
    currentAngle += 15;
    if(currentAngle > 180)
           {
            currentAngle = 180;
           }
            
            softPwmWrite(pin, (int)(currentAngle / 180.0 * 20.0));
}

void motor::antiClockRotate()
{
    currentAngle -= 15;
    currentAngle -= 15;
            if(currentAngle < 1)
            {
                currentAngle = 1;
            }
            softPwmWrite(pin, (int)(currentAngle / 180.0 * 20.0));
}



