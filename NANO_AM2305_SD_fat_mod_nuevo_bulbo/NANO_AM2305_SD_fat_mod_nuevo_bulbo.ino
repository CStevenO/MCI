#include "Def.h"
void setup() 
{
  wdt_disable();
  #include "Conf.h"
  wdt_enable(WDTO_4S);
  

}

void loop() 
{
  //tiempo=millis();
  tiempoActual(); //RTC
  obtenerVariables(); //AM2305
  principal(); //MENU
  enviarDatos(); //RTC
  watchdogSetup(); //perro guardian
}
