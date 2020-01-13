void conectarWifi() {
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) 
  {
  
    conect=false;
    
    if (Serial.available()) {
    mensaje = Serial.readStringUntil(';');

    if(conect==false)
    {
    myFile = SD.open("Datos.txt");
                  int peso = myFile.size();//guarda el tamaño del fichero
                  
                  if(myFile)
                  {
                    if(UltimaPosicion>=peso)   
                    
                    {
                      UltimaPosicion=0;
                      SD.remove("Datos.txt");
                    }
                    myFile.seek(UltimaPosicion);
                    
                    while(myFile.available())
                   {

                    mensajeGuardado = myFile.read();
                    UltimaPosicion = myFile.position();
                    
                    client.publish("MCI_ST_IN", mensaje.c_str());
                    if(mensajeGuardado==59)//ASCII de &
                     {            
                      break;
                     }
                   }
                  
                   myFile.close();
                  }
    }

    }
    delay(0);
  }
  conect=true;
}
