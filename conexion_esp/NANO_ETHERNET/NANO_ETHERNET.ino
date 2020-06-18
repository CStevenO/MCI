#include "Def.h"
void setup() {
#include "Conf.h"
  //  pinMode(4, OUTPUT);
  //  digitalWrite(4, HIGH);
}

void loop() {
  mqttClient.loop();
  if (!mqttClient.connected()) {
    reconnect();
  }
  if (Serial.available()) {
    mensaje = Serial.readStringUntil(';');
    //Serial.println(mensaje);
    if (mensaje == 5) {
      asm volatile ("  jmp 0");
    }
    mqttClient.publish("ING_DATOS", mensaje.c_str());
  }
  //doggieTickle();  // if you uncomment this line, it will keep resetting the timer.
}

void reconnect() {
  Ethernet.begin(mac);
  while (!mqttClient.connected()) {
  String clientId  = "ING_PER-" + String(random(0xffff),HEX);
    if (mqttClient.connect(clientId.c_str())) {
     Serial.print("MQTT connected");
      mqttClient.subscribe("SAL_DA");
    }

   else 
   {
    Serial.print("failed, rc=");
      Serial.print(mqttClient.state());
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
  //esp.print(mMQTT);
  Serial.print(mMQTT);
  mMQTT = "";
  //Serial.println();
}
