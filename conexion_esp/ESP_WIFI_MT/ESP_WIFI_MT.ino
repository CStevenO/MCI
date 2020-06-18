#include "Def.h"

void reconnect() {
  if (WiFi.status() != WL_CONNECTED) {
    conectarWifi();
  }
  // Loop until we're reconnected
  while (!client.connected()) {
    String clientId  = "ING_PER-" + String(random(0xffff),HEX);
    if (client.connect(clientId.c_str())) {
      Serial.print("MQTT connected");
      client.subscribe("SAL_DA");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 1 seconds");
      // Wait 5 seconds before retrying
      delay(0);
      delay(1000);
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
//ESP.wdtFeed();
//WiFi.setAutoConnect(ssid,password);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  if (Serial.available()) {
    mensaje = Serial.readStringUntil(';');

    client.publish("ING_DATOS", mensaje.c_str());
  }
  // put your main code here, to run repeatedly:
  client.loop();
  if (WiFi.status() != WL_CONNECTED) {
    conectarWifi();
  }
}
