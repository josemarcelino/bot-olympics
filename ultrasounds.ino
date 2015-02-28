#define trigPinRight 4
#define echoPinRight 5
#define trigPinLeft 2
#define echoPinLeft 3
#define WALL_DISTANCE 20
#define TRUE 1
#define FALSE 0
#define AJUSTANGLE 15
#define LIMIT_MAX 40

#define motorRight1 11
#define motorRight2 10
#define motorLeft2 8
#define motorLeft1 9
#define MaxSpeed 150
#define offSet 40
#define TIME_BY_DEGREE 80 

int maximumRange = 40;
int minimumRange = 10;
long durationRight, durationLeft, distanceRight, distanceLeft;
float mediaRight, mediaLeft, maxValueRight = 0.0f, maxValueLeft = 0.0f, minValueRight = 123125.0f, minValueLeft = 31245.0f;
float contador = 0.0f;
int ajustedLeft = FALSE;
int ajustedRight = FALSE;

int velocityRight = 50;
int velocityLeft = 50;


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

void rotateLeft(){
	Control(velocityLeft+offSet,velocityRight);
}

void rotateRight() {
	Control(velocityLeft, velocityRight+offSet);
}

void setup() {
	Serial.begin(9600);
	pinMode(trigPinLeft, OUTPUT);
	pinMode(echoPinLeft, INPUT);
	pinMode(trigPinRight, OUTPUT);
	pinMode(echoPinRight, INPUT);
	pinMode(motorRight1, OUTPUT);
	pinMode(motorRight2, OUTPUT);
	pinMode(motorLeft1, OUTPUT);
	pinMode(motorLeft2, OUTPUT);
}


void loop() {

	digitalWrite(trigPinLeft, LOW);
	delayMicroseconds(2);

	digitalWrite(trigPinRight, LOW);
	delayMicroseconds(2);

	digitalWrite(trigPinLeft, HIGH);
	delayMicroseconds(10);

	digitalWrite(trigPinRight, HIGH);
	delayMicroseconds(10);

	digitalWrite(trigPinLeft, LOW);
	digitalWrite(trigPinRight, LOW);

	durationLeft = pulseIn(echoPinLeft, HIGH, 3500);
	durationRight = pulseIn(echoPinRight, HIGH, 3500);

	//findFire
	//findGap

	distanceLeft = durationLeft/58.2;
	distanceRight = durationRight/58.2;

	if(distanceRight <= LIMIT_MAX && distanceRight != 0) {
		Control(0, 0);
		rotateRight();
	} else {
		if(distanceLeft <= LIMIT_MAX && distanceLeft != 0) {
			if(distanceLeft > WALL_DISTANCE) {
				rotateLeft();
				Serial.println("Rotating Left");
			} else if (distanceLeft < WALL_DISTANCE) {
				rotateRight();
				Serial.println("Rotating Right");
			} else {
				Serial.println("Moving ahead");
				Control(50, 50);
			}
		}else {
			Serial.println("Rotating Left");
			rotateLeft();
		}
	}
	Serial.print("VALUE: ");
	Serial.println(distanceLeft);
}













