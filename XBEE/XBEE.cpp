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
void Xbee::setSerial(Stream &serial)
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
void Xbee::flush()
{
  _serial->flush();
}
void Xbee::write(char val)
{
  _serial->write(val);
}
bool Xbee::ReadPacket()
{
  Borrar();
  while(!available()){}
  while(!Salida)
  {
    b=read();
    if(_pos > 0 && b == ESCAPE_S )            //revisa sí el byte que acaba de ingresar es un byte de escape 0x7d
    {
      while(!available()){}
      b=read();
      b=0x20 ^ b;
      //write(b);
    }
    if(_pos>=API_ID_INDEX)           //suma todos los bytes que estan ingresando despues del byte de longitud hasta el byte checksum sin tener en cuenta este
    {
      checksumTotal+=b;
    }
    switch(_pos)
    {
      case 0:                     //BYTE DE INICIO 0X7E
        if(b==START_BYTE)
        {
          _pos++;
        }
      break;
      case 1:                     //PRIMER BYTE DE LONGITUD
        Length=b;
        _pos++;
      break;
      case 2:                     //SEGUNDO BYTE DE LONGITUD
        Length=(Length<<8)+b;
        _pos++;
      break;
      case 3:                     //TIPO DE REQUERIMIENTO
        FrameType=b;
        _pos++;
      break;
      default:
        if(FrameType==RESPUESTA)        //TRAMA PARA RECIBIR UNA RESPUESTA
        {
            switch(_pos)
            {
              case 4:               //FRAMEID
                _pos++;
              break;
              case 5:             //PRIMER 16-BIT DEST.ADDRESS
                _pos++;
              break;
              case 6:             //SEGUNDO 16-BIT DEST.ADDRESS
                _pos++;
              break;
              case 7:             //TRANSMIT RETRY COUNT
                _pos++;
              break;
              case 8:             //ESTADO DE ENTREGA
                EstadoRespuesta=b;
                _pos++;
              break;
              case 9:           //DISCOVERY STATUS
                _pos++;
              break;
              case 10:          //CHECKSUM
                _checksumRecibido=b;
                _pos++;
                Salida=true;
              break;
            }
        }
        else if (FrameType==ENTREGA)    //TRAMA PARA RECIBIR MENSAJES
        {
          if(_pos>=4 && _pos<=11)       // 8 BYTES DE MAC-ADDRESS DEL EMISOR
          {
            DireccionEmisor[_pos-4]=b;
            _pos++;
          }
          else
          {
            if(_pos>=12 && _pos<=14)   //2 BYTES DE 16-BIT SOURCE ADDRESS 1 BYTE DE RECEIVE OPTIONS
            {
              _pos++;
            }
            else if(_pos>=15 && 0x00+_pos<=Length+0x02) // N BYTES DE MENSAJE
            {
              if(_pos==15)
              {
                Length_Msg=Length-12;
                lista = Length_Msg;
                /*
                if(Primera_Vez)
                {
                  Primera_Vez=false;
                  write(0x00);
                }
                else{
                  delete [] Msg_Recibido;
                  write(0x01);
                }
                */
                Msg_Recibido=new uint8_t[lista];
              }
              Msg_Recibido[_pos-15]=b;
              _pos++;
            }
            else
            {
              _checksumRecibido=b;           //CHECKSUM
              _pos++;
              Salida=true;
            }
          }
        }
    }
    while(!available() && !Salida){}
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
bool Xbee::send(uint8_t *Mensaje,uint8_t *EAddress, uint8_t Longitud)
{
    //CREAR TRAMA AQUI
    longitud=ByEspecial(Longitud+0XE);
    write(0X7E);
    write((longitud&0XFF00)>>8);    //0XE es constante y toca sumarle la longitud del mensaje
    write(longitud&0XFF);
    write(0X10);
    write(0X01);
    _checksumEnviado=0X10+0X01;
    for(int i=0;i<8;i++)
    {
      if(((ByEspecial(EAddress[i]))&0XFF00)>>8==0x00)
      {
        write(EAddress[i]);
      }
      else
      {
        write(0x7D);
        write((ByEspecial(EAddress[i]))&0XFF)
      }
      _checksumEnviado=EAddress[i]+_checksumEnviado;
    }
    write(0XFF);
    write(0XFE);
    _checksumEnviado=_checksumEnviado + 0XFF + 0XFE;
    write(0X00);
    write(0X00);
    for(int j=0;j<(Longitud);j++)
    {
      if(((ByEspecial(Mensaje[j]))&0XFF00)>>8==0x00)
      {
        write(Mensaje[j]);
      }
      else
      {
        write(0x7D);
        write((ByEspecial(Mensaje[j]))&0XFF)
      }
      _checksumEnviado=_checksumEnviado+(Mensaje[j]);
    }
    _checksumEnviado=0XFF-(0XFF&_checksumEnviado);
    write(_checksumEnviado);
    delay(100);
    ReadPacket();
    if(Estado==0x00)
    {
      return true;
    }
    else
    {
      return false;
    }
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
  Salida=false;
  checksumTotal = 0x00;
  _pos = 0;
}
uint8_t Xbee::Estado()
{
  return EstadoRespuesta;
}
uint8_t Xbee::ByEspecial(uint8_t Byt)
{
  if(Byt==START_BYTE || Byt==ESCAPE_S || Byt==XON || Byt==XOFF)
  {
    Byt=20^Byt;
    return (0x7D00+Byt);
  }
  else
  {
    return Byt;
  }
}
