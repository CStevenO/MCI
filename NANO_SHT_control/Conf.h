//Serial.begin(9600);
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
// MCP
mcp.begin();
mcp.pinMode(ducOut, OUTPUT);
mcp.pinMode(subOut, OUTPUT);
mcp.pinMode(venOut, OUTPUT);
//
mcp.digitalWrite(ducOut, HIGH);
mcp.digitalWrite(subOut, HIGH);
mcp.digitalWrite(venOut, HIGH);
//
mcp.pinMode(ducIn, INPUT_PULLUP);
mcp.pinMode(subIn, INPUT_PULLUP);
mcp.pinMode(venIn, INPUT_PULLUP);
//EEPROM
cargar(); //Carga los parámetros de configuración.
// MENU
pinMode(boton, INPUT_PULLUP);
//POT
for (i = 0; i < numLecturas; i++)
{
  lecturas[i] = 0;
}
//Perro Guardian
watchdogSetup();
