// LCD
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x3F, 16, 2);
#define imprimir(cadena){lcd.print(cadena);}

//TyH
unsigned long milisAnterior = 0;
#include <OneWire.h>
#include <DallasTemperature.h>
OneWire oneWireObjeto(4);
DallasTemperature sensorDS18B20(&oneWireObjeto);
float base = 10.0; // base log.
float a = 7.5;     // wikipedia
float b = 237.7;   // wikipedia
float c = 6.11;    //wikipedia
float Pr = 1016; //pressione atmosferica

float calculaPresion(float temp)
{
 return c * pow(base, (a * temp) / (b + temp));  
}

float correzione(float Tw, float t)
 {
  return 0.00066 * (1 + 0.00155* Tw) * Pr * (t - Tw);
  }

float calculaHumedad(float t, float Tw)
{
  float Es = calculaPresion(t); // pressione vapor saturo con Ts
  float Ew = calculaPresion(Tw); // pressione vapor saturo con Tw
 
  float correzioneSprung = correzione(Tw, t); 

  float e = Ew - correzioneSprung; // Formula di Sprung
  float humedadRelativa = e / Es * 100;// calcola umidita Relativa
  
  return humedadRelativa;
}

float t;
float Tw; 
double h;
#define OffsetT 0
#define OffsetH 0

// RTC
#include "RTClib.h"

//SD
//#include <SPI.h>
//#include <SdFat.h>
//SdFat SD;

//File myFile;
////byte minutoant = 0;
//int UltimaPosicion=0;
//byte cont=0;
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
long fecha = 0;

//COMUNICACION UART
#include <AltSoftSerial.h>
AltSoftSerial esp;

//MESH
#define intervalo 5
String mensajeSalida = "";
String mensajeEntrada = "";
//char mensajeGuardado = "";
//char linea = "";
byte idMensaje = 0;
//byte idMen = 0;
byte indice = 0;
bool unicaVez = false;
bool unicaVez1 = false;
bool unicaVez2 = false;
bool unicaVez3 = false;
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
