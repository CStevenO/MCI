#include <Wire.h>
#include <LiquidCrystal_I2C.h> 
#include "Sodaq_DS3231.h"
#include <dht.h>
#include "Adafruit_MCP23017.h"
#include <AltSoftSerial.h>

AltSoftSerial altSerial;

#define DHT22PIN 4     // PIN SENSOR
//#define DHTTYPE DHT22   // DHT 22  (AM2302)

dht1wire DHT(DHT22PIN, dht::DHT22);

Adafruit_MCP23017 mcp;

//dht (DHTPIN, DHTTYPE);

LiquidCrystal_I2C lcd(0x3F,16,2); 
  
void setup() 
{
  Wire.begin(); // Inicia el puerto I2C
  rtc.begin(); // Inicia la comunicaci¢n con el RTC
  DHT.read();
  Serial.begin(9600);
  altSerial.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.clear();
  mcp.begin();  

  mcp.pinMode(7, OUTPUT);
  mcp.pinMode(6, OUTPUT);
  mcp.pinMode(5, OUTPUT);
  mcp.pinMode(4, OUTPUT);
}
 
void loop(){


DateTime now = rtc.now(); // Obtiene la fecha y hora del RTC

// Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = (DHT.getHumidity()/10);
  // Read temperature as Celsius
  int t = (DHT.getTemperature()/10);
  Serial.print(t);
 Serial.print(';');
    Serial.println(t);


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
    mcp.digitalWrite(7, HIGH);
    mcp.digitalWrite(6, HIGH);
    mcp.digitalWrite(5, HIGH);
    mcp.digitalWrite(4, LOW);
  }
delay(2000); // La informaci¢n se actualiza cada 0.4 seg.

if(t>=30)
  {
    mcp.digitalWrite(7, HIGH);
    mcp.digitalWrite(6, HIGH);
    mcp.digitalWrite(5, LOW);
    mcp.digitalWrite(4, HIGH);
  }

if(h>=80 && t>=30)
  {
    mcp.digitalWrite(7, HIGH);
    mcp.digitalWrite(6, HIGH);
    mcp.digitalWrite(5, LOW);
    mcp.digitalWrite(4, LOW);
  }

else

 {
    mcp.digitalWrite(7, HIGH);
    mcp.digitalWrite(6, HIGH);
    mcp.digitalWrite(5, HIGH);
    mcp.digitalWrite(4, HIGH);
  }
}
