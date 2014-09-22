//Librerias necesarias para la matriz de LEDs
#include <Wire.h>
#include "Adafruit_LEDBackpack.h"
#include "Adafruit_GFX.h"

//Matriz
Adafruit_8x8matrix matriz = Adafruit_8x8matrix();
//Variable para almacenar la lectura de humedad
int humedad = 0;

void setup() {
  Serial.begin(57600);
  matriz.begin(0x70); //Inicializacion de la matriz
  //Inicializamos los LEDs
  //LED amarillo en el pin 10 -> Tierra seca
  pinMode(10, OUTPUT);
  //LED verde en el pin 11 -> Tierra optima
  pinMode(11, OUTPUT);
  //LED rojo en el pin 12 -> Tierra inundada
  pinMode(12, OUTPUT);
}
//Dibujamos las caritas
static const uint8_t PROGMEM
  planta_contenta[] =
  { B00111100,
    B01000010,
    B10100101,
    B10000001,
    B10100101,
    B10011001,
    B01000010,
    B00111100 },
  planta_triste[] =
  { B00111100,
    B01000010,
    B10100101,
    B10000001,
    B10011001,
    B10100101,
    B01000010,
    B00111100 },
   planta_ahogada[] = 
   {
     B00111100,
     B01000010,
     B10100101,
     B11001111,
     B11101111,
     B11111111,
     B11111111,
     B11111111 };

void loop() {
  humedad = analogRead(0);
  Serial.print("Lectura del valor de humedad:");
  Serial.println(humedad);
  //Si la lectura de humedad esta por debajo de 300
  //la planta necesita agua y esta triste
  if (humedad < 300) {
    matriz.clear();
    matriz.drawBitmap(0, 0, planta_triste, 8, 8, LED_ON);
    matriz.writeDisplay();
    //Encendemos el LED amarillo
    digitalWrite(10, HIGH);
    digitalWrite(11, LOW);
    digitalWrite(12, LOW);
    delay(500); 
  }
  //Si la lectura esta entre 300 y 700 la humedad
  //es correcta y la planta esta contenta
  else if ((humedad >= 300) && (humedad < 700)) {
    matriz.clear();
    matriz.drawBitmap(0, 0, planta_contenta, 8, 8, LED_ON);
    matriz.writeDisplay();
    //Encendemos el LED verde
    digitalWrite(10, LOW);
    digitalWrite(11, HIGH);
    digitalWrite(12, LOW);
    delay(500);
  }
  //Lecturas superiores a 700 significan que la tierra esta
  //demasiado humeda y la planta se ahoga
  else {
    matriz.clear();
    matriz.drawBitmap(0, 0, planta_ahogada, 8, 8, LED_ON);
    matriz.writeDisplay();
    //Encendemos el LED rojo
    digitalWrite(10, LOW);
    digitalWrite(11, LOW);
    digitalWrite(12, HIGH);
    delay(500); 
  }
  delay(100);
}
