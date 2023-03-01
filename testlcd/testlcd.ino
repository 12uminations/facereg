#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2); //0x27 
void setup() {
  // put your setup code here, to run once:
  lcd.begin();
  lcd.backlight();
}

void loop() {
  // put your main code here, to run repeatedly:
  lcd.setCursor(0,0);
  lcd.print("Hello World");
  delay(3000);
  lcd.clear();

  lcd.setCursor(0,1);
  lcd.print("LMOA U SUCK");
  delay(3000);
  lcd.clear();
}
