
#include <LittleFS.h>
#include <ArduinoJson.h>
#include <Adafruit_GFX.h>       // OLED
#include <Adafruit_SSD1306.h>   // OLED

#include <TimeLib.h>            // usado na aba time 


// OLED (biblioteca Wire)   // D01
// OLED (biblioteca Wire)   // D02
#define buttonA 12         // D06
#define buttonB 13         // D07
#define buttonC 15         // D08


// DEFINE PARAMETROS DO OLED
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C           // OLED do Marcatti (4 input pins)
//#define SCREEN_ADDRESS 0x3D           // OLED do Ferreira (8 input pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
// cria objeto Adafruit_SSD1306 com objeto Wire (library) como parâmetro

int voltaParcial = 0;
int voltaCompleta = 0;
int tInicial = 0;
int tFinal = 0;
int buttonStateA = 0;
int buttonStateB = 0;
int buttonStateC = 0;


void oledPrint(String msg, int coluna, int linha) {
  display.setCursor(coluna, linha);
  display.print(msg);
}


void setup() {
  // put your setup code here, to run once:

  pinMode(buttonA, INPUT);
  pinMode(buttonB, INPUT);
  pinMode(buttonC, INPUT);
  // INICIA SERIAL - BAUD 74880 MOSTRA TIPO DO RESET
  Serial.begin(74880);
  Serial.println(F("Serial Begun"));  // for dubugging purposes

  // INICIA LITTLEFS
  if (!LittleFS.begin()) {
    Serial.println("LittleFS mount failed");
    return;
  }

  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Don't proceed, loop forever
    // Será que a gente consegue colocar um reset por código aqui?
  }

  display.display();
  display.setTextSize(1);
  display.setTextColor(WHITE);

  delay(1000);

  display.clearDisplay();

}

void loop() {

  /*
   * 3 botões
   * buttonA adiciona uma volta parcial
   * buttonB reduz uma volta parcial
   * buttonC zera volta parcial
   */

  buttonStateA = digitalRead(buttonA);
  if (buttonStateA == HIGH){
    //fazer alguma coisa
  }
  
  buttonStateB = digitalRead(buttonB);
  if (buttonStateB == HIGH){
    //fazer alguma coisa
  }
  
  buttonStateC = digitalRead(buttonC);
  if (buttonStateC == HIGH){
    //fazer alguma coisa
  }

}
