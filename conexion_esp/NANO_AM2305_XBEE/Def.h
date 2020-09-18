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

//COMUNICACION UART
#include <AltSoftSerial.h>
AltSoftSerial esp;

//RELES
#include "Adafruit_MCP23017.h"
Adafruit_MCP23017 mcp;
#define disOut 7 // RELÉ 4
#define ducOut 6 // RELÉ 3
#define subOut 5 // RELÉ 2
#define venOut 4 // RELÉ 1


//MESH
#define intervalo 5
String mensajeSalida = "";
String mensajeEntrada = "";
String* mensaEntrada;
byte idMensaje = 0;
byte indice = 0;
int datos[6];
int idInvernadero=1783;
#define separador ','
byte i = 0;
bool unica=false;
//WATCHDOG
#include <avr/wdt.h>
