// LCD
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x3F, 16, 2);
#define imprimir(cadena){lcd.print(cadena);}

//DHT
unsigned long milisAnterior = 0;
#include <DHT.h>
#define DHTPIN 4    // PIN SENSOR
#define DHTTYPE DHT22   // DHT 22  (AM2302)
DHT dht(DHTPIN, DHTTYPE);
float t;
float h;
#define OffsetT 0
#define OffsetH 0

// RTC
#include "RTClib.h"
String mensajeS = " ";

//int idInv = 0;
RTC_DS3231 RTC;
short anio = 0;
byte mes = 0;
byte dia = 0;
byte hora = 0;
byte minuto =  0;
byte segundo = 0;
long fecha = 0;

//Sublimacion
#include "Adafruit_MCP23017.h"
byte hora1Sub = 13;
byte min1Sub = 55;
byte hora2Sub = 15;
byte min2Sub = 0;
bool compro = true;                              //false = hi>hf     ;     true = hi<hf
short tiempo_sub_ini = (hora1Sub * 60) + min1Sub;
short tiempo_sub_fin = (hora2Sub * 60) + min2Sub;
short tiempo_actual = 0;
Adafruit_MCP23017 mcp;
//Salidas
//#define disOut 7 // RELÉ 4
//#define ducOut 6 // RELÉ 3
#define subOut 5 // RELÉ 2
//#define venOut 4 // RELÉ 1
//Entradas
//#define disIn 3
//#define ducIn 2
#define subIn 1
//#define venIn 0

//COMUNICACION UART
#include <AltSoftSerial.h>
AltSoftSerial esp;

//MESH
#define intervalo 5
String mensajeSalida = "";
String mensajeEntrada = "";
byte idMensaje = 0;
byte indice = 0;
bool unicaVez = false;
bool unicaVez1 = false;
bool unicaVez2 = false;
bool unicaVez3 = false;
int datos[6];
int idInvernadero=1783;
#define separador ','
byte i = 0;

//WATCHDOG
#include <avr/wdt.h>
