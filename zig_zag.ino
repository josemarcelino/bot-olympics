#define trigPinRight 4
#define echoPinRight 5
#define trigPinLeft 2
#define echoPinLeft 3
#define TRUE 1
#define FALSE 0

#define colorPin A2

#define FORWARD_SPEED 100

#define motorRight1 11
#define motorRight2 10
#define motorLeft2 8
#define motorLeft1 9
#define MaxSpeed 150

int maximumRange = 40;
int minimumRange = 10;
long durationRight, durationLeft, distanceRight, distanceLeft;
long lastDistanceRight = 0;
float mediaRight, mediaLeft, maxValueRight = 0.0f, maxValueLeft = 0.0f, minValueRight = 123125.0f, minValueLeft = 31245.0f;
float contador = 0.0f;
int ajustedLeft = FALSE;
int ajustedRight = FALSE;

int velocityRight = 50;
int velocityLeft = 50;

int timeout;
int isSearching = FALSE;
long int rotateTimer;

int globalTimer = 0;

void rotateLeft(){
	Control(velocityLeft+offSet,velocityRight);
}

void rotateRight() {
	Control(velocityLeft, velocityRight+offSet);
}

//degrees to rotate, side as -1 or 1 to define left or right, respectively
void rotateInPlace(int degrees, int side) {
	//CAREFULL! if values are not calibrated (because of batteries), adjust 'offset'
	Control(-offSet*side/1.4, offSet*side/1.4);
	while (millis() - rotateTimer < degrees*TIME_BY_DEGREE);
}

int canSeeFlames() {
	int flameLevel = analogRead(A1);
	if (flameLevel >= flameCertain) {
		digitalWrite(7, HIGH);
		return 1;
	} else if (flameLevel >= flameDoubt) {
		digitalWrite(7, LOW);
		return 0;
	} else {
		digitalWrite(7, LOW);
		return -1;
	}
}

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

	pinMode(A2, INPUT);

	//flame sensor
	pinMode(A1, INPUT);
	//flame pin
	pinMode(7, OUTPUT);

	//wall pin
	pinMode(13, OUTPUT);

	timeout = LIMIT_MAX*58.2f;
}

int insideRoom() {
	int value = digitalRead(colorPin);
	return value;

}

void loop() {
	digitalWrite(trigPinLeft, LOW);
	delayMicroseconds(2);

	digitalWrite(trigPinLeft, HIGH);
	delayMicroseconds(10);

	digitalWrite(trigPinLeft, LOW);
	durationLeft = pulseIn(echoPinLeft, HIGH, timeout);

	digitalWrite(trigPinRight, LOW);
	delayMicroseconds(2);

	digitalWrite(trigPinRight, HIGH);
	delayMicroseconds(10);

	digitalWrite(trigPinRight, LOW);

	durationRight = pulseIn(echoPinRight, HIGH, timeout);

	distanceLeft = durationLeft/58.2;
	distanceRight = durationRight/58.2;

	Serial.println(insideRoom());

}











