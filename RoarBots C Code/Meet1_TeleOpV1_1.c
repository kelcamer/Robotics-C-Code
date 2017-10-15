#pragma config(Hubs,	S1, HTMotor,	HTMotor,	HTServo,	none)
#pragma config(Sensor, S1,		 ,							 sensorI2CMuxController)
#pragma config(Motor,	 mtr_S1_C1_1,			leftMotor,		 tmotorTetrix, openLoop)
#pragma config(Motor,	 mtr_S1_C1_2,			rightMotor,		 tmotorTetrix, openLoop)
#pragma config(Motor,	 mtr_S1_C2_1,			spinner,			 tmotorTetrix, openLoop)
#pragma config(Motor,	 mtr_S1_C2_2,			shoulder,			 tmotorTetrix, openLoop)
#pragma config(Servo,	 srvo_S1_C3_1,		elbow,								tServoContinuousRotation)
#pragma config(Servo,	 srvo_S1_C3_2,		claw,									tServoContinuousRotation)
#pragma config(Servo,	 srvo_S1_C3_3,		servo3,								tServoNone)
#pragma config(Servo,	 srvo_S1_C3_4,		servo4,								tServoNone)
#pragma config(Servo,	 srvo_S1_C3_5,		servo5,								tServoNone)
#pragma config(Servo,	 srvo_S1_C3_6,		servo6,								tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard							 !!*//

void initialiazeRobot(){
	nMotorEncoder[leftMotor] = 0;
	nMotorEncoder[rightMotor] = 0;
	nMotorEncoder[spinner] = 0;
	nMotorEncoder[shoulder] = 0;
	servoTarget[elbow] = 0;
	servoTarget[claw] = 0;
	motor[leftMotor] = 0;
	motor[rightMotor] = 0;
	motor[spinner] = 0;
	motor[shoulder] = 0;
}

#include "JoystickDriver.c"

task main()
{
	while(true)
	{
		getJoystickSettings(joystick);
		int minClawVal = 0; // random value
		int maxClawVal = 500; // random value
		int minElbowVal = 0; // random value
		int maxElbowVal = 500; // random value

		initializeRobot();

		///////////////////		Joystick #1 (Driver)	///////////////////

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

		//spinner forward
		if(joy1Btn(6))
			motor[spinner]=70;
		motor[spinner]=0;

		//spinner backward
		if(joy1Btn(8))
			motor[spinner]=-70;
		motor[spinner]=0;

		///////////////////		Joystick #2 (Manipulator) ///////////////////

		//shoulder
		if(joy2Btn(6))
			motor[shoulder]=70;
		motor[shoulder]=0;

		//shoulder backwards
		if(joy2Btn(8))
			motor[shoulder]=-70;
		motor[shoulder]=0;

		servoChangeRate[servo1] = 2;

		while(servoTarget[elbow]<minElbowVal && servoTarget[elbow]>maxElbowVal)
		{
			//elbow up
			if(joy2Btn(3))
				servoTarget[elbow]+=1;

			//elbow down
			if(joy2Btn(2))
				servoTarget[elbow]-=1;
			servoTarget[elbow] = ServoValue[elbow];
		}

		while(servoTarget[claw]<minClawVal && servoTarget[claw]>maxClawVal)
		{
			//open claw
			if(joy2Btn(5))
				servoTarget[claw]+=1;
			servoTarget[claw] = ServoValue[claw];

			//close claw
			if(joy2Btn(7))
				servoTarget[claw]-=1;
			servoTarget[claw] = ServoValue[claw];
		}

	}
}