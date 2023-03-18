#include<iostream>
using namespace std;

int main()
{
	double Kp;
	double Ki;
	double Kd;

	double Error=0;
	double LastError=0;
	double LastlastError=0;

	double PIDOutput=0;
	double SystemOutput=0;
	double LastSystemOutput=0;

	double Input;
	cin >> Input;
	Kp = 0.1;
	Ki = 0.1;
	Kd = 0.5;
	do {
		Error = Input - PIDOutput;
		cout << PIDOutput << " ";
		PIDOutput = PIDOutput + \
			Kp * (Error - LastError) + Ki * Error + Kd * (Error - 2 * LastError + LastlastError);
		cout << PIDOutput << endl;
		LastlastError = LastError;
		LastError = Error;
	} while (abs(PIDOutput - Input) > 0.5);
}