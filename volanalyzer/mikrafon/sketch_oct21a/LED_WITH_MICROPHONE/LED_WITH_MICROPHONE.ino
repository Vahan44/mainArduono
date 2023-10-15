#include <Adafruit_NeoPixel.h>
#define LED_PIN 5
#define NUM_OF_LED 49
Adafruit_NeoPixel NeoPixel(NUM_OF_LED, LED_PIN, NEO_GRB + NEO_KHZ800);

//---------------------------------------------------------------------------

#include "VolAnalyzer.h"
VolAnalyzer analyzer(A0);

//---------------------------------------------------------------------------

void setup() {
  pinMode(6, OUTPUT);
  Serial.begin(115200);
  analyzer.setVolK(20);
  analyzer.setTrsh(10);
  analyzer.setVolMin(10);
  analyzer.setVolMax(100);
}

//---------------------------------------------------------------------------

void loop() {

  int stripe = map(analyzer.getRaw(), 0 , analyzer.getMax(), 0, 49);

  for (int i = 0; i <= stripe; i++) {
    NeoPixel.clear();
    NeoPixel.setPixelColor(i, NeoPixel.Color(0, 255, 0));
    NeoPixel.show();
    //Serial.print("a - ");Serial.println(i);
    if (i == stripe) {
      for (int i = stripe; i >= 0; i--) {
        NeoPixel.clear();
        NeoPixel.setPixelColor(i, NeoPixel.Color(0, 255, 0));
        NeoPixel.show();
        //Serial.print("b - ");Serial.println(i);
      }
    }
  }

  //---------------------------------------------------------------------------
  /*
    if (analyzer.tick()) {
      Serial.print(analyzer.getVol());
      Serial.print(',');
      Serial.print(analyzer.getRaw());
      Serial.print(',');
      Serial.print(analyzer.getMin());
      Serial.print(',');
      Serial.println(analyzer.getMax());
      if (analyzer.getRaw() > 450) {
        digitalWrite(13, 1);
        delay(50);
        digitalWrite(13, 0);
      }
    }
  */
  //---------------------------------------------------------------------------
}
