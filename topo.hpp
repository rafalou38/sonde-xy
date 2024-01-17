#include <Servo.h>

#include "consts.hpp"

int zMax = 250;
Servo push;

void BLClear() {
  push.write(60);
}
void BLDown() {
  push.write(10);
}
void BLUp() {
  push.write(90);
}

bool BLContact() {
  return digitalRead(TOPOLOGY_SENSOR_PIN);
}

int prev = 0;
void setupTopology(Stepper &stz)
{
  push.attach(TOPOLOGY_PUSH_PIN); // attaches the servo on pin 9 to the servo object
  pinMode(TOPOLOGY_SENSOR_PIN, INPUT_PULLUP);

  stz.setSpeed(300);
  stz.step(zMax - prev);

  delay(200);
  BLClear();
  delay(200);
  BLDown();
  delay(1000);
  BLClear();

  int i = 0;
  while (true)
  {
    stz.step(-1);
    delay(50);
    if (BLContact())
    {
      BLUp();

      zMax = i + 1;
      stz.step(zMax);
      //Serial.println(zMax);
      break;
    }

    i++;
  }
}

void runTopology(Stepper &sty, Stepper &stx, Stepper &stz)
{
  for (int x = 0; x < width; x += stepsTopo)
  {

    for (int y = 0; y < height; y += stepsTopo)
    {
      BLDown();
      delay(100);
      BLClear();
      int z = 0;
      while (true)
      {
        stz.step(-1);
        delay(50);

        if (BLContact())
        {
          BLUp();

          Serial.print(x);
          Serial.print(",");
          Serial.print(y);
          Serial.print(",");
          Serial.println(z);
          prev = z;
          stz.step(z + 5);
          delay(400);
          break;
        }
        z++;
      }
      sty.step(stepsTopo);
    }
    stx.step(stepsTopo);
    sty.step(-height);
  }
}
