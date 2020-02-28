const int sensorPin = A0;    // seleccionar la entrada para el sensor
float sensorValue;       // variable que almacena el valor raw (0 a 1023)
float psi;
float kpa;
#define OFFSET 0;

void setup()
{
   Serial.begin(9600);
}
 
void loop() 
{
   sensorValue = analogRead(sensorPin);   // realizar la lectura
   psi=14.69+((0.01574889)*sensorValue)-(0.644444444);
   kpa=100+((0.10861301)*sensorValue)-4.44444444444;
   Serial.print(String(kpa)+", ");
   Serial.println(String(psi));
   delay(500);
}
