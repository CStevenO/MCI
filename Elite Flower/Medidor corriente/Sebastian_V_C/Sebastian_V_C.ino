// EmonLibrary examples openenergymonitor.org, Licence GNU GPL V3

#include "EmonLib.h"             // Include Emon Library
#include <SPI.h>
#include <SdFat.h>
SdFat SD;

File myFile;
EnergyMonitor emon1;             // Create an instance
EnergyMonitor emon2;             // Create an instance
EnergyMonitor emon3;             // Create an instance

float irms1;
float vrms1;
float realP1;
float irms2;
float vrms2;
float realP2;
float irms3;
float vrms3;
float realP3;
String dato;


void setup()
{  
  Serial.begin(9600);
  SD.begin(10);
  
  emon1.voltage(5, 234.26, 1.7);  // Voltage: input pin, calibration, phase_shift
//  emon1.current(2, 60);       // Current: input pin, calibration.
  emon1.current(2, 60);       // Current: input pin, calibration.

  emon2.voltage(6, 234.26, 1.7);  // Voltage: input pin, calibration, phase_shift
  emon2.current(3, 60);       // Current: input pin, calibration.

  emon3.voltage(7, 234.26, 1.7);  // Voltage: input pin, calibration, phase_shift
  emon3.current(4, 60);       // Current: input pin, calibration.

myFile = SD.open("DATOS.csv", FILE_WRITE);
      
        myFile.println("Irms1,Vrms1,PotenciaReal1,Irms2,Vrms2,PotenciaReal2,");
        myFile.close();

}

void loop()
{
  emon1.calcVI(20,2000);         // Calculate all. No.of half wavelengths (crossings), time-out
  emon2.calcVI(20,2000);         // Calculate all. No.of half wavelengths (crossings), time-out
  emon3.calcVI(20,2000);         // Calculate all. No.of half wavelengths (crossings), time-out
  //emon1.serialprint();           // Print out all variables (realpower, apparent power, Vrms, Irms, power factor)

    float realPower1       = emon1.realPower;        //extract Real Power into variable
  float realPower2       = emon2.realPower;        //extract Real Power into variable
    float realPower3       = emon3.realPower;        //extract Real Power into variable

//float realPowerT= realPower1 + realPower2;

   irms1 =emon1.Irms;
 vrms1 =emon1.Vrms;
 realP1 =emon1.realPower;

irms2 =emon2.Irms;
 vrms2 =emon2.Vrms;
 realP2 =emon2.realPower;

 irms3 =emon3.Irms;
 vrms3 =emon3.Vrms;
 realP3 =emon3.realPower;
 
  dato= String(irms1) + "," + String(vrms1) + "," + String(realP1)+ "," +String(irms2) + "," + String(vrms2) + "," + String(realP2) + "," +String(irms3) + "," + String(vrms3) + "," + String(realP3);
  Serial.print(emon1.Irms);
   Serial.print(",");
  Serial.print(emon1.Vrms);
  Serial.print(",");
  Serial.print(emon1.realPower);
   Serial.print(",");
   Serial.print(emon2.Irms);
   Serial.print(",");
  Serial.print(emon2.Vrms);
  Serial.print(",");
  Serial.print(emon2.realPower);
 Serial.print(",");
   Serial.print(emon3.Irms);
   Serial.print(",");
  Serial.print(emon3.Vrms);
  Serial.print(",");
  Serial.print(emon3.realPower);
 Serial.println(";");

//  Serial.print(emon2.Irms);
//   Serial.print(",");
//  Serial.print(emon2.Vrms);
//  Serial.print(",");
//  Serial.print(emon2.realPower);
//   Serial.print(",");
//   Serial.print(realPowerT);
//   Serial.println(";");


   myFile=SD.open("DATOS.csv",FILE_WRITE);
   myFile.println(dato);
   myFile.close();
  
//  float supplyVoltage   = emon1.Vrms;             //extract Vrms into Variable
//  float Irms            = emon1.Irms;             //extract Irms into Variable

 delay(30000);
 //delay(500);
}
