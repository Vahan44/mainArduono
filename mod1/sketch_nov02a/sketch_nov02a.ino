#include "IRremote.h"
IRrecv irrecv(3);
decode_results res;

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
#include "VolAnalyzer.h"
VolAnalyzer analyzer(A0);
//1.707000FF
//2.CACB8233
//3.A447EC91
//4.431DF197
//5.707020DF
//6.7070A05F
//7.71D20C55
//8.308EDBD3
//9.A3688391
//vol+.707048B7
//vol-.10F13D9
//ch+.707008F7
//ch-.DF0CAEB7
//on/off.FF6906C4


int led1 = 0;
int led2 = 0;
int k;
int b;
int aj;
int dzax;
int red;
int green;
int blue;
//int i = 25;
int j;
int l;
long unsigned int p = 0;
void setup() {
  // attachInterrupt(digitalPinToInterrupt(3), DecodeIR, RISING);
  pinMode(3, INPUT);
  pinMode(13, OUTPUT);
  Serial.begin(9600);
  irrecv.enableIRIn();
  analyzer.setVolK(20);
  analyzer.setTrsh(10);
  NeoPixel.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
  NeoPixel.setBrightness(255); // Set brightness

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


void clr()
{
   NeoPixel.clear();
        NeoPixel.show();
        //Serial.println(aj);
  }
void loop() {
if ( irrecv.decode( &res )) {
    Serial.println(res.value, HEX);

    irrecv.resume();
  }


    if(!irrecv.decode( &res )){
    if (analyzer.tick()) {


      aj = map(analyzer.getRaw(), 0, 450, 30, 60);
      Serial.println(aj);
      l = map(aj, 30, 60, 4 , 1);
      if (aj > k && aj >= 30 && !irrecv.decode( &res )) {
        uint16_t time = millis() >> 2;
        for (int i = 30; i < aj; i++) {

          j = 60 - i;
            byte x = (time >> 1) - (i << l);//l
        NeoPixel.setPixelColor(i, hsvToRgb((uint32_t)x * 359 / 256, 255, 255));
        NeoPixel.setPixelColor(j, hsvToRgb((uint32_t)x * 359 / 256, 255, 255));
       //NeoPixel.setPixelColor(i, 56, 255, 55);
       //NeoPixel.setPixelColor(j,56, 255, 55);
         //show
        }
         NeoPixel.show();
      }
      else if (p % 4 == 0 && !irrecv.decode( &res )) {
       clr();
      }

      k = aj;
      p++;
    }
    }
      

}
