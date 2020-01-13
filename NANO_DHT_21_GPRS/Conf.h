Serial.begin(9600);
//LCD
lcd.init();
lcd.backlight();
lcd.clear();
//RTC
RTC.begin();
//dht
dht.begin();
//
//RTC.adjust(DateTime(__DATE__, __TIME__)); //Ajustar Hora
// gsm.begin(9600);
// esp.begin(9600);
watchdogSetup();
