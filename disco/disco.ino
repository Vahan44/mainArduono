#include <Adafruit_NeoPixel.h>
//#ifdef __AVR__
//#include <avr/power.h> // Required for 16 MHz Adafruit Trinket
//#endif

#define PIN_NEO_PIXEL  6   // Arduino pin that connects to NeoPixel
#define NUM_PIXELS     60  // The number of LEDs (pixels) on NeoPixel

Adafruit_NeoPixel NeoPixel(NUM_PIXELS, PIN_NEO_PIXEL, NEO_GRB + NEO_KHZ800);


// амплитудный анализ звука
//https://www.youtube.com/watch?v=YD8Hmexqzvc
//https://alexgyver.ru/colormusic/



void setup() {
  pinMode(13, OUTPUT);

  NeoPixel.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
  // Set brightness
}
void loop() {

        for (int i = 0; i <= 60; i++) {
       NeoPixel.setPixelColor(i, 15, 15, 15);
        }
                  NeoPixel.show();
             
      }