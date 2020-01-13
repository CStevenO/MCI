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
  oP = map(potenciometro(), limSup, limInf, 16, 0);
  if (oP >= 16) {
    oP = 16;
  }
  return oP;
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

byte obtenerHumedad() {
  valor =  map(potenciometro(), limSup, limInf, 99, 0);
  if (valor >= 99) {
    valor = 99;
  }
  return valor;
}

byte obtenerHisteresis() {
  valor =  map(potenciometro(), limSup, limInf, 5, 1);
  if (valor >= 5) {
    valor = 5;
  }
  return valor;
}

byte obtenerOnOFF() {
  valor =  map(potenciometro(), limSup, limInf, 1, 0);
  if (potenciometro() < (limSup / 2)) {
    return 0;
  } else {
    return 1;
  }
}
