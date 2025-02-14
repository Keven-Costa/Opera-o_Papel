#include "animacao.h"

int i = 0;

byte customChar1[] = {
    0x18,
    0x18,
    0x18,
    0x18,
    0x18,
    0x18,
    0x18,
    0x18};

byte customChar2[] = {
    0x03,
    0x03,
    0x03,
    0x03,
    0x03,
    0x03,
    0x03,
    0x03};

void animarLCD(LiquidCrystal_I2C &lcd)
{
    lcd.clear();
    lcd.setCursor(i, 0);
    lcd.write(0);

    lcd.setCursor(i, 1);
    lcd.write(0);

    lcd.setCursor(i, 2);
    lcd.write(0);

    lcd.setCursor(i, 3);
    lcd.write(0);
    delay(50);

    lcd.clear();
    lcd.setCursor(i, 0);
    lcd.write(1);
    lcd.setCursor(i, 1);
    lcd.write(1);
    lcd.setCursor(i, 2);
    lcd.write(1);
    lcd.setCursor(i, 3);
    lcd.write(1);

    delay(50);

    lcd.clear();

    i++;
    if (i == 20)
        i = 0;
}

void configuracaoLcd(LiquidCrystal_I2C &lcd)
{
    lcd.init();
    lcd.backlight();
    lcd.createChar(0, customChar1);
    lcd.createChar(1, customChar2);
    lcd.clear();
}
