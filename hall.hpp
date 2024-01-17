#include "consts.hpp"


int origin = 0;

void setupHall()
{
    pinMode(HALL_PIN, INPUT);
    origin = analogRead(HALL_PIN);
}

int readHall()
{
    return analogRead(HALL_PIN) - origin;
}

void runHall(Stepper &sty, Stepper &stx)
{
    int dir = 1;
    for (int x = 0; x < width; x += stepsHall)
    {
        stx.step(stepsHall);
        // for (int y = 0; y < height; y += stepsHall)
        for (
            int y = dir == 1 ? 0 : height;
            dir == 1 ? y < height : y > 0;
            y += stepsHall * dir)
        {
            sty.step(stepsHall * dir);
            delay(50);

            Serial.print(x);
            Serial.print(",");
            Serial.print(y);
            Serial.print(",");
            Serial.println(readHall());
        }
        // sty.step(-height);
    }
}