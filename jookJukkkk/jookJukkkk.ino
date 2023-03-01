#include <Servo.h>
Servo myServo;
int button = 12 ;
int val = 0 ;
int a=0;
bool i = true;
void setup() {
  pinMode(button, INPUT);
   Serial.begin(9600);
    myServo.attach(13);

}
void but(){
  val = digitalRead(button);
  if(val == HIGH){
    a++ ;
    delay(1000);
    Serial.print("NUM : ");
    Serial.println(a);
  }
}
  
void loop(){
  but();
  if(i == true){
    if(a%2 != 0){
      myServo.write(0);
      delay(135);
      a++;
      i = false;
     }
    else myServo.write(90);
  }
  else{
    if(a%2 != 0){
      myServo.write(180);
      delay(135);
      a++;
      i = true;
     }
    else myServo.write(90); 
  }
   


}
