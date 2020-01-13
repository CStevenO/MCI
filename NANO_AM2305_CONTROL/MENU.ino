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
      horasDuc();
      break;
    case 3:
      paramHum();
      break;
    case 4:
      estadoActuadores();
      break;
    case 5:
      estado = 0;
      break;
    case 6:
      parametros();
      break;
    case 7:
      modificarParam();
      break;
    default:
      estado = 0;
      break;
  }
  estadoAnterior = estadoActual;
}



////////////////////////////////////////////////////////////////////////////////////


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


void principal() {
  lcd.setCursor(0, 0);
  imprimir("H"); lcd.print(h, 1); imprimir("%");
  imprimir("   T"); lcd.print(t, 1); imprimir((char)223); imprimir("C");
  lcd.setCursor(0, 1);
  if (hora < 10) {
    imprimir("0");
  }
  imprimir(hora);
  imprimir(":");
  if (minuto < 10) {
    imprimir("0");
  }
  imprimir(minuto);
  imprimir(":");
  if (segundo < 10) {
    imprimir("0");
  }
  imprimir(segundo);
  lcd.setCursor(13, 1);
  imprimir(v); imprimir(s); imprimir(d);
}

void horasDuc() {
  lcd.setCursor(0, 0); imprimir("Horario Ductos ");
  lcd.setCursor(0, 1);
  if (hora1Duc < 10) {
    imprimir("0");
  }
  imprimir(hora1Duc);
  imprimir(":");
  if (min1Duc < 10) {
    imprimir("0");
  }
  imprimir(min1Duc);
  imprimir(" ---- ");
  if (hora2Duc < 10) {
    imprimir("0");
  }
  imprimir(hora2Duc);
  imprimir(":");
  if (min2Duc < 10) {
    imprimir("0");
  }
  imprimir(min2Duc);
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

void paramHum() {
  lcd.setCursor(0, 0); imprimir("SP Humedad: ");
  if (sph < 10) {
    imprimir("00");
  }
  if (sph >= 10 && sph < 100) {
    imprimir("0");
  }
  imprimir(sph);
  imprimir("%");
  lcd.setCursor(0, 1);
  imprimir("Hist: ");
  if (histeresis < 10) {
    imprimir("0");
  }
  imprimir(histeresis); imprimir("%");
}

void mPulsador() {
  estadoActual = rebote(estadoAnterior);
  if (estadoAnterior == HIGH && estadoActual == LOW)
  {
    lcd.clear();
    if (estado != 6 && estado != 7) {
      estado++;
    }
    if (estado == 7) {
      subEstado++;
    }
    if (estado == 6) {
      delay(500);
      if (digitalRead(boton) == HIGH) {
        estado++;
      }
    }
    tiempoP = millis();
  }

  if (millis() > tiempoP + 2000) {
    if (digitalRead(boton) == LOW && estado != 6 && estado != 7) {
      lcd.clear();
      lcd.setCursor(0, 0); imprimir("Ingresando a   ");
      lcd.setCursor(0, 1); imprimir("Ajustes       ");
      delay(2000);
      lcd.clear();
      estado = 6;
    }

    if (digitalRead(boton) == LOW && (estado == 6 || estado == 7)) {
      guardar();
    }
  }

  if (estado >= 1 && estado <= 4) {
    if ((millis() - tiempoP) >= inactividad) {
      lcd.clear();
      estado = 0;
    }
  }
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
      imprimir("Ductos ON       ");
      break;
    case 4:
      lcd.setCursor(0, 1);
      imprimir("Ductos OFF        ");
      break;
    case 5:
      lcd.setCursor(0, 1);
      imprimir("SP Humedad        ");
      break;
    case 6:
      lcd.setCursor(0, 1);
      imprimir("Histeresis      ");
      break;
    case 7:
      lcd.setCursor(0, 1);
      imprimir("Habilitar Vent   ");
      break;
    case 8:
      lcd.setCursor(0, 1);
      imprimir("Habilitar Sublim ");
      break;
    case 9:
      lcd.setCursor(0, 1);
      imprimir("Habilitar Ductos  ");
      break;
    case 10:
      lcd.setCursor(0, 1);
      imprimir("Encender Vent    ");
      break;
    case 11:
      lcd.setCursor(0, 1);
      imprimir("Apagar Vent       ");
      break;
    case 12:
      lcd.setCursor(0, 1);
      imprimir("Encender Sublim    ");
      break;
    case 13:
      lcd.setCursor(0, 1);
      imprimir("Apagar Sublim     ");
      break;
    case 14:
      lcd.setCursor(0, 1);
      imprimir("Encender Ductos    ");
      break;
    case 15:
      lcd.setCursor(0, 1);
      imprimir("Apagar Ductos     ");
      break;
    case 16:
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
      if (subEstado == 0) {
        valorH = obtenerHora();
      } else if (subEstado == 1) {
        valorM = obtenerMinuto();
      } else if (subEstado == 2) {
        lcd.clear();
        hora1Duc = valorH;
        min1Duc  = valorM;
        lcd.setCursor(0, 0);
        imprimir("Datos Ingresados    ");
        delay(1500);
        lcd.clear();
        estado = 6;
        subEstado = 0;
      }
      lcd.setCursor(0, 0); imprimir("Ductos ON      ");
      imprimirHM();
      break;
    case 4:
      if (subEstado == 0) {
        valorH = obtenerHora();
      } else if (subEstado == 1) {
        valorM = obtenerMinuto();
      } else if (subEstado == 2) {
        lcd.clear();
        hora2Duc = valorH;
        min2Duc  = valorM;
        lcd.setCursor(0, 0);
        imprimir("Datos Ingresados    ");
        delay(1500);
        lcd.clear();
        estado = 6;
        subEstado = 0;
      }
      lcd.setCursor(0, 0); imprimir("Ductos OFF      ");
      imprimirHM();
      break;
    case 5:
      if (subEstado == 0) {
        valorH = obtenerHumedad();
      } else if (subEstado == 1) {
        sph = valorH;
        lcd.setCursor(0, 0);
        imprimir("Datos Ingresados    ");
        delay(1500);
        lcd.clear();
        estado = 6;
        subEstado = 0;
      }
      lcd.setCursor(0, 0); imprimir("SP Humedad:        ");
      lcd.setCursor(0, 1);
      if (valorH < 10) {
        imprimir("00");
      }
      if (valorH >= 10 && valorH < 100) {
        imprimir("0");
      }
      imprimir(valorH);
      imprimir("%");
      break;
    case 6:
      if (subEstado == 0) {
        valorH = obtenerHisteresis();
      } else if (subEstado == 1) {
        histeresis = valorH;
        lcd.setCursor(0, 0);
        imprimir("Datos Ingresados");
        delay(1500);
        lcd.clear();
        estado = 6;
        subEstado = 0;
      }
      lcd.setCursor(0, 0); imprimir("Histeresis:         ");
      lcd.setCursor(0, 1);
      imprimir(valorH);
      imprimir("%");
      break;
    case 7:
      if (subEstado == 0) {
        valorH = obtenerOnOFF();
      } else if (subEstado == 1) {
        actSPh = valorH;
        lcd.setCursor(0, 0);
        imprimir("Datos Ingresados");
        delay(1500);
        lcd.clear();
        estado = 6;
        subEstado = 0;
      }
      lcd.setCursor(0, 0); imprimir("Habilitar Vent      ");
      lcd.setCursor(0, 1);
      if (valorH == 0) {
        imprimir("OFF   ");
      } else {
        imprimir("ON    ");
      }
      break;
    case 8:
      if (subEstado == 0) {
        valorH = obtenerOnOFF();
      } else if (subEstado == 1) {
        actHSub = valorH;
        lcd.setCursor(0, 0);
        imprimir("Datos Ingresados   ");
        delay(1500);
        lcd.clear();
        estado = 6;
        subEstado = 0;
      }
      lcd.setCursor(0, 0); imprimir("Habilitar Sublim     ");
      lcd.setCursor(0, 1);
      if (valorH == 0) {
        imprimir("OFF   ");
      } else {
        imprimir("ON    ");
      }
      break;
    case 9:
      if (subEstado == 0) {
        valorH = obtenerOnOFF();
      } else if (subEstado == 1) {
        actHDuc = valorH;
        lcd.setCursor(0, 0);
        imprimir("Datos Ingresados   ");
        delay(1500);
        lcd.clear();
        estado = 6;
        subEstado = 0;
      }
      lcd.setCursor(0, 0); imprimir("Habilitar Ductos    ");
      lcd.setCursor(0, 1);
      if (valorH == 0) {
        imprimir("OFF   ");
      } else {
        imprimir("ON    ");
      }
      break;
    case 10:
      v = 'V';
      mcp.digitalWrite(venOut, LOW);
      lcd.clear();
      imprimir("Vent Encendidos       ");
      delay(500);
      lcd.clear();
      estado = 6;
      subEstado = 0;
      break;
    case 11:
      v = '-';
      mcp.digitalWrite(venOut, HIGH);
      lcd.clear();
      imprimir("Vent Apagados      ");
      delay(500);
      lcd.clear();
      estado = 6;
      subEstado = 0;
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
      d = 'D';
      mcp.digitalWrite(ducOut, LOW);
      lcd.clear();
      imprimir("Duct Encendidos     ");
      delay(500);
      lcd.clear();
      estado = 6;
      subEstado = 0;
      break;
    case 15:
      d = '-';
      mcp.digitalWrite(ducOut, HIGH);
      lcd.clear();
      imprimir("Duct Apagados      ");
      delay(500);
      lcd.clear();
      estado = 6;
      subEstado = 0;
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

void estadoActuadores() {
  lcd.setCursor(0, 0); imprimir("Actuadores:      ");
  lcd.setCursor(0, 1);
  imprimir("V->");
  if (actSPh == true) {
    lcd.write(byte(1));
  } else {
    lcd.write(byte(2));
  }
  imprimir(" S->");
  if (actHSub == true) {
    lcd.write(byte(1));
  } else {
    lcd.write(byte(2));
  }
  imprimir(" D->");
  if (actHDuc == true) {
    lcd.write(byte(1));
  } else {
    lcd.write(byte(2));
  }
}
