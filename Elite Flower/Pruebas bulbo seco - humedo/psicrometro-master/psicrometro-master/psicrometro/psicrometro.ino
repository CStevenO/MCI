
//Must work between 10 and 24 C
//Ter seco a pin 4
//Term humedo a pin 5
//Output (PWM) pin 6

#include <OneWire.h>
#include <DallasTemperature.h>

//tabla
typedef struct {
   float temperatura;
   float valor;
   } mmHG;
   
mmHG mimmHG[157]={
{10,9.209},{10.1,9.273},{10.2,9.336},{10.3,9.4},{10.4,9.463},{10.5,9.527},{10.6,9.59},{10.7,9.654},{10.8,9.717},{10.9,9.781},{11,9.844},{11.1,9.911},{11.2,9.979},{11.3,10.046},{11.4,10.114},{11.5,10.181},{11.6,10.248},{11.7,10.316},{11.8,10.383},{11.9,10.451},{12,10.518},{12.1,10.589},{12.2,10.661},{12.3,10.732},{12.4,10.803},{12.5,10.875},{12.6,10.946},{12.7,11.017},{12.8,11.088},{12.9,11.16},{13,11.231},{13.1,11.307},{13.2,11.382},{13.3,11.458},{13.4,11.533},{13.5,11.609},{13.6,11.685},{13.7,11.76},{13.8,11.836},{13.9,11.911},{14,11.987},{14.1,12.067},{14.2,12.147},{14.3,12.227},{14.4,12.307},{14.5,12.388},{14.6,12.468},{14.7,12.548},{14.8,12.628},{14.9,12.708},{15,12.788},{15.1,12.873},{15.2,12.957},{15.3,13.042},{15.4,13.126},{15.5,13.211},{15.6,13.296},{15.7,13.38},{15.8,13.465},{15.9,13.549},{16,13.634},{16.1,13.724},{16.2,13.813},{16.3,13.903},{16.4,13.992},{16.5,14.082},{16.6,14.172},{16.7,14.261},{16.8,14.351},{16.9,14.44},{17,14.53},{17.1,14.625},{17.2,14.719},{17.3,14.814},{17.4,14.909},{17.5,15.004},{17.6,15.098},{17.7,15.193},{17.8,15.288},{17.9,15.382},{18,15.477},{18.1,15.577},{18.2,15.677},{18.3,15.777},{18.4,15.877},{18.5,15.977},
{18.6,16.077},{18.7,16.177},{18.8,16.277},{18.9,16.377},{19,16.477},{19.1,16.583},{19.2,16.689},{19.3,16.794},{19.4,16.9},{19.5,17.006},{19.6,17.112},{19.7,17.218},{19.8,17.323},{19.9,17.429},{20,17.535},{20.1,17.647},{20.2,17.758},{20.3,17.87},{20.4,17.981},{20.5,18.093},{20.6,18.204},{20.7,18.316},{20.8,18.427},
{20.9,18.539},{21,18.65},{21.1,18.768},{21.2,18.885},{21.3,19.003},{21.4,19.121},{21.5,19.239},{21.6,19.356},{21.7,19.474},{21.8,19.592},{21.9,19.709},{22,19.827},{22.1,19.951},{22.2,20.075},{22.3,20.199},{22.4,20.323},{22.5,20.448},{22.6,20.572},{22.7,20.696},{22.8,20.82},{22.9,20.944},{23,21.068},{23.1,21.199},
{23.2,21.33},{23.3,21.461},{23.4,21.592},{23.5,21.723},{23.6,21.853},{23.7,21.984},{23.8,22.115},{23.9,22.246},{24,22.377},{24.1,22.515},{24.2,22.653},{24.3,22.791},{24.4,22.929},{24.5,23.067},{24.6,23.204},{24.7,23.342},{24.8,23.48},{24.9,23.618},{25,23.756},{25.1,23.901},{25.2,24.047},{25.3,24.192},{25.4,24.337}
};  
float seco, humedo, HR, H8, H9, H10,H11,H12, fanconvalue;
 unsigned long timer1=0;
// Data wire is plugged into ports 3 the Arduino
#define ONE_WIRE_BUS_A 4
#define ONE_WIRE_BUS_B 5
//#define ONE_WIRE_BUS_C 6
//#define ONE_WIRE_BUS_D 7
//#define fadePin 6
//#define vccpin 9
#define ECHO false




#define TEMPERATURE_PRECISION 12
//// arrays to hold device addresses
////4REDES CON 4 SENSORES POR RED MAX
DeviceAddress Thermometer[16];

// Setup a oneWire instance to communicate with OneWire devices
OneWire oneWireA(ONE_WIRE_BUS_A);
OneWire oneWireB(ONE_WIRE_BUS_B);
//OneWire oneWireC(ONE_WIRE_BUS_C);
//OneWire oneWireD(ONE_WIRE_BUS_D);


// Pass our oneWire reference to Dallas Temperature.
DallasTemperature sensorsA(&oneWireA);
DallasTemperature sensorsB(&oneWireB);
//DallasTemperature sensorsC(&oneWireC);
//DallasTemperature sensorsD(&oneWireD);



int numberOfDevices[2]={0,0};

int i;




// 1- wire functions
// function to print the temperature for a NET
float printTemperature(DallasTemperature sensor, int red)
{
  
sensor.requestTemperatures();
int i;
float temp;
 
 

 


for(i=0; i< numberOfDevices[red-1];i++){

 // Serial.print("B"); Serial.print(red); Serial.print(i); Serial.print(" TEMPERATURE ");
  temp=sensor.getTempC(Thermometer[(red-1)*4+i]);

  //Serial.println(temp);
  delay(100);
  return temp;
 
  
  
}

  
 

  
}
float send_value(float temp) {
 //Ajustamos a un decimal
 temp=int(temp*10);
  temp=temp/10;
 if (ECHO){ Serial.print("busco para "); Serial.println(temp);}
  float temp1;
   for( int i=0; i < 157; i++) {
     if(temp==mimmHG[i].temperatura) {
       
       temp1= mimmHG[i].valor;
 if (ECHO){ Serial.print("encontardo con valor "); Serial.println(temp1);}
     }
  }
 if ( temp > 25.4) temp1=24.337;
 if (temp < 10) temp1 =9.209;
  return temp1;
  //lo dejamos fijo;
}




//main program
void setup(void) {
  
//pinMode(vccpin,OUTPUT);
//pinMode(fadePin, OUTPUT);

//analogWrite(vccpin,255);
Serial.begin(19200); //hay que leer a 57600 por la modificacion del valor del reloj
  //setPwmFrequency(6,1);
  Serial.println("Soy fancon5");
   
  //for 1 wire
      delay(3000); //debemos esperar la sincronizacion antes de enviar

  sensorsA.begin();
  sensorsB.begin();
//  sensorsC.begin();
//  sensorsD.begin();


 // Grab a count of devices on the wire
 numberOfDevices[0]= sensorsA.getDeviceCount();
 numberOfDevices[1] = sensorsB.getDeviceCount();
// numberOfDevices[2] = sensorsC.getDeviceCount();
//  numberOfDevices[3] = sensorsD.getDeviceCount();
 Serial.println(numberOfDevices[0]);
 Serial.println(numberOfDevices[1]);
//  Serial.println(numberOfDevices[2]);
//   Serial.println(numberOfDevices[3]);

 // your code continues below...
  for (i=0; i<numberOfDevices[0]; i++){ 
 if (!sensorsA.getAddress(Thermometer[i], i)) ; 
 sensorsA.setResolution(Thermometer[i], TEMPERATURE_PRECISION);
  }
  //RED B
  for (i=0; i<numberOfDevices[1]; i++){ 
 if (!sensorsB.getAddress(Thermometer[i+4], i)) ; 
 sensorsB.setResolution(Thermometer[i+4], TEMPERATURE_PRECISION);
  }
    //RED D
//  for (i=0; i<numberOfDevices[2]; i++){ 
// if (!sensorsC.getAddress(Thermometer[i+8], i)) ; 
// sensorsC.setResolution(Thermometer[i+8], TEMPERATURE_PRECISION);
//  }
//  
//   //RED E
//  for (i=0; i<numberOfDevices[3]; i++){ 
// if (!sensorsD.getAddress(Thermometer[i+12], i)) ; 
// sensorsD.setResolution(Thermometer[i+12], TEMPERATURE_PRECISION);
  //}
 
  
  //test de inicio
//  digitalWrite(13, HIGH);
//  delay(5000);
//  digitalWrite(13, LOW);

}


void loop(void) {


 
  seco= printTemperature(sensorsA, 1);
  humedo= printTemperature(sensorsB, 2);



//hacemos el calculo de la humedad H% es la sonda humeda
seco=(((int)(seco*10))/10);
humedo=(((int)(humedo*10))/10);


if (ECHO) {Serial.print("seco= ");Serial.println(seco);}

H9=send_value(seco)/0.75006;




H8=send_value(humedo)/0.75006;

 if (((seco-humedo) > 0) && (H9 > 0)){
H12=932;
H10=H8-(0.0007*H12*(seco-humedo));
 HR= 100*(H10/H9);
 }
 else { HR=100;}

 if (HR==100 || HR > 100 ){ HR=100;}
 

 //para evitar desbordaiento
 if (millis()<timer1) timer1=millis();
 //se envia cada 5 min el dato
if ((millis()-timer1) > 20000) {
//   fanconvalue=map(HR,0,100,0,255);
 //fanconvalue=254;
// analogWrite(fadePin, fanconvalue);
  //delay(22000);
 Serial.print("+D10-TEMPERATURE*"); Serial.print(seco);
  Serial.print("+D20-TEMPERATURE*"); Serial.print(humedo);

 Serial.print("+D30-HUMIDITY*");Serial.println(HR);
 timer1=millis(); 
}
  
}
