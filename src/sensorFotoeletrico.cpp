#include "sensorFotoeletrico.h"

extern unsigned long startTime;
extern unsigned long endTime;
extern bool sensorActive;
extern int duracaoMilisegundos;

extern int valor;
extern int valorSensorFotoeletrico;

float medirPulso()
{

    // Verfica se o Sensor de Proximidade esta ativado
    if (valorSensorFotoeletrico == LOW)
    {
        startTime = millis();
        sensorActive = true;
    }

    // Verfica se o Sensor de Proximidade esta desativado
    if (valorSensorFotoeletrico == HIGH)
    {

        endTime = millis();
        duracaoMilisegundos = endTime - startTime; // Calcula o tempo de ativação

        sensorActive = false; // Reseta a flag para aguardar o próximo pulso
    }

    // Verifica duração para não ultrapação o limite
    if (duracaoMilisegundos > 3000)
    {
        duracaoMilisegundos = 3000;
    }
    return duracaoMilisegundos;

    delay(100); // Pequeno atraso para evitar leitura excessiva
}

void exibirMedicaoPulso(LiquidCrystal_I2C &lcd)
{

    lcd.setCursor(0, 0);
    lcd.print("Medicao de pulso");

    valor = valor;

    lcd.setCursor(3, 3);
    lcd.print(valor);

    lcd.setCursor(5, 1);
    lcd.print("Segundos");
}