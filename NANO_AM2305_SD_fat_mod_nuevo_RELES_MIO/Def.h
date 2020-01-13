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

//SD
//#include <SPI.h>
//#include <SdFat.h>
//SdFat SD;

//File myFile;
//int UltimaPosicion=0;
//byte cont=0;

String mensajeS = " ";

//int idInv = 0;
RTC_DS3231 RTC;
short anio = 0;
byte mes = 0;
byte dia = 0;
byte hora = 0;
byte minuto =  0;
byte segundo = 0;
short momentoInicioSub = 0;
short momentoFinSub = 0;
short momentoAhora = 0;

//COMUNICACION UART
#include <AltSoftSerial.h>
AltSoftSerial esp;

//MENU
#define boton 3
byte estado = 0;
byte subEstado = 0;
boolean estadoAnterior = HIGH;
boolean estadoActual = HIGH;
unsigned long tiempoP = 0;
byte parametro = 0;
byte valorH = 0;
byte valorM = 0;
byte valor = 0;
char s = '-';
#define inactividad 30000

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
int idInvernadero=1848;
#define separador ','

//MCP
#include "Adafruit_MCP23017.h"
Adafruit_MCP23017 mcp;
boolean subActual = false;
boolean subAnterior = false;

//Salidas
#define subOut 5 // RELÉ 2

//Entradas
#define subIn 1

// EEPROM
#include <EEPROM.h>
/////////////////////////////   Horas de sublimación
byte hora1Sub = 0;
byte min1Sub = 0;
byte hora2Sub = 0;
byte min2Sub = 0;

//LECTURA DEL POTENCIOMETRO
#define pot A6
#define numLecturas 5
int lecturas[numLecturas];
int promedio;
int total = 0;
byte i = 0;
#define limSup 1020
#define limInf 0

//WATCHDOG
#include <avr/wdt.h>

//Reinicio
//unsigned long tiempo = 0;

//MCP
//#include "Adafruit_MCP23017.h"
//Adafruit_MCP23017 mcp;