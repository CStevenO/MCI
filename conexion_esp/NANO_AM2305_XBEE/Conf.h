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
mcp.begin();
mcp.pinMode(subOut, OUTPUT);
mcp.pinMode(ducOut, OUTPUT);
mcp.pinMode(venOut, OUTPUT);
mcp.pinMode(disOut, OUTPUT);
watchdogSetup();
