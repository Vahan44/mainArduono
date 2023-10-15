const int trigPin = 12;
const int echoPin = 13;
const int elo = 5;// defines variables
long duration;
int distance;



#include <Adafruit_NeoPixel.h>
//#ifdef __AVR__
//#include <avr/power.h> // Required for 16 MHz Adafruit Trinket
//#endif

#define PIN_NEO_PIXEL 11  // Arduino pin that connects to NeoPixel
#define NUM_PIXELS 60     // The number of LEDs (pixels) on NeoPixel

Adafruit_NeoPixel NeoPixel(NUM_PIXELS, PIN_NEO_PIXEL, NEO_GRB + NEO_KHZ800);

void setup() {
  pinMode(trigPin, OUTPUT);  // Sets the trigPin as an Output
  pinMode(echoPin, INPUT);   // Sets the echoPin as an Input
  NeoPixel.begin();
 


  pinMode(A1, INPUT);
  Serial.begin(9600);  // Starts the serial communication
}
void loop() {
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2;
  // Prints the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.println(distance);

  distance = map(distance, 0, 30, 60, 0);

  for (int i = 0; i <= distance; i++) {
    NeoPixel.setPixelColor(i, 255, 255, 255);
    //NeoPixel.show();
  }
  NeoPixel.show();
    NeoPixel.clear();
    NeoPixel.show();
  
}