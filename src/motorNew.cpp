#include<wiringPi.h>
#include<softPwm.h>
#include "motorNew.h"

motor::motor(int i)
{
    pin = i;
    wiringPiSetupSys();
    softPwmCreate(pin, 0, 100);
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

