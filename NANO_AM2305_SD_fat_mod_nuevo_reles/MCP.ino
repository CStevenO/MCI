void momentos() {
  momentoInicioSub = (hora1Sub * 60) + min1Sub;
  momentoFinSub = (hora2Sub * 60) + min2Sub;
  momentoAhora = (hora * 60) + minuto;
}

void actuadores() {
  momentos();
  if (estado != 6 && estado != 7) {

     subActual = esHoraSub();

     if (subActual == true && subAnterior == false) {
      s = 'S';
      mcp.digitalWrite(subOut, LOW);
    }
    if (subActual == false && subAnterior == true) {
      s = '-';
      mcp.digitalWrite(subOut, HIGH);
    }
    subAnterior = subActual;
  }
}
