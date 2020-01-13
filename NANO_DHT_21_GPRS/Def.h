// LCD
//#include <SoftwareSerial.h>
//SoftwareSerial gsm(7, 6); // RX, TX
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x3F, 16, 2);
//#include <AltSoftSerial.h>
//AltSoftSerial esp;
#define imprimir(cadena){lcd.print(cadena);}
//DHT
unsigned long milisAnterior = 0;
#include "DHT.h"
#define DHTPIN 4
#define DHTTYPE DHT21
DHT dht(DHTPIN, DHTTYPE);
float t;
float h;
#define OffsetT 0
#define OffsetH 0
// RTC
#include "RTClib.h"
RTC_DS3231 RTC;
String fecha = "";
short anio = 0;
byte mes = 0;
byte dia = 0;
byte hora = 0;
byte minuto =  0;
byte segundo = 0;
//SIM
#define intervalo 5
String url = "";
bool unicaVez = false;
bool unicaVez2 = false;
bool unicaVez3 = false;
#define idInvernadero "1808"
byte i = 0;
String apn = "internet.comcel.com.co";
//Perro
#include <avr/wdt.h>
unsigned long resetTime = 0;
#define TIMEOUTPERIOD 20000  // You can make this time as long as you want, it's not limited to 8 seconds like the normal watchdog
#define doggieTickle() resetTime = millis();  // This macro will reset the timer
