void cargar() {
  hora1Sub = EEPROM.read(0);
  min1Sub = EEPROM.read(1);
  hora2Sub = EEPROM.read(2);
  min2Sub = EEPROM.read(3);
  /////////////////////////////////////////
  hora1Asp = EEPROM.read(4);
  min1Asp = EEPROM.read(5);
  hora2Asp = EEPROM.read(6);
  min2Asp = EEPROM.read(7);
  ////////////////////////////////////////
  sph = EEPROM.read(8);
  histeresis = EEPROM.read(9);
  actHSub = EEPROM.read(10);
  actHAsp  = EEPROM.read(11);
  actSPh = EEPROM.read(12);
}

void guardar() {
  lcd.clear();
  lcd.setCursor(0, 0); lcd.print("Datos Guardados!");
  EEPROM.write(0, hora1Sub);
  EEPROM.write(1, min1Sub);
  EEPROM.write(2, hora2Sub);
  EEPROM.write(3, min2Sub);
  EEPROM.write(4, hora1Asp);
  EEPROM.write(5, min1Asp);
  EEPROM.write(6, hora2Asp);
  EEPROM.write(7, min2Asp);
  EEPROM.write(8, sph);
  EEPROM.write(9, histeresis);
  EEPROM.write(10, actHSub);
  EEPROM.write(11, actHAsp);
  EEPROM.write(12, actSPh);
  delay(1500);
  lcd.clear();
  estado = 0;
}
