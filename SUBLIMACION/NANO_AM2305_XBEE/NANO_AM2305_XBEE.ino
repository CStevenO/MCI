#include "Def.h"
void setup()
{
  wdt_disable();
  #include "Conf.h"
  wdt_enable(WDTO_8S);
  //RTC.adjust(DateTime(2020, 3, 25, 13, 50, 0));
}

void loop()
{
  tiempoActual(); //RTC
  sublimacion();  //sublimacion
  obtenerVariables(); //AM2305
  principal(); //MENU
  enviarDatos(); //RTC
  watchdogSetup(); //perro guardian
}
