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
#define pinSonda A1
unsigned long previo=0;
float escala = 0.1; 
int cont1=0;
float voltaje;
float voltajeProm;
float lectura;
float voltajeSum=0;
String mensajeSalidaSuelo = "";


//WATCHDOG
#include <avr/wdt.h>
