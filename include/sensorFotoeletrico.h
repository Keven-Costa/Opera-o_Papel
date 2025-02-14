#ifndef SENSOR_FOTOELETRICO_H // Evita inclusão duplicada
#define SENSOR_FOTOELETRICO_H

#include <Arduino.h>
#include "animacao.h" // Inclusão do arquivo de cabeçalho para utilizar LiquidCrystal_I2C e evitar múltiplas inclusões.



// Declaração das funções para medição de pulso
float medirPulso();
void exibirMedicaoPulso(LiquidCrystal_I2C &lcd);

#endif