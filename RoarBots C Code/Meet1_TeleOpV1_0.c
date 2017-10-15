#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTServo,  none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Motor,  mtr_S1_C1_1,     leftMotor,     tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     rightMotor,    tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_1,     motorF,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     motorG,        tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S1_C3_1,    servo1,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_2,    servo2,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "JoystickDriver.c"

task main()
{

	while(true)
	{
		getJoystickSettings(joystick);

		//get joystick values
		int leftJoyVal = joystick.joy1_y1;
		int rightJoyVal = joystick.joy1_y2;

		//process joystick values
		if(rightJoyVal <= 20)
			rightJoyVal = 0;
		if(leftJoyVal <= 20)
			leftJoyVal = 0;

		//Set joystick values to a ratio
		rightJoyVal/=(127/100);
		leftJoyVal/=(127/100);

		//set motor speeds
		motor[leftMotor] = leftJoyVal;
		motor[rightMotor] = rightJoyVal;



	}
}
