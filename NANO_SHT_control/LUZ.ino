void energia() 
{
  luzActual = digitalRead(luz);
  if (luzActual == false && luzAnterior == true) 
  {
    lcd.noBacklight();
    mensajeSalida.reserve(40);
    mensajeSalida = "02," + String(anio) + "-" + String(mes) + "-" + String(dia) + " " + String(hora) + ":" + String(minuto) + ":" + String(segundo) + "," + String(idInvernadero) + ",LN;";
    esp.print(mensajeSalida);
    mensajeSalida = "";
  }
  if (luzActual == true && luzAnterior == false) 
  {
    lcd.backlight();
    mensajeSalida.reserve(40);
    mensajeSalida = "02," + String(anio) + "-" + String(mes) + "-" + String(dia) + " " + String(hora) + ":" + String(minuto) + ":" + String(segundo) + "," + String(idInvernadero) + ",LS;";
    esp.print(mensajeSalida);
    mensajeSalida = "";
  }
  luzAnterior = luzActual;
}

void encendido()
{
  sub = mcp.digitalRead(subIn);
  //Serial.println(sub);
  //Serial.println(subE);

  ven = mcp.digitalRead(venIn);
  duc = mcp.digitalRead(ducIn);
  
}
