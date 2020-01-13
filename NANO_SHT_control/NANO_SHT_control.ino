#include "Def.h"
void setup() 
{
  wdt_disable();
  #include "Conf.h"
  wdt_enable(WDTO_4S);
}

void loop() 
{
  tiempoActual();
  obtenerVariables();
  enviarDatos();
  menu();
  energia();
  actuadores();
  watchdogSetup(); //perro guardian
  encendido();
}
