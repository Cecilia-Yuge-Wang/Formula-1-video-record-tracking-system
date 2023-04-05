#include<wiringPi.h>
#include<softPwm.h>
#include "motor.h"

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

void motor::Rotate(float angle)
{
    if (angle > 180) {
        angle = 180;
    }
    else if (angle < 1) {
        angle = 1;
    }
    softPwmWrite(pin, (int)(angle * 10 / 180 + 2.5));
}

