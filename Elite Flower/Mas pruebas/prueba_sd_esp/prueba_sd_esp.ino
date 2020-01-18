String mensajeS= " ";
char minuto;
char minutoant;
byte cons;


void setup() {
  Serial.begin(9600);

}

void loop() {

  if (Serial.available())
  {
    mensajeS = Serial.readString();
  // minuto = mensajeS.substring(18).toInt();
   minuto=mensajeS.charAt(17);
  // minutoant=mensajeS.charAt(17);
Serial.println(minuto);
Serial.println(minutoant);

          if(minutoant==minuto)
          {
            cons=1;
            Serial.println(cons);
            Serial.println(minuto);
            Serial.println(minutoant);
          }
          else
          {
            cons=0;
            Serial.println(cons);
            Serial.println(minuto);
            Serial.println(minutoant);
          }
  
           minutoant=minuto;
        
          if((minuto == 48 || minuto == 53)  && cons==0)  //guarda un archivo no enviado solo del minuto del intervalo
                 {
                   
                    
                   
                     
                     Serial.println("Guardo");
   
                  }


  }

}
