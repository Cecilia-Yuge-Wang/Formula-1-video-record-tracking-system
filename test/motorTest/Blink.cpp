﻿#include <wiringPi.h>
#include <softPwm.h>
#include <iostream>

#define motor1  27//方向机
#define	motor2	17//高低机

using namespace std;

void normalScanning();
void verticalScanning();
void turnleft(int);
void turnright(int);
void turnup(int);
void turndown(int);
void rotateleft();
void rotateright();

int main(void)
{
	wiringPiSetupSys();

	pinMode(motor1, OUTPUT);
	pinMode(motor2, OUTPUT);

	softPwmCreate(motor1, 0, 400);
	softPwmCreate(motor2, 0, 400);

	
	/*delay(1000);
	softPwmWrite(motor1, 5);
	softPwmWrite(motor2, 15);*/

	bool running = true;

	while (running)
	{
		char input;
		std::cin>>input;

		switch (input)
		{
		case '1':
			rotateleft();
			break;
		case '2':
			rotateright();
			break;
		case '3':
			running = false;
			break;
		
		default:
			std::cout<<"Useless command"<<std::endl;
			break;
		}

		
	}

	/*delay(1000);
	softPwmWrite(motor1, pwmVal);
	softPwmWrite(motor2, pwmVal);*/

	return 0;
}

void normalScanning()
{
	for (int j = 13.3; j > 8.3; j--)
	{
		softPwmWrite(motor2, j);
		for (int i = 6.7; i <= 13.3; i++)
		{
			softPwmWrite(motor1, i);
			delay(50);
		}

		for (int i = 13.3; i >= 6.7; i--)
		{
			softPwmWrite(motor1, i);
			delay(50);
		}
	}
}

void verticalScanning()
{
	for (int i = 9; i <= 11; i++)
	{
		softPwmWrite(motor1, i);
		for (int j = 4; j <= 18; j++)
		{
			softPwmWrite(motor2, j);
			delay(50);
		}

		for (int i = 18; i < 4; i--)
		{
			softPwmWrite(motor2, i);
			delay(50);
		}
	}
}

void turnleft(int pwm)
{
	int newVal = 0;
	int pwmVal = pwm;
	newVal = pwmVal-1;
	softPwmWrite(motor1, newVal);

}

void turnright(int pwm)
{
	int newVal, pwmVal;
	pwmVal = pwm;
	newVal = pwmVal + 1;
	softPwmWrite(motor1, newVal);

}

void turnup(int pwm)
{
	int newVal = 0;
	int pwmVal = pwm;
	newVal = pwmVal - 1;
	softPwmWrite(motor2, newVal);
}

void turndown(int pwm)
{
	int newVal = 0;
	int pwmVal = pwm;
	newVal = pwmVal + 1;
	softPwmWrite(motor2, newVal);
}


void rotateleft()
{
	softPwmWrite(motor1,1);
}

void rotateright()
{
	softPwmWrite(motor1,20);
}