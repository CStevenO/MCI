//float fatt = (3.3/1024)*100; //converte da Volt a Temperatura
//int PinTs = 0; // PinAnolog0 lettura bulbo secco
//int PinTw = 1; // PinAnalog1 lettura bulbo umido

#include <OneWire.h>
#include <DallasTemperature.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x3F, 16, 2);
#define imprimir(cadena){lcd.print(cadena);}

const int pinDatosDQ = 4;

OneWire oneWireObjeto(pinDatosDQ);
DallasTemperature sensorDS18B20(&oneWireObjeto);

// vedi wikipedia al link indicato sopra
float base = 10.0; // base log.
float a = 7.5;     // wikipedia
float b = 237.7;   // wikipedia
float c = 6.11;    //wikipedia
float Pr = 1026; //pressione atmosferica
// *********************************************************
//pressione di vapore acqueo saturo alla temperatura ( Ts o Tw)
// vedi wikipedia alink indicato
float calcoloPressione(float temp)
{
 return c * pow(base, (a * temp) / (b + temp));  
}
//costante strumentale Psicrometro da formula Sprung
// coefficente di Ferrel ( 0.00066*(1+0.00155*Tw)
float correzione(float Tw, float Ts)
 {
  return 0.00066 * (1 + 0.00155* Tw) * Pr * (Ts - Tw);
  }

//Calcola il valore pressione di vapore acqueo saturo alla temperatura ( Ts o Tw) 
float calcolaUmidita(float Ts, float Tw)
{
  float Es = calcoloPressione(Ts); // pressione vapor saturo con Ts
  float Ew = calcoloPressione(Tw); // pressione vapor saturo con Tw
 
  float correzioneSprung = correzione(Tw, Ts); 

  float e = Ew - correzioneSprung; // Formula di Sprung
  float UmiditaRelativa = e / Es * 100;// calcola umidita Relativa
  
  return UmiditaRelativa;// ritorna l'umidità relativa
                         // alle due temperature rilevate
                         // dal sensore LM35 secco
                         // e dal sensore LM35 umido
}

void setup()
{
//analogReference(EXTERNAL); // in questa versione si porta sul pin AREF 
                           // i 3,3V prelavati da Arduino
//Serial.begin(9600);   //attiva la porta seriale
sensorDS18B20.begin(); 
lcd.init();
lcd.backlight();
lcd.clear();

}

void loop()
{
  //lettura  sensori
    sensorDS18B20.requestTemperatures();
//   int tempTs = analogRead(PinTs);// legge bulbo secco
    float Ts = sensorDS18B20.getTempCByIndex(1);
    
//   int tempTw = analogRead(PinTw);// legge bulbo umido
   float Tw = sensorDS18B20.getTempCByIndex(0);

 
  double UR = calcolaUmidita(Ts, Tw); // calcola UR umidita relativa


  lcd.setCursor(0, 0); 
  imprimir("H"); lcd.print(UR, 1); imprimir("%");
  imprimir("   Ts"); lcd.print(Ts, 1); imprimir((char)223); imprimir("C");
  lcd.setCursor(0, 1); 
  imprimir("   Th"); lcd.print(Tw, 1); imprimir((char)223); imprimir("C");

  // visualizza sul monitor i valori rilevati e calcolati 
  
//  Serial.print("TempSecco = ");
//  Serial.print(Ts);
//  Serial.println();
//  Serial.print("TempUmido = ");
//  Serial.print(Tw);
//  Serial.println();
//
//  Serial.print("Umidità relativa = ");
//  Serial.print(UR);
//  Serial.println();
//  
//  Serial.print("*************");
//  Serial.println();
  
  delay(2000);// attesa per altra lettura
} 
