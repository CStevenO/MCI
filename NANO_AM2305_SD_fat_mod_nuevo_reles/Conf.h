Wire.begin(); // Inicia el puerto I2C
//LCD
lcd.init();
lcd.backlight();
lcd.clear();
lcd.createChar(1, habilitado);
lcd.createChar(2, deshabilitado);
//RTC
RTC.begin();
//dht
dht.begin();
//LUZ
pinMode(luz, INPUT);
//COMUNICACION UART
esp.begin(9600);
//Serial.begin(9600);
//Perro
watchdogSetup();
//SD
SD.begin(10);
//modulo mcp
mcp.begin();  
mcp.pinMode(subOut, OUTPUT);

mcp.digitalWrite(subOut, HIGH);

mcp.pinMode(subIn, INPUT_PULLUP);


//EEPROM
cargar(); //Carga los parámetros de configuración.
// MENU
pinMode(boton, INPUT_PULLUP);
//POT
for (i = 0; i < numLecturas; i++)
{
  lecturas[i] = 0;
}
