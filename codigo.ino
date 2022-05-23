#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

Adafruit_SSD1306 display = Adafruit_SSD1306(128, 32, &Wire);

// OLED FeatherWing buttons map to different pins depending on board:
#if defined(ESP8266)
#define BUTTON_A  0
#define BUTTON_B 16
#define BUTTON_C  2
#elif defined(ESP32)
#define BUTTON_A 15
#define BUTTON_B 32
#define BUTTON_C 14
#elif defined(ARDUINO_STM32_FEATHER)
#define BUTTON_A PA15
#define BUTTON_B PC7
#define BUTTON_C PC5
#elif defined(TEENSYDUINO)
#define BUTTON_A  4
#define BUTTON_B  3
#define BUTTON_C  8
#elif defined(ARDUINO_FEATHER52832)
#define BUTTON_A 31
#define BUTTON_B 30
#define BUTTON_C 27
#else // 32u4, M0, M4, nrf52840 and 328p
#define BUTTON_A  9
#define BUTTON_B  6
#define BUTTON_C  5
#endif


int n1 = 23;
int n2 = 3;
int btn1 = 1;
int btn2 = 19;
int pot = 4;
int valorPot = 0;
int cont = 0;
int posG = 0;
int sentido=0;
const int filas = 4;
const int columna = 2;
String menu[filas][columna] = {{"Direccion :" , "Izq"},
  {"Tiempo :" , "10 seg"},
  {"Estado :" , "Iniciar"},
  {"Velocidad :" , "50%"}
};

int opciones1 = 0;
int opciones2 = 5;
int opciones3 = 0;

void setup() {

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); // Address 0x3C for 128x32

  Serial.println("OLED begun");


  display.display();
  delay(1000);

  // Clear the buffer.
  display.clearDisplay();
  display.display();

  pinMode(n1 , OUTPUT);
  pinMode(n2 , OUTPUT);

  pinMode(btn1 , INPUT_PULLUP);
  pinMode(btn2 , INPUT_PULLUP);




  // text display tests
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);

  //display.println("hola");
  //display.setCursor(0, 0);
  //display.display(); // actually display all of the above
}

void loop() {

  /*
    digitalWrite(n1 , HIGH);
    digitalWrite(n2 , LOW);
    int buttonState1 = digitalRead(btn1);

    if (buttonState1 == 0) {
    display.clearDisplay();
    display.display();
    display.setCursor(0, 0);
    Serial.print("btn1 encendido");
    display.println("btn1");
    display.display();
    }
    int buttonState2 = digitalRead(btn2);
    if (buttonState2 == 0) {
    display.clearDisplay();
    display.display();
    display.setCursor(0, 0);
    display.println("btn2");
    display.display();
    }

    display.clearDisplay();
    display.display();
    valorPot = analogRead(pot);
    display.setCursor(20, 20);
    display.println(valorPot);
    display.display();
  */

  int buttonState1 = digitalRead(btn1);
  //delay(100);
  if (buttonState1 == 0) {

    cont++;
    if (cont == 4) {

      cont = 0;
    }

    menuOled(cont);
    delay(200);
  }
  int buttonState2 = digitalRead(btn2);
  if (buttonState2 == 0) {

    switch (cont) { //cambio los valores segun la opcion
      case 0:
        if (  opciones1  == 0) {//verifico el estado de cada opciion
          opciones1  = 1;
          menu[0][1] = "Der";
          sentido=1;
          
        }
        else {
          if (  opciones1  == 1) {//verifico el estado de cada opciion
            opciones1  = 0;
            menu[0][1] = "Izq";
            sentido=0;
          }
        }
        menuOled(cont);
        delay(200);
        break;
      case 1:

        opciones2  = opciones2 + 5;
        menu[1][1] = ( (String) opciones2) + " seg";
        if (opciones2 > 30) {
          opciones2  = 0;
        }

        menuOled(cont);
        delay(200);
        break;
      case 2:
        if (  opciones3  == 0) {//verifico el estado para iniciar o parar
          opciones3  = 1;
          menu[2][1] = "Girando";
          if(sentido == 0){
            digitalWrite(n1 , HIGH);
            digitalWrite(n2 , LOW);
            }
            else if(sentido == 1){
            digitalWrite(n1 , LOW);
            digitalWrite(n2 , HIGH);
            }
          
        }
        else {
          if (  opciones3  == 1) {//verifico el estado de cada opciion
            opciones3  = 0;
            menu[2][1] = "Stop";
            digitalWrite(n1 , LOW);
            digitalWrite(n2 , LOW);
          }
        }
        menuOled(cont);
        delay(200);
        break;
      case 3:

        valorPote();
        break;
    }

  }

  if (cont == 3) {
    valorPote();
  }

}

void valorPote() {
  int valor = (analogRead(pot) * 100) / 4095;
  menu[3][1] = (String) valor + " %" ;
  menuOled(cont);
  delay(200);

}



void menuOled(int pos) {

  // posG = pos;
  int contFila = 10;

  int select = 0;

  //matriz[0][0] = 3;

  display.setTextSize(0);
  display.clearDisplay();
  display.setCursor(20 , 0);
  display.setTextColor(SSD1306_WHITE);
  display.println("Menu inicio");


  for (int i = pos ; i < filas ; i++) {


    if (select == 0) {

      display.setTextColor(SSD1306_BLACK);
      display.fillRect(0, 9, 128, 10, SSD1306_WHITE);//y , x ,w , h , color
      select++;
    }
    else {
      display.setTextColor(SSD1306_WHITE);
    }

    display.setCursor(0 , contFila);
    display.println(menu[i][0] + menu[i][1]);
    display.display();
    contFila = contFila + 10;
    display.display();
    //delay(1000);
  }
  /*
    display.setCursor(20 , 0);
    display.setTextColor(SSD1306_WHITE);
    display.println("Menu inicio");
    display.display();
  */

  contFila = 10;




}
