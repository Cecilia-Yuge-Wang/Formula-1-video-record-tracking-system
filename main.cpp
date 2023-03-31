#include<wiringPi.h>
#include<softPwm.h>
#include<iostream>
#include "motor.h"

#define motor1 17 //vertical
#define motor2 27 //horizontal

using namespace std;

int main()
{
    motor verticalMotor(motor1);
    motor horizontalMotor(motor2);

    while (true)
    {
        char choice = getchar();
    
        switch (choice)
        {
            case 'a':
                //turning left 
                horizontalMotor.clockwiseRotate();
                break;
            
            case 'd':
                //turning right
                horizontalMotor.antiClockRotate();
                break;
            
            case 'w':
                //turning up
                verticalMotor.clockwiseRotate();
                break;
            
            case 's':
                //turning down
                verticalMotor.antiClockRotate();
                break;
            
            default:
                break;
        }
    }
    
    return 0;
}
