void principal() 
{
  lcd.setCursor(0, 0); 
  imprimir("V: "); lcd.print(voltaje); 
  lcd.setCursor(10, 0); 
  imprimir(" "); imprimir("mV");
  lcd.setCursor(0, 1);
  if (hora < 10) 
  {
    imprimir("0");
  }
  imprimir(hora);
  imprimir(":");
  if (minuto < 10) 
  {
    imprimir("0");
  }
  imprimir(minuto);
  imprimir(":");
  if (segundo < 10) 
  {
    imprimir("0");
  }
  imprimir(segundo); 
}
