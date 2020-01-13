#include <ESP8266WiFi.h>
#include <PubSubClient.h>
const char* ssid = "MTOinvernadero";                           //!!!!!!!!!!!!!!!!!!!!!
const char* password = "MTOinv2017";                //!!!!!!!!!!!!!!!!!!!!!
const char* mqtt_server = "10.50.1.154";                 //!!!!!!!!!!!!!!!!!!!!!
WiFiClient espClient;
PubSubClient client(espClient);
String mensaje = "";
String mMQTT = "";

//SD
#include <SPI.h>
#include <SdFat.h>
SdFat SD;

File myFile;
int UltimaPosicion=0;
char mensajeGuardado;
bool conect = false;
