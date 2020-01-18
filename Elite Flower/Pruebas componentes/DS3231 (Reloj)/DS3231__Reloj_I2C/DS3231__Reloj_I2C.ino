// Date and time functions using RX8025 RTC connected via I2C and Wire lib

#include <Wire.h>
#include "Sodaq_DS3231.h"

RTC_DS3231 RTC;

String weekDay[7] = {"Miercoles", "Jueves", "Viernes", "Sabado", "Domingo", "Lunes", "Martes" };
String monthsNames[12] = { "Enero", "Febrero", "Marzo", "Abril", "Mayo",  "Junio", "Julio","Agosto","Septiembre","Octubre","Noviembre","Diciembre" };

void setup () 
{
    Serial.begin(57600);
    Wire.begin();
    rtc.begin();
}

uint32_t old_ts;

void loop () 
{
    DateTime now = RTC.now(); //get the current date-time
    uint32_t ts = now.getEpoch();

    if (old_ts == 0 || old_ts != ts) {
	old_ts = ts;
	Serial.print(now.year(), DEC);
	Serial.print('/');
	Serial.print(now.month(), DEC);
	Serial.print('/');
	Serial.print(now.day(), DEC);
	Serial.print(' ');
	Serial.print(now.hour(), DEC);
	Serial.print(':');
	Serial.print(now.minute(), DEC);
	Serial.print(':');
	Serial.print(now.second(), DEC);
	Serial.print(' ');
	Serial.print(weekDay[now.dayOfWeek()]);
	Serial.println();
//	Serial.print("Seconds since Unix Epoch: "); 
//	Serial.print(ts, DEC);
//	Serial.println();
    }
    delay(1000);
}
