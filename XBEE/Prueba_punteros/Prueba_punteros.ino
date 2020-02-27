#include "XBEE.h"

#include"stdlib.h"

void setup() {
  
  Serial.begin(9600);
  
}


String Msg;
int Longitud;

void loop() {

  Xbee Prueba;
  Prueba.begin(Serial);
  while(1){
    /*
     //ESTADO
    while(!Prueba.available()){}
    Prueba.ReadPacket();
    Serial.write(Prueba.Estado());  
    */
    //Lectura
  uint8_t* entrada;
  uint8_t* Direccion= new uint8_t [8];
  for(int i=0;i<8;i++)
  {
    Direccion[i]=0x00;
  }
  while(!Prueba.available()){}
  Prueba.ReadPacket();
  //Prueba.Sera();
  Longitud=Prueba.GetLengthMsg();
  entrada= new uint8_t[Longitud];
  entrada=Prueba.Mensaje();
  if(Prueba.send(entrada,Direccion,Longitud))
  {
    Serial.print("si");
  }
  else
  {
    Serial.print("no");
  }
  delete[] entrada;
  //Serial.write(Longitud);
  
  }
 /*
  uint8_t* p1;
  int en;
  uint16_t b;
  while(1)
  {
  while(!Serial.available()){}
  b=Serial.read();
  en=b-2;
  p1=new uint8_t[en];
  for(int i=0;i<en;i++)
  {
    while(!Serial.available()){}
    p1[i]=Serial.read();
    Serial.write(p1[i]);
  }
  delete[] p1;
  }*/
}
