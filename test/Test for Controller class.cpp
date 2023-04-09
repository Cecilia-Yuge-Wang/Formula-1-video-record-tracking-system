#include<wiringPi.h>
#include<softPwm.h>
#include<iostream>
#include"../src/Controller.h"

#define motor1 17 //Vertical
#define motor2 27 //Horizontal

using namespace std;

int main()
{
    float y;
    float x;

    Controller Control(motor1,motor2);



    while(true)
    {
        cin>>y;
        cin>>x;
        
        ServoControl(y,x);
    }

    return 0;
}

