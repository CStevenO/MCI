#include "Def.h"

void reconnect() {
  if (WiFi.status() != WL_CONNECTED) {
    conectarWifi();
  }
  // Loop until we're reconnected
  while (!client.connected()) {
    if (client.connect("BL_SP_31")) {
      //Serial.print("MQTT connected");
      client.subscribe("MCI_SP_OUT");
    } else {
      //Serial.print("failed, rc=");
      //Serial.print(client.state());
      //Serial.println(" try again in 1 seconds");
      // Wait 5 seconds before retrying
      delay(0);
    }
  }
}

void callback(char* topic, byte* payload, unsigned int length) {
  for (int i = 0; i < length; i++) {
    char receivedChar = (char)payload[i];
    mMQTT += receivedChar;
  }
  Serial.print(mMQTT);
  mMQTT = "";
  //Serial.println();
}


void setup() {
  // put your setup code here, to run once:
#include "Conf.h"
ESP.wdtFeed();
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  if (Serial.available()) {
    mensaje = Serial.readStringUntil(';');

    client.publish("MCI_SP_IN", mensaje.c_str());
  }
  // put your main code here, to run repeatedly:
  client.loop();
  if (WiFi.status() != WL_CONNECTED) {
    conectarWifi();
  }
}
