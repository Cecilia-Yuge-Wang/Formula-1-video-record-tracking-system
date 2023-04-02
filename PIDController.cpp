#include "PIDController.h"

PIDController::PIDController(double Kp, double Ki, double Kd)
{
    Kp = Kp; 
    Ki = Ki;
    Kd = Kd;
    Error = 0;
    LastError = 0;
    LastlastError = 0;
    PidOutput = 0;
    SystemOutput = 0;
    LastSystemOutput = 0;
}

double PIDController::calculate(double input, double target) {
    Error = target - input;
    PidOutput = Kp * (Error - LastError) + Ki * Error + Kd * (Error - 2 * LastError + LastlastError);

    LastlastError = LastError;
    LastError = Error;
    
    return PidOutput;
}