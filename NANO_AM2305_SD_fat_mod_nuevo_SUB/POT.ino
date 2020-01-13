int potenciometro() {
  for (i = 0; i < numLecturas; i++) {
    total = total - lecturas[i];
    lecturas[i] = analogRead(pot);
    total = total + lecturas[i];
    delay(0.5);
  }
  promedio = total / numLecturas;
  return promedio;
}

byte obtenerParametro() {
  byte oP = 0;
  oP = map(potenciometro(), limSup, limInf, 6, 0);
  if (oP >= 6) {
    oP = 6;
  }
  return oP;
}

byte obtenerActivacionS() {
  valor = map(potenciometro(), limSup, limInf, 60, 0);
  if (valor >= 60) {
    valor = 60;
  }
  return valor;
}

byte obtenerHora() {
  valor = map(potenciometro(), limSup, limInf, 23, 0);
  if (valor >= 23) {
    valor = 23;
  }
  return valor;
}

byte obtenerMinuto() {
  valor = map(potenciometro(), limSup, limInf, 59, 0);
  if (valor >= 59) {
    valor = 59;
  }
  return valor;
}
