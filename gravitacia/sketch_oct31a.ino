#include <Adafruit_NeoPixel.h>
//#ifdef __AVR__
//#include <avr/power.h> // Required for 16 MHz Adafruit Trinket
//#endif

#define PIN_NEO_PIXEL  6   // Arduino pin that connects to NeoPixel
#define NUM_PIXELS     49  // The number of LEDs (pixels) on NeoPixel

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
  for (int m = 0; m <= 49; m++) {
    NeoPixel.setPixelColor(m, NeoPixel.Color(62, 12, 90));
    NeoPixel.show();
    NeoPixel.setBrightness(255); // Set brightness

  }
}
uint32_t hsvToRgb(uint16_t h, uint8_t s, uint8_t v) {
  uint8_t f = (h % 60) * 255 / 60;
  uint8_t p = (255 - s) * (uint16_t)v / 255;
  uint8_t q = (255 - f * (uint16_t)s / 255) * (uint16_t)v / 255;
  uint8_t t = (255 - (255 - f) * (uint16_t)s / 255) * (uint16_t)v / 255;
  uint8_t r = 0, g = 0, b = 0;
  switch ((h / 60) % 6) {
    case 0: r = v; g = t; b = p; break;
    case 1: r = q; g = v; b = p; break;
    case 2: r = p; g = v; b = t; break;
    case 3: r = p; g = q; b = v; break;
    case 4: r = t; g = p; b = v; break;
    case 5: r = v; g = p; b = q; break;
  }
  return NeoPixel.Color(r, g, b);

}
int k;
int b;
int aj;
int dzax;
int red;
int green;
int blue;
int i;
int j;

void loop() {

  if (analyzer.tick()) {
    //Serial.print(analyzer.getVol());
    //Serial.print(',');
  Serial.println(analyzer.getMax());
    //Serial.print(',');
    //Serial.print(analyzer.getMin());
    //Serial.print(',');
    //Serial.println(analyzer.getMax());
    //if (analyzer.getRaw() > 450) {
    // digitalWrite(13, 1);
    // delay(50);
    // digitalWrite(13, 0);
    // }

    aj = map(analyzer.getMax(), 0, 600, 20, 49);
    dzax = 49 - aj;

    if (aj > k && aj > 10 && aj >= 25 && dzax <=  25) {

      // NeoPixel.setPixelColor(24, NeoPixel.Color(red,green,blue));

      uint16_t time = millis() >> 1;
      //NeoPixel.setPixelColor(25, NeoPixel.Color(red,green,blue));
      byte x = (time >> 1) - (i << 4);
      //   NeoPixel.setPixelColor(i, hsvToRgb((uint32_t)x * 359 / 256, 255, 255));
      //  NeoPixel.setPixelColor(j, hsvToRgb((uint32_t)x * 359 / 256, 255, 255));
      //delay(5);

      NeoPixel.clear();

      for (i = 25; i <= aj; i++) {
        j = 49 - i;
        NeoPixel.setPixelColor(i, hsvToRgb((uint32_t)x * 359 / 256, 255, 255));
        NeoPixel.setPixelColor(j, hsvToRgb((uint32_t)x * 359 / 256, 255, 255));
        NeoPixel.show();
      }


    }
    k = aj;
    /*for (int i = 0; i <= NUM_PIXELS; i++) {
      NeoPixel.setPixelColor(i, NeoPixel.Color(0, 255, 0));
      if (i == NUM_PIXELS) {
        for (int i = NUM_PIXELS; i > 0; i--) {
          NeoPixel.setPixelColor(i, NeoPixel.Color(255, 0, 0));

        delay(100); // pause between each pixel
      }
      }
      }
    */
  }
}
