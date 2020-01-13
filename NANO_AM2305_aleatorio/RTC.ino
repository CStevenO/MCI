void tiempoActual() 
{
  DateTime now = RTC.now(); // Obtiene la fecha y hora del RTC
  anio = now.year();
  mes = now.month();
  dia = now.day();
  hora = now.hour();
  minuto =  now.minute();
  segundo = now.second();
}

void enviarDatos() {
 
  if (esp.available()>0) 
  {
//    mensajeEntrada.reserve(5);
    mensajeEntrada = esp.readStringUntil(';');
    Serial.print(mensajeEntrada);
    idMensaje = mensajeEntrada.substring(1).toInt();
    idMen = mensajeEntrada.substring(4).toInt();
    lcd.setCursor(14, 1);
    lcd.print(idMensaje); 
    lcd.setCursor(16, 1);
    lcd.print(idMen); 
    
    switch(idMensaje)
    {
    case 0:
      //      mensajeS.reserve(40);
      //      mensajeSalida = "01," + String(anio) + "-" + String(mes) + "-" + String(dia) + " " + String(hora) + ":" + String(minuto) + ":" + String(segundo) + "," + idInvernadero + "," + String(t, 2) + "," + String(h, 2) + ";";

              switch(idMen)
              {
                case 0:

                  lcd.setCursor(9, 1);
                  lcd.print("N"); 
                  lcd.print(" ");
                  lcd.print(minuto); 

                break;

                case 1:
                
                  lcd.setCursor(9, 1);
                  lcd.print("S"); 
                  lcd.print(" ");
                  lcd.print(minuto); 
                  
                break;
              }
                         
    break;
    
    case 3:
    
      mensajeEntrada = mensajeEntrada.substring(3);
      for (i = 0; i < 6 ; i++)
      {
        indice = mensajeEntrada.indexOf(separador);
        datos[i] = (mensajeEntrada.substring(0, indice)).toInt();
        mensajeEntrada = mensajeEntrada.substring(indice + 1);
      }
      RTC.adjust(DateTime(datos[0], datos[1], datos[2], datos[3], datos[4], datos[5]));
    
    case 4:
        //enciende efectores

    break;
    }
      
   }
  if (minuto % intervalo == 0 && !unicaVez && h > 0 && h <= 100 && t > 0 && t < 50) 
  {
    mensajeSalida.reserve(40);
    mensajeSalida = "01," + String(anio) + "-" + String(mes) + "-" + String(dia) + " " + String(hora) + ":" + String(minuto) + ":" + String(segundo) + "," + idInvernadero + "," + String(t, 2) + "," + String(h, 2) + ";";
    //mensajeSalida =  idInvernadero + "," + String(h, 2) + "," + String(t, 2) + ";";
    lcd.clear();
    unicaVez = true;
    esp.print(mensajeSalida);
//    Serial.print(mensajeSalida);
  }

    
  if (minuto % intervalo != 0) 
  {
    unicaVez = false;
  }
}
