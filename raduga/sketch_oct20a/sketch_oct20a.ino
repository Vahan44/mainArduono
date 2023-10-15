#define LED_PIN 11     // пин ленты
#define LED_NUM 49   // кол-во светодиодов
#define LED_BR 255     // яркость ленты
#define B1_PIN 3      // пин кнопки 1
#define B2_PIN 4      // пин кнопки 2
#define BUZZ_PIN 5    // пин пищалки
#define ZONE_SIZE 10  // размер зоны
#define MIN_SPEED 5   // минимальная скорость
#define MAX_SPEED 20  // максимальная скорость
#define WIN_SCORE 5   // победный счёт
#define spd 0
//Подключим библиотеку ленты и создадим ленту:

#include "FastLED.h"
CRGB leds[LED_NUM];
//Также создадим две кнопки (структура описана выше в главе Библиотеки):

//Button b1(B1_PIN);
//Button b2(B2_PIN);
//В блоке setup() настроим ленту, пин пищалки, а также запустим новую игру:

void setup() {
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, LED_NUM);
  FastLED.setBrightness(LED_BR);
  pinMode(BUZZ_PIN, OUTPUT);
  newGame();
}
//Функция новой игры мигает зонами игроков тремя цветами и пищит, после чего задаёт начальные условия:

void newGame() {
  blinkTone(CRGB::Red, CRGB::Red, 300, 300);
  blinkTone(CRGB::Yellow, CRGB::Yellow, 300, 300);
  blinkTone(CRGB::Green, CRGB::Green, 600, 300);
  fillZones(CRGB::Green, CRGB::Green);
  FastLED.show();
  randomSeed(millis()); // делаем случайные числа более случайными
  newRound();
}
//Где newRound() и задаёт стартовые значения скорости и позиции шарика:

void newRound() {
//  spd = 5;  // случайное направление
  pos = (LED_NUM * 10) / 2;     // в центр ленты
}
//Выше использовалась функция blinkTone(), давайте посмотрим что у неё внутри:

// (цвет1, цвет2, частота, время задержки)
void blinkTone(CRGB color1, CRGB color2, int freq, int del) {
  fillZones(color1, color2);    // залить зоны
  FastLED.show();               // показать
  tone(BUZZ_PIN, freq);         // пищать
  delay(del);                   // ждём
  noTone(BUZZ_PIN);             // не пищать
  fillZones(0, 0);              // выключить зоны
  FastLED.show();               // показать
  delay(del);                   // ждать
}
//Данная функция моргает и пищит с заданной частотой и временем. Моргает здесь функция fillZones(), которая просто красит начальный и конечный отрезки ленты указанными цветами. Она выглядит так:

void fillZones(CRGB color1, CRGB color2) {
  // заливаем концы ленты переданными цветами
  for (int i = 0; i < ZONE_SIZE; i++) {
    leds[i] = color1;
    leds[LED_NUM - i - 1] = color2;
  }
}
//В основном цикле программы у нас вызываются две функции: опрос кнопок и процесс самой игры:

void loop() {
  poolButtons();
  gameRoutine();
}
//Опрос кнопок – проверяем клик. Если игрок кликнул вне своей зоны – проиграл раунд. Кликнул внутри зоны – мяч отбивается и происходит пересчёт скорости: чем ближе к краю ленты, тем сильнее отскок.

void poolButtons() {
  if (3.click()) {                             // произошёл клик игрока 1
    if (pos >= ZONE_SIZE * 10) gameOver(0);     // мячик вне зоны 1 игрока - проиграл
    else {                                      // мячик в зоне - отбил
      tone(BUZZ_PIN, 1200, 60);
      //spd = map(pos, ZONE_SIZE * 10, 0, MIN_SPEED, MAX_SPEED); // меняем скорость
    }
  }
  // аналогично для игрока 2
  if (3.click()) {
//    if (pos < (LED_NUM - ZONE_SIZE) * 10) gameOver(1);
    else {
      tone(BUZZ_PIN, 1200, 60);
  //    spd = map(pos, (LED_NUM - ZONE_SIZE) * 10, LED_NUM * 10, -MIN_SPEED, -MAX_SPEED);
    }
  }
}
//Тут же используется функция gameOver(), которая сигнализирует о проигрыше раунда у конкретного игрока:

// (номер игрока, 0 или 1)
void gameOver(byte player) {
  newRound();    // новый раунд
  if (player == 0) {
    score2++;
    if (score2 == WIN_SCORE) {  // победил игрок 2
      score1 = score2 = 0;      // обнуляем счёт
      // победный бип бип бип игрока 2
      blinkTone(CRGB::Black, CRGB::Green, 600, 200);
      blinkTone(CRGB::Black, CRGB::Green, 600, 200);
      blinkTone(CRGB::Black, CRGB::Green, 600, 200);
      delay(500);
      newGame();  // новая игра
    } else blinkTone(CRGB::Red, CRGB::Green, 200, 500);   // красный бииип игрока 1
  } else {
    score1++;
    if (score1 == WIN_SCORE) {  // победил игрок 1
      score1 = score2 = 0;
      blinkTone(CRGB::Green, CRGB::Black, 600, 200);
      blinkTone(CRGB::Green, CRGB::Black, 600, 200);
      blinkTone(CRGB::Green, CRGB::Black, 600, 200);
      delay(500);
      newGame();  // новая игра
    } else blinkTone(CRGB::Green, CRGB::Red, 200, 500);
  }
}
//Функция реализована не очень красиво, можно сократить её вдвое. Это ваше домашнее задание =)

//Процесс игры – тут нас встречает таймер на 10мс, в котором происходит движение “шарика” и его отрисовка:

void gameRoutine() {
  if (millis() - tmr >= 10) {   // каждые 10 мс
    tmr = millis();
    // ...
  }
}
//Внутри таймера двигаем шарик и проверяем, не вылетел ли он за ленту:

pos += spd;     // двигаем мячик
if (pos < 0) {  // вылетел слева
  gameOver(0);  // игрок 1 проиграл
  return;       // выходим
}
if (pos >= LED_NUM * 10) {  // вылетел справа
  gameOver(1);              // игрок 2 проиграл
  return;                   // выходим
}
//Если вылетел – выходим из функции, чтобы не отрисовывать шарик в несуществующем месте ленты!

//Дальше очищаем ленту, заново рисуем зоны и поверх – текущею позицию шарика. Координаты у нас десятикратные, поэтому делим на 10:

FastLED.clear();
fillZones(CRGB::Green, CRGB::Green);  // показываем зоны
leds[pos / 10] = CRGB::Cyan;          // рисуем мячик
FastLED.show();
