void setup() {
 Serial.begin(9600);
 pinMode(A0,INPUT); 
}

void loop() {
  
 int LDRvalue = analogRead(A0);

  Serial.println(LDRvalue);
  delay(100);
 
  
}
