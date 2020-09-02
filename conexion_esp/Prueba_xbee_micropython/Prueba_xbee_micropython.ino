#include <AltSoftSerial.h>
AltSoftSerial esp;
void setup() {
  
  //COMUNICACION UART
  esp.begin(9600);
  Serial.begin(9600);
}
String mensajeEntrada;
int idMensaje;
void loop() {
  // put your main code here, to run repeatedly:
  if (esp.available()>0) 
  {
    Serial.print(".");
    mensajeEntrada = esp.readStringUntil(';');
    Serial.println(mensajeEntrada);
    mensajeEntrada = mensajeEntrada.substring(3);
    esp.println(mensajeEntrada+ ";" );
  }
  delay(500);
}

  
