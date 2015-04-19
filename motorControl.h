//calibration values used for each motor
#define rightMotorVelocityOffset 0
#define leftMotorVelocityOffset 0

//struct used to store each motor's values
typedef struct {
	float curSpeed;
	float calibrationOffset;
} motorRules;

//struct used to control both motors behaviours
typedef struct {
	float baseSpeed;
	float turnAcceleration;
	motorRules rightMotor;
	motorRules leftMotor;
} motorEngine;

void setupEngine();
void startMovement();
void turn();
void stopMovement();