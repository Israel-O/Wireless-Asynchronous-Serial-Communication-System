int laser = 13;  //Laser pointer pin

void setup() {
  Serial.begin(9600);  //start the serial monitor
  pinMode(laser, OUTPUT);
  digitalWrite(laser,LOW);

}
int get_from_serial(){  //return the users text from the serial monitor as a character
  int character = Serial.read();
  return character;
}

String toBinary(int n) //convert users text to binary and return as a string
{
    String r;
    while(n!=0) {r = (n % 2 == 0 ? "0" : "1") + r; n /= 2;}
    return r;
}

void laserOn(){ //turn laser on
  digitalWrite(laser, HIGH);
}

void laserOff(){ //turn laser off
  digitalWrite(laser, LOW);
}
void laserMessage(String binary){  //Turn laser on/off with regards to the binary string obtained
  for (int i = 0; i <= binary.length(); i++){
    if (binary[i] == '1'){  //turn laser on if '1' is encounterd in the binary string
      laserOn();
    }
    else if (binary[i] == '0'){ ////turn laser off if '0' is encounterd in the binary string
      laserOff();
    }
    delay(1000);  //stop execution for one second
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  while (Serial.available() > 0){  //if the user has entered a text, perform the following actions
    int character = get_from_serial();  //get users text as a character
    if (character != 10){ //10 is defined as '\n' in binary from the ASCII table, it indicates that the user has entered all the text they want
      String binary = toBinary(character);  //convert character to binary
      Serial.println(binary);  //display binary on serial monitor
      laserOff();
      laserMessage(binary); //laser responds to binary string
      laserOff();
    }
  }
}
