#ifndef RGBLED_H  // Evita inclusão duplicada
#define RGBLED_H

// Inclui as bibliotecas necessárias
#include <Arduino.h>

// Definição dos pinos do LED RGB
#define LED_R 9
#define LED_G 10
#define LED_B 11

// Declaração das funções para piscar o LED em cores específicas
void piscaLedRoxo();
void piscaLedCiano();

#endif
