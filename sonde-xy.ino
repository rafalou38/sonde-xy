
#include <Stepper.h>

#include "hall.hpp"
#include "topo.hpp"
#include "consts.hpp"

bool TOPOLOGIE = true;

// initialize the stepper library on pins 8 through 11:
Stepper sty(20, 9, 10, 11, 12);
Stepper stx(20, 5, 6, 7, 8);
Stepper stz(20, 2, 3, 4, A0);

void setup()
{
  // initialize the serial port:
  Serial.begin(9600);
  Serial.println("START");
  Serial.println("x,y,v");

  if (TOPOLOGIE)
    stz.setSpeed(50);
  else
    setupHall();

  sty.setSpeed(500);
  stx.setSpeed(500);
  sty.step(-height);
  stx.step(-width);
  sty.setSpeed(50);
  stx.setSpeed(50);

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

void loop()
{
}
