#define trigPinRight 4
#define echoPinRight 5
#define trigPinLeft 2
#define echoPinLeft 3

int maximumRange = 40;
int minimumRange = 10;
long durationRight durationLeft, distanceRight, distanceLeft;
float mediaRight, mediaLeft, maxValueRight = 0.0f, maxValueLeft = 0.0f, minValueRight = 123125636322.0f, minValueLeft = 3124536323.0f;
float contador = 0.0f;


void setup() {
	Serial.begin(9600);
	pinMode(trigPinLeft, OUTPUT);
	pinMode(echoPinLeft, INPUT);
	pinMode(trigPinRight, OUTPUT);
	pinMode(echoPinRight, INPUT);
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

	distanceRight = durationRight/58.2;
	distanceLeft = durationLeft/58.2;

   /*if((distanceRight >= maximumRange && distanceLeft >= maximumRange) || (distanceRight <= minimumRange && distanceLeft <= minimumRange)) {

	}*/

	contador+=1;
	mediaRight+=distanceRight;
	medialeft+=distanceLeft;
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
	if(contador == 1000) {
		mediaRight/=contador;
		mediaLeft/=contador;
		contador = 0;
		Serial.println("Media de Right: " + mediaRight + " || Media de Left: " + mediaLeft);
		Serial.println("Menor Valor Right: " + minValueRight + " || Menor Valor Left: " + minValueLeft);
		Serial.println("Maior Valor Right: " + maxValueRight + " || Maior Valor Left: " + maxValueLeft);
		mediaRight = 0.0f;
		mediaLeft = 0.0f;
		minValueRight = 21231425.0f;
		minValueLeft = 2847358.0f;
		maxValueLeft = 0.0f;
		maxValueRight = 0.0f;
	}

}






















