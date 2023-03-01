#include <Servo.h>
#include <Ultrasonic.h>
Servo myServo;

String mycmd;
const int trigPin = 11;
int echoPin = 12;
boolean stop = true;
int lightpin = A0; // select the input pin for LDR
int sensorValue = 0; // variable to store the value coming from the sensor
void setup() {
  // put your setup code here, to run once:
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input

  Serial.begin(9600);
  myServo.attach(10);

}
void dclose(){
  if(stop == true){
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
      if(cm<20){
        if(sensorValue < 300){
          //Serial.print(cm);
          myServo.write(180);
          delay(2500);
          myServo.write(90);
          digitalWrite(13,1);
          stop = false;
        }
        else{
          //Serial.print(cm);
          myServo.write(180);
          delay(5000);
          myServo.write(90);
          stop = false;
        }
      }
    }
}
void lighthold(){
  sensorValue = analogRead(lightpin);
  //Serial.println(sensorValue);
  delay(100);
}
void loop() {
  // put your main code here, to run repeatedly:
  while(Serial.available()==0){
      dclose();
      lighthold();
  }
  
  mycmd = Serial.readStringUntil('\r');
  myServo.write(90);
  if(mycmd=="AON" or "GRAM" or "JO"){
    if(sensorValue < 300){
      myServo.write(0);
      delay(2500);
      myServo.write(90);
      stop = true;
    }
    else{
      myServo.write(0);
      delay(5000);
      myServo.write(90);
      stop = true;
    }
  }
}
long microsecondsToCentimeters(long microseconds)
{
// The speed of sound is 340 m/s or 29 microseconds per centimeter.
// The ping travels out and back, so to find the distance of the
// object we take half of the distance travelled.
return microseconds / 29 / 2;
}
