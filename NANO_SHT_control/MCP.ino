void momentos() {
  momentoInicioSub = (hora1Sub * 60) + min1Sub;
  momentoFinSub = (hora2Sub * 60) + min2Sub;
  momentoInicioDuc = (hora1Duc * 60) + min1Duc;
  momentoFinDuc = (hora2Duc * 60) + min2Duc;
  momentoAhora = (hora * 60) + minuto;
}

void actuadores() {
  momentos();
  if (estado != 6 && estado != 7) {
    //Gestion de los ventiladores por humedad
    ventActual = hayHumedad();
    subActual = esHoraSub();
    ducActual = esHoraDuc();

    if (ventActual == true && ventAnterior == false) {
      v = 'V';
      mcp.digitalWrite(venOut, LOW);
      encendido();
      delay(500);
      mensajeSalida.reserve(35);
      if(ven==1)
      {
      mensajeSalida = "02," + String(anio) + "-" + String(mes) + "-" + String(dia) + " " + String(hora) + ":" + String(minuto) + ":" + String(segundo) + "," + String(idInvernadero) + ",V1,VE;";
      esp.print(mensajeSalida);
      }
      else
      {
      mensajeSalida = "02," + String(anio) + "-" + String(mes) + "-" + String(dia) + " " + String(hora) + ":" + String(minuto) + ":" + String(segundo) + "," + String(idInvernadero) + ",V1,VA;";
      esp.print(mensajeSalida);
      }
      delay(500);
      mensajeSalida = "";
    }
    if (ventActual == false && ventAnterior == true) {
      v = '-';
      mensajeSalida.reserve(35);
      mensajeSalida = "02," + String(anio) + "-" + String(mes) + "-" + String(dia) + " " + String(hora) + ":" + String(minuto) + ":" + String(segundo) + "," + String(idInvernadero) + ",V0;";
      esp.print(mensajeSalida);
      mcp.digitalWrite(venOut, HIGH);
      mensajeSalida = "";
    }

    if (subActual == true && subAnterior == false) {
      s = 'S';
      mcp.digitalWrite(subOut, LOW);
      encendido();
      delay(500);
      mensajeSalida.reserve(35);
      if(sub==1)
      {
      mensajeSalida = "02," + String(anio) + "-" + String(mes) + "-" + String(dia) + " " + String(hora) + ":" + String(minuto) + ":" + String(segundo) + "," + String(idInvernadero) + ",S1,SE;";
      esp.print(mensajeSalida);
      }
      else
      {
      mensajeSalida = "02," + String(anio) + "-" + String(mes) + "-" + String(dia) + " " + String(hora) + ":" + String(minuto) + ":" + String(segundo) + "," + String(idInvernadero) + ",S1,SA;";
      esp.print(mensajeSalida);
      }
      delay(500);
      mensajeSalida = ""; 
    }
    if (subActual == false && subAnterior == true) {
      s = '-';
      mensajeSalida.reserve(35);
      mensajeSalida = "02," + String(anio) + "-" + String(mes) + "-" + String(dia) + " " + String(hora) + ":" + String(minuto) + ":" + String(segundo) + "," + String(idInvernadero) + ",S0;";
      esp.print(mensajeSalida);
      mcp.digitalWrite(subOut, HIGH);
      mensajeSalida = "";
    }

    if (ducActual == true && ducAnterior == false) {
      d = 'D';
      mcp.digitalWrite(ducOut, LOW);
      encendido();
      delay(500);
      mensajeSalida.reserve(35);
      if(duc==1)
      {
      mensajeSalida = "02," + String(anio) + "-" + String(mes) + "-" + String(dia) + " " + String(hora) + ":" + String(minuto) + ":" + String(segundo) + "," + String(idInvernadero) + ",D1,DE;";
      esp.print(mensajeSalida);
      }
      else
      {
      mensajeSalida = "02," + String(anio) + "-" + String(mes) + "-" + String(dia) + " " + String(hora) + ":" + String(minuto) + ":" + String(segundo) + "," + String(idInvernadero) + ",D1,DA;";
      esp.print(mensajeSalida);
      }
      delay(500);
      mensajeSalida = "";
    }
    if (ducActual == false && ducAnterior == true) {
      d = '-';
      mensajeSalida.reserve(35);
      mensajeSalida = "02," + String(anio) + "-" + String(mes) + "-" + String(dia) + " " + String(hora) + ":" + String(minuto) + ":" + String(segundo) + "," + String(idInvernadero) + ",D0;";
      esp.print(mensajeSalida);
      mcp.digitalWrite(ducOut, HIGH);
      mensajeSalida = "";
    }

    ventAnterior = ventActual;
    subAnterior = subActual;
    ducAnterior = ducActual;
  }
}
