
#include <OneWire.h>
#include <DallasTemperature.h>
OneWire oneWireObjeto(4);
DallasTemperature sensorDS18B20(&oneWireObjeto); //El sensor DS18B20 necesita obligatoriamente una recistencia de 4.7k desde el pin da datos y VCC
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  sensorDS18B20.begin(); 
}


float value,HR,ax,t;
void loop() {
  HR=0;
  for(int i=0;i<7;i++)
  {
  sensorDS18B20.requestTemperatures();
  t = sensorDS18B20.getTempCByIndex(0);
  // put your main code here, to run repeatedly:
  value=analogRead(A1);
  ax=value*5/1023;
  HR=(ax-0.43)/((5.43/100000)*t+0.0271)-13.16+HR;
  }
  HR=HR/7;
  Serial.println("Humedad Relativa: "+String(HR)+" Temperatura: "+String(t));
  //delay(100);
}
