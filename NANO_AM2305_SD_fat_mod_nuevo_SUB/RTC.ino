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
    mensajeEntrada = esp.readStringUntil(';');
    idMensaje = mensajeEntrada.substring(1).toInt();
    idMen = mensajeEntrada.substring(4).toInt();  
    
    switch(idMensaje)
    {

    
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


 if (minuto % intervalo == 0 && segundo >= 0 && segundo <= 10 &&!unicaVez && h > 0 && t > 0 ) 

  {
    mensajeSalida.reserve(40);
    mensajeSalida = "01," + String(anio) + "-" + String(mes) + "-" + String(dia) + " " + String(hora) + ":" + String(minuto) + ":" + "0" + "," + idInvernadero + "," + String(t, 2) + "," + String(h, 2) + ";";
    lcd.clear();
    unicaVez = true;
    esp.print(mensajeSalida);
  }
    
  if (minuto % intervalo != 0) 
  {
    unicaVez = false;
  }

  if(hora== 4 && minuto == 52 && segundo >20 && segundo <35)
  {
     asm("jmp 0x0000");
  }

   if(hora== 11 && minuto == 52 && segundo >20 && segundo <35)
  {
     asm("jmp 0x0000");
  }

   if(hora== 16 && minuto == 52 && segundo >20 && segundo <35)
  {
     asm("jmp 0x0000");
  }

  if(hora==23 && minuto == 52 && segundo >20 && segundo <35)
  {
     asm("jmp 0x0000");
  }

}
