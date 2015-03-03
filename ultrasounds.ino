//pin declaration
#define trigPinLeft 2
#define echoPinLeft 3
#define trigPinRight 4
#define echoPinRight 5
#define motorLeft2 8
#define motorLeft1 9
#define motorRight2 10
#define motorRight1 11

//debug pins
#define debugLedGreen 7
#define debugLedRed 13

#define TRUE 1
#define FALSE 0

#define WALL_DISTANCE 15  //distance to keep from wall
#define LIMIT_MAX 30      //field of view (FoV) distance

#define FORWARD_SPEED 100 //movement speed
#define MaxSpeed 150      // --> variavel do marcelino

#define motorCalibrationOffset 1.5f   //motor calibration variable (multiplier of left motor's velocity while turning)
#define rotationVelocity 40           //'bonus' velocity for turning
#define TIME_BY_DEGREE 10             //time it takes, in mimllis, to complete a degree while turning

//flame related
#define flameDoubt 100    //readings above this CAN be a flame
#define flameCertain 500  //readings above this WILL be a flame

#define N_UNTIL_LOST 500  //number of measures until it is lost

#define TIME_TO_CM 58.2f  //variable to convert sonar readings to cm

#define WHITE_MIN_VALUE 290
#define BLACK_MAX_VALUE 100
#define MAX_COLOUR_VALUE 500

long durationRight, durationLeft;   //time until sonar signal is returned
long distanceRight, distanceLeft;   //distance calculation from time elapsed

int velocityRight = 50;   //
int velocityLeft = 50;    //

int timeout;              //sonar timeout calculated based on FoV distance
long int rotateTimer;     //timer used to rotate 'x' degrees in-place

int isLost = FALSE;       //variable used to check if robot is lost
int counterToLost = 0;    //variable used to set the max measures the robot can make before becoming lost

int isInRoom = FALSE;

void BruteForceRekt() {
  
  digitalWrite(trigPinLeft, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPinLeft, HIGH);
  delayMicroseconds(10);

  digitalWrite(trigPinLeft, LOW);
  int echoLeft = pulseIn(echoPinLeft, HIGH, timeout);
  
  
  if(echoLeft != 0 && echoLeft <= LIMIT_MAX){
    rotateInPlace(90, 1);
  }
  
  Control(FORWARD_SPEED/2, FORWARD_SPEED/2);
  delay(2000);
  Control(0,0);
  
}

void isInsideTheRoom() {
  int valueColourSensor = analogRead(A0);

  if(valueColourSensor < MAX_COLOUR_VALUE){
    if(valueColourSensor > WHITE_MIN_VALUE) {
      delay(100);
      if(isInRoom == FALSE){
        checkSurroundings();
      }
      isInRoom = 1 - isInRoom;
    }
  }
    //digitalWrite(13, HIGH);
    //digitalWrite(13, LOW);
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

void rotateLeft(){
  Control(velocityLeft+rotationVelocity,velocityRight);
}

void rotateRight() {
  Control(velocityLeft, velocityRight+rotationVelocity*motorCalibrationOffset);
}

//degrees to rotate, side as -1 or 1 to define left or right, respectively
void rotateInPlace(int degrees, int side) {
  rotateTimer = millis();
  //CAREFULL! if values are not calibrated (because of batteries), adjust 'rotationVelocity'
  Control(-rotationVelocity*side/1.4, rotationVelocity*side/1.4);
  while (millis() - rotateTimer < degrees*TIME_BY_DEGREE);
}

int canSeeFlames() {
  int flameLevel = analogRead(A1);
  if (flameLevel >= flameCertain) {
    //digitalWrite(7, HIGH);
    return 1;
  } 
  else if (flameLevel >= flameDoubt) {
    //digitalWrite(7, LOW);
    return 0;
  } 
  else {
    //digitalWrite(7, LOW);
    return -1;
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

  pinMode(A0, INPUT);
  //flame sensor
  pinMode(A1, INPUT);
  //flame pin
  pinMode(7, OUTPUT);

  //wall pin
  pinMode(13, OUTPUT);

  timeout = LIMIT_MAX*TIME_TO_CM;
  BruteForceRekt();
}

int foundWall() {
  //Serial.print("Wall at ");
  //Serial.println(distanceRight);
  return (distanceRight != 0) ? TRUE : FALSE;
}

//just light LED up when right sensor is seing a wall
void checkForWalls() {
  if (foundWall() == TRUE) {
    digitalWrite(13, HIGH);
  } 
  else {
    digitalWrite(13, LOW);
  }
}

//slowly rotates around to check for flames
//TODO if a flame is found, go towards it
void checkSurroundings() {
  Control(0, 0);
	 rotateInPlace(30, 1);	//rotate 30 degrees to the right
   	//get flame readings
   	rotateInPlace(30, 1);	//rotate again
   	//get flame readings
   	rotateInPlace(60, -1);	//if nothing was found, get back to patrolling
   
}

void loop() {

  isInsideTheRoom();

  if(isInRoom == TRUE){
      digitalWrite(13, HIGH);
  } else {
    digitalWrite(13, LOW);
  }

  Serial.print("COLOR: ");
  Serial.println(analogRead(A0));

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

  distanceLeft = durationLeft/TIME_TO_CM;
  distanceRight = durationRight/TIME_TO_CM;

  if (isLost == FALSE) {
    digitalWrite(7, LOW);
  } 
  else {
    digitalWrite(7, HIGH);
  }

  if (canSeeFlames() != 1) {
    if (isLost == TRUE) {
      Control(FORWARD_SPEED, FORWARD_SPEED);
      if ((distanceRight <= LIMIT_MAX/2 && distanceRight != 0) || (distanceLeft <= LIMIT_MAX && distanceLeft != 0)) {
        isLost = FALSE;
        counterToLost = 0;
      }
    } 
    else {
      if (distanceRight <= LIMIT_MAX/2 && distanceRight != 0) {
        Control(0, 0);
        
        rotateInPlace(90, 1);
      } 
      else {
        if(distanceLeft <= LIMIT_MAX && distanceLeft != 0) {
          if(distanceLeft > WALL_DISTANCE) {
            rotateLeft();
            if ((counterToLost++) >= N_UNTIL_LOST) {
              isLost = TRUE;
            }
            //Serial.println("Rotating Left");
          } 
          else if (distanceLeft < WALL_DISTANCE) {
            rotateRight();
            counterToLost = 0;
            //Serial.println("Rotating Right");
          } 
          else {
            //Serial.println("Moving ahead");
            Control(FORWARD_SPEED, FORWARD_SPEED);
            counterToLost = 0;
          }
        } 
        else {
          //Serial.println("Rotating Left");
          rotateLeft();
          if ((counterToLost++) >= N_UNTIL_LOST) {
            isLost = TRUE;
          }
        }
      }
    }
  } 
  else {
    int maxMeasure;
    int measure = analogRead(A1);
    delay(100);
    rotateInPlace(5, 1);
    int measure2 = analogRead(A1);
    delay(100);
    rotateInPlace(10, -1);
    int measure3 = analogRead(A1);

    if (measure >= measure2 && measure >= measure3) {
      rotateInPlace(5, 1);
      maxMeasure = measure;
    } 
    else if (measure2 >= measure && measure2 >= measure3) {
      rotateInPlace(10, 1);
      maxMeasure = measure2;
    } 
    else {
      maxMeasure = measure3;
    }

    Serial.println(measure);
    digitalWrite(7, HIGH);
    if (maxMeasure >= 600) {
      Control(0, 0);
      digitalWrite(13, HIGH);
      while (analogRead(A1) > 200) {
        delay(10);
      }
      digitalWrite(13, LOW);
    }
  }
  delay(10);
}

























