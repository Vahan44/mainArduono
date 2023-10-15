#include <Adafruit_NeoPixel.h>
#define PIN_NEO_PIXEL  6   // Arduino pin that connects to NeoPixel
#define NUM_PIXELS     49  // The number of LEDs (pixels) on NeoPixel

Adafruit_NeoPixel NeoPixel(NUM_PIXELS, PIN_NEO_PIXEL, NEO_GRB + NEO_KHZ800);

#include "VolAnalyzer.h"
VolAnalyzer analyzer(A0);


void setup() {
  pinMode(13, OUTPUT);
  Serial.begin(115200);
  analyzer.setVolK(20);
  analyzer.setTrsh(10);
  analyzer.setVolMin(10);
  analyzer.setVolMax(60);
  NeoPixel.begin(); 
}


int k;
int aj;
int i;
int j;
int n;
int Time; 



int x;
int y ;
int z;
int x1;
int y1;
int z1;
void loop() {
  

  if (analyzer.tick()) {
    
    Serial.println(aj);
     aj = map(analyzer.getRaw(), 0, 450, 25, 49);
if(aj > k){
   

   if(aj > 20){
    Time = millis();
    
    n = 1;
    }
     
    if(millis() - Time > 30){
    NeoPixel.setBrightness(255);
    NeoPixel.setPixelColor(n, 255,255,255);
    Time = millis();
    n++;
    }
    k = aj;
    NeoPixel.clear();
  

  }
  }
  }
