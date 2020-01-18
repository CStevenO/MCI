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

                  if(minuto % intervalo == 0)  //guarda un archivo no enviado solo del minuto del intervalo
                  {
                    
                       
                    myFile = SD.open("DATOS.txt", FILE_WRITE);//abrimos  el archivo
                   // Serial.println("Creo archivo");
//                    if (myFile) 
//                   {
                    
                     myFile.println(mensajeSalida);
                                       //  Serial.println("Guardo archivo");

                     lcd.setCursor(14, 1);
                     lcd.print("G"); 
                     myFile.close();
               
//                    }
               
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
                      cont++;
                      if(cont==2)
                      {               
                      SD.remove("DATOS.txt");
                      lcd.setCursor(14, 1);
                      lcd.print("B"); 
                      asm("jmp 0x0000");
                      cont=0;
                      }                                    
                    }
                    myFile.seek(UltimaPosicion);
                    
                    while(myFile.available()&& minuto % intervalo != 0)
                   {

                    mensajeGuardado = myFile.read();
                    UltimaPosicion = myFile.position();
                    esp.print(mensajeGuardado);
                    lcd.setCursor(14, 1);
                    lcd.print("E"); 
                    if(mensajeGuardado==59)//ASCII de ;
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
  if (minuto % intervalo == 0 && !unicaVez && segundo==0 && h >= 0 && t >= 0 ) 

  {
    mensajeSalida.reserve(40);
    mensajeSalida = "01," + String(anio) + "-" + String(mes) + "-" + String(dia) + " " + String(hora) + ":" + String(minuto) + ":" + "0" + "," + idInvernadero + "," + String(t, 2) + "," + String(h, 2) + ";";
    lcd.clear();
    unicaVez = true;
    esp.print(mensajeSalida);
  }

  if (minuto % intervalo == 0 && !unicaVez1 && segundo==10 && h < 100 && t < 100 )
  {
    unicaVez1 = true;
    esp.print(mensajeSalida);
  }

   if (minuto % intervalo == 0 && !unicaVez2 &&segundo==30 && h < 100 && t < 100)
  {
    unicaVez2 = true;
    esp.print(mensajeSalida);
  }

  if (minuto % intervalo == 0 && !unicaVez3 &&segundo==50 && h < 100 && t < 100)
  {
    unicaVez3 = true;
    esp.print(mensajeSalida);
    mensajeSalida = "";
  }

  //humedad suelo
  //unsigned long tiempoSuelo=millis();
  if((millis()-previo) <= 60000)
  {
  lectura = analogRead(pinSonda);
  lectura = map(lectura, 0, 1023, 0, 500);
  voltaje = lectura/escala;
  voltajeSum= voltajeSum + voltaje;
  cont1++;
  }
  else
  {
    previo=millis();
    voltajeProm= voltajeSum / cont1;
    cont1=0;
    voltajeSum=0;
    mensajeSalidaSuelo.reserve(30);
    mensajeSalidaSuelo = "07," + String(anio) + "-" + String(mes) + "-" + String(dia) + " " + String(hora) + ":" + String(minuto) + ":" + String(segundo) + ',' + String(voltajeProm) + ';';
    esp.print(mensajeSalidaSuelo);
    //mensajeSalidaSuelo= "";
  }
  
    
  if (minuto % intervalo != 0) 
  {
    unicaVez = false;
    unicaVez1 = false;
    unicaVez2 = false;
    unicaVez3 = false;
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
