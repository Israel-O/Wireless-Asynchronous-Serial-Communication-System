#include <LiquidCrystal.h>  //to use the LCD screen
int ldrPin = A0; //ldr pin on arduino for reading analog data
int relay = 100; //manual light intensity to trigger reading mechanism from laser pointer
String rMessage;

LiquidCrystal lcd(7, 8, 9, 10, 11, 12);
int message = 0b1000000;
void setup() {
  Serial.begin(9600);  //begin serial to communicate using serial monitor
  pinMode(ldrPin, INPUT); 
  int ambient = analogRead(ldrPin);  //sets ambient to the light intensity of immediate environment to prevent false readings
  lcd.begin(16, 2);
}

int readLight(){  //return light intensity value
  return analogRead(ldrPin);
}

int readLaserMessage(int lightReading){  //convert laser pulses to binary
  message = 0b1000000;
  int count = 6; //used for indexing and iteration
  while (count >= 0){
    if (lightReading > relay){ //tests if data being received is from laser instead of environment
      bitSet(message, count); //convert bit to a 1 at position count
      count--;
      delay(1000);
    }
    else{
      count--;
      delay(1000);
    }
    delay(100); //delay to account for arduino slow response time 
    lightReading = readLight();
  }
  return message; //return binary string of laser message as an int
}
void loop() {
  int lightReading = readLight();
  if (lightReading > relay){ //tests if data being received is from laser instead of environment
    int message = readLaserMessage(lightReading); 
    rMessage += static_cast<char> (message); //convert binary int to a char
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
