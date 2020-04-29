#include "Def.h"
void setup()
{
  wdt_disable();
  #include "Conf.h"
  wdt_enable(WDTO_8S);
  //RTC.adjust(DateTime(2020, 3, 26, 10, 17, 0));
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
