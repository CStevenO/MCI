void tiempoActual() {
  DateTime now = RTC.now();
  anio = now.year();
  mes = now.month();
  dia = now.day();
  hora = now.hour();
  minuto =  now.minute();
  segundo = now.second();
}

void enviarDatos() {

  if (minuto % intervalo == 0 && !unicaVez && h > 0 && h <= 100 && t > 0 && t < 50) {
    url.reserve(40);
    fecha = String(anio) + "-" + String(mes) + "-" + String(dia) + " " + String(hora) + ":" + String(minuto) + ":" + String(segundo);
    fecha = urlencode(fecha);
    url = "http://190.93.138.4/gprs/insertar.php?fecha=" + fecha + "&id_invernadero=" + idInvernadero + "&humedad=" + String(h, 2) + "&temperatura=" +  String(t, 2);
    //Serial.println(url);

    //    while (!msj) {
    //      if (esp.available()) {
    //        mensaje1 =mensaje1+esp.readString();
    //        //Serial.println(mensaje1);
    //        cnt++;
    //      }
    //      if(cnt==2){
    //        msj=true;
    //      }
    //    }


    //
    //delay(10000);
    //Serial.println("AT");
    //delay(1000);
    //runsl();
    Serial.println("AT+SAPBR=3,1,Contype,GPRS");
  delay(1000);
  //runsl();
  Serial.println("AT+SAPBR=3,1,APN," + apn);
  delay(1000);
  //runsl();
  Serial.println("AT+SAPBR =1,1");
  delay(1000);
  //runsl();
  Serial.println("AT+HTTPINIT");
  delay(1000);
  //runsl();
  Serial.println("AT+HTTPPARA=CID,1");
  delay(1000);
  Serial.println("AT+HTTPPARA=URL," + url);
  delay(1000);
  //runsl();
  Serial.println("AT+HTTPACTION=0");
  delay(5000);
  //runsl();
  Serial.println("AT+HTTPREAD");
  //runsl();
  delay(100);
  Serial.println("AT+HTTPTERM");
  //runsl();
  delay(2000);
  Serial.println("AT+SAPBR=0,1");
  delay(2000);
    //runsl();

    //        url = "http://190.93.138.4/gprs/insertar.php?fecha=" + fecha + "&id_invernadero=" + mensaje1.substring(0, 4) + "&humedad=" + mensaje1.substring(11, 16) + "&temperatura=" +  mensaje1.substring(5, 10);
    //        delay(60000);
    //
    //        gsm.println("AT");
    //        delay(1000);
    //        //runsl();
    //        gsm.println("AT+SAPBR=3,1,Contype,GPRS");
    //        delay(1000);
    //        //runsl();
    //        gsm.println("AT+SAPBR=3,1,APN," + apn);
    //        delay(1000);
    //        //runsl();
    //        gsm.println("AT+SAPBR =1,1");
    //        delay(1000);
    //        //runsl();
    //        gsm.println("AT+HTTPINIT");
    //        delay(1000);
    //        //runsl();
    //        gsm.println("AT+HTTPPARA=CID,1");
    //        delay(1000);
    //        //runsl();
    //        gsm.println("AT+HTTPPARA=URL," + url);
    //        delay(2000);
    //        //runsl();
    //        gsm.println("AT+HTTPACTION=0");
    //        delay(1000);
    //        //runsl();
    //        Serial.println("AT+HTTPREAD");
    //        //runsl();
    //        delay(100);
    //        gsm.println("AT+HTTPTERM");
    //        //runsl();
    //        delay(1000);
    //        gsm.println("AT+SAPBR=0,1");
    //        delay(1000);
    //        //runsl();
    //
    //        url = "http://190.93.138.4/gprs/insertar.php?fecha=" + fecha + "&id_invernadero=" + mensaje1.substring(17, 21) + "&humedad=" + mensaje1.substring(28, 33) + "&temperatura=" + mensaje1.substring(22, 27)  ;
    //        delay(60000);
    //
    //        gsm.println("AT");
    //        delay(1000);
    //        //runsl();
    //        gsm.println("AT+SAPBR=3,1,Contype,GPRS");
    //        delay(1000);
    //        //runsl();
    //        gsm.println("AT+SAPBR=3,1,APN," + apn);
    //        delay(1000);
    //        //runsl();
    //        gsm.println("AT+SAPBR =1,1");
    //        delay(1000);
    //        //runsl();
    //        gsm.println("AT+HTTPINIT");
    //        delay(1000);
    //        //runsl();
    //        gsm.println("AT+HTTPPARA=CID,1");
    //        delay(1000);
    //        //runsl();
    //        gsm.println("AT+HTTPPARA=URL," + url);
    //        delay(2000);
    //        //runsl();
    //        gsm.println("AT+HTTPACTION=0");
    //        delay(1000);
    //        //runsl();
    //        Serial.println("AT+HTTPREAD");
    //        //runsl();
    //        delay(100);
    //        gsm.println("AT+HTTPTERM");
    //        //runsl();
    //        delay(1000);
    //        gsm.println("AT+SAPBR=0,1");
    //        delay(1000);
    //        //runsl();

    //    mensaje1="";
    //    msj=false;
    //    cnt=0;

    lcd.clear();
    unicaVez = true;
  }

 if (minuto % intervalo == 0 && !unicaVez2 &&segundo==30 && h <= 100 && t <= 100)
  {
        Serial.println("AT+SAPBR=3,1,Contype,GPRS");
  delay(1000);
  //runsl();
  Serial.println("AT+SAPBR=3,1,APN," + apn);
  delay(1000);
  //runsl();
  Serial.println("AT+SAPBR =1,1");
  delay(1000);
  //runsl();
  Serial.println("AT+HTTPINIT");
  delay(1000);
  //runsl();
  Serial.println("AT+HTTPPARA=CID,1");
  delay(1000);
  Serial.println("AT+HTTPPARA=URL," + url);
  delay(1000);
  //runsl();
  Serial.println("AT+HTTPACTION=0");
  delay(5000);
  //runsl();
  Serial.println("AT+HTTPREAD");
  //runsl();
  delay(100);
  Serial.println("AT+HTTPTERM");
  //runsl();
  delay(2000);
  Serial.println("AT+SAPBR=0,1");
  delay(2000);
    unicaVez2 = true;
   
    
  }

  if (minuto % intervalo == 0 && !unicaVez3 &&segundo==50 && h <= 100 && t <= 100)
  {
        Serial.println("AT+SAPBR=3,1,Contype,GPRS");
  delay(1000);
  //runsl();
  Serial.println("AT+SAPBR=3,1,APN," + apn);
  delay(1000);
  //runsl();
  Serial.println("AT+SAPBR =1,1");
  delay(1000);
  //runsl();
  Serial.println("AT+HTTPINIT");
  delay(1000);
  //runsl();
  Serial.println("AT+HTTPPARA=CID,1");
  delay(1000);
  Serial.println("AT+HTTPPARA=URL," + url);
  delay(1000);
  //runsl();
  Serial.println("AT+HTTPACTION=0");
  delay(5000);
  //runsl();
  Serial.println("AT+HTTPREAD");
  //runsl();
  delay(100);
  Serial.println("AT+HTTPTERM");
  //runsl();
  delay(2000);
  Serial.println("AT+SAPBR=0,1");
  delay(2000);
    unicaVez3 = true;
   
  }
  
  if (minuto % intervalo != 0) {
    unicaVez = false;
    unicaVez2 = false;
    unicaVez3 = false;
  }
}



//void enviar(String url) {
//  gsm.println("AT+SAPBR=3,1,Contype,GPRS");
//  delay(1000);
//  runsl();
//  gsm.println("AT+SAPBR=3,1,APN," + apn);
//  delay(1000);
//  runsl();
//  gsm.println("AT+SAPBR =1,1");
//  delay(1000);
//  runsl();
//  gsm.println("AT+HTTPINIT");
//  delay(1000);
//  runsl();
//  gsm.println("AT+HTTPPARA=CID,1");
//  delay(1000);
//  gsm.println("AT+HTTPPARA=URL," + url);
//  delay(2000);
//  runsl();
//  gsm.println("AT+HTTPACTION=0");
//  delay(1000);
//  runsl();
//  Serial.println("AT+HTTPREAD");
//  runsl();
//  delay(100);
//  gsm.println("AT+HTTPTERM");
//  runsl();
//  delay(1000);
//  gsm.println("AT+SAPBR=0,1");
//  delay(1000);
//  runsl();
//}
//
//void runsl() {
//  lcd.clear();
//  if (Serial.available())
//  {
//    Serial.print(gsm.readString());
//    //lcd.clear();
//  }
//}
