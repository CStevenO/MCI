#include "Def.h"
void setup() 
{
//  wdt_disable();
  #include "Conf.h"
//  wdt_enable(WDTO_4S);
}

void loop() 
{
  
  tiempoActual(); //RTC
  obtenerVariables(); //AM2305
  enviarDatos(); //RTC
  menu();
  sublim();
  //watchdogSetup(); //perro guardian
  
}
