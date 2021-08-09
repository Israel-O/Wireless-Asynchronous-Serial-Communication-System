#include <LiquidCrystal.h>
int ldrPin = A0;
int relay = 100;
String rMessage;

LiquidCrystal lcd(7, 8, 9, 10, 11, 12);
int message = 0b1000000;
void setup() {
  Serial.begin(9600);
  pinMode(ldrPin, INPUT);
  int ambient = analogRead(ldrPin);
  lcd.begin(16, 2);
}

int readLight(){
  return analogRead(ldrPin);
}

int readLaserMessage(int lightReading){
  message = 0b1000000;
  int i = 6;
  int count = 6;
  while (i >= 0){
    if (lightReading > relay){
      bitSet(message, i);
      i--;
      delay(1000);
    }
    else{
      i--;
      delay(1000);
    }
    delay(100);
    lightReading = readLight();
  }
  return message;
}
void loop() {
  int lightReading = readLight();
  if (lightReading > relay){
    int message = readLaserMessage(lightReading);
    rMessage += static_cast<char> (message);
    lcd.setCursor(0, 0);
    if (message != 0b1000000){
      lcd.print(rMessage);
    }
    else{
      lcd.clear();
      rMessage = "";
    }
    
  }
  


}
