
/* ==== Include Libraries ==== */

#include <RH_ASK.h>
#include <SPI.h>
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

/* ==== define constand ==== */

#define LED_PIN 6
#define NUMPIXELS 204
#define MAX_BRIGHTNESS 255
#define MAX_TEMPO 100
#define STR_OUT_LENGTH 23


/* ==== declaire variables ==== */

String str_x;
String str_y;
String str_z;
String str_num_leds;
String str_tempo;
String str_out;

int num_leds_on;
int tempo;
int list[NUMPIXELS];
int red;
int green;
int blue;

RH_ASK rf_driver;
Adafruit_NeoPixel ledStrip = Adafruit_NeoPixel(NUMPIXELS, LED_PIN, NEO_GRBW + NEO_KHZ800);


/* ==== Setup ==== */

void setup()
{
  rf_driver.init();
  Serial.begin(9600);
  Serial.print("Hello!");
  ledStrip.begin();
  for (int i = 0; i < NUMPIXELS; i++) {
    ledStrip.setPixelColor(i, ledStrip.Color(0, 0, 0));
  }
  ledStrip.show();
  Serial.println("Setup Done");
}

/* ==== Loop ==== */

void loop()
{
  uint8_t buf[STR_OUT_LENGTH];
  uint8_t buflen = sizeof(buf);
  if (rf_driver.recv(buf, &buflen))
  {
    str_out = String((char*)buf);
    for (int i = 0; i < str_out.length(); i++) {
      if (str_out.substring(i, i + 1) == "x") {
        str_x = str_out.substring(i + 1, i + 5);
      } else if (str_out.substring(i, i + 1) == "y") {
        str_y = str_out.substring(i + 1, i + 5);
      } else if (str_out.substring(i, i + 1) == "z") {
        str_z = str_out.substring(i + 1, i + 5);
      } else if (str_out.substring(i, i + 1) == "a") {
        str_num_leds = str_out.substring(i + 1, i + 4);
      } else if (str_out.substring(i, i + 1) == "b") {
        str_tempo = str_out.substring(i + 1, i + 5);
      }
    }

    red = (int) map ((str_x.toFloat() * 1000), 0, 1023, 0, 255);
    green = (int) map ((str_y.toFloat() * 1000), 0, 1023, 0, 255);
    blue = (int) map ((str_z.toFloat() * 1000), 0, 1023, 0, 255);
    num_leds_on = map (str_num_leds.toInt(), 100, 999, 0, NUMPIXELS);
    tempo = map (str_tempo.toInt(), 100, 999, 0, MAX_TEMPO);

    Serial.print("x: ");
    Serial.print(red);
    Serial.print("  -  y: ");
    Serial.print(green);
    Serial.print("  -  z: ");
    Serial.print(blue);
    Serial.print("  -  Aantal LEDS: ");
    Serial.print(num_leds_on);
    Serial.print("  -  Tempo: ");
    Serial.println(tempo);

    for (int i = 0; i < num_leds_on; i++) {
      int y = random(0, NUMPIXELS);
      list[i] = y;
      for (int j = 0; j < NUMPIXELS; j++) {
        if (list[j] > 0) {
          ledStrip.setPixelColor(list[j], ledStrip.Color(red, green, blue));
          ledStrip.show();
          delay(tempo);
        }
        for (int z = 255; z > 0; z = z - 2)
        {
          ledStrip.setBrightness(z);
          ledStrip.show();
          delay(tempo);
        }
      }
      memset(list, 0, sizeof(list));
    }
  }
}
