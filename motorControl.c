#include "motorControl.h"

void setupEngine(motorEngine engineToSetup, float baseSpeed, float turnAcceleration) {
	engineToSetup.baseSpeed = baseSpeed;
	engineToSetup.turnAcceleration = turnAcceleration;
	engineToSetup.rightMotor.curSpeed = 0.0f;
	engineToSetup.rightMotor.calibrationOffset = rightMotorVelocityOffset;
	engineToSetup.leftMotor.curSpeed = 0.0f;
	engineToSetup.leftMotor.calibrationOffset = leftMotorVelocityOffset;
}

//function used to set the motor's speed values to default
void startMovement() {
	curEngine->rightMotor.curSpeed = curEngine->baseSpeed + curEngine->rightMotor.calibrationOffset;
	curEngine->leftMotor.curSpeed = curEngine->baseSpeed + curEngine->leftMotor.calibrationOffset;
}

//function used to turn right/left
void turn(int side) {
	if (side == -1) {	//turn left
		curEngine->rightMotor.curSpeed = curEngine->leftMotor.curSpeed + curEngine->turnAcceleration + curEngine->rightMotor.calibrationOffset;	//puts rightMotor at turning speed
	}
	else if (side == 1) {	//turn right
		curEngine->leftMotor.curSpeed = curEngine->rightMotor.curSpeed + curEngine->turnAcceleration + curEngine->leftMotor.calibrationOffset;	//puts leftMotor at turning speed
	}
}

//function used to stop motors
void stopMovement() {
	curEngine->rightMotor.curSpeed = 0.0f;
	curEngine->leftMotor.curSpeed = 0.0f;
}