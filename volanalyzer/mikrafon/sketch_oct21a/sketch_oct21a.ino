#include <Adafruit_NeoPixel.h>

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
  analyzer.setVolMax(100);
}
long unsigned time_1;
long unsigned time_2;

void loop() {
  if (analyzer.tick()) {

    // Serial.println(analyzer.getRaw());

Serial.println(analyzer.getRaw());
    if (analyzer.getRaw() > 400) {
      time_1 = millis();

      if (analyzer.getRaw() > 400) {
        time_2 = millis();
        if (time_1 - time_2 < 400) {
          digitalWrite(13, 1);

          delay(30);
        }
      }
    }
  }
}
