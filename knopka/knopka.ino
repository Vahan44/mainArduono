void setup() {
  pinMode(7, INPUT_PULLUP);
pinMode(13, OUTPUT);
Serial.begin(9600);
}
int i = 0;
void loop() {
 if(i % 2 == 0 && digitalRead(7) == 0){
  digitalWrite(13, 1);
  delay(100);
  i++;
  }
   if(i % 2 == 1 && digitalRead(7) == 1){
  digitalWrite(13, 1);
  delay(100);
  i++;
  }
  Serial.print(i);
 
}
