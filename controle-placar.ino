#include "InputDebounce.h"
#include <SPI.h>
#include <Wire.h>
//#include <LittleFS.h>
#include <ArduinoJson.h>
#include <Adafruit_GFX.h>       // OLED
#include <Adafruit_SSD1306.h>   // OLED

#include <TimeLib.h>            // usado na aba time


// OLED (biblioteca Wire)   // D01
// OLED (biblioteca Wire)   // D02
static const int inputButtonA = 12;         // D06
static const int inputButtonB = 13;         // D07
static const int inputButtonC = 15;         // D08

static InputDebounce buttonA;
static InputDebounce buttonB;
static InputDebounce buttonC;

#define BUTTON_DEBOUNCE_DELAY 20


// DEFINE PARAMETROS DO OLED
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

int voltaParcial = 0;
int voltaCompleta = 0;

unsigned long tInicial = 0;
unsigned long tFinal = 0;
unsigned long tRefresh = 0;
unsigned long tAtual = 0;
unsigned long timeNow = 0;
unsigned long timeBefore = 0;
unsigned long diffTime = 0;
unsigned long diffTotal = 0;

int segundoParcial = 0;
int minutoParcial = 0;
int horaParcial = 0;
int segundoCompleto = 0;
int minutoCompleto = 0;
int horaCompleto = 0;


String tTotal;
String tParcial;


String longTimeStr(const time_t &t){

  // Retorna segundos como "d:hh:mm:ss"
  String s = "";
 //String s = String(t / SECS_PER_DAY) + ':';
 if (hour(t) < 10) {
   s += '0';
 }
 s += String(hour(t)) + ':';

  if (minute(t) < 1) {
    s += "0";
  }
  else if(minute(t) >= 1 && minute(t) < 10){
    s += '0';
  }
  s += String(minute(t)) + ':';

  if (second(t) < 10) {
    s += '0';
  }
  s += String(second(t));

  return s;
}

void oledPrint(String msg, int coluna, int linha) {
  display.setCursor(coluna, linha);
  display.print(msg);
}

void printDisplay(){
  tRefresh = tAtual;
  display.clearDisplay();
  delay(10);
  oledPrint("Voltas totais:", 5, 5);
  oledPrint("T. tot:", 5, 15);
  oledPrint("Voltas parciais:", 5, 25);
  oledPrint("T. parc:", 5, 35);

  oledPrint(String(voltaCompleta), 100, 5);
  oledPrint(tTotal, 65, 15);
  oledPrint(String(voltaParcial), 105, 25);
  oledPrint(tParcial, 65, 35);

  oledPrint(longTimeStr(millis()/1000), 80, 55);
  display.display();
}


void addScore(uint8_t pinIn){
  voltaParcial++;
  voltaCompleta++;

  Serial.print("Time before: ");
  Serial.println(timeBefore);
  diffTime = tAtual - timeBefore;
  diffTotal += diffTime;
  timeBefore = tAtual;
  Serial.print("Time atual: ");
  Serial.println(tAtual);
  Serial.print("Diff Time: ");
  Serial.println(diffTime);

  tParcial = longTimeStr(diffTime);
  tTotal = longTimeStr(diffTotal);
  printDisplay();
}

void rmvScore(uint8_t pinIn){
  voltaParcial--;
  voltaCompleta--;
  printDisplay();
}

void rstScore(uint8_t pinIn){
  voltaParcial = 0;
  printDisplay();
}

void setup() {

  pinMode(inputButtonA, INPUT);
  pinMode(inputButtonB, INPUT);
  pinMode(inputButtonC, INPUT);
  // INICIA SERIAL - BAUD 74880 MOSTRA TIPO DO RESET
  Serial.begin(74880);
  Serial.println(F("Serial Begun"));  // for dubugging purposes

  buttonA.registerCallbacks(addScore, NULL, NULL, NULL);
  buttonB.registerCallbacks(rmvScore, NULL, NULL, NULL);
  buttonC.registerCallbacks(rstScore, NULL, NULL, NULL);

  buttonA.setup(inputButtonA, BUTTON_DEBOUNCE_DELAY, InputDebounce::PIM_EXT_PULL_DOWN_RES);
  buttonB.setup(inputButtonB, BUTTON_DEBOUNCE_DELAY, InputDebounce::PIM_EXT_PULL_DOWN_RES);
  buttonC.setup(inputButtonC, BUTTON_DEBOUNCE_DELAY, InputDebounce::PIM_EXT_PULL_DOWN_RES);

//  // INICIA LITTLEFS
//  if (!LittleFS.begin()) {
//    Serial.println("LittleFS mount failed");
//    return;
//  }

  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }
  oledPrint("Olá",0,0);
  display.display();
  display.setTextSize(1.5);
  display.setTextColor(WHITE);

  delay(1000);

  display.clearDisplay();
  printDisplay();

}

void loop() {

  unsigned long now = millis();
  timeNow = millis()/1000;
  tAtual = millis()/1000;
  if(tAtual - tRefresh == 1UL){
    printDisplay();
  }



  buttonA.process(now);
  buttonB.process(now);
  buttonC.process(now);

  delay(1);


}
