void sublim()
{
  cargar();

  if(valorH1 == hora && valorM1 == minuto && sublimacion == 1)
   {
    mcp.digitalWrite(subOut, HIGH);
    Serial.println("sublimacion on");
    }

    if(valorH2 == hora && valorM2 == minuto)
   {
    mcp.digitalWrite(subOut, LOW);
    Serial.println("sublimacion off");
    }

}
