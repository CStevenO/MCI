void menu() {
  mPulsador();
  switch (estado) {
    case 0:
      principal();
      break;
    case 1:
      horasSub();
      break;
     case 2:  
      activacionSub();
      break;
    case 3:
      modificarParam();
      break;
    default:
      estado = 0;
      break;
  }
  estadoAnterior = estadoActual;
}

boolean rebote(boolean eAnterior)
{
  boolean eActual = digitalRead(boton);
  if (eAnterior != eActual)
  {
    delay(1);
    eActual = digitalRead(boton);
  }
  return eActual;
}

void mPulsador() 
{
 estadoActual = rebote(estadoAnterior);
  if (estadoAnterior == HIGH && estadoActual == LOW )
  {
    lcd.clear();
    if (estado != 3 && estado !=2) {
      estado++;
    }

    
//    if (estado == 2) {
//      subEstado++;
//    }

if (estado == 2) {
      delay(500);
      if (digitalRead(boton) == HIGH) {
        subEstado1++;
      }
    }

if (estado == 3) {
      delay(500);
      if (digitalRead(boton) == HIGH) {
        subEstado++;
      }
    }

    tiempoP = millis();
  }
  

    if(estado != 0)
  {
    if ((millis() - tiempoP) >= inactividad) 
    {
      lcd.clear();
      estado = 0;
    }
  }
}

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
    subEstado=0;
    subEstado1=0;
}

void horasSub() {
  lcd.setCursor(0, 0); imprimir("Horario Sublim ");
  lcd.setCursor(0, 1);
  cargar();
  if (ValorH1 < 10) {
    imprimir("0");
  }
  imprimir(ValorH1);
  imprimir(":");
  if (ValorM1 < 10) {
    imprimir("0");
  }
  imprimir(ValorM1);
  imprimir(" ---- ");
  if (ValorH2 < 10) {
    imprimir("0");
  }
  imprimir(ValorH2);
  imprimir(":");
  if (ValorM2 < 10) {
    imprimir("0");
  }
  imprimir(ValorM2);

}

void activacionSub()
{
  lcd.setCursor(0, 0); imprimir("Activar Sublim ");
  valorA1=obtenerActivacionS();
   Serial.print(estado);
    Serial.println(subEstado1);
  switch (estado) 
    {
    case 2:
    if(subEstado1 == 2)
     {
       estado=3; 
     }
     break;
    }

  if(valorA1<25 && valorA1>10)
  {
    lcd.setCursor(0, 1); imprimir("SI");
    Serial.print(estado);
    Serial.println(subEstado1);
    switch (estado) 
    {
    case 2:
    if(subEstado1 == 2)
     {
       lcd.setCursor(0, 0); imprimir("Activar Sublim ");
       lcd.setCursor(0, 1); imprimir("Activando...");
       sublimacion=1;
       guardar();
       estado=0;
       subEstado=3;
     }
     break;
    }
  }

   if(valorA1>25)
  {
    lcd.setCursor(0, 0); imprimir("Activar Sublim ");
    lcd.setCursor(0, 1); imprimir("NO");
    switch (estado) 
    {
    case 2:
    if(subEstado1 == 2)
     {
         subEstado=1;
         //subEstado1=4;
         estado=3; 
     }
     break;
    }
  }
  
}

void modificarParam()
{

  
  switch (estado) {
  case 3:
  if(subEstado == 1)
  {
  
      valorH1 = obtenerHora();
      if(valorH1<=9)
      {
        lcd.setCursor(0, 0); imprimir("Modificar Sublim ");
        lcd.setCursor(0, 1);
        imprimir("0");
        imprimir(valorH1);
        imprimir(":00");
        imprimir(" ---- ");
        imprimir("00:00");
      }
      else
      {
        lcd.setCursor(0, 0); imprimir("Modificar Sublim ");
        lcd.setCursor(0, 1);
        imprimir(valorH1);
        imprimir(":00");
        imprimir(" ---- ");
        imprimir("00:00");
      }

  }
  
  if(subEstado == 2)
  {
      valorM1 = obtenerMinuto();
      if(valorM1<=9)
      {
        lcd.setCursor(0, 0); imprimir("Modificar Sublim ");
        lcd.setCursor(0, 1);
        imprimir(valorH1);
        imprimir(":0");
        imprimir(valorM1);
        imprimir(" ---- ");
        imprimir("00:00");
      }
      else
      {
        lcd.setCursor(0, 0); imprimir("Modificar Sublim ");
        lcd.setCursor(0, 1);
        imprimir(valorH1);
        imprimir(":");
        imprimir(valorM1);
        imprimir(" ---- ");
        imprimir("00:00");  
     }
  }

  if(subEstado == 3)
  { 
      valorH2 = obtenerHora();
      if(valorH2<=9)
      {
        lcd.setCursor(0, 0); imprimir("Modificar Sublim ");
        lcd.setCursor(0, 1);
        imprimir(valorH1);
        imprimir(":");
        imprimir(valorM1);
        imprimir(" ---- ");
        imprimir("0");
        imprimir(valorH2);
        imprimir(":00");
      }
      else
      {
        lcd.setCursor(0, 0); imprimir("Modificar Sublim ");
        lcd.setCursor(0, 1);
        imprimir(valorH1);
        imprimir(":");
        imprimir(valorM1);
        imprimir(" ---- ");
        imprimir(valorH2);
        imprimir(":00");
      }

  }
  
  if(subEstado == 4)
  {
      valorM2 = obtenerMinuto();
      if(valorM2<=9)
      {
        lcd.setCursor(0, 0); imprimir("Modificar Sublim ");
        lcd.setCursor(0, 1);
        imprimir(valorH1);
        imprimir(":");
        imprimir(valorM1);
        imprimir(" ---- ");
        imprimir(valorH2);
        imprimir(":0");
        imprimir(valorM2);
      }
      else
      {
        lcd.setCursor(0, 0); imprimir("Modificar Sublim ");
        lcd.setCursor(0, 1);
        imprimir(valorH1);
        imprimir(":");
        imprimir(valorM1);
        imprimir(" ---- ");
        imprimir(valorH2);
        imprimir(":");
        imprimir(valorM2);
      }
  }
  if(subEstado==5)
  {
      lcd.setCursor(0, 0); imprimir("Guardar datos?");
      lcd.setCursor(0, 1); imprimir("SI:MENU NO:RESET");
  }
  
  if(subEstado==6)
  {
   
      guardar();
  }
      break;
}

}
