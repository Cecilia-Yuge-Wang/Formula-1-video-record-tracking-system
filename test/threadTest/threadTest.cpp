#include <iostream>
#include <thread>
#include "motor.h"
#include "Controller.h"

#define motor1 17 // Vertical
#define motor2 27 // Horizontal

int main()
{
    Controller controller(motor1,motor2);
    float rx = 150;
    float ry = 1080;

    controller.getCoordinate(ry, rx);
    

}