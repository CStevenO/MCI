#include <Printers.h>
#include "stdlib.h"

//#include <AltSoftSerial.h>
//AltSoftSerial esp;

#include <avr/wdt.h>

String mensajeEntrada = " " ;
byte idMensaje = 0 ;
#define intervalo 5
String mensajeSalida = "";
byte indice = 0;
short idInvernadero = 0x6F7;
int i = 0;
#define separador ','
uint16_t datos[6];

// RTC
#include <RTClib.h>
RTC_DS3231 RTC;
short anio = 0;
byte mes = 0;
byte dia = 0;
byte hora = 0;
byte minuto =  0;
byte segundo = 0;
long fecha = 0;


unsigned long milisAnterior = 0;
#include <DHT.h>
#define DHTPIN 5    // PIN SENSOR
#define DHTTYPE DHT21   // DHT 22  (AM2302)
DHT dht(DHTPIN, DHTTYPE);
float t;
float h;
#define OffsetT 0
#define OffsetH 0


// LCD
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x3F, 16, 2);
#define imprimir(cadena){lcd.print(cadena);}

//SD
#include <SPI.h>
#include <SdFat.h>
SdFat SD;

File myFile;


unsigned long envio = 0;



#include <XBee.h>
XBee xbee = XBee();
#include <SoftwareSerial.h>


//#define rxPin 10
//#define txPin 11

// set up a new serial port
//SoftwareSerial mySerial =  SoftwareSerial(rxPin, txPin);

String Msg;
XBeeResponse response = XBeeResponse();
ZBRxResponse rx=ZBRxResponse();
ModemStatusResponse msr = ModemStatusResponse();



uint8_t payload[39]={"   "};
XBeeAddress64 addr64 = XBeeAddress64(0x0013A200,0x41A0AECD);
ZBTxRequest zbTx = ZBTxRequest(addr64,payload,sizeof(payload));
ZBTxStatusResponse txStatus = ZBTxStatusResponse();

void setup(){
//  // define pin modes for tx, rx:
//  pinMode(rxPin, INPUT);
//  pinMode(txPin, OUTPUT);
//  // set the data rate for the SoftwareSerial port
//  mySerial.begin(9600);
  wdt_disable();
  dht.begin();
  //COMUNICACION UART
  Serial.begin(9600);
 // Serial.println("DHTxx test!");
  xbee.setSerial(Serial);
  RTC.begin(); 
  //RTC.adjust(DateTime(2020, 07, 04, 10, 02, 00));
  wdt_enable(WDTO_8S);
}

void loop () {
xctu(); 
tiempoActual();
obtenerVariables();
principal(); 
enviarDatos();
watchdogSetup();

//


//  myFile = SD.open("DATOS.txt", FILE_WRITE);
//  myFile.close();
//    
// anio= (payload[1]<<8 | payload[2] );
//
  
}

void tiempoActual() 
{
  DateTime now = RTC.now(); // Obtiene la fecha y hora del RTC
  anio = now.year();
  mes = now.month();
  dia = now.day();
  hora = now.hour();
  minuto =  now.minute();
  segundo = now.second();
  fecha = now.unixtime();
}

void obtenerVariables() 
{
//if (millis() - milisAnterior >= 5000) 
//{
    //milisAnterior = millis();
    t = dht.readTemperature() + OffsetT;
    h = dht.readHumidity() + OffsetH ;
      //delay (5000);
//   t=1;
   // h=2;
   
   // lcd.clear();
    //}
}

void principal() 
{
  lcd.setCursor(0, 0); 
  imprimir("H"); lcd.print(h, 1); imprimir("%");
  imprimir("   T"); lcd.print(t, 1); imprimir((char)223); imprimir("C");
  lcd.setCursor(0, 1);
  if (hora < 10) 
  {
    imprimir("0");
  }
  imprimir(hora);
  imprimir(":");
  if (minuto < 10) 
  {
    imprimir("0");
  }
  imprimir(minuto);
  imprimir(":");
  if (segundo < 10) 
  {
    imprimir("0");
  }
  imprimir(segundo);
}


void xctu() {
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
     // Serial.print(" Se obtuvo algo");
      if (rx.getOption() == ZB_PACKET_ACKNOWLEDGED) {
            // the sender got an ACK
            //Serial.println(" packet acknowledged");
            
        } else {
          //Serial.println(" packet not acknowledged");
        }
        mensajeEntrada = "";
//        for (int i = 0; i < rx.getDataLength(); i++) {
//          //Serial.write(rx.getData()[i]);
//          mensajeEntrada = mensajeEntrada + rx.getData()[i];
//        }
        mensajeEntrada = (char*)rx.getData();
    //   if (esp.available()>0) 
    //  {
//       mensajeEntrada = esp.readStringUntil(';');
       idMensaje = mensajeEntrada.substring(1).toInt();
         //Serial.print(mensajeEntrada);
        switch(idMensaje)
        {
        case 0:
                                         
        break;
        
        case 3:
        
          mensajeEntrada = mensajeEntrada.substring(3);
          Serial.println(mensajeEntrada);
          for (i = 0; i < 6 ; i++)
          {
            //Serial.println(mensajeEntrada);
            indice = mensajeEntrada.indexOf(separador);
            datos[i] = (mensajeEntrada.substring(0, indice)).toInt();
            mensajeEntrada = mensajeEntrada.substring(indice + 1);
            
          }
          
         RTC.adjust(DateTime(datos[0], datos[1], datos[2], datos[3], datos[4], datos[5]));
        
        case 4:
            //enciende efectores
    
        break;
        }
          
   //}

        
        Msg = StringToCharArray(" Se recibio algo",15);
//        for(int i=0;i<15;i++)
//        {
          //payload[i]=Msg[i];
       // }
       // zbTx = ZBTxRequest(addr64,payload,15);
       // xbee.send(zbTx);
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
      Serial.print(" error code:");
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


void enviarDatos() {

if (millis() - milisAnterior >= 30000) 
{
    milisAnterior = millis();

mensajeSalida = "01," + String(anio) + "-" + String(mes) + "-" + String(dia) + " " + String(hora) + ":" + String(minuto) + ":" + "00" + "," + idInvernadero + "," + String(t, 2) + "," + String(h, 2) + ";";
Msg = StringToCharArray(mensajeSalida,39);
        for(int i=0;i<39;i++)
        {
          payload[i]=Msg[i];
        }
        xbee.send(zbTx);
        //delay(10000);
            
}




 
  if(hora== 4 && minuto == 52 && segundo == 20)
  {
     asm("jmp 0x0000");
  }

   if(hora== 11 && minuto == 52 && segundo == 20)
  {
     asm("jmp 0x0000");
  }

   if(hora== 16 && minuto == 52 && segundo == 20)
  {
     asm("jmp 0x0000");
  }

  if(hora==23 && minuto == 52 && segundo == 20)
  {
     asm("jmp 0x0000");
  }

}

void watchdogSetup()
{
wdt_reset();
}
