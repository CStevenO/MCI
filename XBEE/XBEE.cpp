#incluide "XBEE.h"

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

    if(_pos>0 && b=ESCAPE)
    {
      while(!available())
      {}
      b=read();
      b=0x20 ^ b;
    }
    if(pos>=API_ID_INDEX)
    {
      _checksumTotal+=b;
    }
    switch(_pos)
    {
      case 0:
        if(b==START_BYTE)
        {
          _pos++;
        }
      break;
      case 1:
        Length=b;
        _pos++;
      break;
      case 2:
        Length=Length<<8+b;
        _pos++;
      break;
      case 3:
        FrameType=b;
        _pos++;
      break;
      default:
        if(FrameType==RESPUESTA)
        {
            switch(_pos)
            {
              case 4:
                _pos++;
              break;
              case 5:
                _pos++;
              break;
              case 6:
                _pos++;
              break;
              case 7:
                _pos++;
              break;
              case 8:
                EstadoRespuesta=b;
                _pos++;
              break;
              case 9:
                _pos++;
              break;
              case 10:
                _checksumRecibido=b;
                _pos++;
              break;
            }
        }
        else if (FrameType==ENTREGA)
        {
          if(_pos>=4 && _pos<=11)
          {
            DireccionEmisor[_pos-4]=b;
            _pos++;
          }
          else
          {
            if(_pos>=12 && _pos<=14)
            {
              _pos++;
            }
            else if(_pos>=15 && _pos<=Length)
            {
              Msg_Recibido[_pos-15]=b;
              _pos++;
            }
            else
            {
              _checksumRecibido=b
            }
          }
        }
    }
  }
  checksumTotal=0XFF-(checksumTotal)&0XFF;
  if(checksunTotal==checksumRecibido)
  {
    return true;
  }
  else
  {
    return false;
  }
}
void XBEE::begin(Stream &serial)
{
  _serial=&serial;
}
void XBEE::setSerial(Stream &serial)
{
  _serial=&serial;
}
