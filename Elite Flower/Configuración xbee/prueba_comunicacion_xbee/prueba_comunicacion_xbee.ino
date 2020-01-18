// LCD
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x3F, 16, 2);
#define imprimir(cadena){lcd.print(cadena);}
//COMUNICACION UART
#include <AltSoftSerial.h>
AltSoftSerial esp;
String mensajeSalida = "";
// RTC
#include "RTClib.h"
RTC_DS3231 RTC;
short anio = 0;
byte mes = 0;
byte dia = 0;
byte hora = 0;
byte minuto =  0;
byte segundo = 0;
int t=2;
int h=1;
void setup() 
{
 Wire.begin(); // Inicia el puerto I2C
// lcd.init();
//lcd.backlight();
//lcd.clear();
//RTC
RTC.begin();
//COMUNICACION UART
esp.begin(9600);
Serial.begin(9600);
}

void loop() 
{
 DateTime now = RTC.now(); // Obtiene la fecha y hora del RTC
  anio = now.year();
  mes = now.month();
  dia = now.day();
  hora = now.hour();
  minuto =  now.minute();
  segundo = now.second();
  
// lcd.setCursor(0, 0); 
//  imprimir("H"); lcd.print(h, 1); imprimir("%");
//  imprimir("   T"); lcd.print(t, 1); imprimir((char)223); imprimir("C");
//  lcd.setCursor(0, 1);
//  if (hora < 10) 
//  {
//    imprimir("0");
//  }
//  imprimir(hora);
//  imprimir(":");
//  if (minuto < 10) 
//  {
//    imprimir("0");
//  }
//  imprimir(minuto);
//  imprimir(":");
//  if (segundo < 10) 
//  {
//    imprimir("0");
//  }
//  imprimir(segundo);

 mensajeSalida.reserve(40);
      mensajeSalida = "01," + String(anio) + "-" + String(mes) + "-" + String(dia) + " " + String(hora) + ":" + String(minuto) + ":" + String(segundo) + "," + "1111" + "," + String(t, 2) + "," + String(h, 2) + ";";
 esp.print(mensajeSalida);
 //Serial.println("hola");
 delay(5000);

 //delay(3000);
  

}
