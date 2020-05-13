#include <Printers.h>
#include <XBee.h>

#include "stdlib.h"
#include <AltSoftSerial.h>
AltSoftSerial esp;

XBee xbee = XBee();
XBeeResponse response = XBeeResponse();
ZBRxResponse rx=ZBRxResponse();
ModemStatusResponse msr = ModemStatusResponse();

uint8_t payload[]={"                "};

XBeeAddress64 addr64 = XBeeAddress64(0x0013a200,0x403e0f30);
ZBTxRequest zbTx = ZBTxRequest(addr64,payload,sizeof(payload));
ZBTxStatusResponse txStatus = ZBTxStatusResponse();
int i=0;
String Msg;
void setup() {
  // put your setup code here, to run once:
  esp.begin(9600);
  Serial.begin(9600);
  xbee.setSerial(esp);
}

void loop() {
  uint8_t* Msg;
  Msg=new uint8_t[10];
  
  /*
  for(int i=0;i<10;i++)
  {
    payload[i]=Msg[i];
  }
  // put your main code here, to run repeatedly:
  xbee.send(zbTx);
  if(xbee.readPacket(500)){
    if(xbee.getResponse().getApiId()==ZB_TX_STATUS_RESPONSE) {
      xbee.getResponse().getZBTxStatusResponse(txStatus);

      // get the delivery status, the fifth byte
      if (txStatus.getDeliveryStatus() == SUCCESS) {
        // success.  time to celebrate
        Serial.print("Enviado");
      }
      else{
        Serial.print("No Enviado");
      }
     }
  }
  i++;
  delay(2000);
  */
  xbee.readPacket(500);

  if(xbee.getResponse().isAvailable())
  {
    if(xbee.getResponse().getApiId() == ZB_RX_RESPONSE) {
      xbee.getResponse().getZBRxResponse(rx);
      Serial.print("Se obtuvo algo");
      if (rx.getOption() == ZB_PACKET_ACKNOWLEDGED) {
            // the sender got an ACK
            Serial.println("packet acknowledged");
        } else {
          Serial.println("packet not acknowledged");
        }
        for (int i = 0; i < rx.getDataLength(); i++) {
          Serial.write(rx.getData()[i]);
          
        }
        Msg = StringToCharArray("Se recibio algo",15);
        for(int i=0;i<15;i++)
        {
          payload[i]=Msg[i];
        }
        zbTx = ZBTxRequest(addr64,payload,15);
        xbee.send(zbTx);
        /*
        for (int i = 0; i < xbee.getResponse().getFrameDataLength(); i++) {
        Serial.print("frame data [");
        Serial.print(i, DEC);
        Serial.print("] is ");
        Serial.println(xbee.getResponse().getFrameData()[i], HEX);
      }
      */
    }
    
  }
  else if (xbee.getResponse().isError()) {
      Serial.print("error code:");
      Serial.println(xbee.getResponse().getErrorCode());
    }
}

uint8_t * StringToCharArray(String Cadena, int Tamano){
        uint8_t * ArrayChar = new uint8_t[Tamano];
        //Obtenemos los caracteres uno a uno y posicionamos en el Arreglo.
        for(int i = 0; i < Tamano; i++){
            ArrayChar[i] = Cadena[i];
        }
        return ArrayChar;
}
