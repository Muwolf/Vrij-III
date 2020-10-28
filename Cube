
/* ==== Include Libraries ==== */

#include <FastLED.h>

/* ==== define constand ==== */

#define LED_PIN 6
#define NUM_LEDS 144

const byte interruptPin = 2;

#define MIN_BRIGHTNESS 10
#define MAX_BRIGHTNESS 255
#define MAX_TEMPO 15
#define MIN_TEMPO 1


/* ==== declaire variables ==== */


int num_leds_on;
float tempo;
int list[NUM_LEDS];
int red;
int green;
int blue;
float maxRed;
float maxGreen;
float maxBlue;
int speedRed;
int speedGreen;
int speedBlue;
int state;

unsigned long previousMillis = 0;
unsigned long interval;


uint8_t  gHueDelta = 1;


CRGB leds[NUM_LEDS];

void setup() {
  pinMode(interruptPin, INPUT_PULLUP);
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(interruptPin), blink, RISING);
  FastLED.addLeds<NEOPIXEL, LED_PIN>(leds, NUM_LEDS);
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB::Black;
  }
  FastLED.show();
}


void loop() {
  interval = 100 + ((MAX_TEMPO * 50) - (tempo * 50));
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    /* ----- Statebase machine ----- */

    Serial.print("State is ");
    if (state == 0) {
      Serial.println("Happy");
      maxRed = 200;
      maxGreen = 100;
      maxBlue = 0;
      num_leds_on = 30;
      tempo = 10;
    } else if (state == 1) {
      Serial.println("Surpriced");
      maxRed = 255;
      maxGreen = 50;
      maxBlue = 255;
      num_leds_on = 15;
      tempo = 7;
    } else if (state == 2) {
      Serial.println("Angry");
      maxRed = 255;
      maxGreen = 0;
      maxBlue = 0;
      num_leds_on = 30;
      tempo = 7;
    } else if (state == 3) {
      Serial.println("Sad");
      maxRed = 255;
      maxGreen = 0;
      maxBlue = 255;
      num_leds_on = 4;
      tempo = 1;
    } else {
      Serial.println("Idk");
    }

    /* ----- resetting values ----- */

    red = 0;
    green = 0;
    blue = 0;

    speedRed = decideTempo(tempo, maxRed);
    speedGreen = decideTempo(tempo, maxGreen);
    speedBlue = decideTempo(tempo, maxBlue);

    /* ----- He's Making a list, and checking it twice ----- */

    for (int i = 0; i < num_leds_on; i++) {
      int y = random(0, NUM_LEDS);
      list[i] = y;
    }

    /* ----- figuring out highest "Max value" ----- */
    /* ----- Max function only accepts two values ----- */

    int y = max(maxRed, maxGreen);
    int x = (max(y, maxBlue)) * 2;

    int a = max(speedRed, speedGreen);
    int b = max(a, speedBlue);

    int inc = x / b * 2;


    /* ----- Start one cycle ----- */
    for (int i = tempo; i <= x; i = i + b) {

      red = adjustColor(red, speedRed);
      speedRed = speedCheck(red, speedRed, maxRed);

      green = adjustColor(green, speedGreen);
      speedGreen = speedCheck(green, speedGreen, maxGreen);

      blue = adjustColor(blue, speedBlue);
      speedBlue = speedCheck(blue, speedBlue, maxBlue);

      for (int j = 0; j <= NUM_LEDS ; j++) {
        leds[list[j]].setRGB(red, green, blue);
      }
      FastLED.show();
    }

    /* ----- Clear the list ----- */

    for (int i = 0; i < NUM_LEDS; i++) {
      leds[i] = CRGB::Black;
    }
    FastLED.show();

    for (int i = 0; i <= NUM_LEDS; i++) {
      list[i] = 0;
    }
  }
}

/* ----- Functions ----- */

int decideTempo(float _tempo, float _maxColor) {
  _tempo = (_tempo * (_maxColor / 255));
  if (_tempo < 1) {
    _tempo = 1;
  }
  if (_maxColor < 10) {
    _tempo = 0;
  }
  return _tempo;
}

int adjustColor(int _color, int _colorSpeed) {
  _color += _colorSpeed;
  if (_color < 0) {
    _color = 0;
  }
  return _color;
}

int speedCheck (int _color, int _colorSpeed, int _maxColor) {
  if (_color >= _maxColor) {
    _colorSpeed *= -1;
  }
  return _colorSpeed;
}

void blink() {
  state += 1;
  if (state >= 4) {
    state = 0;
  }
}
