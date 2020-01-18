#include <Wire.h>
#include <LiquidCrystal_I2C.h> 
#include "Sodaq_DS3231.h"
#include <dht.h>
#include "Adafruit_MCP23017.h"
#include <AltSoftSerial.h>

#define DHT22PIN 4     // PIN SENSOR


Adafruit_MCP23017 mcp;

dht1wire DHT(DHT22PIN, dht::DHT22);

AltSoftSerial altSerial;

LiquidCrystal_I2C lcd(0x3F,16,2); 
 
int i=0;
String str;
String mensaje;
float temperature;

void setup() 
{
  Wire.begin(); // Inicia el puerto I2C
  rtc.begin(); // Inicia la comunicaci¢n con el RTC
  DHT.read();
  altSerial.begin(9600);
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.clear();
  mcp.begin();  

  mcp.pinMode(7, OUTPUT);
  mcp.pinMode(6, OUTPUT);
  mcp.pinMode(5, OUTPUT);
  mcp.pinMode(4, OUTPUT);
}
 
void loop()

{

DateTime now = rtc.now(); // Obtiene la fecha y hora del RTC

float h = (DHT.getHumidity()/10);
float t = (DHT.getTemperature()/10);

lcd.setCursor(0,0);
lcd.print("F:");
int ano=now.year()-2000;
lcd.print(ano);
lcd.print("/");
lcd.print(now.month(), DEC);
lcd.print("/");
lcd.print(now.date(), DEC);
lcd.print(" ");
lcd.print(now.hour(), DEC);
lcd.print(":");
lcd.print(now.minute(), DEC);
lcd.print(":");
lcd.print(now.second(), DEC);
mensaje.reserve(27);
mensaje = "01," + String(ano) + "/" + String(now.month()) + "/" + String(now.date()) + "," + String(now.hour()) + ":" + String(now.minute()) + ":" + String(now.second()) + "," + String(t, 2) + "," + String(h, 2) + ";";

altSerial.print(mensaje);

lcd.setCursor(0,1);
lcd.print("H:"); 
lcd.print(h,1); //le doy solo una decima al float
lcd.print("% ");
lcd.print("T:"); 
lcd.print(t,1);
lcd.print((char)223);
lcd.print("C");

if(h>=80)
  {
    i=1;  
  }

if(t>=30)
  {
    i=2;
  }

if(h<80)
  {
    i=0;
  }

if(i==1)
  {
    mcp.digitalWrite(7, HIGH);
    mcp.digitalWrite(6, HIGH);
    mcp.digitalWrite(5, HIGH);
    mcp.digitalWrite(4, LOW); 
  }

if(1==2)
  {
    mcp.digitalWrite(7, HIGH);
    mcp.digitalWrite(6, HIGH);
    mcp.digitalWrite(5, LOW);
    mcp.digitalWrite(4, HIGH);
  }
   
if(i==0)

 {
    mcp.digitalWrite(7, HIGH);
    mcp.digitalWrite(6, HIGH);
    mcp.digitalWrite(5, HIGH);
    mcp.digitalWrite(4, HIGH);
  }
}
