void tiempoActual() {
  DateTime now = RTC.now();
  anio = now.year();
  mes = now.month();
  dia = now.day();
  hora = now.hour();
  minuto =  now.minute();
  segundo = now.second();
}

void enviarDatos() {
  if (esp.available()) {
    mensajeEntrada.reserve(40);
    mensajeEntrada = esp.readStringUntil(';');
    idMensaje = mensajeEntrada.substring(0, 2).toInt();
    if (idMensaje == 3) {
      mensajeEntrada = mensajeEntrada.substring(3);
      for (i = 0; i < 6 ; i++)
      {
        indice = mensajeEntrada.indexOf(separador);
        datos[i] = (mensajeEntrada.substring(0, indice)).toInt();
        mensajeEntrada = mensajeEntrada.substring(indice + 1);
      }
      RTC.adjust(DateTime(datos[0], datos[1], datos[2], datos[3], datos[4], datos[5]));
      asm volatile ("  jmp 0");
    }
  }

  if (minuto % intervalo == 0 && !unicaVez && h > 0 && h <= 100 && t > 0 && t < 50) {
    mensajeSalida.reserve(40);
    mensajeSalida = "01," + String(anio) + "-" + String(mes) + "-" + String(dia) + " " + String(hora) + ":" + String(minuto) + ":" + String(segundo) + "," + idInvernadero + "," + String(t, 2) + "," + String(h, 2) + ";";
    tiempoRetraso = millis();
    lcd.clear();
    esp.print(mensajeSalida);
    unicaVez = true;
  }
  if (minuto % intervalo != 0) {
    unicaVez = false;
  }
}

boolean esHoraDuc() {
  if (momentoInicioDuc < momentoFinDuc) {
    if (momentoAhora >= momentoInicioDuc && momentoAhora < momentoFinDuc && actHDuc) {
      return true;
    } else {
      return false;
    }
  }
  if (momentoInicioDuc > momentoFinDuc) {
    if ((momentoAhora >= momentoInicioDuc || momentoAhora < momentoFinDuc) && actHDuc) {
      return true;
    } else {
      return false;
    }
  }
  if (momentoInicioDuc == momentoFinDuc) {
    return false;
  }
}

boolean esHoraSub() {
  if (momentoInicioSub < momentoFinSub) {
    if (momentoAhora >= momentoInicioSub && momentoAhora < momentoFinSub && actHSub) {
      return true;
    } else {
      return false;
    }
  }
  if (momentoInicioSub > momentoFinSub) {
    if ((momentoAhora >= momentoInicioSub || momentoAhora < momentoFinSub) && actHSub) {
      return true;
    } else {
      return false;
    }
  }
  if (momentoInicioSub == momentoFinSub) {
    return false;
  }
}
