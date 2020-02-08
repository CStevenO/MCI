#incluide "XBEE.h"
#incluce "stdlib.h"
#incluide "HardwareSerial.h"

XBEE::Xbee()
{
  _pos=0;
}
XBEE::~Xbee()
{
}
bool XBEE::available()
{
  return _serial->available();
}
uint8_t XBEE::read()
{
  return _serial->read();
}
void XBEE::flush()
{
  _serial->flush();
}
void XBEE::write(uint8_t val)
{
  _serial->write(val);
}
bool XBEE::ReadPacket()
{
  while(available())
  {
    b=read();

    if(_pos>0 && b=ESCAPE)            //revisa sí el byte que acaba de ingresar es un byte de escape 0x7d
    {
      while(!available()){}
      b=read();
      b=0x20 ^ b;
    }
    if(pos>=API_ID_INDEX)           //suma todos los bytes que estan ingresando despues del byte de longitud hasta el byte checksum sin tener en cuenta este
    {
      _checksumTotal+=b;
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
        Length=Length<<8+b;
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
            else if(_pos>=15 && _pos<=Length) // N BYTES DE MENSAJE
            {
              if(_pos>=15)
              {
                Msg_Recibido=new uint8_t[Length-15];
                Length_Msg = Length-15;
              }
              Msg_Recibido[_pos-15]=b;
              _pos++;
            }
            else
            {
              _checksumRecibido=b           //CHECKSUM
            }
          }
        }
    }
    while(!available()){}
  }
  checksumTotal=0XFF-(checksumTotal)&0XFF;      //CONVIERTE LA SUMA TOTAL EN EL CHECKSUM
  if(checksunTotal==checksumRecibido)           //¿SE RECIBIO BIEN EL MENSAJE?
  {
    return true;      //SI
  }
  else
  {
    return false;     //NO
  }
}
bool XBEE::send(uint8_t *Mensaje,uint8_t *EAddress)
{
    write(0X7E);
    write(longitud&0XFF00>>8);    //0XE es constante y toca sumarle la longitud del mensaje
    write(longitud&0XFF);
    write(0X10);
    write(0X01);
    checksumEnviado=0X10+0X01;
    for(int i=0;i<8;i++)
    {
      write(EAddress[i]);
      checksumEnviado=EAddress[i]+checksumEnviado;
    }
    write(0XFF);
    write(0XFE);
    checksumEnviado=0XFF+0XFE+checksumEnviado;
    write(0X00);
    write(0X00);
    for(int j=0;j<(longitud-0X0E);j++)
    {
      write(*Mensaje[j]);
      checksumEnviado=*Mensaje[j]+checksumEnviado;
    }
    checksumEnviado=0XFF-(0XFF&checksumEnviado);
    write(checksumEnviado);
    delay(100);
    ReadPacket()
}
void XBEE::begin(Stream &serial)
{
  _serial=&serial;
}
void XBEE::setSerial(Stream &serial)
{
  _serial=&serial;
}
char* XBEE::Mensaje()
{
    return Msg_Recibido;
}
int XBEE::GetLengthMsg()
{
  return Length_Msg;
}
