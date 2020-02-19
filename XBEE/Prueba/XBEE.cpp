#include "XBEE.h"
#include "stdlib.h"
#include "HardwareSerial.h"
#include<Arduino.h>

Xbee::Xbee()
{
_pos=0;
Salida = false;
Primera_Vez=true;
}
Xbee::~Xbee()
{
}
void Xbee::begin(Stream &serial)
{
_serial=&serial;
}
bool Xbee::available()
{
  return _serial->available();
}
uint8_t Xbee::read()
{
  return _serial->read();
}
void Xbee::write(char val)
{
  _serial->write(val);
}
uint8_t* Xbee::Mensaje()
{
    return Msg_Recibido;
}
int Xbee::GetLengthMsg()
{
  return Length_Msg;
}
void Xbee::Borrar()
{
  checksumTotal = 0x00;
  if(!Primera_Vez)
  {
  delete Msg_Recibido;
  }
  else
  {
    Primera_Vez=false;
  }
}
bool Xbee::ReadPacket()
{
  Borrar();
  Lectura();
  if(b!=START_BYTE)
  {
    return false;
  }
  Lectura();
  Comprobacion();
  Length=b;
  Lectura();
  Comprobacion();
  Length=(Length<<8)+b;
  write(Length);
  Lectura();
  Comprobacion();
  checksumTotal+=b;
  FrameType=b;
  if(FrameType==ENTREGA)
  {
    for(int i=0;i<8;i++)
    {
      Lectura();
      Comprobacion();
      checksumTotal+=b;
      DireccionEmisor[i]=b;
    }
    Lectura();
    Comprobacion();
    checksumTotal+=b;
    Lectura();
    Comprobacion();
    checksumTotal+=b;
    Lectura();
    Comprobacion();
    checksumTotal+=b;
    Length_Msg=Length-12;
    lista=Length_Msg;
    write(Length_Msg);
    Msg_Recibido=new uint8_t[lista];
    for(int i=0;i<Length_Msg;i++)
    {
      Lectura();
      Comprobacion();
      checksumTotal+=b;
      Msg_Recibido[i]=b;
    }
    Lectura();
    Comprobacion();
    _checksumRecibido=b;
  }
  checksumTotal=0XFF-(checksumTotal)&0XFF;      //CONVIERTE LA SUMA TOTAL EN EL CHECKSUM
  if(checksumTotal == _checksumRecibido)           //¿SE RECIBIO BIEN EL MENSAJE?
  {
    return true;      //SI
  }
  else
  {
    return false;     //NO
  }
}
void Xbee::Comprobacion()
{
  if(b==ESCAPE_S)
  {
    Lectura();
    b=0x20^b;
  }
}
void Xbee::Lectura()
{
  while(!available()){}
  b=read();
}
void Xbee::Sera()
{
  Borrar();
  Lectura();
  Comprobacion();
  Length=b;
  Lectura();
  Comprobacion();
  Length=(Length<<8)+b;
  Length_Msg=Length-12;
  lista=Length_Msg;
  write(Length_Msg);
  Msg_Recibido=new uint8_t[lista];
  write(0x01);
  for(int i=0;i<Length_Msg;i++)
  {
    Lectura();
    Comprobacion();
    checksumTotal+=b;
    Msg_Recibido[i]=b;
  }
}
