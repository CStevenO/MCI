void obtenerVariables() {
  if (estado == 0) {
    if (millis() - milisAnterior >= 5000) {
      milisAnterior = millis();
      t = sht1x.readTemperatureC() + OffsetT;
      h = sht1x.readHumidity() + OffsetH ;
      lcd.clear();
    }
  }
}

boolean hayHumedad() {
  if (h >= sph && actSPh) {
    return true;
  }
  if (h <= sph - histeresis) {
    return false;
  }
}
