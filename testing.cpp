#include <wiringPi.h>
#include <softPwm.h>
#include <iostream>

#define motor1  27//方向机
#define	motor2	17//高低机

using namespace std;

int main()
{
    wiringPiSetupSys();

    softPwmCreate(motor1, 0, 100);
    int currentAngle=0;
    while (true)
    {
        int input;
        std::cin>>input;

        if (input == 1)
        {
           currentAngle  += 15;
           if(currentAngle>180)
           {
            currentAngle = 180;
           }
            
            softPwmWrite(motor1, (int)(currentAngle / 180.0 * 20.0) );
        }
    }

    return 0;
}