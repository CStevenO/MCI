Serial.begin(9600);
Serial.setTimeout(120000);
WiFi.begin(ssid, password);
//Serial.print("Conectando");
while (WiFi.status() != WL_CONNECTED) {
  delay(0);
}
//Serial.println("Conexion Exitosa");
client.setServer(mqtt_server, 1883);
client.setCallback(callback);
//client.publish("MCI_SP_IN","CONECTADO");
