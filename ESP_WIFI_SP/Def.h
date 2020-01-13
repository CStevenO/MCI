#include <ESP8266WiFi.h>
#include <PubSubClient.h>
const char* ssid = "MTOinvernadero";                           //!!!!!!!!!!!!!!!!!!!!!
const char* password = "MTOinv2017";                //!!!!!!!!!!!!!!!!!!!!!
const char* mqtt_server = "10.50.1.154";                 //!!!!!!!!!!!!!!!!!!!!!
WiFiClient espClient;
PubSubClient client(espClient);
String mensaje = "";
String mMQTT = "";
