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
    mensajeSalidaSuelo = String(anio) + "-" + String(mes) + "-" + String(dia) + " " + String(hora) + ":" + String(minuto) + ":" + String(segundo) + ',' + String(voltajeProm) + ';';
    //Serial.println(mensajeSalidaSuelo);
    myFile = SD.open("DATOS.txt", FILE_WRITE);
    if(myFile)
    {
    myFile.println(mensajeSalidaSuelo);
    myFile.close();
    lcd.setCursor(10, 1);
    imprimir("G");
    //Serial.println("G");
    }
    else
    {
      lcd.setCursor(10, 1);
      imprimir("E");
      asm("jmp 0x0000");
      
    }
    delay(1000);
    lcd.clear();
  }
}
