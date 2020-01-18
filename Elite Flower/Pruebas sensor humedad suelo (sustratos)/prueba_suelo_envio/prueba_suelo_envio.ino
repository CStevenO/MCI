unsigned long previo=0;
float escala = 0.1; 
int cont1=0;
int voltaje;
int voltajeProm;
float lectura;
int voltajeSum=0;
String mensajeSalida = "";


void setup() {
Serial.begin(9600);

}

void loop() {
if((millis()-previo) <= 6000)
  {
  voltaje = 10;
  //lectura = map(lectura, 0, 1023, 0, 500);
  //voltaje = lectura/escala;
  voltajeSum= voltajeSum + voltaje;
  
  cont1++;
//  Serial.println(cont1);
  Serial.print("Voltaje: ");
  Serial.print(voltajeSum);
   Serial.print("    tiempo: ");
  Serial.println(previo);
  
  }
  else
  {
    previo=millis();
     Serial.println(cont1);
    voltajeProm= voltajeSum / cont1;
    cont1=0;
    voltajeSum=0;
    mensajeSalida.reserve(30);
    mensajeSalida = "07," + String(voltajeProm) + ';';

   
Serial.println(voltajeProm);
   Serial.println("envia");
    Serial.println(mensajeSalida);
    mensajeSalida= "";
  }

}
