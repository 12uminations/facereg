#include <Servo.h>
Servo myServo;
Servo urServo;
void setup() {
  // put your setup code here, to run once:
  urServo.attach(5);
}

void loop() {
  // put your main code here, to run repeatedly:
  urServo.write(0);
}
