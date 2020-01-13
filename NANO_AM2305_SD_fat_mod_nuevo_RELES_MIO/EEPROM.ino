void cargar() 
{
  hora1Sub = EEPROM.read(0);
  min1Sub = EEPROM.read(1);
  hora2Sub = EEPROM.read(2);
  min2Sub = EEPROM.read(3);
}

void guardar() {
  lcd.clear();
  lcd.setCursor(0, 0); lcd.print("Datos Guardados!");
  EEPROM.write(0, hora1Sub);
  EEPROM.write(1, min1Sub);
  EEPROM.write(2, hora2Sub);
  EEPROM.write(3, min2Sub);
  delay(1500);
  lcd.clear();
  estado = 0;
}
