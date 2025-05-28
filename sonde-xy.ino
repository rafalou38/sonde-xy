
#include <Stepper.h>

#include "hall.hpp"
#include "topo.hpp"
#include "consts.hpp"

bool TOPOLOGIE = false;

// initialize the stepper library on pins 8 through 11:
Stepper sty(20, 9, 10, 11, 12);
Stepper stx(20, 5, 6, 7, 8);
Stepper stz(20, 2, 3, 4, A0);

void setup() {
  // initialize the serial port:
  Serial.begin(115200);
  Serial.println("START");
  Serial.println("x,y,v");

  sty.setSpeed(200);
  stx.setSpeed(200);
  stz.setSpeed(300);
  if (!TOPOLOGIE) stz.step(200);
  sty.step(-height);
  stx.step(-width);

  if (TOPOLOGIE)
    stz.setSpeed(50);
  else {
    setupHall();
    stz.step(-201);
    stz.step(5);
  }

  if (TOPOLOGIE)
    setupTopology(stz);

  //sty.step(-height);
  //stx.step(-width);

  if (TOPOLOGIE)
    runTopology(sty, stx, stz);
  else
    runHall(sty, stx);

  Serial.println("END");
}

void loop() {
}
