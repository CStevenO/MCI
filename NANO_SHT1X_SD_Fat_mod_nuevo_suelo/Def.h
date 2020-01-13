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
#define OffsetH 0

// RTC
#include "RTClib.h"


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
byte idMensaje = 0;

byte indice = 0;
bool unicaVez = false;
bool unicaVez1 = false;
bool unicaVez2 = false;
bool unicaVez3 = false;
int datos[6];
int idInvernadero=1878;
#define separador ','
byte i = 0;

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

//MCP
//#include "Adafruit_MCP23017.h"
//Adafruit_MCP23017 mcp;
