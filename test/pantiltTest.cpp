#include<wiringPi.h>
#include<iostream>
#include"../src/pantilt.h"

using namespace std;

#define motor1 17;//高低机
#define motor2 27;//方向机

int main()
{
    pantilt myPantilt(17, 27);

    while (true)
    {
        myPantilt.right();
    }

    return 0;
}