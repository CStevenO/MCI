void obtenerVariables() {
  if (millis() - milisAnterior >= 5000) {
    milisAnterior = millis();
    h = dht.readHumidity() + OffsetT;
    t = dht.readTemperature() + OffsetH ;
    //h=20;
    //t=30;
    lcd.clear();
  }
}

