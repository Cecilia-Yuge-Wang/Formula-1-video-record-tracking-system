





class PIDController {

public:
	PIDController(double Kp, double Ki, double Kd);
	double calculate(double input, double target);

private:
	double Kp;
	double Ki;
	double Kd;

	double Error;
	double LastError;
	double LastlastError;

	double PidOutput;
	double SystemOutput;
	double LastSystemOutput;
};
