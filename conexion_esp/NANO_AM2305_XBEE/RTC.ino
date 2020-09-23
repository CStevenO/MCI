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

String* separacion(String Msj)
{
  String Msj2="";
  int contador = 0;
  int fin = Msj.indexOf(",");
  while(fin != -1){
    contador++;
    Msj2 = Msj2 + Msj.substring(0,fin)+ ",";
    Msj = Msj.substring(fin+1);
    fin = Msj.indexOf(",");
  }
  Msj2 = Msj2 + Msj;
  String* mensa = new String[contador+1];
  fin = Msj2.indexOf(",");
  for(int i=0;i<contador;i++){
    mensa[i] = Msj2.substring(0,fin);
    Msj2 = Msj2.substring(fin+1);
    fin = Msj2.indexOf(",");
    if(contador==i+1){
      mensa[i+1]=Msj2;
    }
  }
  String* msgf=mensa;
  delete[] mensa;
  return msgf;
}

void enviarDatos() {
  if (esp.available()>0) 
  {
    mensajeEntrada = esp.readStringUntil(';');
    mensaEntrada=separacion(mensajeEntrada);
    Serial.println(mensajeEntrada);
    if(*(mensaEntrada)=="CONF_INVER"){
      Serial.println(mensajeEntrada);
      if(*(mensaEntrada+2)=="OFF"){
        mcp.digitalWrite(venOut, HIGH);
      }
      else{
        mcp.digitalWrite(venOut, LOW);
      }
      if(*(mensaEntrada+3)=="OFF"){
        mcp.digitalWrite(subOut, HIGH);
      }
      else{
        mcp.digitalWrite(subOut, LOW);
      }
      if(*(mensaEntrada+4)=="OFF"){
        mcp.digitalWrite(ducOut, HIGH);
      }
      else{
        mcp.digitalWrite(ducOut, LOW);
      }
      if(*(mensaEntrada+5)=="OFF"){
        mcp.digitalWrite(disOut, HIGH);
      }
      else{
        mcp.digitalWrite(disOut, LOW);
      }
    }
    else if(*(mensaEntrada)=="HORA"){
      RTC.adjust(DateTime(String(*(mensaEntrada+1)).toInt(),String(*(mensaEntrada+2)).toInt(),String(*(mensaEntrada+3)).toInt(),String(*(mensaEntrada+4)).toInt(),String(*(mensaEntrada+5)).toInt(),String(*(mensaEntrada+6)).toInt()));
    }
   }
   if (minuto % intervalo == 0 && segundo==0 && unica==false) {
    mensajeSalida = "DATO_INV," + String(anio) + "-" + String(mes) + "-" + String(dia) + " " + String(hora) + ":" + String(minuto) + ":" + "0" + "," + idInvernadero + "," + String(t, 2) + "," + String(h, 2) + ";";
    Serial.println(mensajeSalida);
    lcd.clear();
    unica=true;
    esp.print(mensajeSalida);
    lcd.setCursor(9, 1);
    lcd.print("E"); 
    }
    else if (unica && minuto % intervalo != 0 && segundo!=0){ 
      unica=false;
    }
    if(hora== 4 && minuto == 52 && segundo == 20){
      asm("jmp 0x0000");
    }
    if(hora== 11 && minuto == 52 && segundo == 20){
      asm("jmp 0x0000");
    }
    if(hora== 16 && minuto == 52 && segundo == 20){
      asm("jmp 0x0000");
    }
    if(hora==23 && minuto == 52 && segundo == 20){
      asm("jmp 0x0000");
    }
}
