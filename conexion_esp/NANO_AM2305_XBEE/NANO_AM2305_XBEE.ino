#include "Def.h"
void setup() 
{
  wdt_disable();
  #include "Conf.h"
  wdt_enable(WDTO_8S);
  Serial.begin(9600);
  esp.print("ACT,LV16;");
}

void loop() 
{
  tiempoActual(); //RTC
  obtenerVariables(); //AM2305
  principal(); //MENU
  enviarDatos(); //RTC
  watchdogSetup(); //perro guardian
}
