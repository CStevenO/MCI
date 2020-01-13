#include "Def.h"
void setup() {
#include "Conf.h"
}

void loop() {
  tiempoActual();
  obtenerVariables();
  enviarDatos();
  menu();
  energia();
  reset();
  actuadores();
  wdt_reset();
}
