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
    mqttClient.publish("MCI_SC_IN", mensaje.c_str());
  }
  doggieTickle();  // if you uncomment this line, it will keep resetting the timer.
}

void reconnect() {
  Ethernet.begin(mac);
  while (!mqttClient.connected()) {
    if (mqttClient.connect("NANO_ETER_SC")) {
     // Serial.print("MQTT connected");
      mqttClient.subscribe("MCI_SC_OUT");
    }

//    else 
//    {
//      Serial.print("MQTT no connected");
//    }

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
