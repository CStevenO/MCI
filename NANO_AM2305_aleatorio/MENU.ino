void principal() 
{
  lcd.setCursor(0, 0); 
  imprimir("H"); lcd.print(h, 1); imprimir("%");
  imprimir("   T"); lcd.print(t, 1); imprimir((char)223); imprimir("C");
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

//  if(esp.available()>0)
//   {
//      
// env = esp.readStringUntil(';');
//   val = env.substring(0, 2).toInt();
////      Serial.println(val);
//          Serial.println(val);
//      if(val==1)
//      {
//        lcd.setCursor(9, 1);
//        lcd.print("SE"); 
//        lcd.print(" ");
//        lcd.print(minuto); 
//        Serial.print(minuto);
//      } 
//      else
//      {
//        lcd.setCursor(9, 1);
//        lcd.print("NE");
//        lcd.print(" ");
//        lcd.print(minuto); 
//        Serial.print('N'); 
//      }
//   } 
}
