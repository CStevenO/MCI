// LCD
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x3F, 16, 2);
#define imprimir(cadena){lcd.print(cadena);}
// RTC
#include "RTClib.h"
RTC_DS3231 RTC;
short anio = 0;
byte mes = 0;
byte dia = 0;
byte hora = 0;
byte minuto =  0;
byte segundo = 0;
short momentoInicioSub = 0;
short momentoFinSub = 0;
short momentoInicioDuc = 0;
short momentoFinDuc = 0;
short momentoAhora = 0;
#define retraso 0
unsigned long tiempoRetraso = 0;
//MENU
#define boton 3
byte estado = 0;
byte subEstado = 0;
boolean estadoAnterior = HIGH;
boolean estadoActual = HIGH;
char v = '-';
char s = '-';
char d = '-';
byte habilitado[8] = { B00000, B01110, B10001, B10001, B10001, B10001, B01110, B00000 };
byte deshabilitado[8] = { B00000, B10001, B01010, B00100, B01010, B10001, B00000, B00000 };
unsigned long tiempoP = 0;
byte parametro = 0;
byte valorH = 0;
byte valorM = 0;
byte valor = 0;
#define inactividad 30000
//SHT
unsigned long milisAnterior = 0;
#include <SHT1x.h>
#define dataPin  4
#define clockPin 5
SHT1x sht1x(dataPin, clockPin);
float t;
float h;
byte histeresis = 0;
byte sph = 0;
#define OffsetT 0
#define OffsetH 0
//LUZ
#define luz 2
boolean luzActual = true;
boolean luzAnterior = true;
//COMUNICACIÓN UART
#include <AltSoftSerial.h>
AltSoftSerial esp;
//MESH
#define intervalo 5
String mensajeSalida = "";
String mensajeEntrada = "";
byte idMensaje = 0;
byte indice = 0;
bool unicaVez = false;
int datos[6];
#define idInvernadero "1793"
#define separador ','
//MCP
#include "Adafruit_MCP23017.h"
boolean ventActual = false;
boolean ventAnterior = false;
boolean subActual = false;
boolean subAnterior = false;
boolean ducActual = false;
boolean ducAnterior = false;
Adafruit_MCP23017 mcp;
//Salidas
//#define disOut 7 // RELÉ 4
#define ducOut 6 // RELÉ 3
#define subOut 5 // RELÉ 2
#define venOut 4 // RELÉ 1
//Entradas
//#define disIn 3
#define ducIn 2
#define subIn 1
#define venIn 0
// EEPROM
#include <EEPROM.h>
/////////////////////////////   Horas de sublimación
byte hora1Sub = 0;
byte min1Sub = 0;
byte hora2Sub = 0;
byte min2Sub = 0;
/////////////////////////////   Horas de ductos
byte hora1Duc = 0;
byte min1Duc = 0;
byte hora2Duc = 0;
byte min2Duc = 0;
/////////////////////////// ACTIVACION DE ACTUADORES
bool actHSub = false;
bool actHDuc = false;
bool actSPh = false;
//LECTURA DEL POTENCIOMETRO
#define pot A6
#define numLecturas 5
int lecturas[numLecturas];
int promedio;
int total = 0;
byte i = 0;
#define limSup 1020
#define limInf 0
// Perro Guardian
#include <avr/wdt.h>
