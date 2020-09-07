#include <AltSoftSerial.h>
AltSoftSerial esp;
#include"stdlib.h"
void setup() {
  
  //COMUNICACION UART
  esp.begin(9600);
  Serial.begin(9600);
  if(esp.available()>0){
    while(esp.available()!= 0){
      esp.read();
    }
  }
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
  return mensa;
}
String mensajeEntrada;
String* mensaEntrada;
void loop() {
  // put your main code here, to run repeatedly:
  if (esp.available()>0) 
  {
    mensajeEntrada = esp.readStringUntil(';');
    Serial.println(mensajeEntrada);
    mensaEntrada=separacion(mensajeEntrada);
    if(*(mensaEntrada)=="CONF_INVER")
    {
      Serial.println(*(mensaEntrada+1));
    }
    else if(*(mensaEntrada)=="HORA"){
       Serial.println((*(mensaEntrada+1)) + "/" + *(mensaEntrada+2) + "/" + *(mensaEntrada+3) + " " + *(mensaEntrada+4) + ":" + *(mensaEntrada+5) + ":" + *(mensaEntrada+6));  
    }
  }
  delay(500);
}

  
