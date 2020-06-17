
/* ==== Include Libraries ==== */

#include <RH_ASK.h>
#include <SPI.h>
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

/* ==== define constand ==== */

#define LED_PIN 6
#define NUMPIXELS 144
#define MAX_BRIGHTNESS 127
#define MAX_TEMPO 100


/* ==== declaire variables ==== */



int num_leds_on;
int tempo;
int list[NUMPIXELS];
int red;
int green;
int blue;
int maxRed;
int maxGreen;
int maxBlue;
int speedRed;
int speedGreen;
int speedBlue;

RH_ASK rf_driver;
Adafruit_NeoPixel ledStrip = Adafruit_NeoPixel(NUMPIXELS, LED_PIN, NEO_GRB + NEO_KHZ800);


/* ==== Setup ==== */

void setup()
{

  Serial.begin(9600);
  Serial.print("Hello! ");
  ledStrip.begin();
  ledStrip.setBrightness(MAX_BRIGHTNESS);
  for (int i = 0; i < NUMPIXELS; i++) {
    ledStrip.setPixelColor(i, ledStrip.Color(0, 0, 0));
  }
  ledStrip.show();
  Serial.println("- Setup Done");
}

/* ==== Loop ==== */

void loop()
{

  /* ----- static values, will be based on sensory imput) ----- */
  maxRed = 50;
  maxGreen = 100;
  maxBlue = 150;
  num_leds_on = 10;
  tempo =  5;

  /* ----- resetting values ----- */

  red = 0;
  green = 0;
  blue = 0;

  speedRed = tempo;
  speedGreen = tempo;
  speedBlue = tempo;

  /* ----- He's Making a list, and checking it twice ----- */ 

  for (int i = 0; i < num_leds_on; i++) {
    int y = random(0, NUMPIXELS);
    list[i] = y;
    Serial.print(i);
    Serial.print(": ");
    Serial.print(list[i]);
    Serial.print("   ");
  }
  Serial.println(" ");

  /* ----- figuring out highest "Max value" ----- */
  /* ----- Max function only accepts two values ----- */

  int y = max(maxRed, maxGreen);
  int x = (max(y, maxBlue)) * 2;

  /* ----- Start one cycle ----- */
  for (int i = tempo; i <= x; i = i + tempo) {
    
    red = adjustColor(red, speedRed);
    speedRed = speedCheck(red, speedRed, maxRed);
    
    green = adjustColor(green, speedGreen);
    speedGreen = speedCheck(green, speedGreen, maxGreen);
    
    blue = adjustColor(blue, speedBlue);
    speedBlue = speedCheck(blue, speedBlue, maxBlue);

    Serial.print("Itteration: ");
    Serial.print(i / tempo);
    Serial.print(" out of: ");
    Serial.print(x / tempo);
    Serial.print(" - Red: ");
    Serial.print(red);
    Serial.print(" Green: ");
    Serial.print(green);
    Serial.print(" Blue: ");
    Serial.print(blue);

  /* ----- This forloop should only light up the leds in the list. Instead i get a lot of strange values ----- */

    for (int j = 0; j <= sizeof(list) ; j++) {
      Serial.print(" - Led#: ");
      Serial.println(list[j]);
      ledStrip.setPixelColor(list[j], red, green, blue); 
      ledStrip.show();
    }
  }
  
  /* ----- Clear the list ----- */
  for (int i = 0; i <= sizeof(list); i++) {
    list[i] = 0;
  }

  Serial.println("End of loop");
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
