Wire.begin(); // Inicia el puerto I2C
//LCD
lcd.init();
lcd.backlight();
lcd.clear();
//RTC
RTC.begin();
//dht
dht.begin();
//COMUNICACION UART
esp.begin(9600);
//Serial.begin(9600);
//Perro
watchdogSetup();

mcp.begin();
mcp.pinMode(subOut, OUTPUT);
//
mcp.digitalWrite(subOut, LOW);
//
mcp.pinMode(subIn, INPUT_PULLUP);
