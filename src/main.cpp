//  BIG_NUMBERS_FONT_3_COLUMN_2_ROWS_VARIANT_2
#include "animacao.h"
#include "rgbLed.h"
#include "sensorFotoeletrico.h"
#include "LCDBigNumbers.hpp"

#define USE_SERIAL_2004_LCD
#define LCD_I2C_ADDRESS 0x27 // Endereço do LCD
#define LCD_COLUMNS 20       // Número de colunas
#define LCD_ROWS 4           // Número de linhas

// Inicializa os objetos para controle do display LCD
LiquidCrystal_I2C myLCD(LCD_I2C_ADDRESS, LCD_COLUMNS, LCD_ROWS);
LCDBigNumbers bigNum(&myLCD, BIG_NUMBERS_FONT_3_COLUMN_2_ROWS_VARIANT_2);

// Define os pinos dos componentes
#define CHAVE_LADO_1 2
#define CHAVE_LADO_2 3
#define CHAVE_SEGURANCA 7
#define POTENCIOMETRO A0
#define SENSOR_FOTOELETRICO 6
#define LED_R 9
#define LED_G 10
#define LED_B 11

int estadoChave1 = 0;
int estadoChave2 = 0;
int intervalo = 0;
int tempo = 0;

// Variáveis para controlar o tempo
unsigned long previousMillis = 0;

// Variáveis para auxiliar na função limparTela()
bool telaLimpa1 = false;
bool telaLimpa2 = false;
bool telaLimpa3 = false;

// Variáveis para auxiliar em limpar a mensagem
bool limparMensagem1 = false;
bool limparMensagem2 = false;
bool limparMensagem3 = false;

// Variáveis para auxiliar em exibir a mensagem
bool mensagemExibida1 = false;
bool mensagemExibida2 = false;
bool mensagemExibida3 = false;

const long intervaloExibicao = 900; // Tempo que a mensagem ficará na tela (900 ms)

// Variáveis para a função millis (medirPulso())
unsigned long startTime = 0;
unsigned long endTime = 0;
bool sensorActive = false;

int duracaoMilisegundos = 0;

int valor = 0;                   // Armazena o valor retornado da função medirPulso()
int valorSensorFotoeletrico = 0; // Armazena o valor do sensor fortoelétrico

// Declaração das funções
void limparTela(bool *telaLimpa);

void setup()
{
  // Define as Chaves como INPUT
  pinMode(CHAVE_LADO_1, INPUT);
  pinMode(CHAVE_LADO_2, INPUT);
  pinMode(CHAVE_SEGURANCA, INPUT);

  // Define os LEDs como OUTPUT
  pinMode(LED_R, OUTPUT);
  pinMode(LED_G, OUTPUT);
  pinMode(LED_B, OUTPUT);

  Serial.begin(9600);
  configuracaoLcd(myLCD);
  bigNum.begin(); // Inicializa o LCDBigNumbers

  // Loop para realizar a animação
  for (int i = 0; i < 20; i++)
  {
    animarLCD(myLCD);
  }

  myLCD.setCursor(7, 1);
  myLCD.print("Keven");
  delay(900);
  myLCD.clear();
}

void loop()
{

  unsigned long currentMillis = millis();

  estadoChave1 = digitalRead(CHAVE_LADO_1);
  estadoChave2 = digitalRead(CHAVE_LADO_2);
  valorSensorFotoeletrico = digitalRead(SENSOR_FOTOELETRICO);

  // Estado : 1 (Ajuste por pulso)
  if (estadoChave1 && !estadoChave2)
  {
    // Lilás (Roxo claro)
    piscaLedRoxo();

    limparTela(&telaLimpa1);

    // Exibe a mensagem uma vez
    if (!mensagemExibida2)
    {
      myLCD.setCursor(5, 1);
      myLCD.print("Ajuste por");
      myLCD.setCursor(6, 2);
      myLCD.print("Pulso");

      previousMillis = currentMillis; // Marca o tempo atual
      mensagemExibida2 = true;        // recebe  true para a mensagem não seja exibida
    }

    // Após 900 milisegundos, limpa a tela apenas uma vez
    if (mensagemExibida2 && !limparMensagem2 && (currentMillis - previousMillis >= intervaloExibicao))
    {
      myLCD.clear();
      limparMensagem2 = true; // Garante que só limpe uma vez
    }

    // Verifica se a mensagem foi limpa para exibir outras informações
    if (limparMensagem2 == true)
    {
      valor = medirPulso();
      Serial.println(valor);
      exibirMedicaoPulso(myLCD);
      telaLimpa3 = false;
    }
  }
  // Estado: 2 (Ajuste Manual)
  else if (!estadoChave1 && estadoChave2)
  {
    piscaLedCiano();

    limparTela(&telaLimpa2);

    // Exibe a mensagem uma vez
    if (!mensagemExibida1)
    {
      myLCD.setCursor(5, 1);
      myLCD.print("Ajuste");
      myLCD.setCursor(6, 2);
      myLCD.print("Manual");

      previousMillis = currentMillis; // Marca o tempo atual
      mensagemExibida1 = true;
    }

    // Após 900 milisegundos, limpa a tela apenas uma vez
    if (mensagemExibida1 && !limparMensagem1 && (currentMillis - previousMillis >= intervaloExibicao))
    {
      myLCD.clear();
      limparMensagem1 = true; // Garante que só limpe uma vez
    }

    // Verifica se a mensagem foi limpa para exibir outras informações
    if (limparMensagem1)
    {
      intervalo = analogRead(POTENCIOMETRO);
      tempo = map(intervalo, 0, 1023, 100, 3000);
      bigNum.setBigNumberCursor(2, 2);
      bigNum.print(tempo);
    }

    telaLimpa3 = false;
  }
  // Estado: 0 (Sistema Pronto)
  else if (estadoChave1 && estadoChave2)
  {
    // Desliga todos os LEDs
    analogWrite(LED_R, 255);
    analogWrite(LED_G, 255);
    analogWrite(LED_B, 255);

    // variáveis: Ajuste Manual
    // Reinicializa os estados da tela e mensagens
    telaLimpa2 = false;
    limparMensagem1 = false;
    mensagemExibida1 = false;

    // variáveis: Ajuste por pulso
    // Reinicializa os estados da tela e mensagens
    telaLimpa1 = false;
    limparMensagem2 = false;
    mensagemExibida2 = false;

    limparTela(&telaLimpa3);

    // Salva o tempo atual para a próxima verificação
    previousMillis = currentMillis;

    myLCD.setCursor(2, 1);
    myLCD.print(" Sistema Pronto");
    myLCD.setCursor(2, 2);
    myLCD.print(" Ajuste o Tempo");
  }

  // Verifica a se a Chave Segurança
  while (digitalRead(CHAVE_SEGURANCA) == 0)
  {
    myLCD.clear();
    myLCD.backlight();
    myLCD.setCursor(3, 1);
    myLCD.print("SENSOR TRAVADO");
    delay(800);
    myLCD.noBacklight();
    delay(800);
    myLCD.backlight();
  }
}

void limparTela(bool *telaLimpa)
{
  if (!*telaLimpa)
  {
    myLCD.clear();
    *telaLimpa = true; // Garante que só limpe uma vez
  }
}
