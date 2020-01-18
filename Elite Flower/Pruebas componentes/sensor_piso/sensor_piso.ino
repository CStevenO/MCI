int pinSonda = A1;
float escala = 0.1; //100 para voltios, 0.1 para milivoltios

void setup(){
  
  Serial.begin(19200);

  pinMode(pinSonda, INPUT);

}

void loop(){
 
  float lectura = analogRead(pinSonda);
 
  lectura = map(lectura, 0, 1023, 0, 500);
 
  float voltaje = lectura/escala;

  float salida = (4.824*pow(10,-10))*(pow(voltaje,3))-(2.278*pow(10,-6))*(pow(voltaje,2))+(3.898*(pow(10,-3)))*(voltaje)-(2.154);

Serial.print(voltaje);
Serial.print("   "); 
  Serial.println(salida);
  delay(500);
}
