void obtenerVariables() {
  if (estado == 0) {
    if (millis() - milisAnterior >= 5000) {
      milisAnterior = millis();
//      t = dht.readTemperature() + OffsetT;
//      h = dht.readHumidity() + OffsetH ;
 t = random(20, 21);
 h = random(40, 41) ;
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
