
// int nearLimitColor = 30;

boolean amIInsideTheRoom() {

	int valueColourSensor = analogRead(A0);

	if(valueFlameSensor >= nearLimitColor)
		return 1;
	else
		return 0;

}