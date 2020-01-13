void momentos() {
  momentoInicioSub = (hora1Sub * 60) + min1Sub;
  momentoFinSub = (hora2Sub * 60) + min2Sub;
  momentoInicioDuc = (hora1Duc * 60) + min1Duc;
  momentoFinDuc = (hora2Duc * 60) + min2Duc;
  momentoAhora = (hora * 60) + minuto;
}

void actuadores() {
  momentos();
  if (estado != 6 && estado != 7) {
    //Gestion de los ventiladores por humedad
    ventActual = hayHumedad();
    subActual = esHoraSub();
    ducActual = esHoraDuc();

    if (ventActual == true && ventAnterior == false) {
      v = 'V';
      mcp.digitalWrite(venOut, LOW);
    }
    if (ventActual == false && ventAnterior == true) {
      v = '-';
      mcp.digitalWrite(venOut, HIGH);
    }

    if (subActual == true && subAnterior == false) {
      s = 'S';
      mcp.digitalWrite(subOut, LOW);
    }
    if (subActual == false && subAnterior == true) {
      s = '-';
      mcp.digitalWrite(subOut, HIGH);
    }

    if (ducActual == true && ducAnterior == false) {
      d = 'D';
      mcp.digitalWrite(ducOut, LOW);
    }
    if (ducActual == false && ducAnterior == true) {
      d = '-';
      mcp.digitalWrite(ducOut, HIGH);
    }

    ventAnterior = ventActual;
    subAnterior = subActual;
    ducAnterior = ducActual;
  }
}
