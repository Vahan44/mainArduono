#include "VolAnalyzer.h"
VolAnalyzer analyzer(A0);
void setup() {
  // put your setup code here, to run once:+
pinMode(7, INPUT);
pinMode(6, OUTPUT);
Serial.begin(9600);


}
int i = 0;
int aj;
void loop() {
    if(analyzer.tick()) {
   aj = map(analyzer.getRaw(), 0, 450, 0, 100);
    
   Serial.println(digitalRead(7));
if(digitalRead(7) == 0 && i == 0 || aj > 99){
  digitalWrite(6, 1);
  delay(500);
    i = 1;
    aj = 0;
}
if(digitalRead(7) == 0 && i == 1 || aj > 99){
  digitalWrite(6, 0);
  delay(500);
    i = 0;

}
Serial.print(aj);

}
}
