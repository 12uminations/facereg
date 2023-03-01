
const int trigPin = 11;
int echoPin = 12 ;
void setup() {
  Serial.begin(9600);

}

void Button_Press(){
 
  
}



void Sensor_flood(){
    long duration, cm;
    pinMode(trigPin, OUTPUT);
    pinMode(3, OUTPUT);
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(5);
    digitalWrite(trigPin, LOW);
    pinMode(echoPin, INPUT);
    duration = pulseIn(echoPin, HIGH);

    cm = microsecondsToCentimeters(duration);
    delay(100);
    Serial.println(cm); 

    
  
}




void loop(){
  Sensor_flood();
}




long microsecondsToCentimeters(long microseconds)
{
// The speed of sound is 340 m/s or 29 microseconds per centimeter.
// The ping travels out and back, so to find the distance of the
// object we take half of the distance travelled.
return microseconds / 29 / 2;
}
