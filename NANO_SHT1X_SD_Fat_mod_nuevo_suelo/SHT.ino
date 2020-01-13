void obtenerVariables() {
  if (millis() - milisAnterior >= 5000) 
  {
    
  t = dht.readTemperature() + OffsetT;
    h = dht.readHumidity() + OffsetH ;
    milisAnterior = millis();
  //  h=1;
    //t=1;
//    Serial.print(t);
//    Serial.print(" ");
//    Serial.println(t);
    lcd.clear();
  }
}
