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
    currentAngle += 4;// turning 4 degree in one time

    if(currentAngle > 180) // check the current angle value, if it is beyond the maximum angle of the motor, then set to the maximum value
           {
            currentAngle = 180;
           }
            
            softPwmWrite(pin, (int)(currentAngle / 180.0 * 20.0)); //turn the angle into the pwm value, and control the motor.
}

void motor::antiClockRotate()//similar with the upside function
{
    currentAngle -= 4;
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

