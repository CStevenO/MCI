void cargar() 
{
  ValorH1 = EEPROM.read(0);
  ValorM1 = EEPROM.read(1);
  ValorH2= EEPROM.read(2);
  ValorM2 = EEPROM.read(3);
  sublimacion = EEPROM.read(4);
}

void guardar() {
  lcd.clear();
  lcd.setCursor(0, 0); lcd.print("Datos Guardados!");
  EEPROM.write(0, ValorH1);
  EEPROM.write(1, ValorM1);
  EEPROM.write(2, ValorH2);
  EEPROM.write(3, ValorM2);
  EEPROM.write(4, sublimacion);
  delay(1500);
  lcd.clear();
  estado = 0;
}
