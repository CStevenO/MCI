// LCD
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x3F, 16, 2);
#define imprimir(cadena){lcd.print(cadena);}

//DHT
unsigned long milisAnterior = 0;
#include <SHT1x.h>
#define dataPin  4
#define clockPin 5
SHT1x sht1x(dataPin, clockPin);
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
byte minutoant = 0;
int UltimaPosicion=0;

String mensajeS = " ";

RTC_DS3231 RTC;
short anio = 0;
byte mes = 0;
byte dia = 0;
byte hora = 0;
byte minuto =  0;
byte segundo = 0;

//int val;
//String env = "";

//COMUNICACION UART
#include <AltSoftSerial.h>
AltSoftSerial esp;

//MESH
#define intervalo 5
String mensajeSalida = "";
String mensajeEntrada = "";
char mensajeGuardado = "";
byte idMensaje = 0;
byte idMen = 0;
byte indice = 0;
bool unicaVez = false;
int datos[6];
int idInvernadero=1839;
#define separador ','
byte i = 0;

//WATCHDOG

#include <avr/wdt.h>

//MCP
//#include "Adafruit_MCP23017.h"
//Adafruit_MCP23017 mcp;
