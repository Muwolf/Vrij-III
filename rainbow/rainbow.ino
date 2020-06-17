/*

  NeoPixel LEDs

  modified on 7 May 2019
  by Saeed Hosseini @ Electropeak
  https://electropeak.com/learn/

*/

#include <Adafruit_NeoPixel.h>


#define PIN        6
#define NUM_LEDS 204

#define DELAYVAL 10


int list[NUM_LEDS];
int red = 255;
int green = 255;
int blue = 255;


Adafruit_NeoPixel pixels(NUM_LEDS, PIN, NEO_GRB + NEO_KHZ800);

void NeoFade(int pixel)
{
  pixels.setPixelColor(pixel, 165, 242, 243);
}


void setup() {
  pixels.begin();
}

void loop() {
  for (int i = 0; i < 20; i++) {
    int y = random(0, NUM_LEDS);
    list[i] = y;
    for (int z = 0; z < NUM_LEDS; z++) {
      if (list[z] > 0) {
        NeoFade(list[z]);
      }
    }
  }
  for (int j = 255; j > 0; j = j - 2)
  {
    pixels.setBrightness(j);
    pixels.show();
    delay(DELAYVAL);
  }
}
