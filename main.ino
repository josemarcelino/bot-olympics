#include "motorControl.c"

#define TRUE 1
#define FALSE 0

typedef struct {
	int motorRight 1;
	int motorLeft 2;
} pinList;

motorEngine* curEngine;

//switch between engines for different sets of speeds
motorEngine regularEngine;
motorEngine acceleratedEngine;

//pin-out container
pinList pins;

void setup() {
	//engines setup
	curEngine = &regularEngine;
	setupEngine(regularEngine, 100, 30);
	setupEngine(acceleratedEngine, 200, 60);
}

void loop() {
	//algorithm();
	writeMotorValues();
	delay(2000);
}

//function used to write motor values
void writeMotorValues() {
	analogWrite(pins.rightMotor, curEngine->rightMotor.curSpeed);
	analogWrite(pins.leftMotor, curEngine->leftMotor.curSpeed);
}