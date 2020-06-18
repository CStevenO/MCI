// UART 
//#include <AltSoftSerial.h>
//AltSoftSerial esp;
//ETHERNET Y CLIENTE MQTT
#include <UIPEthernet.h>
#include "PubSubClient.h"
uint8_t mac[6] = {0x00, 0x01, 0xF2, 0xD3, 0x04, 0x05};
EthernetClient ethClient;
PubSubClient mqttClient;
String mensaje = "";
String mMQTT = "";
//Perro
//#include <avr/wdt.h>
unsigned long resetTime = 0;
#define TIMEOUTPERIOD 20000  // You can make this time as long as you want, it's not limited to 8 seconds like the normal watchdog
//#define doggieTickle() resetTime = millis();  // This macro will reset the timer
