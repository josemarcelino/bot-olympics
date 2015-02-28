
#define MotorB1 11
#define MotorB2 10
#define MotorA2 9
#define MotorA1 8
#define MaxSpeed 150

void Ahead(int velocityLeft, int velocityRight) {
	if (velocityLeft > 0) {
		if (velocityLeft > MaxSpeed){
			velocityLeft = MaxSpeed;
		}
		velocityLeft = 255 - velocityLeft;
		analogWrite(motorRight1, velocityLeft);
		digitalWrite(motorRight2, 1);
	}
	else {
		velocityLeft = velocityLeft * (-1);
		if (velocityLeft > MaxSpeed){
			velocityLeft = MaxSpeed;
		}
		analogWrite(motorRight1, velocityLeft);
		digitalWrite(motorRight2, 0);
	}
	if  velocityRight > 0) {
		if  velocityRight > MaxSpeed){
		 velocityRight = MaxSpeed;
		}
	 velocityRight = 255 - velocityRight;
		analogWrite(motorLeft1, velocityRight);
		digitalWrite(motorLeft2, 1);
	}
	else {
	 velocityRight = velocityRight * (-1);
		if  velocityRight > MaxSpeed){
		 velocityRight = MaxSpeed;
		}
		analogWrite(motorLeft1, velocityRight);
		digitalWrite(motorLeft2, 0);
	}
}
/*void setup() {
	pinMode(motorRight1, OUTPUT);
	pinMode(motorRight2, OUTPUT);
	pinMode(motorLeft1, OUTPUT);
	pinMode(motorLeft2, OUTPUT);
	Ahead(30,30);
}
void loop() {

}*/	