//Serial.begin(9600);
//LCD
lcd.init();
lcd.backlight();
lcd.clear();
lcd.createChar(1, habilitado);
lcd.createChar(2, deshabilitado);
//RTC
RTC.begin();
//RTC.adjust(DateTime(__DATE__, __TIME__)); //Ajustar Hora
//LUZ
pinMode(luz, INPUT);
//COMUNICACION UART
esp.begin(9600);
// MCP
mcp.begin();
//mcp.pinMode(disOut, OUTPUT);
mcp.pinMode(aspOut, OUTPUT);
mcp.pinMode(subOut, OUTPUT);
mcp.pinMode(venOut, OUTPUT);
//
//mcp.digitalWrite(disOut, HIGH);
mcp.digitalWrite(aspOut, HIGH);
mcp.digitalWrite(subOut, HIGH);
mcp.digitalWrite(venOut, HIGH);
//
//mcp.pinMode(disIn, INPUT_PULLUP);
mcp.pinMode(aspIn, INPUT_PULLUP);
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
wdt_disable();
wdt_enable(WDTO_8S);
