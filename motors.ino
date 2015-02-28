#define offSet 20
#define velocityRight 50
#define velocityLeft 50
#define TIME_BY_DEGREE 80 

void Control(int velocityLeft, int velocityRight) {
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
	if  (velocityRight > 0) {
		if (velocityRight > MaxSpeed){
		 	velocityRight = MaxSpeed;
		}
	 	velocityRight = 255 - velocityRight;
		analogWrite(motorLeft1, velocityRight);
		digitalWrite(motorLeft2, 1);
	}
	else {
	 	velocityRight = velocityRight * (-1);
		if (velocityRight > MaxSpeed){
		 velocityRight = MaxSpeed;
		}
		analogWrite(motorLeft1, velocityRight);
		digitalWrite(motorLeft2, 0);
	}
}

void rotateRight(){
	Control(velocityLeft,velocityRight-offSet);
}

void rotateLeft() {
	Control(velocityLeft-offSet, velocityRight);
}
