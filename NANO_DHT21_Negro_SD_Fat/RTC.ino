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
    case 0:
              
              switch(idMen)
              {
                case 0:

                  lcd.setCursor(9, 1);
                  lcd.print("N"); 
                  lcd.print(" ");
                  lcd.print(minuto);           

                  if(minuto!=minutoant && minuto % intervalo == 0)  //guarda un archivo no enviado solo del minuto del intervalo
                  {
                    minutoant=minuto;
                    myFile = SD.open("DATOS.txt", FILE_WRITE);//abrimos  el archivo
                     myFile.print(mensajeSalida);
                     lcd.setCursor(14, 1);
                     lcd.print("G"); 
                     myFile.close();
               
                  }
                  
                break;

                case 1:
                
                  lcd.setCursor(9, 1);
                  lcd.print("S"); 
                  lcd.print(" ");
                  lcd.print(minuto); 
                  myFile = SD.open("DATOS.txt");
                  int peso = myFile.size();//guarda el tamaño del fichero
                  
                  if(myFile)
                  {
                    if(UltimaPosicion>=peso)   
                    
                    {
                      UltimaPosicion=0;
                      SD.remove("DATOS.txt");
                      lcd.setCursor(14, 1);
                      lcd.print("B");
                    }
                    myFile.seek(UltimaPosicion);
                    
                    while(myFile.available())
                   {
                    mensajeGuardado = myFile.read();
                    UltimaPosicion = myFile.position();
                    esp.print(mensajeGuardado);
                    lcd.setCursor(14, 1);
                    lcd.print("E"); 
                    if(mensajeGuardado==59)//ASCII de &
                     {            
                      break;
                     }
                   }
                  
                   myFile.close();
                  }
             
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
  if (minuto % intervalo == 0 && segundo == 0 && !unicaVez && h > 0 && t > 0 ) 
  {
    mensajeSalida.reserve(40);
    mensajeSalida = "01," + String(anio) + "-" + String(mes) + "-" + String(dia) + " " + String(hora) + ":" + String(minuto) + ":" + String(segundo) + "," + idInvernadero + "," + String(t, 2) + "," + String(h, 2) + ";";
    //mensajeSalida =  idInvernadero + "," + String(h, 2) + "," + String(t, 2) + ";";
    lcd.clear();
    unicaVez = true;
    esp.print(mensajeSalida);
  }

    
  if (minuto % intervalo != 0) 
  {
    unicaVez = false;
  }
}
