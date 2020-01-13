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
      modificarParam();
      break;
     case 3:
        estado = 0;
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
  if (estadoAnterior == HIGH && estadoActual == LOW)
  {
    lcd.clear();
    if (estado != 2 && estado != 3) {
      estado++;
    }
    if (estado == 3) {
      subEstado++;
    }
    if (estado == 2) {
      delay(500);
      if (digitalRead(boton) == HIGH) {
        estado++;
      }
    }
    tiempoP = millis();
}
if (millis() > tiempoP + 2000) {
    if (digitalRead(boton) == LOW && estado != 2 && estado != 3) {
      lcd.clear();
      lcd.setCursor(0, 0); imprimir("Ingresando a   ");
      lcd.setCursor(0, 1); imprimir("Ajustes       ");
      delay(2000);
      lcd.clear();
      estado = 6;
    }

    if (digitalRead(boton) == LOW && (estado == 2 || estado == 3)) {
      guardar();
    }
  }

  if (estado >= 1 && estado <= 2) {
    if ((millis() - tiempoP) >= inactividad) {
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
}

void horasSub() {
  lcd.setCursor(0, 0); imprimir("Horario Sublim ");
  lcd.setCursor(0, 1);
  if (hora1Sub < 10) {
    imprimir("0");
  }
  imprimir(hora1Sub);
  imprimir(":");
  if (min1Sub < 10) {
    imprimir("0");
  }
  imprimir(min1Sub);
  imprimir(" ---- ");
  if (hora2Sub < 10) {
    imprimir("0");
  }
  imprimir(hora2Sub);
  imprimir(":");
  if (min2Sub < 10) {
    imprimir("0");
  }
  imprimir(min2Sub);
}

void parametros() {
  lcd.setCursor(0, 0); lcd.print("P:");
  parametro = obtenerParametro();
  if (parametro < 10) {
    imprimir("0");
  }
  imprimir(parametro); imprimir("            ");

  switch (parametro) {
    case 1:
      lcd.setCursor(0, 1);
      imprimir("Sublim ON      ");
      break;
    case 2:
      lcd.setCursor(0, 1);
      imprimir("Sublim OFF      ");
      break;
    case 3:
      lcd.setCursor(0, 1);
      imprimir("Habilitar Sublim ");
      break;
    case 4:
      lcd.setCursor(0, 1);
      imprimir("Encender Sublim    ");
      break;
    case 5:
      lcd.setCursor(0, 1);
      imprimir("Apagar Sublim     ");
      break;
    case 6:
      lcd.setCursor(0, 1);
      imprimir("Cancelar y Salir ");
      break;
  }
}

void modificarParam() {
  switch (parametro) {
    case 1:
      if (subEstado == 0) {
        valorH = obtenerHora();
      } else if (subEstado == 1) {
        valorM = obtenerMinuto();
      } else if (subEstado == 2) {
        lcd.clear();
        hora1Sub = valorH;
        min1Sub = valorM;
        lcd.setCursor(0, 0);
        imprimir("Datos Ingresados      ");
        delay(1500);
        lcd.clear();
        estado = 6;
        subEstado = 0;
      }
      lcd.setCursor(0, 0); imprimir("Sub ON       ");
      imprimirHM();
      break;
    case 2:
      if (subEstado == 0) {
        valorH = obtenerHora();
      } else if (subEstado == 1) {
        valorM = obtenerMinuto();
      } else if (subEstado == 2) {
        lcd.clear();
        hora2Sub = valorH;
        min2Sub = valorM;
        lcd.setCursor(0, 0);
        imprimir("Datos Ingresados     ");
        delay(1500);
        lcd.clear();
        estado = 6;
        subEstado = 0;
      }
      lcd.setCursor(0, 0); imprimir("Sub OFF      ");
      imprimirHM();
      break;
    case 3:
      
      break;
    case 4:
     
      break;
    case 5:
      
      break;
    case 6:
  
      break;
    case 7:
      
      break;
    case 8:
     
      break;
    case 9:
      
      break;
    case 10:
  
      break;
    case 12:
      s = 'S';
      mcp.digitalWrite(subOut, LOW);
      lcd.clear();
      imprimir("Sub Encendida      ");
      delay(500);
      lcd.clear();
      estado = 6;
      subEstado = 0;
      break;
    case 13:
      s = '-';
      mcp.digitalWrite(subOut, HIGH);
      lcd.clear();
      imprimir("Sub Agagada        ");
      delay(500);
      lcd.clear();
      estado = 6;
      subEstado = 0;
      break;
    case 14:
     
      break;
    case 15:
     
      break;
    case 16:
      lcd.clear();
      estado = 0;
      subEstado = 0;
      break;
  }
}

void imprimirHM() {
  lcd.setCursor(0, 1);
  if (valorH < 10) {
    imprimir("0");
  }
  imprimir(valorH);
  imprimir(":");
  if (valorM < 10) {
    imprimir("0");
  }
  imprimir(valorM);
}
