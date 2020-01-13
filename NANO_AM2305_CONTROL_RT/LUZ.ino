void energia() {
  luzActual = digitalRead(luz);
  if (luzActual == false && luzAnterior == true) {
    lcd.noBacklight();
    mensajeSalida.reserve(40);
    mensajeSalida = "02," + String(anio) + "-" + String(mes) + "-" + String(dia) + " " + String(hora) + ":" + String(minuto) + ":" + String(segundo) + "," + String(idInvernadero) + ",Se fue;";
    esp.print(mensajeSalida);
  }
  if (luzActual == true && luzAnterior == false) {
    lcd.backlight();
    mensajeSalida.reserve(40);
    mensajeSalida = "02," + String(anio) + "-" + String(mes) + "-" + String(dia) + " " + String(hora) + ":" + String(minuto) + ":" + String(segundo) + "," + String(idInvernadero) + ",Volvio;";
    esp.print(mensajeSalida);
  }
  luzAnterior = luzActual;
}
