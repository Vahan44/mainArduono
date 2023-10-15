
#include <Servo.h>

Servo vho;  // create servo object to control a servo

int potpin = A5;  // analog pin used to connect the potentiometer
int val;    // variable to read the value from the analog pin

void setup() {
pinMode(A5, INPUT);
Serial.begin(9600);
  vho.attach(5);  // attaches the servo on pin 9 to the servo object
}

void loop() {
  val = analogRead(potpin);            // reads the value of the potentiometer (value between 0 and 1023)
  val = map(val, 0, 1023, 0, 180); 
Serial.println(val);
  vho.write(val);                  // sets the servo position according to the scaled value
  //delay(15);                           // waits for the servo to get there
}