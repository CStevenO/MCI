
Wire.begin(); // Inicia el puerto I2C
//LCD
lcd.init();
lcd.backlight();
lcd.clear();

//RTC
RTC.begin();
//COMUNICACION UART
esp.begin(9600);
//Serial.begin(9600);
//Perro
watchdogSetup();
//SHT3x
//Serial.begin(9600);
Sensor.Begin();
//modulo mcp
//mcp.begin();  

// mcp.pinMode(7, OUTPUT);
// mcp.pinMode(6, OUTPUT);
// mcp.pinMode(5, OUTPUT);
// mcp.pinMode(4, OUTPUT);
