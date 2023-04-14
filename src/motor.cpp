#include<wiringPi.h>
#include "motor.h"

motor::motor(int i)
{
    pin = i;
    wiringPiSetupGpio();
    pinMode(pin, PWM_OUTPUT);
    pwmSetMode(PWM_MODE_MS);
    pwmSetRange(200);
    pwmSetClock(1920);
}

void motor::clockwiseRotate()
{
    currentAngle += 4;// turning 4 degree in one time

    if(currentAngle > 180) // check the current angle value, if it is beyond the maximum angle of the motor, then set to the maximum value
           {
            currentAngle = 180;
           }
            
            pwmWrite(pin, (int)(currentAngle / 180.0 * 40)); //turn the angle into the pwm value, and control the motor.
}

void motor::antiClockRotate()//similar with the upside function
{
    currentAngle -= 4;
            if(currentAngle < 1)
            {
                currentAngle = 1;
            }
            pwmWrite(pin, (int)(currentAngle / 180.0 * 40));
}