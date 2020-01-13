void obtenerVariables() 
{
  if (millis() - milisAnterior >= 5000) 
  {
    milisAnterior = millis();
    t = dht.readTemperature() + OffsetT;
    h = dht.readHumidity() + OffsetH ;

 //   t=1;
   // h=2;
   
    lcd.clear();
  }
}
