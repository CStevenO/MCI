Wire.begin(); // Inicia el puerto I2C
//LCD
lcd.init();
lcd.backlight();
lcd.clear();
//RTC
RTC.begin();
//COMUNICACION UART
//Serial.begin(9600);
//Perro
watchdogSetup();
//humedad suelo
 pinMode(pinSonda, INPUT);
 //SD
 SD.begin(10);
