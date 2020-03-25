// LCD
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x3F, 16, 2);
#define imprimir(cadena){lcd.print(cadena);}

//DHT
unsigned long milisAnterior = 0;
#include <DHT.h>
#define DHTPIN 5    // PIN SENSOR
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

int can_subli = 1;
byte hora1Sub[can_subli] = {0};
byte min1Sub[can_subli] = {0};
byte hora2Sub[can_subli] = {0};
byte min2Sub[can_subli] = {0};
short tiempo_sub_ini[can_subli];
short tiempo_sub_fin[can_subli];
for(int i=0;i<can_subli;i++)
{
  tiempo_sub_ini[i] = (hora1Sub[i] * 60) + min1Sub[i];
  tiempo_sub_fin[i] = (hora2Sub[i] * 60) + min2Sub[i];
}
short tiempo_actual = 0;
int subli_pin = 5;    //SEGUNDO RELAY

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
