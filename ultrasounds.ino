#define trigPinRight 4
#define echoPinRight 5
#define trigPinLeft 2
#define echoPinLeft 3
#define WALL_DISTANCE 15
#define TRUE 1
#define FALSE 0
#define AJUSTANGLE 15
#define LIMIT_MAX 30

#define FORWARD_SPEED 100

#define motorRight1 11
#define motorRight2 10
#define motorLeft2 8
#define motorLeft1 9
#define MaxSpeed 150
#define offSet 40
#define TIME_BY_DEGREE 10 

#define patrolTime 3

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

//degrees to rotate, side as -1 or 1 to define left or right, respectively
void rotateInPlace(int degrees, int side) {
	//CAREFULL! if values are not calibrated (because of batteries), adjust 'offset'
	Control(-offSet*side/1.4, offSet*side/1.4);
	while (millis() - rotateTimer < degrees*TIME_BY_DEGREE);
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

	timeout = LIMIT_MAX*58.2f;
	globalTimer = millis();
}

int foundWall() {
	Serial.print("Wall at ");
	Serial.println(distanceRight);
	return (distanceRight != 0) ? TRUE : FALSE;
}

//just light LED up when right sensor is seing a wall
void checkForWalls() {
	if (foundWall() == TRUE) {
		pinMode(13, OUTPUT);
		digitalWrite(13, HIGH);
	} else {
		digitalWrite(13, LOW);
	}
}

//slowly rotates around to check for flames
//TODO if a flame is found, go towards it
void checkSurroundings() {
	rotateInPlace(30, 1);	//rotate 30 degrees to the right
	//get flame readings
	rotateInPlace(30, 1);	//rotate again
	//get flame readings
	rotateInPlace(60, -1);	//if nothing was found, get back to patrolling
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

	//if already was walking for more than 'patrolTime'
	if (millis()-globalTimer >= patrolTime) {
		checkSurroundings();		//look around for flame
		globalTimer = millis();		//update timer
	}

	//for DEBUG purposes, checks if 'right sensor' is seing a wall
	checkForWalls();

	if (distanceRight <= LIMIT_MAX/2 && distanceRight != 0) {
		Control(0, 0);
		Serial.println("Rotating Right (IF)");
		rotateTimer = millis();
		//rotateRight();
		rotateInPlace(90, 1);
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
				Control(FORWARD_SPEED, FORWARD_SPEED);
			}
		} else {
			Serial.println("Rotating Left");
			rotateLeft();
		}
	}
	/*Serial.print("VALUE: ");
	Serial.println(distanceLeft);*/

	lastDistanceRight = distanceRight;
}













