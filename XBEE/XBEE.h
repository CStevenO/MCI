#ifndef XBEE_H
#define XBEE_H

#define START_BYTE 0x7e
#define ESCAPE 0x7d
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
    uint8_t read();
    void flush();
    void write(uint8_t)
    uint8_t checksumTotal;
    uint8_t _checksumRecibido;
    uint8_t _checksumEnviado;
    uint8_t Direccion[8];
    uint8_t DireccionEmisor[8];
    uint8_t Msg_Recibido[100];
    Stream* _serial;
    uint8_t _pos;
    uint8_t b;
    uint16_t Length;
    uint8_t FrameType;
  public:
    Xbee();
    ~Xbee();
    bool ReadPacket();
    void begin(Stream &serial);
    bool send(uint8_t);
    void setSerial(Stream &serial);
}





#endif
