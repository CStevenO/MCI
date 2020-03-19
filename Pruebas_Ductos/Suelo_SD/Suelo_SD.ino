#include "Def.h"
void setup() {
wdt_disable();
#include "Conf.h"
wdt_enable(WDTO_4S);
Serial.begin(9600);

}

void loop()
{
  tiempoActual(); //RTC
  principal(); //MENU
  enviarDatos(); //RTC
  watchdogSetup(); //perro guardian
}
