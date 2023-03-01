int sensorPin = A0; // select the input pin for LDR
int sensorValue = 0; // variable to store the value coming from the sensor
int ledpin = 13;

void setup() {
  Serial.begin(9600); // sets serial port for communication
  pinMode(ledpin,OUTPUT);
}

void loop() {
  sensorValue = analogRead(sensorPin); // read the value form the sensor
  Serial.println(sensorValue); //prints the values coming from the sensor on the screen
  delay(100);
  if(sensorValue <300){
    digitalWrite(ledpin,HIGH);
  }
  else digitalWrite(ledpin,LOW);
}
