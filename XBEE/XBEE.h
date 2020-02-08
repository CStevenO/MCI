#ifndef XBEE_H
#define XBEE_H

#include<Arduino.h>
#include "Stream.h"

#define START_BYTE 0x7e
#define ESCAPE_S 0x7d
#define XON 0x11
#define XOFF 0x13

#define API_ID_INDEX 3
#define ENTREGA 0X90
#define RESPUESTA 0X8B
#define ENVIO 0X10

#define BROADCAST_ADDRESS 0xffff
#define ZB_BROADCAST_ADDRESS 0xfffe

class Xbee
{
  private:
    bool available();
    char read();
    void flush();
    void write(char val);
    char checksumTotal;
    char _checksumRecibido;
    char _checksumEnviado;
    char Direccion[8];
    char DireccionEmisor[8];
    char* Msg_Recibido;
    Stream* _serial;
    char _pos;
    char b;
    uint16_t Length;
    char FrameType;
    int Length_Msg;
    char EstadoRespuesta;
    uint16_t longitud;
  public:
    Xbee();
    ~Xbee();
    int GetLengthMsg();
    bool ReadPacket();
    void begin(Stream &serial);
    bool send(char *Mensaje,char *EAddress);
    void setSerial(Stream &serial);
    char* Mensaje();
};





#endif
