void conectarWifi() {
  Serial.print(WiFi.SSID());
  WiFi.begin(ssid2, password2);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(0);
    WiFi.begin(ssid2, password2);
    WiFi.begin(ssid, password);
    Serial.print("conectando");
    delay(500);
  }
}
