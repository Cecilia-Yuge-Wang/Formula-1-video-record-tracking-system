#include <iostream>
#include <wiringPi.h>
#include <unistd.h>

const int pwm_pin = 18; // GPIO 18

int main()
{
    if (wiringPiSetupGpio() == -1) // Initialize the wiringPi library and use the BCM pin 
    {
        std::cerr << "Failed to initialize wiringPi" << std::endl;
        return 1;
    }

    pinMode(pwm_pin, PWM_OUTPUT); // Setting a Pin as PWM Output
    pwmSetMode(PWM_MODE_MS); // Setting PWM Mode to Mark-Space Mode
    
    int pwm_range = 200;
    int pwm_frequency = 50;
    int pwm_clock = 19200000 / (pwm_range * pwm_frequency);
    
    pwmSetRange(pwm_range);
    pwmSetClock(pwm_clock);

    int duty_cycle_left = 5; // Duty cycle 2.5%
    int duty_cycle_right = 25; // Duty cycle 12.5%

    pwmWrite(pwm_pin, duty_cycle_left); // Setting Duty Cycle and Starting PWM Signal Output
    sleep(2); // delay 2 s

    pwmWrite(pwm_pin, duty_cycle_right); // Setting Duty Cycle and Starting PWM Signal Output
    sleep(2); // delay 2 s
    
    pwmWrite(pwm_pin, 0); // turn off pwm

    return 0;
}
