#include <Servo.h>
#include <Ultrasonic.h>
Servo myServo;
String mycmd;
#define BUZZER 9
const int pingPin = 6;
int inPin = 7;
int button = 8 ;
int FuncON = 0;
int val = 0;
int pushed = 0 ;
int a = 0;
int cm ;
int cm2;
int i=0;
int poten;
int potpin = 1;
int van=1;
const int trigPin = 11;
int echoPin = 12;
boolean stop = false;
int lightpin = A0; // select the input pin for LDR
int sensorValue = 0; // variable to store the value coming from the 
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2); //0x27 

void setup() {
   Serial.begin(9600);
    pinMode(button, INPUT);
    pinMode(BUZZER,OUTPUT);
    pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
    pinMode(echoPin, INPUT); // Sets the echoPin as an Input
    Serial.begin(9600);
    myServo.attach(10);
    lcd.begin();
    lcd.backlight();
}
void soundAlarm(){
    digitalWrite(BUZZER,HIGH);
    tone(BUZZER,500);
    delay(10);
    noTone(BUZZER);
    delay(50);
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
        //Serial.print(cm);
        if(sensorValue < 300){
          lcd.setCursor(0,0);
          lcd.print("GATE CLOSING");
          myServo.write(180);
          delay(2500);
          lcd.clear();
          myServo.write(90);
          stop = false;
        }
        else{
          lcd.setCursor(0,0);
          lcd.print("GATE CLOSING");
          myServo.write(180);
          delay(350);
          lcd.clear();
          myServo.write(90);
          stop = false;
        }
      }
    }
}
void pot() {
  poten = analogRead(potpin);            // reads the value of the potentiometer (value between 0 and 1023)
  poten = map(poten, 0, 1023, 0, 179);     // scale it for use with the servo (value between 0 and 180)
  myServo.write(poten);                  // sets the servo position according to the scaled value
  delay(500);                           // waits for the servo to get there
}

void sensorflood(){

    long duration, cm2;
    pinMode(pingPin, OUTPUT);
    pinMode(3, OUTPUT);
    digitalWrite(pingPin, LOW);
    delayMicroseconds(2);
    digitalWrite(pingPin, HIGH);
    delayMicroseconds(5);
    digitalWrite(pingPin, LOW);
    pinMode(inPin, INPUT);
    duration = pulseIn(inPin, HIGH);
    cm2 = microsecondsToCentimeters(duration);
    if(cm2 < 20 ){
       delay(10);
       Serial.println(cm2);
       soundAlarm();
       light();
       lcd.setCursor(0,0);
       lcd.print("FLOOD !!");
       if(van==1){
        myServo.write(0);
        delay(350);
        myServo.write(90);
        van++;
        }
     }
    if(cm2>20){
      van=1;
      delay(10);
      Serial.println(cm2);
      lcd.clear();
     }
  
}

void light(){
  digitalWrite(13, HIGH);
  delay(10);
  digitalWrite(13, LOW);
  delay(10);
}
void lighthold(){
  sensorValue = analogRead(lightpin);
  //Serial.println(sensorValue);
  delay(100);
  if(sensorValue <300) digitalWrite(13,1);
  else digitalWrite(13,0);
}


void loop(){

  
    while(Serial.available()==0){
      pot();
      sensorflood();
      dclose();
      lighthold();
    }
  
    mycmd = Serial.readStringUntil('\r');
    myServo.write(90);
    if(mycmd=="AON" or "GRAM" or "JO"){
      if(sensorValue < 300){
        lcd.setCursor(0,0);
        lcd.print("GATE OPENING");
        myServo.write(0);
        delay(2500);
        myServo.write(90);
        lcd.clear();
        stop = true;
        }
      else{
        lcd.setCursor(0,0);
        lcd.print("GATE OPENING");
        myServo.write(0);
        delay(350);
        lcd.clear();
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
