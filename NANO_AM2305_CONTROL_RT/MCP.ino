void momentos() {
  momentoInicioSub = (hora1Sub * 60) + min1Sub;
  momentoFinSub = (hora2Sub * 60) + min2Sub;
  momentoInicioAsp = (hora1Asp * 60) + min1Asp;
  momentoFinAsp = (hora2Asp * 60) + min2Asp;
  momentoAhora = (hora * 60) + minuto;
}

void actuadores() {
  momentos();
  if (estado != 6 && estado != 7) {
    //Gestion de los ventiladores por humedad
    ventActual = hayHumedad();
    subActual = esHoraSub();
    aspActual = esHoraAsp();

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

    if (aspActual == true && aspAnterior == false) {
      d = 'D';
      mcp.digitalWrite(aspOut, LOW);
    }
    if (aspActual == false && aspAnterior == true) {
      d = '-';
      mcp.digitalWrite(aspOut, HIGH);
    }

    ventAnterior = ventActual;
    subAnterior = subActual;
    aspAnterior = aspActual;
  }
}
