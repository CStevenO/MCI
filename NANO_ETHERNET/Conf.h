//wdt_disable();
//COMUNICACION UART
//esp.begin(9600);
Serial.begin(9600);
Serial.setTimeout(120000);
//ETHERNET Y MQTT
Ethernet.begin(mac);
mqttClient.setClient(ethClient);
mqttClient.setServer("10.50.1.154", 1883); //for using local broker
mqttClient.setCallback(callback);
//Perro
watchdogSetup();
