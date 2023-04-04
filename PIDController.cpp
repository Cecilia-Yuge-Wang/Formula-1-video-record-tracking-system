#include "PIDController.h"
#include<iostream>

void PIDController::PID_Init(float kp, float ki, float kd)
{
    KP = kp;
    KI = ki;
    KD = kd;
    Error = 0;
    Increment = 0;
    LastError = 0;
    LastlastError = 0;
    PidOutput = 0;

}

float PIDController::calculate(float input, float target) {
    Error = target - input;
    Increment = KP * (Error - LastError) + KI * Error + KD * (Error - 2 * LastError + LastlastError);
    PidOutput = PidOutput + Increment;

    LastlastError = LastError;
    LastError = Error;

    return PidOutput;
}