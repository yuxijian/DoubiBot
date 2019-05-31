#include "Control.h"

Control::Control(int pin_lift, int pin_left, int pin_right)
{
	GoTo(35, 50);

	servo_lift.attach(pin_lift);  //  lifting servo
	servo_left.attach(pin_left);  //  left servo
	servo_right.attach(pin_right);  //  right servo
	delay(100);

	Lift(LIFT_STATE::BETWEEN_NUMS);
	GoTo(35, 50);
}

void Control::Calibrate()
{
	while (true)
	{
		GoTo(-3, 29.2);
		delay(1000);
		GoTo(74.1, 28);
		delay(1000);
	}
}

bool Control::CmdRoutine()
{
	int p, x, y;

	while (Serial.available() > 0)
	{
		char nullByte = char(Serial.read());
		if (nullByte == '\n')
		{
			comdata[data_p] = nullByte;
			data_p = 0;

			switch (comdata[0])
			{
			case 'G':
				strtok(comdata, ",");
				x = atoi(strtok(NULL, ","));
				y = atoi(strtok(NULL, "\n"));

				x = constrain(x, 5, 70);
				y = constrain(y, 20, 50);
				GoTo(x, y);

				Serial.println("Ok");
				break;

			case 'L':
				strtok(comdata, ",");
				x = atoi(strtok(NULL, ","));

				switch (x)
				{
				case 1:
					Lift(LIFT_STATE::ON_DRAW);
					Serial.println("Lift state: ON_DRAW");
					break;

				case 2:
					Lift(LIFT_STATE::BETWEEN_NUMS);
					Serial.println("Lift state: BETWEEN_NUMS");
					break;

				case 3:
					Lift(LIFT_STATE::LIFTED);
					Serial.println("Lift state: LIFTED");
					break;
				default:
					break;
				}

				break;

			case 'H':
				GoHome();
				Serial.println("Ok, homed");

				break;
			}
		}
		else
		{
			comdata[data_p] = nullByte;
			data_p++;
		}
	}

	return true;
}


void Control::DrawNumber(float bx, float by, int num, float scale)
{
	switch (num)
	{

	case 0:
		GoTo(bx + 12 * scale, by + 6 * scale);
		Lift(LIFT_STATE::ON_DRAW);
		circleAntiClockwise(bx + 7 * scale, by + 10 * scale, 10 * scale, -0.8, 6.7, 0.5);
		Lift(LIFT_STATE::BETWEEN_NUMS);
		break;
	case 1:
		GoTo(bx + 3 * scale, by + 15 * scale);
		Lift(LIFT_STATE::ON_DRAW);
		GoTo(bx + 10 * scale, by + 20 * scale);
		GoTo(bx + 10 * scale, by + 0 * scale);
		Lift(LIFT_STATE::BETWEEN_NUMS);
		break;
	case 2:
		GoTo(bx + 2 * scale, by + 12 * scale);
		Lift(LIFT_STATE::ON_DRAW);
		circleClockwise(bx + 8 * scale, by + 14 * scale, 6 * scale, 3, -1.6, 1);
		GoTo(bx + 1 * scale, by + 0 * scale);
		GoTo(bx + 12 * scale, by + 0 * scale);
		Lift(LIFT_STATE::BETWEEN_NUMS);
		break;
	case 3:
		GoTo(bx + 2 * scale, by + 17 * scale);
		Lift(LIFT_STATE::ON_DRAW);
		circleClockwise(bx + 5 * scale, by + 15 * scale, 5 * scale, 3, -2, 1);
		circleClockwise(bx + 5 * scale, by + 5 * scale, 5 * scale, 1.57, -3, 1);
		Lift(LIFT_STATE::BETWEEN_NUMS);
		break;
	case 4:
		GoTo(bx + 10 * scale, by + 0 * scale);
		Lift(LIFT_STATE::ON_DRAW);
		GoTo(bx + 10 * scale, by + 20 * scale);
		GoTo(bx + 2 * scale, by + 6 * scale);
		GoTo(bx + 12 * scale, by + 6 * scale);
		Lift(LIFT_STATE::BETWEEN_NUMS);
		break;
	case 5:
		GoTo(bx + 2 * scale, by + 5 * scale);
		Lift(LIFT_STATE::ON_DRAW);
		circleAntiClockwise(bx + 5 * scale, by + 6 * scale, 6 * scale, -2.5, 2, 1);
		GoTo(bx + 5 * scale, by + 20 * scale);
		GoTo(bx + 12 * scale, by + 20 * scale);
		Lift(LIFT_STATE::BETWEEN_NUMS);
		break;
	case 6:
		GoTo(bx + 2 * scale, by + 10 * scale);
		Lift(LIFT_STATE::ON_DRAW);
		circleClockwise(bx + 7 * scale, by + 6 * scale, 6 * scale, 2, -4.4, 1);
		GoTo(bx + 11 * scale, by + 20 * scale);
		Lift(LIFT_STATE::BETWEEN_NUMS);
		break;
	case 7:
		GoTo(bx + 2 * scale, by + 20 * scale);
		Lift(LIFT_STATE::ON_DRAW);
		GoTo(bx + 12 * scale, by + 20 * scale);
		GoTo(bx + 2 * scale, by + 0);
		Lift(LIFT_STATE::BETWEEN_NUMS);
		break;
	case 8:
		GoTo(bx + 5 * scale, by + 10 * scale);
		Lift(LIFT_STATE::ON_DRAW);
		circleClockwise(bx + 5 * scale, by + 15 * scale, 5 * scale, 4.7, -1.6, 1);
		circleAntiClockwise(bx + 5 * scale, by + 5 * scale, 5 * scale, -4.7, 2, 1);
		Lift(LIFT_STATE::BETWEEN_NUMS);
		break;

	case 9:
		GoTo(bx + 9 * scale, by + 11 * scale);
		Lift(LIFT_STATE::ON_DRAW);
		circleClockwise(bx + 7 * scale, by + 15 * scale, 5 * scale, 4, -0.5, 1);
		GoTo(bx + 5 * scale, by + 0);
		Lift(LIFT_STATE::BETWEEN_NUMS);
		break;

	case 111:

		Lift(LIFT_STATE::ON_DRAW);
		GoTo(70, 46);
		GoTo(65, 43);

		GoTo(65, 49);
		GoTo(5, 49);
		GoTo(5, 45);
		GoTo(65, 45);
		GoTo(65, 40);

		GoTo(5, 40);
		GoTo(5, 35);
		GoTo(65, 35);
		GoTo(65, 30);

		GoTo(5, 30);
		GoTo(5, 25);
		GoTo(65, 25);
		GoTo(65, 20);

		GoTo(5, 20);
		GoTo(60, 44);

		GoTo(75.2, 47);
		Lift(LIFT_STATE::LIFTED);

		break;

	case 11:
		GoTo(bx + 5 * scale, by + 15 * scale);
		Lift(LIFT_STATE::ON_DRAW);
		circleAntiClockwise(bx + 5 * scale, by + 15 * scale, 0.1 * scale, 1, -1, 1);
		delay(200);
		Lift(LIFT_STATE::BETWEEN_NUMS);
		GoTo(bx + 5 * scale, by + 5 * scale);
		Lift(LIFT_STATE::ON_DRAW);
		circleAntiClockwise(bx + 5 * scale, by + 5 * scale, 0.1 * scale, 1, -1, 1);
		delay(200);
		Lift(LIFT_STATE::BETWEEN_NUMS);
		break;

	}
}

void Control::DrawWeatherIcon(float bx, float by, int type, float scale)
{
	switch (type)
	{
	case 1: //sunny
		GoTo(bx + 10 * scale, by + 10 * scale);
		Lift(LIFT_STATE::ON_DRAW);
		circleAntiClockwise(bx + 10 * scale, by + 10 * scale, 8 * scale, -0.8, 7, 1);
		Lift(LIFT_STATE::BETWEEN_NUMS);

		GoTo(bx + 10 * scale, by + 22 * scale);
		Lift(LIFT_STATE::ON_DRAW);
		delay(200);
		Lift(LIFT_STATE::BETWEEN_NUMS);
		GoTo(bx + 19 * scale, by + 19 * scale);
		Lift(LIFT_STATE::ON_DRAW);
		delay(200);
		Lift(LIFT_STATE::BETWEEN_NUMS);
		GoTo(bx + 22 * scale, by + 10 * scale);
		Lift(LIFT_STATE::ON_DRAW);
		delay(200);
		Lift(LIFT_STATE::BETWEEN_NUMS);
		GoTo(bx + 19 * scale, by + 1 * scale);
		Lift(LIFT_STATE::ON_DRAW);
		delay(200);
		Lift(LIFT_STATE::BETWEEN_NUMS);
		GoTo(bx + 10 * scale, by - 2 * scale);
		Lift(LIFT_STATE::ON_DRAW);
		delay(200);
		Lift(LIFT_STATE::BETWEEN_NUMS);
		GoTo(bx + 1 * scale, by + 1 * scale);
		Lift(LIFT_STATE::ON_DRAW);
		delay(200);
		Lift(LIFT_STATE::BETWEEN_NUMS);
		GoTo(bx + -2 * scale, by + 10 * scale);
		Lift(LIFT_STATE::ON_DRAW);
		delay(200);
		Lift(LIFT_STATE::BETWEEN_NUMS);
		GoTo(bx + 1 * scale, by + 19 * scale);
		Lift(LIFT_STATE::ON_DRAW);
		delay(200);
		break;
	}
}

void Control::Lift(LIFT_STATE s)
{
	int target;

	switch (s)
	{
	case LIFT_STATE::ON_DRAW:
		target = LIFT0;
		break;
	case LIFT_STATE::BETWEEN_NUMS:
		target = LIFT1;
		break;
	case LIFT_STATE::LIFTED:
		target = LIFT2;
		break;
	}

	if (servoLift > target)
	{
		while (servoLift > target)
		{
			servoLift--;
			servo_lift.writeMicroseconds(servoLift);
			delayMicroseconds(LIFTSPEED);
		}
	}
	else
	{
		while (servoLift < target)
		{
			servoLift++;
			servo_lift.writeMicroseconds(servoLift);
			delayMicroseconds(LIFTSPEED);
		}

	}
}

void Control::circleClockwise(float bx, float by, float radius, int start, int ende, float sqee)
{
	float inkr = -0.05;
	float count = 0;

	do
	{
		GoTo(sqee * radius * cos(start + count) + bx,
			radius * sin(start + count) + by);
		count += inkr;
	} while ((start + count) > ende);

}

void Control::circleAntiClockwise(float bx, float by, float radius, int start, int ende, float sqee)
{
	float inkr = 0.05;
	float count = 0;

	do
	{
		GoTo(sqee * radius * cos(start + count) + bx,
			radius * sin(start + count) + by);
		count += inkr;
	} while ((start + count) <= ende);
}

void Control::GoTo(double pX, double pY)
{
	double dx, dy, c;
	int i;

	// dx dy of new point
	dx = pX - lastX;
	dy = pY - lastY;
	//path lenght in mm, times 4 equals 4 steps per mm
	c = floor(4 * sqrt(dx * dx + dy * dy));

	if (c < 1) c = 1;

	for (i = 0; i <= c; i++)
	{
		// draw line point by point
		set_XY(lastX + (i * dx / c), lastY + (i * dy / c));
	}

	lastX = pX;
	lastY = pY;
}

void Control::GoHome()
{
	Lift(LIFT_STATE::LIFTED);
	GoTo(75.2, 49);
	Lift(LIFT_STATE::BETWEEN_NUMS);
	Serial.println("Ok, homed");
}

void Control::Clear()
{
	DrawNumber(3, 3, 111, 1);
}

double Control::return_angle(double a, double b, double c)
{
	// cosine rule for angle between c and a
	return acos((a * a + c * c - b * b) / (2 * a * c));
}

void Control::set_XY(double Tx, double Ty)
{
	delay(1);
	double dx, dy, c, a1, a2, Hx, Hy;

	// calculate triangle between pen, servoLeft and arm joint
	// cartesian dx/dy
	dx = Tx - O1X;
	dy = Ty - O1Y;

	// polar lemgth (c) and angle (a1)
	c = sqrt(dx * dx + dy * dy); // 
	a1 = atan2(dy, dx); //
	a2 = return_angle(L1, L2, c);

	servo_left.writeMicroseconds(floor(((a2 + a1 - M_PI) * SERVOFAKTOR) + SERVOLEFTNULL));

	// calculate joinr arm point for triangle of the right servo arm
	a2 = return_angle(L2, L1, c);
	Hx = Tx + L3 * cos((a1 - a2 + 0.621) + M_PI); //36,5бу
	Hy = Ty + L3 * sin((a1 - a2 + 0.621) + M_PI);

	// calculate triangle between pen joint, servoRight and arm joint
	dx = Hx - O2X;
	dy = Hy - O2Y;

	c = sqrt(dx * dx + dy * dy);
	a1 = atan2(dy, dx);
	a2 = return_angle(L1, (L2 - L3), c);

	servo_right.writeMicroseconds(floor(((a1 - a2) * SERVOFAKTOR) + SERVORIGHTNULL));


	//Serial.print(floor(((a2 + a1 - M_PI) * SERVOFAKTOR) + SERVOLEFTNULL));
	//Serial.print(" ");
	//Serial.println(floor(((a2 + a1 - M_PI) * SERVOFAKTOR) + SERVOLEFTNULL));

}
