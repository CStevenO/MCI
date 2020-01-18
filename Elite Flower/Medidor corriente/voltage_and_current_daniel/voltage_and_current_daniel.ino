//#define CLIENT_ID       "UnoMQTT"
//#include <UIPEthernet.h>
//#include "PubSubClient.h"
//uint8_t mac[6] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05};
//#define INTERVAL        5000
//
//EthernetClient ethClient;
//PubSubClient mqttClient;


#include "EmonLib.h"             // Include Emon Library
EnergyMonitor emon1;             // Create an instance
EnergyMonitor emon2;             // Create an instance
EnergyMonitor emon3;             // Create an instance
//
//double potenciaSomatoria1 = 0;
//double potenciaSomatoria2 = 0;
//double potenciaSomatoria3 = 0;
float tiempo = 0;

unsigned long milis1;
unsigned long milis2;
int dMilis;
long previousMillis;
float total = 0;


void setup()
{
  //Ethernet.begin(mac);

  //emon1.voltage(7, 108.6, 1.7);  // Voltage: input pin, calibration, phase_shift
  emon1.current(4, 61);      // Current: input pin, calibration.

  //emon2.voltage(6, 104.8, 1.7);  // Voltage: input pin, calibration, phase_shift
  emon2.current(3, 60.2);      // Current: input pin, calibration.
  //
  //emon3.voltage(5, 105, 1.7);  // Voltage: input pin, calibration, phase_shift
  emon3.current(2, 59.4);      // Current: input pin, calibration.
  //
  //  mqttClient.setClient(ethClient);
  //  mqttClient.setServer("192.168.0.3", 1883); //for using local broker
  previousMillis = millis();
  Serial.begin(9600);
}

void loop()
{
  //
  emon1.calcVI(20, 2000);        // Calculate all. No.of half wavelengths (crossings), time-out
  emon2.calcVI(20, 2000);        // Calculate all. No.of half wavelengths (crossings), time-out
  emon3.calcVI(20, 2000);       // Calculate all. No.of half wavelengths (crossings), time-out
  //
  //  //
  //  float Vrms1   = emon1.Vrms;             //extract Vrms into Variable
  //  float Vrms2   = emon2.Vrms;             //extract Vrms into Variable
  //  float Vrms3   = emon3.Vrms;             //extract Vrms into Variable
  //  //
    float Irms1            = emon1.Irms;             //extract Irms into Variable
    float Irms2            = emon2.Irms;             //extract Irms into Variable
    float Irms3            = emon3.Irms;             //extract Irms into Variable
  //  //
  //  float fp1     = emon1.powerFactor;
  //  float fp2     = emon2.powerFactor;
  //  float fp3     = emon3.powerFactor;
  //  //
  float Pa1 = emon1.realPower;
  float Pa2 = emon2.realPower;
  float Pa3 = emon2.realPower;
  //
  milis2 = millis();
  dMilis = milis2 - milis1;
  total = total + (Pa1 * dMilis) / 3600000;
  total = total + (Pa2 * dMilis) / 3600000;
  total = total + (Pa3 * dMilis) / 3600000;
  milis1 = millis();
  //
  //  //
  Serial.print("I-1: "); Serial.print(Irms1);  Serial.print("   ");
  Serial.print("I-2: "); Serial.print(Irms2);  Serial.print("   ");
  Serial.print("I-3: "); Serial.println(Irms3);
  //Serial.print(" ---- ");
  //  //
  //  //    Serial.print("V-1: "); Serial.print(Vrms1);  Serial.print("    ");
  //  //    Serial.print("V-2: "); Serial.print(Vrms2); Serial.print("    ");
  //  //    Serial.print("V-3: "); Serial.println(Vrms3);
  //  //
  //  //  Serial.print(" ---- ");
  //  //  Serial.print("FP-1: "); Serial.print(fp1);  Serial.print("    ");
  //  //  Serial.print("FP-2: "); Serial.println(fp2);
  //  tiempo = float(millis()) / float(3600000);
  //
  //
  //  if (millis() - previousMillis > INTERVAL) {
  //    if (mqttClient.connect(CLIENT_ID)) {
  //      String msg = String(tiempo);
  //      Serial.println(tiempo);
  //      mqttClient.publish("Consumo", msg.c_str());
  //    }



  //    previousMillis = millis();
  //  }
  //  mqttClient.loop();
  //  ////
  //  float total = potenciaSomatoria1 + potenciaSomatoria2 + potenciaSomatoria3;
  //  //Serial.print("Consumo: "); Serial.print(total); Serial.print("   Tiempo Trans: "); Serial.print(tiempo, 3); Serial.println(" Horas");
  //
}
