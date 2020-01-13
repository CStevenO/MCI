void obtenerVariables() {
  if (millis() - milisAnterior >= 5000) 
  {
    milisAnterior = millis();
    t = dht.readTemperature() + OffsetT;
    h = dht.readHumidity() + OffsetH ;

    lcd.clear();
  }
}
