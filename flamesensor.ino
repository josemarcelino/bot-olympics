
// pinMode(A1, INPUT);
// int nearLimit = 30;

boolean canISeeTheFlame() {

	int valueFlameSensor = analogRead(A1);

	if(valueFlameSensor >= nearLimit)
		return 1;
	else
		return 0;

}