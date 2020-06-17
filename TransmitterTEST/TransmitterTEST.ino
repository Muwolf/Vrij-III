
#include <RH_ASK.h>
#include <SPI.h>

#include "SparkFunLIS3DH.h"

LIS3DH myIMU;

float x;
float y;
float z;
int pot_x;
int pot_y;

const int pot_left = A0;
const int pot_right = A1;

String str_x;
String str_y;
String str_z;
String str_pot_x;
String str_pot_y;
String str_out;

RH_ASK rf_driver;

void setup() {
  pinMode (pot_left, INPUT);
  pinMode (pot_right, INPUT);
  rf_driver.init();
  myIMU.begin();
  Serial.begin(9600);
}

void loop()
{

  //delay(10);

  x = myIMU.readFloatAccelX(), 4;
  if (x < 0) x = x * -1;
  y = myIMU.readFloatAccelY(), 4;
  if (y < 0) y = y * -1;
  z = myIMU.readFloatAccelZ(), 4;
  if (z < 0) z = z * -1;
  pot_x = analogRead(pot_left);
  if (pot_x < 100) pot_x = 100;
  if (pot_x > 999) pot_x = 999;
  pot_y = analogRead(pot_right);
  if (pot_y < 100) pot_y = 100;
  if (pot_y > 999) pot_y = 999;

  str_x = String(x);
  str_y = String(y);
  str_z = String(z);
  str_pot_x = String(pot_x); 
  str_pot_y = String(pot_y); 

  str_out = "x" + str_x + "y" + str_y + "z" + str_z + "a" + str_pot_x + "b" + str_pot_y ;
  static char *msg = str_out.c_str();
  Serial.println(str_out);

  rf_driver.send((uint8_t *)msg, strlen(msg));
  rf_driver.waitPacketSent();

}
