// LCD
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x3F, 16, 2);
#define imprimir(cadena){lcd.print(cadena);}

//DHT
unsigned long milisAnterior = 0;

float t;
float h;
#define OffsetT 0
#define OffsetH 0

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
byte idMensaje = 0;
byte idMen = 0;
byte indice = 0;
bool unicaVez = false;
int datos[6];
int idInvernadero=1766
;
#define separador ','
byte i = 0;


//MCP
//#include "Adafruit_MCP23017.h"
//Adafruit_MCP23017 mcp;
