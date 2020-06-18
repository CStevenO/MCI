#include <ESP8266WiFi.h>
#include <PubSubClient.h>
const char* ssid2 = "Stev";
const char* password2 = "jaja";
const char* ssid = "Red Wi-Fi de Elite Apple";                           //!!!!!!!!!!!!!!!!!!!!!
const char* password = "Elite2019";                //!!!!!!!!!!!!!!!!!!!!!
const char* mqtt_server = "10.50.1.153";                 //!!!!!!!!!!!!!!!!!!!!!
WiFiClient espClient;
PubSubClient client(espClient);
String mensaje = "";
String mMQTT = "";
