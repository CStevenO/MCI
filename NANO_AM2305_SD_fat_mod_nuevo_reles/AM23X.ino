void obtenerVariables() {
  if(estado == 0)
  {
  if (millis() - milisAnterior >= 5000) 
  {
    milisAnterior = millis();
    t = dht.readTemperature() + OffsetT;
    h = dht.readHumidity() + OffsetH ;
//    Serial.print(h);
//    Serial.print(" ");
//    Serial.println(t);
   
    lcd.clear();
  }
}
}
