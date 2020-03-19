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

  if((millis()-previo) <= 15000)
  {
    sensorValue = analogRead(sensorPin);   // realizar la lectura
    psi=14.69+((0.01574889)*sensorValue)-(0.644444444)+psi;
    kpa=100+((0.10861301)*sensorValue)-4.44444444444+kpa;
    cont1++;
  }
  else
  {
    previo=millis();
    psi= psi / cont1;
    kpa= kpa / cont1;
    cont1=0;
    mensajeSalidaSuelo.reserve(30);
    mensajeSalidaSuelo = String(anio) + "-" + String(mes) + "-" + String(dia) + " " + String(hora) + ":" + String(minuto) + ":" + String(segundo) + ',' + String(psi) + ',' + String(kpa) + ';';
    //Serial.println(mensajeSalidaSuelo);
    myFile = SD.open("DATOS.txt", FILE_WRITE);
    myFile.println(mensajeSalidaSuelo);
    myFile.close();

  }
}
