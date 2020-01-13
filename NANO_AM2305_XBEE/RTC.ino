void tiempoActual() 
{
  DateTime now = RTC.now(); // Obtiene la fecha y hora del RTC
  anio = now.year();
  mes = now.month();
  dia = now.day();
  hora = now.hour();
  minuto =  now.minute();
  segundo = now.second();
  fecha = now.unixtime();
}

void enviarDatos() {
 
  if (esp.available()>0) 
  {
    mensajeEntrada = esp.readStringUntil(';');
    idMensaje = mensajeEntrada.substring(1).toInt();
     
    switch(idMensaje)
    {
    case 0:
              
   
                         
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


 if (minuto % intervalo == 0 && !unicaVez && segundo==0 && h <= 100 && t <= 100 ) 

  {
    mensajeSalida.reserve(40);
    mensajeSalida = "01," + String(anio) + "-" + String(mes) + "-" + String(dia) + " " + String(hora) + ":" + String(minuto) + ":" + "0" + "," + idInvernadero + "," + String(t, 2) + "," + String(h, 2) + ";";
//    mensajeSalida = "01," + String(fecha) + "," + idInvernadero + "," + String(t, 2) + "," + String(h, 2) + ";";

    lcd.clear();
    unicaVez = true;
    esp.print(mensajeSalida);
    lcd.setCursor(9, 1);
    lcd.print("E"); 
  }

  if (minuto % intervalo == 0 && !unicaVez1 && segundo==10 && h <= 100 && t <= 100 )
  {
    unicaVez1 = true;
    esp.print(mensajeSalida);
    lcd.setCursor(9, 1);
    lcd.print("E"); 
  }

   if (minuto % intervalo == 0 && !unicaVez2 &&segundo==30 && h <= 100 && t <= 100)
  {
    unicaVez2 = true;
    esp.print(mensajeSalida);
    lcd.setCursor(9, 1);
    lcd.print("E"); 
  }

  if (minuto % intervalo == 0 && !unicaVez3 &&segundo==50 && h <= 100 && t <= 100)
  {
    unicaVez3 = true;
    esp.print(mensajeSalida);
    lcd.setCursor(9, 1);
    lcd.print("E"); 
  }
    
  if (minuto % intervalo != 0) 
  {
    unicaVez = false;
    unicaVez1 = false;
    unicaVez2 = false;
    unicaVez3 = false;
  }

  if(hora== 4 && minuto == 52 && segundo == 20)
  {
     asm("jmp 0x0000");
  }

   if(hora== 11 && minuto == 52 && segundo == 20)
  {
     asm("jmp 0x0000");
  }

   if(hora== 16 && minuto == 52 && segundo == 20)
  {
     asm("jmp 0x0000");
  }

  if(hora==23 && minuto == 52 && segundo == 20)
  {
     asm("jmp 0x0000");
  }

}
