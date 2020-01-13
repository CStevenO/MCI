// LCD
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x3F, 16, 2);
#define imprimir(cadena){lcd.print(cadena);}

//DHT
unsigned long milisAnterior = 0;
//#include <DHT.h>
//#define DHTPIN 4     // PIN SENSOR
//#define DHTTYPE DHT22   // DHT 22  (AM2302)
//DHT dht(DHTPIN, DHTTYPE);
float t;
float h;
#define OffsetT 0
#define OffsetH 0

// RTC
#include "RTClib.h"

//SD
#include <SPI.h>
#include <SdFat.h>
SdFat SD;

File myFile;
//byte minutoant = 0;
int UltimaPosicion=0;
byte cont=0;
//byte conta=0;

String mensajeS = " ";

//int idInv = 0;
RTC_DS3231 RTC;
short anio = 0;
byte mes = 0;
byte dia = 0;
byte hora = 0;
byte minuto =  0;
byte segundo = 0;

//COMUNICACION UART
#include <AltSoftSerial.h>
AltSoftSerial esp;

//MESH
#define intervalo 5
String mensajeSalida = "";
String mensajeEntrada = "";
char mensajeGuardado = "";
//char linea = "";
byte idMensaje = 0;
byte idMen = 0;
byte indice = 0;
bool unicaVez = false;
int datos[6];
int idInvernadero=1758;
#define separador ','
byte i = 0;

//WATCHDOG

#include <avr/wdt.h>

//Reinicio
//unsigned long tiempo = 0;

//MCP
//#include "Adafruit_MCP23017.h"
//Adafruit_MCP23017 mcp;
