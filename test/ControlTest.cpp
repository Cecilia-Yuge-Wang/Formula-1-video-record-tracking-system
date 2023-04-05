#include<wiringPi.h>
#include<softPwm.h>
#include<iostream>
#include "../src/motor.h"
#include "../src/PIDController.h"

#define motor1 17 //vertical
#define motor2 27 //horizontal

using namespace std;

int main()
{
    float image_y;
    float image_x;
    float pid_y;
    float pid_x;

    PIDController PID_Y;
    PIDController PID_X;
    PID_Y.PID_Init(1, 0.05, 0);
    PID_X.PID_Init(1, 0.1, 0);

    motor verticalMotor(motor1);
    motor horizontalMotor(motor2);


    while (true) {

        cin >> image_y;
        cin >> image_x;

        pid_y += PID_Y.calculate(720 / 2, image_y);
        pid_x += PID_X.calculate(1280 / 2, image_x);

        verticalMotor.Rotate(pid_y);
        horizontalMotor.Rotate(pid_x);


    }



}
