#include<wiringPi.h>
#include<iostream>

#define pin 12;

using namespace std;

int main()
{
    wiringPiSetupSys();

    pinMode(12, PWM_OUTPUT);

    pwmSetMode(PWM_MODE_MS);

    pwmSetRange(2000);

    pwmSetClock(192);
    
    while (true)
    {
        
        std::cout<<"-90 degree"<<std::endl;
        pwmWrite(12, 50);
        delay(500);

        std::cout<<"-45 degree"<<std::endl;
        pwmWrite(12, 100);
        delay(500);

        std::cout<<"-45 degree"<<std::endl;
        pwmWrite(12, 150);
        delay(500);
    }
    
    return 0;
}