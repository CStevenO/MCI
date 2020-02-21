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
    uint8_t read();
    void flush();
    void write(char val);
    uint16_t checksumTotal;
    uint8_t _checksumRecibido;
    uint8_t _checksumEnviado;
    uint8_t Direccion[8];
    uint8_t DireccionEmisor[8];   //read
    uint8_t* Msg_Recibido=NULL;
    Stream* _serial;
    int _pos;
    uint8_t b;           //read
    uint16_t Length;
    uint8_t FrameType;
    int Length_Msg;
    uint8_t EstadoRespuesta;
    uint16_t longitud;
    bool Salida;
    size_t lista;
    bool Primera_Vez;
  public:
    Xbee();
    ~Xbee();
    bool available();
    int GetLengthMsg();
    bool ReadPacket();
    void begin(Stream &serial);
    bool send(uint8_t *Mensaje,uint8_t *EAddress, uint8_t Longitud);
    void setSerial(Stream &serial);
    uint8_t* Mensaje();
    void Borrar();
    uint8_t Estado();
    uint16_t ByEspecial(uint8_t Byt);
    /*
    void Comprobacion();
    void Lectura();
    void Sera();
    */
};





#endif
