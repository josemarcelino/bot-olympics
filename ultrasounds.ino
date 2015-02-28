#define trigPinRight 4
#define echoPinRight 5
#define trigPinLeft 2
#define echoPinLeft 3
#define WALL_DISTANCE 10*58.2
#define TRUE 1
#define FALSE 0
#define AJUSTANGLE 15
#define LIMIT_MAX 20*58.2

int maximumRange = 40;
int minimumRange = 10;
long durationRight, durationLeft, distanceRight, distanceLeft;
float mediaRight, mediaLeft, maxValueRight = 0.0f, maxValueLeft = 0.0f, minValueRight = 123125.0f, minValueLeft = 31245.0f;
float contador = 0.0f;
int ajustedLeft = FALSE;
int ajustedRight = FALSE;

void setup() {
	Serial.begin(9600);
	pinMode(trigPinLeft, OUTPUT);
	pinMode(echoPinLeft, INPUT);
	pinMode(trigPinRight, OUTPUT);
	pinMode(echoPinRight, INPUT);
}


void loop() {

	digitalWrite(trigPinLeft, LOW);
	delayMicroseconds(2);

	digitalWrite(trigPinLeft, HIGH);
	delayMicroseconds(10);

	digitalWrite(trigPinLeft, LOW);

	durationLeft = pulseIn(echoPinLeft, HIGH);

	//findFire
	//findGap

	//distanceRight = durationRight/58.2;
	distanceLeft = durationLeft/58.2;
	Control(100, 100);
	if(distanceLeft <= LIMIT_MAX) {
		if(distanceLeft > WALL_DISTANCE && ajustedLeft == FALSE) {
			RotateLeft(AJUSTANGLE);
			ajustedLeft = TRUE;
			ajustedRight = FALSE;
		} else if(distanceLeft < WALL_DISTANCE && adjustedRight == FALSE) {
			RotateRight(AJUSTANGLE);
			ajustedLeft = FALSE;
			ajustedRight = TRUE;
		} 
	} else {
		rotateLeft(AJUSTANGLE);
	}
}













