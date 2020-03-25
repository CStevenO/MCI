#include "Def.h"
void setup()
{
  wdt_disable();
  #include "Conf.h"
  wdt_enable(WDTO_4S);


  pinMode(subli_pin,OUTPUT);

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
