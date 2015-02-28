#define trigPinRight 4
#define echoPinRight 5
#define trigPinLeft 2
#define echoPinLeft 3
#define flameSensor A1

int maximumRange = 40;
int minimumRange = 10;
long durationRight, durationLeft, distanceRight, distanceLeft;
float mediaRight, mediaLeft, maxValueRight = 0.0f, maxValueLeft = 0.0f, minValueRight = 123125.0f, minValueLeft = 31245.0f;
float contador = 0.0f;


void setup() {
	Serial.begin(9600);
	pinMode(trigPinLeft, OUTPUT);
	pinMode(echoPinLeft, INPUT);
	pinMode(trigPinRight, OUTPUT);
	pinMode(echoPinRight, INPUT);
	pinMode(flameSensor, INPUT);
}


void loop() {
	digitalWrite(trigPinRight, LOW);
	digitalWrite(trigPinLeft, LOW);
	delayMicroseconds(2);

	digitalWrite(trigPinRight, HIGH);
	digitalWrite(trigPinLeft, HIGH);
	delayMicroseconds(10);

	digitalWrite(trigPinRight, LOW);
	digitalWrite(trigPinLeft, LOW);
	durationRight  = pulseIn(echoPinRight, HIGH);
	durationLeft = pulseIn(echoPinLeft, HIGH);
	int valueFlameSensor = analogRead(flameSensor);

	Serial.println(durationLeft);

	//distanceRight = durationRight/58.2;
	//distanceLeft = durationLeft/58.2;

   /*if((distanceRight >= maximumRange && distanceLeft >= maximumRange) || (distanceRight <= minimumRange && distanceLeft <= minimumRange)) {

	}*/
/*
	contador+=1;
	mediaRight+=distanceRight;
	mediaLeft+=distanceLeft;
	if(maxValueLeft < distanceLeft) {
		maxValueLeft = distanceLeft;
	}

	if(maxValueRight < distanceRight) {
		maxValueRight = distanceRight;
	}

	if(minValueLeft > distanceLeft) {
		minValueLeft = distanceLeft;
	}

	if(minValueRight > distanceRight) {
		minValueRight = distanceRight;
	}

	/*Serial.println("Valor do pin esquerdo: " + distanceLeft + "; Valor do pin direito: " + distanceRight);*/
	//if(contador == 10){
		/*mediaRight/=contador;
		mediaLeft/=contador;
		contador = 0;
		Serial.print("mediaRight: ");
		Serial.print(mediaRight);
		Serial.print(" || mediaLeft: ");
		Serial.println(mediaLeft);
		Serial.print("menor Valor Right: ");
		Serial.print(minValueRight);
		Serial.print(" || Menor Valor Left: ");
		Serial.println(minValueLeft);
		Serial.print("Maior Valor Right: ");
		Serial.print(maxValueRight);
		Serial.print(" || Maior Valor Left: ");
		Serial.println(maxValueLeft);

		mediaRight = 0.0f;
		mediaLeft = 0.0f;
		minValueRight = 21231425.0f;
		minValueLeft = 2847358.0f;
		maxValueLeft = 0.0f;
		maxValueRight = 0.0f;
		*/
	//}
	

}






















