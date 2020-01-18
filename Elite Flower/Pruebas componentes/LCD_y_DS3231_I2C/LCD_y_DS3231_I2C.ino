#include <Wire.h>
#include <LiquidCrystal_I2C.h> 
#include "Sodaq_DS3231.h"

LiquidCrystal_I2C lcd(0x3F,16,2); 
 
String weekDay[7] = { "Domingo", "Lunes", "Martes", "Miercoles", "Jueves", "Viernes", "Sabado" };
 
void setup() 
{
  Wire.begin(); // Inicia el puerto I2C
rtc.begin(); // Inicia la comunicaci¢n con el RTC
//rtc.adjust(DateTime(__DATE__, __TIME__)); // Establece la fecha y hora (Comentar una vez establecida la hora)
//el anterior se usa solo en la configuracion inicial
   Serial.begin(9600);
   lcd.init();
 lcd.backlight();
  lcd.clear();

}
 
void loop(){
DateTime now = rtc.now(); // Obtiene la fecha y hora del RTC
   
Serial.print(now.year(), DEC); // A§o
Serial.print('/');
Serial.print(now.month(), DEC); // Mes
Serial.print('/');
Serial.print(now.date(), DEC); // Dia
Serial.print(' ');
Serial.print(now.hour(), DEC); // Horas
Serial.print(':');
Serial.print(now.minute(), DEC); // Minutos
Serial.print(':');
Serial.print(now.second(), DEC); // Segundos
Serial.print(':');
Serial.print(weekDay[now.dayOfWeek()]);
Serial.println();
lcd.setCursor(0,0);
lcd.print("Fecha: ");
lcd.print(now.year(), DEC);
lcd.print("/");
lcd.print(now.month(), DEC);
lcd.print("/");
lcd.print(now.date(), DEC);
lcd.print(" ");
lcd.setCursor(0,1);
lcd.print("Hora: ");
lcd.print(now.hour(), DEC);
lcd.print(":");
lcd.print(now.minute(), DEC);
lcd.print(":");
lcd.print(now.second(), DEC);
delay(1000); // La informaci¢n se actualiza cada 1 seg.
lcd.setCursor(0,0);
lcd.print("               ");
lcd.setCursor(0,1);
lcd.print("               ");

}
