#include "rgbLed.h"

unsigned long anterior = 0;
unsigned long intervaloBlink = 1000;
unsigned int liga = 1;

void piscaLedRoxo()
{
    unsigned long atual = millis();
    if (atual - anterior > intervaloBlink)
    {
        if (liga == 1)
        {
            analogWrite(LED_R, 255 - 240);
            analogWrite(LED_G, 255 - 30);
            analogWrite(LED_B, 255 - 255);

            liga = 0;
        }
        else
        {
            // Desliga todos os LEDs
            analogWrite(LED_R, 255);
            analogWrite(LED_G, 255);
            analogWrite(LED_B, 255);
            liga = 1;
        }
        anterior = atual;
    }
}

void piscaLedCiano()
{
    unsigned long atual = millis();
    if (atual - anterior > intervaloBlink)
    {
        if (liga == 1)
        {
            analogWrite(LED_R, 255 - 0);
            analogWrite(LED_G, 255 - 255);
            analogWrite(LED_B, 255 - 255);

            liga = 0;
        }
        else
        {
            // Desliga todos os LEDs
            analogWrite(LED_R, 255);
            analogWrite(LED_G, 255);
            analogWrite(LED_B, 255);
            liga = 1;
        }
        anterior = atual;
    }
}

