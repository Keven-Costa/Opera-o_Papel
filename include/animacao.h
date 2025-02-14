#ifndef ANIMACAO_H
#define ANIMACAO_H

// Inclui as bibliotecas necessárias
#include <Arduino.h>
#include <LiquidCrystal_I2C.h> 

extern LiquidCrystal_I2C myLCD; // Declaração global

// Declaração das funções para manipulação do LCD
void animarLCD(LiquidCrystal_I2C &lcd);
void configuracaoLcd(LiquidCrystal_I2C &lcd);

#endif
