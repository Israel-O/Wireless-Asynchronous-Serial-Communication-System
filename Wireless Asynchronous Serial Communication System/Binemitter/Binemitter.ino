int laser = 13;

void setup() {
  Serial.begin(9600);
  pinMode(laser, OUTPUT);
  digitalWrite(laser,LOW);

}
int get_from_serial(){
  int character = Serial.read();
  return character;
}

String toBinary(int n)
{
    String r;
    while(n!=0) {r = (n % 2 == 0 ? "0" : "1") + r; n /= 2;}
    return r;
}

void laserOn(){
  digitalWrite(laser, HIGH);
}

void laserOff(){
  digitalWrite(laser, LOW);
}
void laserMessage(String binary){
  for (int i = 0; i <= binary.length(); i++){
    if (binary[i] == '1'){
      laserOn();
    }
    else if (binary[i] == '0'){
      laserOff();
    }
    delay(1000);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  while (Serial.available() > 0){
    int character = get_from_serial();
    if (character != 10){
      String binary = toBinary(character);
      Serial.println(binary);
      laserOff();
      laserMessage(binary);
      laserOff();
    }
  }
}
