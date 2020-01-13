// LCD
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x3F, 16, 2);
#define imprimir(cadena){lcd.print(cadena);}

//SHT3x
unsigned long milisAnterior = 0;
#include <SHT3x.h>
SHT3x Sensor;

float t;
float h;
#define OffsetT 0
#define OffsetH 0

//SD
#include <SPI.h>
#include <SdFat.h>
SdFat SD;

File myFile;
int UltimaPosicion=0;
byte cont=0;

// RTC
#include "RTClib.h"


String mensajeS = " ";

int idInv = 0;
bool eliminacion = false;
RTC_DS3231 RTC;
short anio = 0;
byte mes = 0;
byte dia = 0;
byte hora = 0;
byte minuto =  0;
byte segundo = 0;

int val;
String env = "";

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
int idInvernadero=1771;
#define separador ','
byte i = 0;

//WATCHDOG

#include <avr/wdt.h>
//#define TIMEOUTPERIOD 20000             
//#define doggieTickle() resetTime = millis();  // This macro will reset the timer.
//unsigned long resetTime = 0;

//MCP
//#include "Adafruit_MCP23017.h"
//Adafruit_MCP23017 mcp;
