#include<wiringPi.h>
#include<softPwm.h>
#include<iostream>
#include"../src/pantilt.h"
#define motor1 17 // Vertical
#define motor2 27 // Horizontal

using namespace std;

int main()
{
    pantilt Pantilt(motor1,motor2);

    float image_y;
    float image_x;



    while(true)
    {
        cin >> image_y;
        cin >> image_x;
        
        if(image_y>360)
        {
            Pantilt.up();
        }else{
            Pantilt.down();
        }

        if(image_x>640){
            Pantilt.left();
        }else{
            Pantilt.right();
        }

    }

}