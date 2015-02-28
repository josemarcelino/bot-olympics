
// pinMode(A1, INPUT);
// int nearLimitFlame = 30;

boolean canISeeTheFlame() {

	int valueFlameSensor = analogRead(A1);

	if(valueFlameSensor >= nearLimitFlame)
		return 1; // 
	else
		return 0;

}

void lookForFireDirection(){
//Robot already inside Room, fire confirmed
	int max = analogRead(A1);
	int actualread = max;

	while(max <= actualRead){
		max = actualRead;
		actualRead = analogRead(A1);
		// rotate()
	}

	//goForward()
	//rektDatCandle()
}






	






