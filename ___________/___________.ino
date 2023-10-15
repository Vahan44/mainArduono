#include <Adafruit_NeoPixel.h>
//#include <avr/power.h>
#include <IRremote.h>
int r;
int g;
int b;
int br;
const byte IR_RECEIVE_PIN = 3;

#define PIN 11
#define NUMPIXELS 60
int state = 0;
int col = 1;
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  pinMode(A1, INPUT);
  pinMode(10, INPUT_PULLUP);
  pinMode(9, INPUT);
  Serial.begin(115200);
  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);

  pixels.begin();
  //pixels.setBrightness(200);
  //attachInterrupt(digitalPinToInterrupt(3), DecodeIR, RISING);
}



uint32_t hsvToRgb(uint16_t h, uint8_t s, uint8_t v) {
  uint8_t f = (h % 60) * 255 / 60;
  uint8_t p = (255 - s) * (uint16_t)v / 255;
  uint8_t q = (255 - f * (uint16_t)s / 255) * (uint16_t)v / 255;
  uint8_t t = (255 - (255 - f) * (uint16_t)s / 255) * (uint16_t)v / 255;
  uint8_t r = 0, g = 0, b = 0;
  switch ((h / 60) % 6) {
    case 0:
      r = v;
      g = t;
      b = p;
      break;
    case 1:
      r = q;
      g = v;
      b = p;
      break;
    case 2:
      r = p;
      g = v;
      b = t;
      break;
    case 3:
      r = p;
      g = q;
      b = v;
      break;
    case 4:
      r = t;
      g = p;
      b = v;
      break;
    case 5:
      r = v;
      g = p;
      b = q;
      break;
  }
  return pixels.Color(r, g, b);
}
void rainbow() {
  uint16_t time = millis() >> 2;
  for (int i = 0; i < 61; i++) {

    byte x = (time >> 1) - (i << 1);
    pixels.setPixelColor(i, hsvToRgb((uint32_t)x * 359 / 256, 255, 255));
    pixels.show();
  }
}

void colors(int r, int g, int b) {
  for (int i = 0; i < 61; i++) {
    pixels.setPixelColor(i, r, g, b);
  }
  pixels.show();
}


void loop() {
   br = map(analogRead(A1), 0, 1020, 0, 255);
    if (br < 10) {
      br=0;
    }
    pixels.setBrightness(br);



  if (!digitalRead(10)) {
    state = !state;
    delay(100);
  }

  if (!state) {

    if (digitalRead(9) || IrReceiver.decode()) {
      if (col != 8) {
        col++;
      } else {
        col = 1;
      }
      delay(500);
    }
    IrReceiver.resume();


    switch (col) {

      case 1:
        r = 255;
        g = 255;
        b = 255;
        colors(r, g, b);
        break;
      case 2:
        r = 0;
        g = 30;
        b = 255;
        colors(r, g, b);
        break;
      case 3:
        r = 255;
        g = 0;
        b = 0;
        colors(r, g, b);
        break;
      case 4:
        r = 255;
        g = 255;
        b = 10;
        colors(r, g, b);
        break;
      case 5:
        r = 255;
        g = 15;
        b = 85;
        colors(r, g, b);
        break;
      case 6:
        r = 217;
        g = 0;
        b = 240;
        colors(r, g, b);
        break;
      case 7:
        r = 0;
        g = 255;
        b = 255;
        colors(r, g, b);
        break;
      case 8:
        rainbow();

        break;
    }

  } else {
    rainbow();
  }
}



void DecodeIR() {
  if (IrReceiver.decode()) {

    String ir_code = String(IrReceiver.decodedIRData.command, HEX);
    Serial.println(ir_code);

    IrReceiver.resume();
  }
}
