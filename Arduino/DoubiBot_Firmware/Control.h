#pragma once
#include <Servo.h>


enum LIFT_STATE
{
	ON_DRAW,
	BETWEEN_NUMS,
	LIFTED
};

class Control
{
public:
	Control(int pin_lift, int pin_left, int pin_right);
	void Calibrate();

	void DrawNumber(float bx, float by, int num, float scale);
	void DrawWeatherIcon(float bx, float by, int type, float scale);

	void Lift(LIFT_STATE s);
	void GoTo(double pX, double pY);
	void GoHome();
	void Clear();

	bool CmdRoutine();


private:
	// When in calibration mode, adjust the following factor until the servos move exactly 90 degrees
	int SERVOFAKTOR = 550;

	// Zero-position of left and right servo
	// When in calibration mode, adjust the NULL-values so that the servo arms are at all times parallel
	// either to the X or Y axis
	int SERVOLEFTNULL = 1800;
	int SERVORIGHTNULL = 1100;

	int LIFT0 = 1650;
	int LIFT1 = 1550;
	int LIFT2 = 1350;


	int SERVOPINLIFT = 12;
	int SERVOPINLEFT = 5;
	int SERVOPINRIGHT = 14;

	// speed of liftimg arm, higher is slower
	int LIFTSPEED = 1500;

	// 悬臂的长度，根据图纸测量，无需改变
	int L1 = 35;
	int L2 = 57.2;
	int L3 = 13;

	// 左右舵机轴心的位置，根据图纸测量，无需改变
	int O1X = 22;
	int O1Y = -25;
	int O2X = 47;
	int O2Y = -25;

	volatile double lastX = 35;
	volatile double lastY = 50;
	volatile int servoLift = 1500;

	Servo servo_lift;
	Servo servo_left;
	Servo servo_right;

	char comdata[256], data_p; //串口缓存数据
	long time;


	void circleClockwise(float bx, float by, float radius, int start, int ende, float sqee);

	void circleAntiClockwise(float bx, float by, float radius, int start, int ende, float sqee);


	double return_angle(double a, double b, double c);

	void set_XY(double Tx, double Ty);
};