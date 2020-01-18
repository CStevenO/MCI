
#include <AltSoftSerial.h>
//
AltSoftSerial altSerial;

void setup() {
  Serial.begin(9600);
  // while (!Serial) ; // wait for Arduino Serial Monitor to open
  //Serial.println("AltSoftSerial Test Begin");
  altSerial.begin(57600);
  //altSerial.println("Hello World");
}

void loop() {


  //  if (Serial.available()) {
  //    c = Serial.read();
  //    Serial.print(c);
  //  }

//  if (altSerial.available()) {
for(int i=0;i>100000;i++)
   { 
int    c=i;
//c = Serial.read();
    altSerial.print(c);
    delay(2000);
  }
  
}
