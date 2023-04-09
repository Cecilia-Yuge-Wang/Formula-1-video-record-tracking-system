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

    motor Vertical(motor1);
    motor Horizontal(motor2);

    while(true)
    {
        cin >> image_y;
        cin >> image_x;
        
        if(image_y>360)
        {
            if(image_x>640){
                Horizontal.antiClockRotate(); //right
                delay(100);
                Vertical.clockwiseRotate(); //down
                delay(100);
            }else{
                Horizontal.clockwiseRotate(); //left
                delay(100);
                Vertical.clockwiseRotate(); //down
                delay(100);
            }
            
        }else if(image_y<360){
            if(image_x>640){
                Horizontal.antiClockRotate(); //right
                delay(100);
                Vertical.antiClockRotate(); //up
                delay(100);
            }else{
                Horizontal.clockwiseRotate(); //left
                delay(100);
                Vertical.antiClockRotate(); //up
                delay(100);
            }
        }

 /*       if(image_y>360)
        {
            Vertical.clockwiseRotate(); //up
            delay(50);
        }else{
            Vertical.antiClockRotate(); //down
            delay(50);
        }

        if(image_x>640){
            Horizontal.antiClockRotate(); //right
            delay(50);
        }else{
            Horizontal.clockwiseRotate(); //left
            delay(50);
        }
        
*/

    }

}
