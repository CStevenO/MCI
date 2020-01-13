void obtenerVariables() {
  if (millis() - milisAnterior >= 5000) 
  {
    milisAnterior = millis();
    sensorDS18B20.requestTemperatures();
   t = sensorDS18B20.getTempCByIndex(1);
   Tw = sensorDS18B20.getTempCByIndex(0);
   h = calculaHumedad(t, Tw);

//    Serial.print(h);
//    Serial.print(" ");
//    Serial.println(t);
   
    lcd.clear();

//      if(h>=80)
//   {
//     i=1;  
//    }
//
//      if(t>=30)
//    {
//     i=2;
//    }
//
//      if(h<80)
//    {
//     i=0;
//   }
//
//     if(i==1)
//    {
//       mcp.digitalWrite(7, HIGH);
//       mcp.digitalWrite(6, HIGH);
//       mcp.digitalWrite(5, HIGH);
//       mcp.digitalWrite(4, LOW); 
//    }
//
//     if(i==2)
//    {
//       mcp.digitalWrite(7, HIGH);
//       mcp.digitalWrite(6, HIGH);
//       mcp.digitalWrite(5, LOW);
//       mcp.digitalWrite(4, HIGH);
//    }
//   
//     if(i==0)
//    {
//       mcp.digitalWrite(7, HIGH);
//       mcp.digitalWrite(6, HIGH);
//       mcp.digitalWrite(5, HIGH);
//       mcp.digitalWrite(4, HIGH);
//    }
  }
}
