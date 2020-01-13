#include "Def.h"
void setup() {
#include "Conf.h"
}

void loop() {
  tiempoActual();
  obtenerVariables();
  principal();
  enviarDatos();
  doggieTickle();  // if you uncomment this line, it will keep resetting the timer.
}
