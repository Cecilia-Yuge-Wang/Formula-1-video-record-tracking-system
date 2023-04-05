


class PIDController {

public:
	void PID_Init(float kp, float ki, float kd);
	float calculate(float input, float target);


private:
	float KP;
	float KI;
	float KD;

	float Error;
	float LastError;
	float LastlastError;

	float Increment;
	float PidOutput;

};
