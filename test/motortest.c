#include<wiringPi.h>
#include<softPwm.h>
#include<iostream>
#include"../src/motor.h"
#define motor1 17 // Vertical
#define motor2 27 // Horizontal

using namespace std;

int main()
{
    float image_y;
    float image_x;



    while(true)
    {
        cin >> image_y;
        cin >> image_x;
        
        if(image_y>360)
        {
            motor1.clockwiseRotate();
        }else{
            motor1.antiClockRotate();
        }

        if(image_x>640){
            motor2.clockwiseRotate();
        }else{
            motor2.antiClockRotate();
        }
        

    }

}