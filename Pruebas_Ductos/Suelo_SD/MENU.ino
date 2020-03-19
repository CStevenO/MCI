void principal() 
{
  lcd.setCursor(0, 0); 
  imprimir("P: "); lcd.print(kpa); 
  lcd.setCursor(10, 0); 
  imprimir(" "); imprimir("Pa");
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
