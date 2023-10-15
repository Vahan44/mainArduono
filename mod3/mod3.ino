#include <Adafruit_NeoPixel.h>
//#ifdef __AVR__
//#include <avr/power.h> // Required for 16 MHz Adafruit Trinket
//#endif

#define PIN_NEO_PIXEL  11   // Arduino pin that connects to NeoPixel
#define NUM_PIXELS     60  // The number of LEDs (pixels) on NeoPixel

Adafruit_NeoPixel NeoPixel(NUM_PIXELS, PIN_NEO_PIXEL, NEO_GRB + NEO_KHZ800);


// амплитудный анализ звука
//https://www.youtube.com/watch?v=YD8Hmexqzvc
//https://alexgyver.ru/colormusic/
#include "VolAnalyzer.h"
VolAnalyzer analyzer(A0);


void setup() {
  pinMode(13, OUTPUT);
  Serial.begin(115200);
  analyzer.setVolK(20);
  analyzer.setTrsh(10);
  analyzer.setVolMin(10);
  analyzer.setVolMax(60);
  NeoPixel.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
  // Set brightness
}


int k;

int aj;
int i;
int j;


void loop() {

  if (analyzer.tick()) {
    Serial.println(aj);

    aj = map(analyzer.getRaw(), 0, 450, 30, 70);

    if (aj > k && aj >= 30) {


      if (aj > 33) {
        for (i = 0; i <= 20; i++) {

         

          NeoPixel.setPixelColor(i, 255, 0, 0);
        }

        for (int n = 255; n > 230; n--) {
          NeoPixel.setBrightness(n);
          // delay(1/2000);
          NeoPixel.show();
        }
        // NeoPixel.clear();
        //NeoPixel.show();
      }

      if (aj > 36) {
        for (i = 21; i <= 40; i++) {

         

          NeoPixel.setPixelColor(i, 0, 255, 0);
         

        }
        for (int n = 255; n > 230; n--) {
          NeoPixel.setBrightness(n);
          //delay(1/2000);
          NeoPixel.show();
        }

      }
      if (aj > 42) {
        for (i = 41; i <= 60; i++) {

          NeoPixel.setPixelColor(i, 255, 255, 0);

        }
        for (int n = 255; n > 230; n--) {
          NeoPixel.setBrightness(n);
          //delay(1/2000);
          NeoPixel.show();
        }
        // NeoPixel.clear();
        // NeoPixel.show();
      }

    }
    k = aj;
    NeoPixel.clear();
    NeoPixel.show();

  }
}
