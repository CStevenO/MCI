// LCD
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x3F, 16, 2);
#define imprimir(cadena){lcd.print(cadena);}

//SD
#include <SPI.h>
#include <SdFat.h>
SdFat SD;

File myFile;

// RTC
#include "RTClib.h"
RTC_DS3231 RTC;
short anio = 0;
byte mes = 0;
byte dia = 0;
byte hora = 0;
byte minuto =  0;
byte segundo = 0;
String mensajeS = " ";

//Humedad suelo
const int sensorPin = A0;    // seleccionar la entrada para el sensor
float sensorValue;       // variable que almacena el valor raw (0 a 1023)
float psi=0;
float kpa=0;
#define OFFSET 0;


//WATCHDOG
#include <avr/wdt.h>
