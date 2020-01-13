#include "Def.h"
void setup() {


#include "Conf.h"



}

void loop() 
{
  tiempoActual(); //RTC
  obtenerVariables(); //AM2305
  principal(); //MENU
  enviarDatos(); //RTC

}
